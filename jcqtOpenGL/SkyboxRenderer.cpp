#include "SkyboxRenderer.h"
#include "Bitmap.h"
#include "UtilsCubemap.h"

#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>

#include <QFile>

#include <glm/gtx/texture.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "../extern/stb/src/include/stb/stb_image.h"
#include "../extern/gli/src/gli/gli/gli.hpp"
#include "../extern/gli/src/gli/gli/texture2d.hpp"
#include "../extern/gli/src/gli/gli/load_ktx.hpp"

namespace jcqt
{
	static QByteArray getFileData ( const char* filename )
	{
		QFile f ( filename );

		QByteArray data;

		if ( !f.open ( QIODeviceBase::ReadOnly ) )
		{
			qWarning () << "Failed to open file " << filename << ". Cannot return file data." << Qt::endl;
			return data;
		}

		data = f.readAll ();
		f.close ();
		return data;
	}

	SkyboxRenderer::SkyboxRenderer ( const char* envMap, const char* envMapIrradiance )
		: m_dummyVAO ( 0 )
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		// load brdfLUT
		{
			int w, h, numMipmaps;

			QByteArray brdfLUTRaw = getFileData ( ":/textures/brdfLUT.ktx" );

			std::size_t sz = brdfLUTRaw.size ();

			gli::texture gliTex = gli::load_ktx ( brdfLUTRaw.constData (), sz );
			gli::gl GL ( gli::gl::PROFILE_KTX );
			gli::gl::format const format = GL.translate ( gliTex.format (), gliTex.swizzles () );
			glm::tvec3<GLsizei> extent ( gliTex.extent ( 0 ) );
			w = extent.x;
			h = extent.y;
			numMipmaps = glm::levels<2, int> ( glm::tvec2<int> ( w, h ) );

			m_brdfLUT.create ( QOpenGLTexture::Target2D );
			m_brdfLUT->create ();
			m_brdfLUT->setFormat ( ( QOpenGLTexture::TextureFormat ) format.Internal );
			m_brdfLUT->setMipLevels ( numMipmaps );
			m_brdfLUT->setSize ( w, h );
			m_brdfLUT->allocateStorage ( ( QOpenGLTexture::PixelFormat ) format.External, ( QOpenGLTexture::PixelType ) format.Type );
			m_brdfLUT->setData ( ( QOpenGLTexture::PixelFormat ) format.External, ( QOpenGLTexture::PixelType ) format.Type, gliTex.data ( 0, 0, 0 ) );
			m_brdfLUT->setMinificationFilter ( QOpenGLTexture::LinearMipMapLinear );
			m_brdfLUT->setMagnificationFilter ( QOpenGLTexture::Linear );
			m_brdfLUT->setMipMaxLevel ( numMipmaps - 1 );
			m_brdfLUT->setWrapMode ( QOpenGLTexture::Repeat );
			m_brdfLUT->setMaximumAnisotropy ( 16 );
		}

		// load environment cube map
		{
			int w, h, comp;

			QByteArray envMapRaw = getFileData ( ":/textures/immenstadter_horn_2k.hdr" );

			int byteSize = static_cast< int >( envMapRaw.size () );

			const stbi_uc* ptr = (stbi_uc *)envMapRaw.constData ();

			const float* img = stbi_loadf_from_memory ( ptr, byteSize, &w, &h, &comp, 3 );

			assert ( img );
			Bitmap in ( w, h, comp, eBitmapFormat::eBitmapFormat_FLOAT, img );
			const bool isEquirecatngular = w == 2 * h;
			Bitmap out = isEquirecatngular ? convertEquirectangularMapToVerticalCross ( in ) : in;
			stbi_image_free ( ( void* ) img );
			Bitmap cubemap = convertVerticalCrossToCubeMapFaces ( out );

			const int numMipmaps = glm::levels<2, int> ( glm::tvec2<int> ( cubemap.w_, cubemap.h_ ) );

			m_envMap.create ( QOpenGLTexture::TargetCubeMap );
			m_envMap->create ();
			m_envMap->setFormat ( QOpenGLTexture::RGB32F );
			m_envMap->setMipLevels ( numMipmaps );
			m_envMap->setSize ( cubemap.w_, cubemap.h_ );
			m_envMap->setWrapMode ( QOpenGLTexture::ClampToEdge );
			m_envMap->setMagnificationFilter ( QOpenGLTexture::Linear );
			m_envMap->setMinificationFilter ( QOpenGLTexture::LinearMipMapLinear );
			m_envMap->setMipMaxLevel ( numMipmaps - 1 );
			f->glEnable ( GL_TEXTURE_CUBE_MAP_SEAMLESS );
			m_envMap->allocateStorage ( QOpenGLTexture::RGB, QOpenGLTexture::Float32 );

			const quint8* data = cubemap.data_.constData ();
			const qsizetype offset = static_cast< qsizetype >( cubemap.w_ * cubemap.h_ * Bitmap::getBytesPerComponent ( cubemap.fmt_ ) );

			m_envMap->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapPositiveX, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 0 * offset ) );
			m_envMap->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapNegativeX, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 1 * offset ) );
			m_envMap->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapPositiveY, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 2 * offset ) );
			m_envMap->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapNegativeY, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 3 * offset ) );
			m_envMap->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapPositiveZ, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 4 * offset ) );
			m_envMap->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapNegativeZ, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 5 * offset ) );
		}

		// load environment cube map
		{
			int w, h, comp;

			QByteArray envMapIrrRaw = getFileData ( ":/textures/immenstadter_horn_2k_irradiance.hdr" );

			int byteSize = static_cast< int >( envMapIrrRaw.size () );

			const stbi_uc* ptr = ( stbi_uc* ) envMapIrrRaw.constData ();

			const float* img = stbi_loadf_from_memory ( ptr, byteSize, &w, &h, &comp, 3 );

			assert ( img );
			Bitmap in ( w, h, comp, eBitmapFormat::eBitmapFormat_FLOAT, img );
			const bool isEquirecatngular = w == 2 * h;
			Bitmap out = isEquirecatngular ? convertEquirectangularMapToVerticalCross ( in ) : in;
			stbi_image_free ( ( void* ) img );
			Bitmap cubemap = convertVerticalCrossToCubeMapFaces ( out );

			const int numMipmaps = glm::levels<2, int> ( glm::tvec2<int> ( cubemap.w_, cubemap.h_ ) );

			m_envMapIrradiance.create ( QOpenGLTexture::TargetCubeMap );
			m_envMapIrradiance->create ();
			m_envMapIrradiance->setFormat ( QOpenGLTexture::RGB32F );
			m_envMapIrradiance->setMipLevels ( numMipmaps );
			m_envMapIrradiance->setSize ( cubemap.w_, cubemap.h_ );
			m_envMapIrradiance->setWrapMode ( QOpenGLTexture::ClampToEdge );
			m_envMapIrradiance->setMagnificationFilter ( QOpenGLTexture::Linear );
			m_envMapIrradiance->setMinificationFilter ( QOpenGLTexture::LinearMipMapLinear );
			m_envMapIrradiance->setMipMaxLevel ( numMipmaps - 1 );
			f->glEnable ( GL_TEXTURE_CUBE_MAP_SEAMLESS );
			m_envMapIrradiance->allocateStorage ( QOpenGLTexture::RGB, QOpenGLTexture::Float32 );

			const quint8* data = cubemap.data_.constData ();
			const qsizetype offset = static_cast< qsizetype >( cubemap.w_ * cubemap.h_ * Bitmap::getBytesPerComponent ( cubemap.fmt_ ) );

			m_envMapIrradiance->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapPositiveX, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 0 * offset ) );
			m_envMapIrradiance->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapNegativeX, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 1 * offset ) );
			m_envMapIrradiance->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapPositiveY, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 2 * offset ) );
			m_envMapIrradiance->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapNegativeY, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 3 * offset ) );
			m_envMapIrradiance->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapPositiveZ, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 4 * offset ) );
			m_envMapIrradiance->setData ( 0, 0, 0, cubemap.w_, cubemap.h_, 1, 0, 0, QOpenGLTexture::CubeMapNegativeZ, 1, QOpenGLTexture::PixelFormat::RGB, QOpenGLTexture::Float32, ( const void* ) ( data + 5 * offset ) );
		}

		f->glCreateVertexArrays ( 1, &m_dummyVAO );

		const GLuint pbrTextures [] = { m_envMap->textureId (), m_envMapIrradiance->textureId (), m_brdfLUT->textureId () };
		f->glBindTextures ( kIdxTex_EnvMap, 3, pbrTextures );

		m_program.create (ctx);
		m_program->addShaderFromSourceFile ( QOpenGLShader::Vertex, ":/shaders/GL_cube.vert" );
		m_program->addShaderFromSourceFile ( QOpenGLShader::Fragment, ":/shaders/GL_cube.frag" );
		m_program->link ();
	}

	SkyboxRenderer::~SkyboxRenderer ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		f->glDeleteVertexArrays ( 1, &m_dummyVAO );

		m_program->release ();
		m_program.clear ();

		m_envMap->destroy ();
		m_envMap.clear ();

		m_envMapIrradiance->destroy ();
		m_envMapIrradiance.clear ();

		m_brdfLUT->destroy ();
		m_brdfLUT.clear ();
	}

	void SkyboxRenderer::draw () const
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		m_program->bind ();
		f->glBindTextureUnit ( kIdxTex_SamplerCube, m_envMap->textureId () );
		f->glDepthMask ( GL_FALSE );
		f->glBindVertexArray ( m_dummyVAO );
		f->glDrawArrays ( GL_TRIANGLES, 0, 36 );
		f->glDepthMask ( GL_TRUE );
	}
}
