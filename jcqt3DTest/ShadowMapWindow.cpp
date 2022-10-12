#include "ShadowMapWindow.h"

#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>

#include <QTime>

#include <QKeyEvent>
#include <QMouseEvent>
#include <QWheelEvent>

ShadowMapWindow::ShadowMapWindow ( QOpenGLContext* shareContext, QOpenGLWindow::UpdateBehavior updateBehavior, QWindow* parent )
	: QOpenGLWindow ( shareContext, updateBehavior, parent )
	, m_freezeCullingView ( false )
	, m_enableGPUCulling ( false )
	, m_drawMeshes(true)
	, m_drawGrid(true)
	, m_perFrameDataBuffer ( 0 )
	, m_boundingBoxesBuffer ( 0 )
	, m_numVisibleMeshesBuffer ( 0 )
	, m_numVisibleMeshesPtr ( nullptr )
	, m_camera(m_positioner)
	, m_timeStampMS(QTime::currentTime().msecsSinceStartOfDay())
{
	m_mouseState.pos = vec2 ( 0.0f );
	m_mouseState.pressedLeft = false;

	m_positioner.lookAt ( vec3 ( -10.0f, 3.0f, 3.0f ), vec3 ( 0.0f, 0.0f, -1.0f ), vec3 ( 0.0f, 1.0f, 0.0f ) );
	m_cullingView = m_camera.getViewMatrix ();
	
	QSize sz = size ();
	const float aspectRatio = sz.width () / ( float ) sz.height ();
	const float fovDegs = 45.0f;
	const float zNear = 0.1f;
	const float zFar = 1000.0f;
	
	m_perFrameData.view = m_camera.getViewMatrix ();
	m_perFrameData.proj = glm::perspective ( glm::radians ( fovDegs ), aspectRatio, zNear, zFar );
	m_perFrameData.light = mat4 ( 1.0f );
	m_perFrameData.cameraPos = vec4(m_camera.getPosition (), 1.0f);
	m_perFrameData.light = mat4 ( 0.0f ); // unused for right now
	m_perFrameData.numShapesToCull = 0;

	jcqt::getFrustumPlanes ( m_perFrameData.proj * m_cullingView, m_perFrameData.frustumPlanes );
	jcqt::getFrustumCorners ( m_perFrameData.proj * m_cullingView, m_perFrameData.frustumCorners );
}

ShadowMapWindow::ShadowMapWindow(QOpenGLWindow::UpdateBehavior updateBehavior, QWindow* parent)
	: QOpenGLWindow(updateBehavior, parent)
	, m_freezeCullingView ( false )
	, m_enableGPUCulling ( false )
	, m_perFrameDataBuffer ( 0 )
	, m_boundingBoxesBuffer ( 0 )
	, m_numVisibleMeshesBuffer ( 0 )
	, m_numVisibleMeshesPtr ( nullptr )
	, m_camera ( m_positioner )
{
	m_mouseState.pos = vec2 ( 0.0f );
	m_mouseState.pressedLeft = false;

	m_positioner.lookAt ( vec3 ( -10.0f, 3.0f, 3.0f ), vec3 ( 0.0f, 0.0f, -1.0f ), vec3 ( 0.0f, 1.0f, 0.0f ) );
	m_cullingView = m_camera.getViewMatrix ();

	QSize sz = size ();
	const float aspectRatio = sz.width () / ( float ) sz.height ();
	const float fovDegs = 45.0f;
	const float zNear = 0.1f;
	const float zFar = 1000.0f;

	m_perFrameData.view = m_camera.getViewMatrix ();
	m_perFrameData.proj = glm::perspective ( glm::radians ( fovDegs ), aspectRatio, zNear, zFar );
	m_perFrameData.light = mat4 ( 1.0f );
	m_perFrameData.cameraPos = vec4 ( m_camera.getPosition (), 1.0f );
	m_perFrameData.light = mat4 ( 0.0f ); // unused for right now
	m_perFrameData.numShapesToCull = 0;

	jcqt::getFrustumPlanes ( m_perFrameData.proj * m_cullingView, m_perFrameData.frustumPlanes );
	jcqt::getFrustumCorners ( m_perFrameData.proj * m_cullingView, m_perFrameData.frustumCorners );
}

ShadowMapWindow::~ShadowMapWindow ()
{
	makeCurrent ();
	teardownTimeMonitor ();
	teardownGL ();
	teardownDebugLogger ();
}

void ShadowMapWindow::initShaders ()
{
	QOpenGLContext* ctx = context ();

	m_gridProgram.create ( ctx );
	m_gridProgram->addShaderFromSourceFile ( QOpenGLShader::Vertex, ":/shaders/GL_grid.vert" );
	m_gridProgram->addShaderFromSourceFile ( QOpenGLShader::Fragment, ":/shaders/GL_grid.frag" );
	m_gridProgram->link ();

	m_sceneProgram.create ( ctx );
	m_sceneProgram->addShaderFromSourceFile ( QOpenGLShader::Vertex, ":/shaders/GL_scene_IBL.vert" );
	m_sceneProgram->addShaderFromSourceFile ( QOpenGLShader::Fragment, ":/shaders/GL_scene_IBL.frag" );
	m_sceneProgram->link ();

	m_cullProgram.create ( ctx );
	m_cullProgram->addShaderFromSourceFile ( QOpenGLShader::Compute, ":/shaders/GL_FrustumCulling.comp" );
	m_cullProgram->link ();
}

void ShadowMapWindow::initBuffers ()
{
	QOpenGLContext* ctx = context ();
	auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

	if ( !jcqt::g_extFunctionsInitialized )
	{
		jcqt::initExtFunctions ( ctx );
	}

	const GLuint kMaxNumObjects = 128 * 1024;
	
	const GLsizeiptr kUniformBufferSize = sizeof ( m_perFrameData );
	const GLsizeiptr kBoundingBoxesBufferSize = sizeof ( jcqt::BoundingBox ) * kMaxNumObjects;

	const GLuint kBufferIndex_PerFrameUniforms = jcqt::kIdxBind_SSBOModelMatrices + 1;
	const GLuint kBufferIndex_BoundingBoxes = kBufferIndex_PerFrameUniforms + 1;
	const GLuint kBufferIndex_DrawCommands = kBufferIndex_BoundingBoxes + 1;
	const GLuint kBufferIndex_NumVisibleMeshes = kBufferIndex_DrawCommands + 1;

	f->glCreateBuffers ( 1, &m_perFrameDataBuffer );
	f->glNamedBufferStorage ( m_perFrameDataBuffer, kUniformBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT );
	f->glBindBufferRange ( GL_UNIFORM_BUFFER, kBufferIndex_PerFrameUniforms, m_perFrameDataBuffer, 0, kUniformBufferSize );

	f->glCreateBuffers ( 1, &m_boundingBoxesBuffer );
	f->glNamedBufferStorage ( m_boundingBoxesBuffer, kBoundingBoxesBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT );

	f->glCreateBuffers ( 1, &m_numVisibleMeshesBuffer );
	f->glNamedBufferStorage (m_numVisibleMeshesBuffer, sizeof ( quint32 ), nullptr, GL_MAP_READ_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT );
	m_numVisibleMeshesPtr = ( quint32* ) f->glMapNamedBuffer ( m_numVisibleMeshesBuffer, GL_READ_WRITE );
	assert ( m_numVisibleMeshesPtr );
}

void ShadowMapWindow::loadScene ()
{
	m_sceneData.create ( ":/meshes/bistro_all.meshes", ":/scenes/bistro_all.scene", ":/materials/bistro_all.materials" );
	m_indirectMesh.create ( *(m_sceneData.get()) );
//	m_mesh.create ( *( m_sceneData.get () ));

	m_skyboxRenderer.create ();
	m_lineCanvas.create ();
}

void ShadowMapWindow::initDebugLogger ()
{
	QOpenGLContext* ctx = context ();

	if ( !ctx->hasExtension ( QByteArrayLiteral ( "GL_KHR_debug" ) ) )
	{
		qWarning () << "GL_KHR_debug extension not present. Cannot initialize debug logger" << Qt::endl;
		return;
	}

	m_debugLogger.create ( this );
	m_debugLogger->initialize ();
	connect ( m_debugLogger.data (), &QOpenGLDebugLogger::messageLogged, this, &ShadowMapWindow::handleLoggedMessage );
	m_debugLogger->startLogging ();
	m_debugLogger->enableMessages ();
}

void ShadowMapWindow::initTimeMonitor ()
{
	m_timeMonitor.create ( this );

	// TODO: setup timer queries
}

void ShadowMapWindow::teardownGL ()
{
	teardownScene ();
	teardownBuffers ();
	teardownShaders ();
}

void ShadowMapWindow::teardownBuffers ()
{
	makeCurrent ();

	QOpenGLContext* ctx = context ();

	auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

	f->glUnmapNamedBuffer ( m_numVisibleMeshesBuffer );

	m_numVisibleMeshesPtr = nullptr;

	f->glDeleteBuffers ( 1, &m_perFrameDataBuffer );
	f->glDeleteBuffers ( 1, &m_boundingBoxesBuffer );
	f->glDeleteBuffers ( 1, &m_numVisibleMeshesBuffer );
}

void ShadowMapWindow::teardownScene ()
{
	m_skyboxRenderer.clear ();
	m_lineCanvas.clear ();
//	m_mesh.clear ();
	m_indirectMesh.clear ();
	m_sceneData.clear ();
}

void ShadowMapWindow::teardownShaders ()
{
	m_gridProgram.clear ();
	m_cullProgram.clear ();
	m_sceneProgram.clear ();
}

void ShadowMapWindow::teardownTimeMonitor ()
{
	m_timeMonitor.clear ();
}

void ShadowMapWindow::teardownDebugLogger ()
{
	m_debugLogger->stopLogging ();

	disconnect ( m_debugLogger.data (), &QOpenGLDebugLogger::messageLogged, this, &ShadowMapWindow::handleLoggedMessage );
	
	m_debugLogger.clear ();
}

void ShadowMapWindow::handleLoggedMessage(const QOpenGLDebugMessage& msg) 
{
	// TODO: implement

	qDebug () << msg << Qt::endl;
}

void ShadowMapWindow::initializeGL ()
{
	QOpenGLContext* ctx = context ();
	auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

	m_positioner.maxSpeed_ = 1.0f;	

	initDebugLogger ();
	initTimeMonitor ();
	initShaders ();
	initBuffers ();
	loadScene ();

	f->glClearColor ( 1.0f, 1.0f, 1.0f, 1.0f );
	f->glBlendFunc ( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
	f->glEnable ( GL_DEPTH_TEST );

	QList<BoundingBox> reorderedBoxes;
	reorderedBoxes.reserve ( m_sceneData->shapes_.size () );

	// pretransformed bounding boxes to world space
	for ( const DrawData& dd : m_sceneData->shapes_ )
	{
		const mat4 model = m_sceneData->scene_.globalTransforms_ [ dd.transformIndex ];
		reorderedBoxes.push_back ( m_sceneData->meshData_.boxes_ [ dd.meshIndex ] );
		reorderedBoxes.back ().transform ( model );
	}

	f->glNamedBufferSubData ( m_boundingBoxesBuffer, 0, static_cast< GLsizei >( reorderedBoxes.size () * sizeof ( BoundingBox ) ), reorderedBoxes.constData () );
}

void ShadowMapWindow::resizeGL(int w, int h) 
{
	const float aspectRatio = w / ( float ) h;
	m_perFrameData.proj = glm::perspective ( 45.0f, aspectRatio, 0.1f, 1000.f );
}

void ShadowMapWindow::paintGL ()
{
	QOpenGLContext* ctx = context ();
	auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

	qint32 currentTime = QTime::currentTime ().msecsSinceStartOfDay ();

	float deltaSeconds = getDeltaSeconds ( currentTime );

	m_timeStampMS = currentTime;

	m_positioner.update ( deltaSeconds, m_mouseState.pos, m_mouseState.pressedLeft );

	const qint32 w = width ();
	const qint32 h = height ();
	const float aspectRatio = w / ( float ) h;

	f->glViewport ( 0, 0, w, h );
	f->glClearNamedFramebufferfv ( 0, GL_COLOR, 0, glm::value_ptr ( vec4 ( 0.0f, 0.0f, 0.0f, 1.0f ) ) );
	f->glClearNamedFramebufferfi ( 0, GL_DEPTH_STENCIL, 1.0f, 0 );

	if ( !m_freezeCullingView )
		m_cullingView = m_camera.getViewMatrix ();

	const mat4 proj = glm::perspective ( 45.0f, aspectRatio, 0.1f, 1000.0f );
	const mat4 view = m_camera.getViewMatrix ();

	m_perFrameData.view = view;
	m_perFrameData.proj = proj;
	m_perFrameData.light = mat4 ( 0.0f );
	m_perFrameData.cameraPos = vec4 ( m_camera.getPosition (), 1.0f );
	m_perFrameData.numShapesToCull = m_enableGPUCulling ? ( quint32 ) m_sceneData->shapes_.size () : 0u;

	jcqt::getFrustumPlanes ( proj * m_cullingView, m_perFrameData.frustumPlanes );
	jcqt::getFrustumCorners ( proj * m_cullingView, m_perFrameData.frustumCorners );

	const GLsizeiptr kUniformBufferSize = sizeof ( m_perFrameData );
	
	const GLuint kBufferIndex_PerFrameUniforms = jcqt::kIdxBind_SSBOModelMatrices + 1;
	const GLuint kBufferIndex_BoundingBoxes = kBufferIndex_PerFrameUniforms + 1;
	const GLuint kBufferIndex_DrawCommands = kBufferIndex_BoundingBoxes + 1;
	const GLuint kBufferIndex_NumVisibleMeshes = kBufferIndex_DrawCommands + 1;

	f->glNamedBufferSubData ( m_perFrameDataBuffer, 0, kUniformBufferSize, &m_perFrameData );

	// cull
	*m_numVisibleMeshesPtr = 0;
	m_cullProgram->bind ();
	f->glMemoryBarrier ( GL_BUFFER_UPDATE_BARRIER_BIT );
	f->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kBufferIndex_BoundingBoxes, m_boundingBoxesBuffer );
	f->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kBufferIndex_DrawCommands, m_indirectMesh->m_indirectBuffer.handle () );
	f->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kBufferIndex_NumVisibleMeshes, m_numVisibleMeshesBuffer );
	f->glDispatchCompute ( 1 + ( GLuint ) m_sceneData->shapes_.size () / 64, 1, 1 );
	f->glMemoryBarrier ( GL_COMMAND_BARRIER_BIT | GL_SHADER_STORAGE_BARRIER_BIT | GL_CLIENT_MAPPED_BUFFER_BARRIER_BIT );
	
	const GLsync fence = f->glFenceSync ( GL_SYNC_GPU_COMMANDS_COMPLETE, 0 );

	// 1. render scene
	m_skyboxRenderer->draw ();
	f->glDisable ( GL_BLEND );
	f->glEnable ( GL_DEPTH_TEST );
	// 1.1 Bistro
	if ( m_drawMeshes )
	{
		m_sceneProgram->bind ();
		m_indirectMesh->draw ( m_sceneData->shapes_.size () );
	}

	// 1.2 Grid
	f->glEnable ( GL_BLEND );

	if ( m_drawGrid )
	{
		m_gridProgram->bind ();
		f->glDrawArraysInstancedBaseInstance ( GL_TRIANGLES, 0, 6, 1, 0 );
	}

	if ( m_freezeCullingView )
	{
		renderCameraFrustum ( *( m_lineCanvas.get () ), m_cullingView, proj, vec4 ( 1.f, 1.f, 0.f, 1.f ), 100 );
	}

	m_lineCanvas->flush ();

	// wait for compute shader results to become visible
	for ( ;;)
	{
		const GLenum res = f->glClientWaitSync ( fence, GL_SYNC_FLUSH_COMMANDS_BIT, 1000 );
		if ( res == GL_ALREADY_SIGNALED || res == GL_CONDITION_SATISFIED ) break;
	}

	f->glDeleteSync ( fence );
}

void ShadowMapWindow::keyPressEvent ( QKeyEvent* e )
{
	switch ( e->key() )
	{
	case Qt::Key_Escape:
		break;
	case Qt::Key_W:
		m_positioner.movement_.forward_ = true;
		break;
	case Qt::Key_S:
		m_positioner.movement_.backward_ = true;
		break;
	case Qt::Key_A:
		m_positioner.movement_.left_ = true;
		break;
	case Qt::Key_D:
		m_positioner.movement_.right_ = true;
		break;
	case Qt::Key_1:
		m_positioner.movement_.up_ = true;
		break;
	case Qt::Key_2:
		m_positioner.movement_.down_ = true;
		break;
	case Qt::Key_Shift:
		m_positioner.movement_.fastSpeed_ = true;
		break;
	case Qt::Key_Space:
		m_positioner.setUpVector ( vec3 ( 0.f, 1.f, 0.f ) );
		break;
	case Qt::Key_P:
		m_freezeCullingView = !m_freezeCullingView;
		break;
	default:
		break;
	}

	e->accept ();	
}

void ShadowMapWindow::keyReleaseEvent ( QKeyEvent* e )
{
	switch ( e->key () )
	{
	case Qt::Key_Escape:
		close ();
		break;
	case Qt::Key_W:
		m_positioner.movement_.forward_ = false;
		break;
	case Qt::Key_S:
		m_positioner.movement_.backward_ = false;
		break;
	case Qt::Key_A:
		m_positioner.movement_.left_ = false;
		break;
	case Qt::Key_D:
		m_positioner.movement_.right_ = false;
		break;
	case Qt::Key_1:
		m_positioner.movement_.up_ = false;
		break;
	case Qt::Key_2:
		m_positioner.movement_.down_ = false;
		break;
	case Qt::Key_Shift:
		m_positioner.movement_.fastSpeed_ = false;
		break;	
	default:
		break;
	}

	e->accept ();
}

void ShadowMapWindow::mouseDoubleClickEvent ( QMouseEvent* e )
{
	e->accept ();
}

void ShadowMapWindow::mouseMoveEvent ( QMouseEvent* e )
{
	if ( m_mouseState.pressedLeft )
	{
		QPointF p = e->globalPosition ();
		QSize sz = size ();
		m_mouseState.pos.x = static_cast< float >( p.x () / ( float ) sz.width () );
		m_mouseState.pos.y = static_cast< float >( p.y () / ( float ) sz.height () );
	}

	update ();
}

void ShadowMapWindow::mousePressEvent ( QMouseEvent* e )
{
	if ( e->button () == Qt::LeftButton )
	{
		QPointF p = e->globalPosition ();
		QSize sz = size ();		
		m_mouseState.pos.x = static_cast< float >( p.x () / ( float ) sz.width () );
		m_mouseState.pos.y = static_cast< float >( p.y () / ( float ) sz.height () );
		m_mouseState.pressedLeft = true;
	}
	
	e->accept ();
}

void ShadowMapWindow::mouseReleaseEvent ( QMouseEvent* e )
{
	if ( e->button () == Qt::LeftButton )
	{
		QPointF p = e->globalPosition ();
		QSize sz = size ();
		m_mouseState.pos.x = static_cast< float >( p.x () / ( float ) sz.width () );
		m_mouseState.pos.y = static_cast< float >( p.y () / ( float ) sz.height () );
		m_mouseState.pressedLeft = false;
	}

	e->accept ();
}

void ShadowMapWindow::wheelEvent ( QWheelEvent* e )
{
	e->accept ();
}

bool ShadowMapWindow::event ( QEvent* e )
{
	switch ( e->type() )
	{
	case QEvent::KeyPress:
	//	QKeyEvent* ke = static_cast< QKeyEvent* >( e );
		keyPressEvent ( static_cast< QKeyEvent* >( e ) );
		break;
	case QEvent::KeyRelease:
//		QKeyEvent* ke = static_cast< QKeyEvent* >( e );
		keyReleaseEvent ( static_cast< QKeyEvent* >( e ) );
		break;
	case QEvent::MouseButtonPress:
//		QMouseEvent* me = static_cast< QMouseEvent* >( e );
		mousePressEvent ( static_cast< QMouseEvent* >( e ) );
		break;
	case QEvent::MouseButtonRelease:
//		QMouseEvent* me = static_cast< QMouseEvent* >( e );
		mouseReleaseEvent ( static_cast< QMouseEvent* >( e ) );
		break;
	case QEvent::MouseMove:
//		QMouseEvent* me = static_cast< QMouseEvent* >( e );
		mouseMoveEvent ( static_cast< QMouseEvent* >( e ) );
		break;
	case QEvent::Wheel:
//		QWheelEvent* we = static_cast< QWheelEvent* >( e );
		wheelEvent ( static_cast< QWheelEvent* >( e ) );
		break;
	case QEvent::MouseButtonDblClick:
//		QMouseEvent* me = static_cast< QMouseEvent* >( e );
		mouseDoubleClickEvent ( static_cast< QMouseEvent* >( e ) );
		break;
	case QEvent::Expose:
		exposeEvent ( static_cast< QExposeEvent* >( e ) );
		break;
	default:
		break;
	}

	return true;
}

void ShadowMapWindow::exposeEvent ( QExposeEvent* e )
{
	if ( isExposed () )
		update ();
}

float ShadowMapWindow::getDeltaSeconds ( qint32 currentTimeMS ) const
{
	return static_cast< float >( currentTimeMS - m_timeStampMS ) * 0.001f;
}
