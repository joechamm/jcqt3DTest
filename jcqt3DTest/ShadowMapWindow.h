/*****************************************************************//**
 * \file   ShadowMapWindow.h
 * \licence MIT License

Copyright (c) 2022 Joseph Cunningham

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
 * \brief  
 * 
 * \author joechamm
 * \date   October 2022
 *********************************************************************/
#ifndef __SHADOW_MAP_WINDOW_H__
#define __SHADOW_MAP_WINDOW_H__

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>
#include <QOpenGLTimeMonitor>
#include <QOpenGLDebugLogger>

#include "../jcqtOpenGL/SceneDataLazy.h"
#include "../jcqtOpenGL/DrawMesh.h"
#include "../jcqtOpenGL/MeshIndirect.h"
#include "../jcqtOpenGL/SceneData.h"
#include "../jcqtOpenGL/Camera.h"
#include "../jcqtOpenGL/LineCanvas.h"
#include "../jcqtOpenGL/SkyboxRenderer.h"
#include "../jcqtOpenGL/jcqtopengl_extension_functions.h"

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>

using glm::mat4;
using glm::mat3;
using glm::mat2;
using glm::vec4;
using glm::vec3;
using glm::vec2;

using namespace jcqt;

class ShadowMapWindow : public QOpenGLWindow
{
	Q_OBJECT 
public:
	ShadowMapWindow ( QOpenGLContext* shareContext, QOpenGLWindow::UpdateBehavior updateBehavior = NoPartialUpdate, QWindow* parent = nullptr );
	ShadowMapWindow ( QOpenGLWindow::UpdateBehavior updateBehavior = NoPartialUpdate, QWindow* parent = nullptr );
	~ShadowMapWindow ();

public slots:
	void handleLoggedMessage ( const QOpenGLDebugMessage& msg );

protected:
	void initializeGL () override;
	void paintGL () override;
	void resizeGL (int w, int h) override;

	void keyPressEvent ( QKeyEvent* e ) override;
	void keyReleaseEvent ( QKeyEvent* e ) override;
	void mouseDoubleClickEvent ( QMouseEvent* ev ) override;
	void mouseMoveEvent ( QMouseEvent* ev ) override;
	void mousePressEvent ( QMouseEvent* ev ) override;
	void mouseReleaseEvent ( QMouseEvent* ev ) override;
	void wheelEvent ( QWheelEvent* ev ) override;

	bool event ( QEvent* event ) override;

	void exposeEvent ( QExposeEvent* event ) override;
private:

	void initShaders ();
	void initBuffers ();
	void loadScene ();

	void teardownBuffers ();
	void teardownShaders ();
	void teardownScene ();

	void teardownGL ();

	void initDebugLogger ();
	void initTimeMonitor ();

	void teardownDebugLogger ();
	void teardownTimeMonitor ();

	float getDeltaSeconds (qint32 currentTimeMS) const;

	struct PerFrameData
	{
		mat4 view;
		mat4 proj;
		mat4 light = mat4 ( 1.0f );
		vec4 cameraPos;
		vec4 frustumPlanes [ 6 ];
		vec4 frustumCorners [ 8 ];
		GLuint numShapesToCull;
	};

	struct MouseState
	{
		vec2 pos = vec2 ( 0.0f );
		bool pressedLeft = false;
	};


	qint32									m_timeStampMS;

	bool									m_freezeCullingView;
	bool									m_enableGPUCulling;
	bool									m_drawMeshes;
	bool									m_drawGrid;

	MouseState								m_mouseState;
	PerFrameData							m_perFrameData;

	mat4									m_cullingView;

	CameraPositioner_FirstPerson			m_positioner;
	Camera									m_camera;

	QSharedPointer<QOpenGLDebugLogger>		m_debugLogger;
	QSharedPointer<QOpenGLTimeMonitor>		m_timeMonitor;

	QSharedPointer<QOpenGLShaderProgram>	m_gridProgram;
	QSharedPointer<QOpenGLShaderProgram>	m_sceneProgram;
	QSharedPointer<QOpenGLShaderProgram>	m_cullProgram;

	QSharedPointer<SceneData>				m_sceneData;
//	QSharedPointer<DrawMesh>				m_mesh;
	QSharedPointer<MeshIndirect<SceneData>> m_indirectMesh;

	QSharedPointer<SkyboxRenderer>			m_skyboxRenderer;
	QSharedPointer<LineCanvas>				m_lineCanvas;

	GLuint									m_perFrameDataBuffer;
	GLuint									m_boundingBoxesBuffer;
	GLuint									m_numVisibleMeshesBuffer;

	volatile quint32*						m_numVisibleMeshesPtr = nullptr;
};

#endif // !__SHADOW_MAP_WINDOW_H__
