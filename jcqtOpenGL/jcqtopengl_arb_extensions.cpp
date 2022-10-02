#include "jcqtopengl_arb_extensions.h"

namespace jcqt
{
	GLAPI bool g_extFunctionsInitialized = false;

	GLAPI PFNGLGETTEXTUREHANDLEARBPROC glGetTextureHandleARB = nullptr;
	GLAPI PFNGLGETTEXTURESAMPLERHANDLEARBPROC glGetTextureSamplerHandleARB = nullptr;
	GLAPI PFNGLMAKETEXTUREHANDLERESIDENTARBPROC glMakeTextureHandleResidentARB = nullptr;
	GLAPI PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC glMakeTextureHandleNonResidentARB = nullptr;	
	GLAPI PFNGLGETIMAGEHANDLEARBPROC glGetImageHandleARB = nullptr;
	GLAPI PFNGLMAKEIMAGEHANDLERESIDENTARBPROC glMakeImageHandleResidentARB = nullptr;
	GLAPI PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC glMakeImageHandleNonResidentARB = nullptr;
	GLAPI PFNGLUNIFORMHANDLEUI64ARBPROC glUniformHandleui64ARB = nullptr;
	GLAPI PFNGLUNIFORMHANDLEUI64VARBPROC glUniformHandleui64vARB = nullptr;
	GLAPI PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC glProgramUniformHandleui64ARB = nullptr;
	GLAPI PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC glProgramUniformHandleui64vARB = nullptr;
	GLAPI PFNGLISTEXTUREHANDLERESIDENTARBPROC glIsTextureHandleResidentARB = nullptr;
	GLAPI PFNGLISIMAGEHANDLERESIDENTARBPROC glIsImageHandleResidentARB = nullptr;

	// ARB_indirect_parameters
	GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC glMultiDrawArraysIndirectCountARB = nullptr;
	GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC glMultiDrawElementsIndirectCountARB = nullptr;

	// NV_mesh_shader extension functions
	GLAPI PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV = nullptr;
	GLAPI PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV = nullptr;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV = nullptr;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV = nullptr;

	bool initExtFunctions ( QOpenGLContext* context )
	{
		if ( g_extFunctionsInitialized )
			return true;

		QSet<QByteArray> ctxextensions = context->extensions ();
		
		if ( ctxextensions.contains ( "GL_ARB_bindless_texture" ) )
		{
			glGetTextureHandleARB = reinterpret_cast< PFNGLGETTEXTUREHANDLEARBPROC >( context->getProcAddress ( "glGetTextureHandleARB" ) );
			glGetTextureSamplerHandleARB = reinterpret_cast< PFNGLGETTEXTURESAMPLERHANDLEARBPROC >( context->getProcAddress ( "glGetTextureSamplerHandleARB" ) );
			glMakeTextureHandleResidentARB = reinterpret_cast< PFNGLMAKETEXTUREHANDLERESIDENTARBPROC >( context->getProcAddress ( "glMakeTextureHandleResidentARB" ) );
			glMakeTextureHandleNonResidentARB = reinterpret_cast< PFNGLMAKETEXTUREHANDLENONRESIDENTARBPROC >( context->getProcAddress ( "glMakeTextureHandleNonResidentARB" ) );
			glGetImageHandleARB = reinterpret_cast< PFNGLGETIMAGEHANDLEARBPROC >( context->getProcAddress ( "glGetImageHandleARB" ) );
			glMakeImageHandleResidentARB = reinterpret_cast< PFNGLMAKEIMAGEHANDLERESIDENTARBPROC >( context->getProcAddress ( "glMakeImageHandleResidentARB" ) );
			glMakeImageHandleNonResidentARB = reinterpret_cast< PFNGLMAKEIMAGEHANDLENONRESIDENTARBPROC >( context->getProcAddress ( "glMakeImageHandleNonResidentARB" ) );
			glUniformHandleui64ARB = reinterpret_cast< PFNGLUNIFORMHANDLEUI64ARBPROC >( context->getProcAddress ( "glUniformHandleui64ARB" ) );
			glUniformHandleui64vARB = reinterpret_cast< PFNGLUNIFORMHANDLEUI64VARBPROC >( context->getProcAddress ( "glUniformHandleui64vARB" ) );
			glProgramUniformHandleui64ARB = reinterpret_cast< PFNGLPROGRAMUNIFORMHANDLEUI64ARBPROC >( context->getProcAddress ( "glProgramUniformHandleui64ARB" ) );
			glProgramUniformHandleui64vARB = reinterpret_cast< PFNGLPROGRAMUNIFORMHANDLEUI64VARBPROC >( context->getProcAddress ( "glProgramUniformHandleui64vARB" ) );
			glIsTextureHandleResidentARB = reinterpret_cast< PFNGLISTEXTUREHANDLERESIDENTARBPROC >( context->getProcAddress ( "glIsTextureHandleResidentARB" ) );
			glIsImageHandleResidentARB = reinterpret_cast< PFNGLISIMAGEHANDLERESIDENTARBPROC >( context->getProcAddress ( "glIsImageHandleResidentARB" ) );
		}
		else
		{
			qWarning () << "GL_ARB_bindless_texture extension not present" << Qt::endl;
		}

		if ( ctxextensions.contains ( "GL_ARB_indirect_parameters" ) )
		{
			glMultiDrawArraysIndirectCountARB = reinterpret_cast< PFNGLMULTIDRAWARRAYSINDIRECTCOUNTARBPROC >( context->getProcAddress ( "glMultiDrawArraysIndirectCountARB" ) );
			glMultiDrawElementsIndirectCountARB = reinterpret_cast< PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTARBPROC >( context->getProcAddress ( "glMultiDrawElementsIndirectCountARB" ) );
		}
		else
		{
			qWarning () << "GL_ARB_indirect_parameters extension not present" << Qt::endl;
		}

		if ( ctxextensions.contains ( "GL_NV_mesh_shader" ) )
		{
			glDrawMeshTasksNV = reinterpret_cast< PFNGLDRAWMESHTASKSNVPROC >( context->getProcAddress ( "glDrawMeshTasksNV" ) );
			glDrawMeshTasksIndirectNV = reinterpret_cast< PFNGLDRAWMESHTASKSINDIRECTNVPROC >( context->getProcAddress ( "glDrawMeshTasksIndirectNV" ) );
			glMultiDrawMeshTasksIndirectNV = reinterpret_cast< PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC >( context->getProcAddress ( "glMultiDrawMeshTasksIndirectNV" ) );
			glMultiDrawMeshTasksIndirectCountNV = reinterpret_cast< PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC >( context->getProcAddress ( "glMultiDrawMeshTasksIndirectCountNV" ) );
		}
		else
		{
			qWarning () << "GL_NV_mesh_shader extension not present" << Qt::endl;
		}

		g_extFunctionsInitialized = true;
		return true;
	}
}