#include "SceneDataLazy.h"

#include "jcqtopengl_arb_extensions.h"

namespace jcqt
{
	static GLuint64 getTextureHandleBindless ( GLuint64 idx, const QList<QSharedPointer<QOpenGLTexture>>& textures )
	{
		if ( idx == INVALID_TEXTURE ) return 0;

		GLuint handle = textures [ idx ]->textureId ();

		GLuint64 handleBindless = glGetTextureHandleARB ( handle );
		glMakeTextureHandleResidentARB ( handleBindless );

		return handleBindless;
	}

	SceneDataLazy::SceneDataLazy ( const char* meshFile, const char* sceneFile, const char* materialFile )
	{
		threadPool_.setMaxThreadCount ( 4 );

		header_ = loadMeshData ( meshFile, meshData_ );
		loadScene ( sceneFile );
		loadMaterials ( materialFile, materialsLoaded_, textureFiles_ );

		// apply a dummy texture to everything
		foreach ( const QByteArray & f, textureFiles_ )
		{
			allMaterialTextures_.emplaceBack ( dummyTexture_ );
		}

		updateMaterials ();

		loadedFiles_.reserve ( textureFiles_.size () );
		
		qint32 idx = 0;

		QtConcurrent::blockingMap ( textureFiles_.constBegin (), textureFiles_.constEnd (), [this, &idx] ( const QByteArray& texFilename ) {
			QImage* pImg = new QImage ( texFilename );
			if ( pImg )
			{
				QMutexLocker locker ( &( this->loadedFilesMutex_ ) );
				this->loadedFiles_.emplaceBack ( LoadedImageData { .index_ = idx++, .image_ = pImg } );
			}
			} );

		//QtConcurrent::

		//// load images concurrently
		//QFuture<void> future = QtConcurrent::map ( textureFiles_, [this] ( int idx ) {
		//		QImage* pImg = new QImage ( this->textureFiles_ [ idx ] );
		//		if ( pImg )
		//		{
		//			QMutexLocker locker ( &( this->loadedFilesMutex_ ) );
		//			this->loadedFiles_.emplaceBack ( LoadedImageData { .index_ = idx, .image_ = pImg } );
		//		}			
		//	} );

		// TODO: handle future
	}

	bool SceneDataLazy::uploadLoadedTextures ()
	{
		LoadedImageData data;

		{
			QMutexLocker locker ( &loadedFilesMutex_ );

			if ( loadedFiles_.isEmpty () ) return false;

			data = loadedFiles_.back ();

			loadedFiles_.pop_back ();
		}

		allMaterialTextures_ [ data.index_ ] = QSharedPointer<QOpenGLTexture>::create ( *(data.image_) );
		
		delete data.image_;
		data.image_ = nullptr;

		updateMaterials ();

		return true;
	}

	void SceneDataLazy::loadScene ( const char* filename )
	{
		jcqt::loadScene ( filename, scene_ );

		// prepare draw data buffer
		QHashIterator<quint32, quint32> it ( scene_.meshes_ );
		while ( it.hasNext () )
		{
			it.next ();

			auto material = scene_.materialForNode_.find ( it.key () );

			if ( material != scene_.materialForNode_.end () )
			{
				shapes_.push_back (
					DrawData {
						.meshIndex = it.value (),
						.materialIndex = material.value (),
						.LOD = 0,
						.indexOffset = meshData_.meshes_ [ it.value () ].indexOffset,
						.vertexOffset = meshData_.meshes_ [ it.value () ].vertexOffset,
						.transformIndex = it.key ()
					}
				);
			}
		}

		// force recalculation of all global transformations
		markAsChanged ( scene_, 0 );
		recalculateGlobalTransforms ( scene_ );
	
	}

	void SceneDataLazy::updateMaterials ()
	{
		const qsizetype numMaterials = materialsLoaded_.size ();

		materials_.resize ( numMaterials );

		for ( qsizetype i = 0; i < numMaterials; i++ )
		{
			const auto& in = materialsLoaded_ [ i ];
			auto& out = materials_ [ i ];
			out = in;
			out.ambientOcclusionMap_ = getTextureHandleBindless ( in.ambientOcclusionMap_, allMaterialTextures_ );
			out.emissiveMap_ = getTextureHandleBindless ( in.emissiveMap_, allMaterialTextures_ );
			out.albedoMap_ = getTextureHandleBindless ( in.albedoMap_, allMaterialTextures_ );
			out.metallicRoughnessMap_ = getTextureHandleBindless ( in.metallicRoughnessMap_, allMaterialTextures_ );
			out.normalMap_ = getTextureHandleBindless ( in.normalMap_, allMaterialTextures_ );
		}
	}
}

