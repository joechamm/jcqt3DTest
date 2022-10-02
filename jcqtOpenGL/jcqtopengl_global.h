/*****************************************************************//**
 * \file   jcqtopengl_global.h
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
#ifndef __JCQTOPENGL_GLOBAL_H__
#define __JCQTOPENGL_GLOBAL_H__

#include <QtCore/qglobal.h>
#include <qopenglext.h>

#ifndef BUILD_STATIC
# if defined(JCQTOPENGL_LIB)
#  define JCQTOPENGL_EXPORT Q_DECL_EXPORT
# else
#  define JCQTOPENGL_EXPORT Q_DECL_IMPORT
# endif
#else
# define JCQTOPENGL_EXPORT
#endif

namespace jcqt
{
	// global constants

	// kIdxBind_ is the prefix for an OpenGL/GLSL buffer binding point

	constexpr quint32 kIdxBind_TightBufferVtx = 0;
	constexpr quint32 kIdxBind_SepBufferVtxPositions = 1;
	constexpr quint32 kIdxBind_SepBufferVtxNormals = 2;
	constexpr quint32 kIdxBind_SepBufferVtxTexCoords = 3;
	constexpr quint32 kIdxBind_SepBufferVtxTangents = 4;
	constexpr quint32 kIdxBind_SepBufferVtxColors = 5;
	constexpr quint32 kIdxBind_SepBufferVtxJoints = 6;
	constexpr quint32 kIdxBind_SepBufferVtxWeights = 7;
	constexpr quint32 kIdxBind_SSBOMaterials = 8;
	constexpr quint32 kIdxBind_SSBOModelMatrices = 9;

	constexpr quint32 kIdxLoc_POSITION = 0;
	constexpr quint32 kIdxLoc_NORMAL = 1;
	constexpr quint32 kIdxLoc_TANGENT = 2;
	constexpr quint32 kIdxLoc_TEXCOORD_0 = 3;
	constexpr quint32 kIdxLoc_TEXCOORD_1 = 4;
	constexpr quint32 kIdxLoc_COLOR_0 = 5;
	constexpr quint32 kIdxLoc_COLOR_1 = 6;
	constexpr quint32 kIdxLoc_JOINTS_0 = 7;
	constexpr quint32 kIdxLoc_JOINTS_1 = 8;
	constexpr quint32 kIdxLoc_WEIGHTS_0 = 9;
	constexpr quint32 kIdxLoc_WEIGHTS_1 = 10;
	constexpr quint32 kIdxLoc_USER_0 = 11;
	constexpr quint32 kIdxLoc_USER_1 = 12;
	constexpr quint32 kIdxLoc_USER_2 = 13;
	constexpr quint32 kIdxLoc_USER_3 = 14;
	constexpr quint32 kIdxLoc_USER_4 = 15;

	// kIndex_ is the prefix for a QList<GLuint> containing buffer names generated by OpenGL
	constexpr quint32 kIndex_Indices = 0;
	constexpr quint32 kIndex_Vertices = 1;
	constexpr quint32 kIndex_Indirect = 2;
	constexpr quint32 kIndex_ModelMatrices = 3;
	constexpr quint32 kIndex_Materials = 4;
}


#endif // !__JCQTOPENGL_GLOBAL_H__
