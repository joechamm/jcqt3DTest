#include "ShadowMapWindow.h"

#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>

ShadowMapWindow::ShadowMapWindow ( QOpenGLContext* shareContext, QOpenGLWindow::UpdateBehavior updateBehavior, QWindow* parent )
	: QOpenGLWindow ( shareContext, updateBehavior, parent )
	, m_freezeCullingView ( false )
	, m_enableGPUCulling ( false )
	, m_perFrameDataBuffer ( 0 )
	, m_boundingBoxesBuffer ( 0 )
	, m_numVisibleMeshesBuffer ( 0 )
	, m_numVisibleMeshesPtr ( nullptr )
	, m_camera(m_positioner)
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

void ShadowMapWindow::teardownGL ()
{
	teardownScene ();
	teardownBuffers ();
	teardownShaders ();
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
	m_mesh.create ( *( m_sceneData.get () ));
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
}

void ShadowMapWindow::initTimeMonitor ()
{
	m_timeMonitor.create ( this );

	// TODO: setup timer queries
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
