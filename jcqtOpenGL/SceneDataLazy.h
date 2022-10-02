/*****************************************************************//**
 * \file   SceneDataLazy.h
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
#ifndef __SCENE_DATA_LAZY_H__
#define __SCENE_DATA_LAZY_H__

#include "jcqtopengl_global.h"

#include <QSharedPointer>
#include <QOpenGLTexture>
#include <QImage>
#include <QMutex>
#include <QThreadPool>
#include <QtConcurrent>

#include "Scene.h"
#include "Material.h"
#include "VtxData.h"

namespace jcqt
{
	class JCQTOPENGL_EXPORT SceneDataLazy
	{
	public:
		struct LoadedImageData
		{
			qint32 index_ = 0;
			QImage* image_ = nullptr;
		};

		const QSharedPointer<QOpenGLTexture> dummyTexture_ = QSharedPointer<QOpenGLTexture>::create ( QImage ( ":/textures/const1.bmp" ) );

		QByteArrayList textureFiles_;
		QList<LoadedImageData> loadedFiles_;
		QMutex loadedFilesMutex_;
		QList<QSharedPointer<QOpenGLTexture>> allMaterialTextures_;

		MeshFileHeader header_;
		MeshData meshData_;

		Scene scene_;
		QList<MaterialDescription> materialsLoaded_;
		QList<MaterialDescription> materials_;
		QList<DrawData> shapes_;

	public:
		SceneDataLazy ( const char* meshFilensm,
			const char* sceneFile,
			const char* materialFile );

		bool uploadLoadedTextures ();

	private:
		void loadScene ( const char* filename );
		void updateMaterials ();

		QThreadPool threadPool_;
	};
}


#endif // !__SCENE_DATA_LAZY_H__
