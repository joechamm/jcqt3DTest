/*****************************************************************//**
 * \file   jcqtopengl_extension_functions.h
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
#ifndef __JCQTOPENGL_EXTENSION_FUNCTIONS_H__
#define __JCQTOPENGL_EXTENSION_FUNCTIONS_H__

#include "jcqtopengl_global.h"
#include <QOpenGLContext>

namespace jcqt
{
	GLAPI bool g_extFunctionsInitialized;

	// GL_ARB_bindless_texture extension functions
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

	// GL_ARB_indirect_parameters extension functions
	GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirect;
	GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount;

	// GL_ARB_gl_spirv exteion functions
	GLAPI PFNGLSPECIALIZESHADERPROC glSpecializeShader;

	// GL_ARB_sparse_buffer
	GLAPI PFNGLBUFFERPAGECOMMITMENTARBPROC glBufferPageCommitmentARB;
	GLAPI PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC glNamedBufferPageCommitmentARB;

	// GL_ARB_polygon_offset_clamp
	GLAPI PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp;

	// GL_ARB_shading_language_include
	GLAPI PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB;
	GLAPI PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB;
	GLAPI PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB;
	GLAPI PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB;
	GLAPI PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB;
	GLAPI PFNGLNAMEDSTRINGARBPROC glNamedStringARB;

	// GL_NV_mesh_shader extension functions
	GLAPI PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV;
	GLAPI PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV;

	// GL_NV_memory_attachment
	GLAPI PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC glGetMemoryObjectDetachedResourcesuivNV;
	GLAPI PFNGLRESETMEMORYOBJECTPARAMETERNVPROC glResetMemoryObjectParameterNV;
	GLAPI PFNGLTEXATTACHMEMORYNVPROC glTexAttachMemoryNV;
	GLAPI PFNGLBUFFERATTACHMEMORYNVPROC glBufferAttachMemoryNV;
	GLAPI PFNGLTEXTUREATTACHMEMORYNVPROC glTextureAttachMemoryNV;
	GLAPI PFNGLNAMEDBUFFERATTACHMEMORYNVPROC glNamedBufferAttachMemoryNV;

	GLAPI bool JCQTOPENGL_EXPORT initExtFunctions ( QOpenGLContext* context );
}

#endif // !__JCQTOPENGL_EXTENSION_FUNCTIONS_H__
