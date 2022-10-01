#include "jcqtopengl_ext_functions.h"

namespace jcqt
{
	// ARB_bindless_texture extension functions
	extern PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB = nullptr;
	extern PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB = nullptr;
	extern PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB = nullptr;
	extern PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB = nullptr;
	extern PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB = nullptr;
	extern PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB = nullptr;
	extern PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB = nullptr;
	extern PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB = nullptr;
	extern PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB = nullptr;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB = nullptr;
	extern PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB = nullptr;
	extern PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB = nullptr;
	extern PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB = nullptr;

	// ARB_indirect_parameters
	extern PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB = nullptr;
	extern PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC glMultiDrawElementsIndirectCountARB = nullptr;

	// NV_mesh_shader extension functions
	extern PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV = nullptr;
	extern PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV = nullptr;
	extern PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV = nullptr;
	extern PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV = nullptr;

	extern bool g_extFunctionsIsInitialized = false;

	bool initExtFunctsions ( QOpenGLContext* ctx )
	{
		if ( g_extFunctionsIsInitialized )
			return true;

		if ( ctx->hasExtension ( "GL_ARB_bindless_texture" ) )
		{
			glGetTextureHandleARB = reinterpret_cast< PFNGLGETTEXTUREHANDLEARBPROC >( ctx->getProcAddress ( "glGetTextureHandleARB" ) );
			glGetTextureSamplerHandleARB = reinterpret_cast< PFNGLGETTEXTURESAMPLERHANDLEARBPROC >( ctx->getProcAddress ( "glGetTextureSamplerHandleARB" ) );
			glMakeTextureHandleResidentARB = reinterpret_cast< PFNGLMAKETEXTUREHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glMakeTextureHandleResidentARB" ) );
			glMakeTextureHandleNonResidentARB = reinterpret_cast< PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC >( ctx->getProcAddress ( "glMakeTextureHandleNonResidentARB" ) );
			glGetImageHandleARB = reinterpret_cast< PFNGLGETIMAGEHANDLEARBPROC >( ctx->getProcAddress ( "glGetImageHandleARB" ) );
			glMakeImageHandleResidentARB = reinterpret_cast< PFNGLMAKEIMAGEHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glMakeImageHandleResidentARB" ) );
			glMakeImageHandleNonResidentARB = reinterpret_cast< PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC >( ctx->getProcAddress ( "glMakeImageHandleNonResidentARB" ) );
			glUniformHandleui64ARB = reinterpret_cast< PFNGLUNIFORMHANDLEUI64ARBPROC >( ctx->getProcAddress ( "glUniformHandleui64ARB" ) );
			glUniformHandleui64vARB = reinterpret_cast< PFNGLUNIFORMHANDLEUI64VARBPROC >( ctx->getProcAddress ( "glUniformHandleui64vARB" ) );
			glProgramUniformHandleui64ARB = reinterpret_cast< PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC >( ctx->getProcAddress ( "glProgramUniformHandleui64ARB" ) );
			glProgramUniformHandleui64vARB = reinterpret_cast< PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC >( ctx->getProcAddress ( "glProgramUniformHandleui64vARB" ) );
			glIsTextureHandleResidentARB = reinterpret_cast< PFNGLISTEXTUREHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glIsTextureHandleResidentARB" ) );
			glIsImageHandleResidentARB = reinterpret_cast< PFNGLISIMAGEHANDLERESIDENTARBPROC >( ctx->getProcAddress ( "glIsImageHandleResidentARB" ) );
		}
		else
		{
			qWarning ( "GL_ARB_bindless_texture extension not present. Cannot get extension functions.\n" );
		}

		if ( ctx->hasExtension ( "GL_ARB_indirect_parameters" ) )
		{
			glMultiDrawArraysIndirectCountARB = reinterpret_cast< PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC >( ctx->getProcAddress ( "glMultiDrawArraysIndirectCountARB" ) );
			glMultiDrawElementsIndirectCountARB = reinterpret_cast< PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC >( ctx->getProcAddress ( "glMultiDrawElementsIndirectCountARB" ) );
		}
		else
		{
			qWarning ( "GL_ARB_indirect_parameters extension not present. Cannot get extension functions.\n" );
		}

		if ( ctx->hasExtension ( "GL_NV_mesh_shader" ) )
		{
			glDrawMeshTasksNV = reinterpret_cast< PFNGLDRAWMESHTASKSNVPROC >( ctx->getProcAddress ( "glDrawMeshTasksNV" ) );
			glDrawMeshTasksIndirectNV = reinterpret_cast< PFNGLDRAWMESHTASKSINDIRECTNVPROC >( ctx->getProcAddress ( "glDrawMeshTasksIndirectNV" ) );
			glMultiDrawMeshTasksIndirectNV = reinterpret_cast< PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC >( ctx->getProcAddress ( "glMultiDrawMeshTasksIndirectNV" ) );
			glMultiDrawMeshTasksIndirectCountNV = reinterpret_cast< PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC >( ctx->getProcAddress ( "glMultiDrawMeshTasksIndirectCountNV" ) );
		}
		else
		{
			qWarning ( "GL_NV_mesh_shader extension not present. Cannot get extension functions.\n" );
		}

		g_extFunctionsIsInitialized = true;
		return true;
	}
}