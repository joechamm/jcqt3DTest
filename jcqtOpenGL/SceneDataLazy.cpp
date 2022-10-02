#include "SceneDataLazy.h"

#include "jcqtopengl_arb_extensions.h"

namespace jcqt
{
	static GLuint64 getTextureHandleBindless ( GLuint64 idx, const QList<QSharedPointer<QOpenGLTexture>>& textures )
	{
		if ( idx == INVALID_TEXTURE ) return 0;

		GLuint handle = textures [ idx ]->textureId ();

		GLuint64 handleBindless = glGetTextureHandleARB ( handle );

		return handleBindless;
	}

	SceneDataLazy::SceneDataLazy ( const char* meshFilensm, const char* sceneFile, const char* materialFile )
	{
		header_ = loadMeshData(meshFile, meshData)
	}

	bool SceneDataLazy::uploadLoadedTextures ()
	{
		return false;
	}

	void SceneDataLazy::loadScene ( const char* filename )
	{}

	void SceneDataLazy::updateMaterials ()
	{}
}

