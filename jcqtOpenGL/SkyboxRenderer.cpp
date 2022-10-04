#include "SkyboxRenderer.h"

#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>



namespace jcqt
{
	SkyboxRenderer::SkyboxRenderer ( const QString& envMap, const QString& envMapIrradiance )
		: m_dummyVAO ( 0 )
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		QImage brdfLUTImg ( QString ( ":/textures/brdfLUT.ktx" ) );
		QImage envMapImg ( envMap );
		QImage envMapIrradianceImg ( envMapIrradiance );

		m_brdfLUT.create ( QOpenGLTexture::Target2D );
		m_brdfLUT->create ();
		m_brdfLUT->setMagnificationFilter ( QOpenGLTexture::Linear );
		m_brdfLUT->setMinificationFilter ( QOpenGLTexture::Linear );
		m_brdfLUT->setWrapMode ( QOpenGLTexture::DirectionS, QOpenGLTexture::Repeat );
		m_brdfLUT->setWrapMode ( QOpenGLTexture::DirectionT, QOpenGLTexture::Repeat );
		m_brdfLUT->setData ( brdfLUTImg.mirrored () );

		m_envMap.create ( QOpenGLTexture::TargetCubeMap );
		m_envMap->create ();
	}
}
