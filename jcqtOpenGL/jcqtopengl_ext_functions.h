/*****************************************************************//**
 * \file   jcqtopengl_ext_functions.h
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
#ifndef __JCQTOPENGL_EXT_FUNCTIONS_H__
#define __JCQTOPENGL_EXT_FUNCTIONS_H__

#include "jcqtopengl_global.h"
#include <QOpenGLContext>

namespace jcqt
{
	// ARB_bindless_texture extension functions
	extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB;
	extern PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB;
	extern PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB;
	extern PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB;
	extern PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB;
	extern PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB;
	extern PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB;
	extern PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB;
	extern PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB;
	extern PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB;
	extern PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB;

	// ARB_indirect_parameters
	extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB;
	extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC glMultiDrawElementsIndirectCountARB;

	// NV_mesh_shader extension functions
	extern PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV;
	extern PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV;
	extern PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV;
	extern PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV;
	extern bool g_extFunctionsIsInitialized;

	extern bool JCQTOPENGL_EXPORT initExtFunctions ( QOpenGLContext* ctx );
	//extern bool initExtFunctions ( QOpenGLContext* ctx );

	//bool JCQTOPENGL_EXPORT initExtFunctsions ( QOpenGLContext* ctx )
	//{
	//	static bool isInitialized = false;
	//	if ( isInitialized )
	//		return true;

	//	if ( ctx->hasExtension ( "GL_ARB_bindless_texture" ) )
	//	{
	//		glGetTextureHandleARB = reinterpret_cast< PFNGLGETTEXTUREHANDLEARBPROC >( ctx->getProcAddress ( "glGetTextureHandleARB" ) );
	//		glGetTextureSamplerHandleARB = reinterpret_cast< PFNGLGETTEXTURESAMPLERHANDLEARBPROC >( ctx->getProcAddress ( "glGetTextureSamplerHandleARB" ) );
	//		glMakeTextureHandleResidentARB = reinterpret_cast< PFNGLMAKETEXTUREHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glMakeTextureHandleResidentARB" ) );
	//		glMakeTextureHandleNonResidentARB = reinterpret_cast< PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC >( ctx->getProcAddress ( "glMakeTextureHandleNonResidentARB" ) );
	//		glGetImageHandleARB = reinterpret_cast< PFNGLGETIMAGEHANDLEARBPROC >( ctx->getProcAddress ( "glGetImageHandleARB" ) );
	//		glMakeImageHandleResidentARB = reinterpret_cast< PFNGLMAKEIMAGEHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glMakeImageHandleResidentARB" ) );
	//		glMakeImageHandleNonResidentARB = reinterpret_cast< PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC >( ctx->getProcAddress ( "glMakeImageHandleNonResidentARB" ) );
	//		glUniformHandleui64ARB = reinterpret_cast< PFNGLUNIFORMHANDLEUI64ARBPROC >( ctx->getProcAddress ( "glUniformHandleui64ARB" ) );
	//		glUniformHandleui64vARB = reinterpret_cast< PFNGLUNIFORMHANDLEUI64VARBPROC >( ctx->getProcAddress ( "glUniformHandleui64vARB" ) );
	//		glProgramUniformHandleui64ARB = reinterpret_cast< PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC >( ctx->getProcAddress ( "glProgramUniformHandleui64ARB" ) );
	//		glProgramUniformHandleui64vARB = reinterpret_cast< PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC >( ctx->getProcAddress ( "glProgramUniformHandleui64vARB" ) );
	//		glIsTextureHandleResidentARB = reinterpret_cast< PFNGLISTEXTUREHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glIsTextureHandleResidentARB" ) );
	//		glIsImageHandleResidentARB = reinterpret_cast< PFNGLISIMAGEHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glIsImageHandleResidentARB" ) );
	//	}
	//	else
	//	{
	//		qWarning ( "GL_ARB_bindless_texture extension not present. Cannot get extension functions.\n" );
	//	}

	//	if ( ctx->hasExtension ( "GL_ARB_indirect_parameters" ) )
	//	{
	//		glMultiDrawArraysIndirectCountARB = reinterpret_cast< PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC >( ctx->getProcAddress ( "glMultiDrawArraysIndirectCountARB" ) );
	//		glMultiDrawElementsIndirectCountARB = reinterpret_cast< PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC >( ctx->getProcAddress ( "glMultiDrawElementsIndirectCountARB" ) );
	//	}
	//	else
	//	{
	//		qWarning ( "GL_ARB_indirect_parameters extension not present. Cannot get extension functions.\n" );
	//	}

	//	if ( ctx->hasExtension ( "GL_NV_mesh_shader" ) )
	//	{
	//		glDrawMeshTasksNV = reinterpret_cast< PFNGLDRAWMESHTASKSNVPROC >( ctx->getProcAddress ( "glDrawMeshTasksNV" ) );
	//		glDrawMeshTasksIndirectNV = reinterpret_cast< PFNGLDRAWMESHTASKSINDIRECTNVPROC >( ctx->getProcAddress ( "glDrawMeshTasksIndirectNV" ) );
	//		glMultiDrawMeshTasksIndirectNV = reinterpret_cast< PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC >( ctx->getProcAddress ( "glMultiDrawMeshTasksIndirectNV" ) );
	//		glMultiDrawMeshTasksIndirectCountNV = reinterpret_cast< PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC >( ctx->getProcAddress ( "glMultiDrawMeshTasksIndirectCountNV" ) );
	//	}
	//	else
	//	{
	//		qWarning ( "GL_NV_mesh_shader extension not present. Cannot get extension functions.\n" );
	//	}

	//	isInitialized = true;
	//	return true;
	//}
}

#endif // !__JCQTOPENGL_EXT_FUNCTIONS_H__

