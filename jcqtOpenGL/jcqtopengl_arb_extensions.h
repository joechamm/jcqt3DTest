/*****************************************************************//**
 * \file   jcqtopengl_arb_extensions.h
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
#ifndef __JCQTOPENGL_ARB_EXTENSIONS_H__
#define __JCQTOPENGL_ARB_EXTENSIONS_H__

#include "jcqtopengl_global.h"
#include <QOpenGLContext>

namespace jcqt
{
	GLAPI bool g_extFunctionsInitialized;

	// ARB_bindless_texture extension functions
	GLAPI PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB;
	GLAPI PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB;
	GLAPI PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB;
	GLAPI PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB;
	GLAPI PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB;
	GLAPI PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB;
	GLAPI PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB;
	GLAPI PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB;
	GLAPI PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB;
	GLAPI PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB;
	GLAPI PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB;
	GLAPI PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB;
	GLAPI PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB;

	// ARB_indirect_parameters extension functions
	GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB;
	GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC glMultiDrawElementsIndirectCountARB;

	// NV_mesh_shader extension functions
	GLAPI PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV;
	GLAPI PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV;

	GLAPI bool JCQTOPENGL_EXPORT initExtFunctions ( QOpenGLContext* context );
}

#endif // !__JCQTOPENGL_ARB_EXTENSIONS_H__
