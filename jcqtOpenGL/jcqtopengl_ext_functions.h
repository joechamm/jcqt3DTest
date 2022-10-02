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

#include <qopenglext.h>


namespace jcqt
{
	
}

//
//#if defined(_WIN32) && !defined(APIENTRY) && !defined(__CYGWIN__) && !defined(__SCITECH_SNAP__)
//#define APIENTRY __stdcall
//#endif 
//
//#ifndef APIENTRY
//#define APIENTRY
//#endif
//#ifndef APIENTRYP
//#define APIENTRYP APIENTRY *
//#endif 
//
//#ifndef GLAPIENTRY
//#define GLAPIENTRY APIENTRY
//#endif
//
//#ifdef __cplusplus
//extern "C" {
//#endif 
//
//struct gladGLVersionStruct
//{
//	int major;
//	int minor;
//};
//
//typedef void* ( *GLADloadproc )( const char* name );
//
//#ifndef GLAPI
//#  if defined (GLAD_GLAPI_EXPORT)
//#    if defined(_WIN32) || defined(__CYGWIN__)
//#      if defined(GLAD_CLAPI_EXPORT_BUILD)
//#        if defined(__GNUC__)
//#          define GLAPI __attribute__ ((dllexport)) extern 
//#		 else 
//#		   define GLAPI __declspec(dllexport) extern
//#		 endif
//#      else 
//#        if defined(__GNUC__)
//#          define GLAPI __attribute__ ((dllimport)) extern
//#        else
//#          define GLAPI __declspec(dllimport) extern
//#        endif 
//#      endif
//#    elif defined(__GNUC__) && defined(GLAD_GLAPI_EXPORT_BUILD)
//#      define GLAPI __attribute__ ((visibility ("default"))) extern
//#    else
//#	   define GLAPI extern
//#	 endif 
//#  else
//#    define GLAPI extern
//#  endif 
//#endif
//
//GLAPI struct gladGLVersionStruct GLVersion;
//
//GLAPI int gladLoadGL ( void );
//
//GLAPI int gladLoadGLLoader ( GLADloadproc );
//
//
//#ifdef __cplusplus
//}
//#endif


//
//#include "jcqtopengl_global.h"
//#include <QOpenGLContext>
//
//namespace jcqt
//{
//	// ARB_bindless_texture extension functions
//	extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB;
//	extern PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB;
//	extern PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB;
//	extern PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB;
//	extern PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB;
//	extern PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB;
//	extern PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB;
//	extern PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB;
//	extern PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB;
//	extern PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB;
//	extern PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB;
//	extern PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB;
//	extern PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB;
//
//	// ARB_indirect_parameters
//	extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB;
//	extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC glMultiDrawElementsIndirectCountARB;
//
//	// NV_mesh_shader extension functions
//	extern PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV;
//	extern PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV;
//	extern PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV;
//	extern PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV;
//	extern bool g_extFunctionsIsInitialized;
//
//	extern bool JCQTOPENGL_EXPORT initExtFunctions ( QOpenGLContext* ctx );
//	
//}

#endif // !__JCQTOPENGL_EXT_FUNCTIONS_H__

