/*****************************************************************//**
 * \file   SceneData.h
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
 * \date   September 2022
 *********************************************************************/
#ifndef __SCENE_DATA_H__
#define __SCENE_DATA_H__

#include "jcqtopengl_global.h"

#include "Scene.h"
#include "Material.h"
#include "VtxData.h"

#include <QList>

QT_FORWARD_DECLARE_CLASS ( QOpenGLTexture );

namespace jcqt
{
	class JCQTOPENGL_EXPORT SceneData
	{
	public:
		SceneData(const char* meshFile,
			const char* sceneFile,
			const char* materialFile );

		void loadScene ( const char* sceneFile );

		MeshFileHeader header_;
		MeshData meshData_;

		Scene scene_;

		QList<QOpenGLTexture> allMaterialTextures_;
		QList<MaterialDescription> materials_;
		QList<DrawData> shapes_;
	};
}
#endif // !__SCENE_DATA_H__
