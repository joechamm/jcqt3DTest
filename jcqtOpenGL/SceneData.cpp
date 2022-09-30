#include "SceneData.h"

#include <QOpenGLTexture>
#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>
#include <qopenglfunctions.h>

//typedef GLuint64 (__stdcall PFN)

namespace jcqt
{
	static uint64_t getTextureHandleBindless ( uint64_t idx, const QList<QOpenGLTexture>& textures )
	{
		if ( idx == INVALID_TEXTURE ) return 0;

		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		
		GLuint handle = textures [ idx ].textureId ();

		if ( !ctx->hasExtension ( "GL_ARB_bindless_texture" ) )
		{
			qWarning ( "GL_ARB_bindless_texture extension not present. Cannot get Texture Handle Bindless.\nExiting...\n" );
			exit ( EXIT_FAILURE );
		}
		
		QFunctionPointer glGetTextureHandleARB = ctx->getProcAddress ( "glGetTextureHandleARB" );
		QFunctionPointer glMakeTextureHandleResidentARB = ctx->getProcAddress ( "glMakeTextureHandleResidentARB" );
		GLuint64 handleBindless = reinterpret_cast< PFNGLGETTEXTUREHANDLEARBPROC >( glGetTextureHandleARB )( handle );
		reinterpret_cast< PFNGLMAKETEXTUREHANDLERESIDENTARBPROC >( glMakeTextureHandleResidentARB )( handleBindless );
		return handleBindless;
	}

	SceneData::SceneData (
		const char* meshFile,
		const char* sceneFile,
		const char* materialFile )
	{
		header_ = loadMeshData ( meshFile, meshData_ );
		loadScene ( sceneFile );

		QByteArrayList textureFiles;
		
		loadMaterials ( materialFile, materials_, textureFiles );

		for ( const auto& f : textureFiles )
		{
			allMaterialTextures_.emplace_back ( QOpenGLTexture ( QImage ( f ) ) );
		}

		for ( auto& mtl : materials_ )
		{
			mtl.ambientOcclusionMap_ = getTextureHandleBindless ( mtl.ambientOcclusionMap_, allMaterialTextures_ );
			mtl.emissiveMap_ = getTextureHandleBindless ( mtl.emissiveMap_, allMaterialTextures_ );
			mtl.albedoMap_ = getTextureHandleBindless ( mtl.albedoMap_, allMaterialTextures_ );
			mtl.metallicRoughnessMap_ = getTextureHandleBindless ( mtl.metallicRoughnessMap_, allMaterialTextures_ );
			mtl.normalMap_ = getTextureHandleBindless ( mtl.normalMap_, allMaterialTextures_ );
		}
	}

	void SceneData::loadScene ( const char* sceneFile )
	{
		jcqt::loadScene ( sceneFile, scene_ );

		// prepare draw data buffer
		QHashIterator<quint32, quint32> it ( scene_.meshes_ );
		while ( it.hasNext () )
		{
			it.next ();
			auto material = scene_.materialForNode_.find ( it.key () );
			if ( material != scene_.materialForNode_.end () )
			{
				shapes_.push_back ( DrawData {
					.meshIndex = it.value (),
					.materialIndex = material.value (),
					.LOD = 0,
					.indexOffset = meshData_.meshes_ [ it.value () ].indexOffset,
					.vertexOffset = meshData_.meshes_ [ it.value () ].vertexOffset,
					.transformIndex = it.key ()
					} );
			}
		}

		// force recalculation of all global transformations
		markAsChanged ( scene_, 0 );
		recalculateGlobalTransforms ( scene_ );
	}
}
