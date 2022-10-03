#include "jcqtopengl_extension_functions.h"

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
	GLAPI PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC glMultiDrawArraysIndirectCount = nullptr;
	GLAPI PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC glMultiDrawElementsIndirectCount = nullptr;
	
	// GL_ARB_gl_spirv exteion functions
	GLAPI PFNGLSPECIALIZESHADERPROC glSpecializeShader = nullptr;

		// GL_ARB_sparse_buffer
	GLAPI PFNGLBUFFERPAGECOMMITMENTARBPROC glBufferPageCommitmentARB = nullptr;
	GLAPI PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC glNamedBufferPageCommitmentARB = nullptr;

	// GL_ARB_polygon_offset_clamp
	GLAPI PFNGLPOLYGONOFFSETCLAMPPROC glPolygonOffsetClamp = nullptr;

	// GL_ARB_shading_language_include
	GLAPI PFNGLCOMPILESHADERINCLUDEARBPROC glCompileShaderIncludeARB = nullptr;
	GLAPI PFNGLDELETENAMEDSTRINGARBPROC glDeleteNamedStringARB = nullptr;
	GLAPI PFNGLGETNAMEDSTRINGARBPROC glGetNamedStringARB = nullptr;
	GLAPI PFNGLGETNAMEDSTRINGIVARBPROC glGetNamedStringivARB = nullptr;
	GLAPI PFNGLISNAMEDSTRINGARBPROC glIsNamedStringARB = nullptr;
	GLAPI PFNGLNAMEDSTRINGARBPROC glNamedStringARB = nullptr;

	// NV_mesh_shader extension functions
	GLAPI PFNGLDRAWMESHTASKSNVPROC glDrawMeshTasksNV = nullptr;
	GLAPI PFNGLDRAWMESHTASKSINDIRECTNVPROC glDrawMeshTasksIndirectNV = nullptr;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTNVPROC glMultiDrawMeshTasksIndirectNV = nullptr;
	GLAPI PFNGLMULTIDRAWMESHTASKSINDIRECTCOUNTNVPROC glMultiDrawMeshTasksIndirectCountNV = nullptr;

	// GL_NV_memory_attachment
	GLAPI PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC glGetMemoryObjectDetachedResourcesuivNV = nullptr;
	GLAPI PFNGLRESETMEMORYOBJECTPARAMETERNVPROC glResetMemoryObjectParameterNV = nullptr;
	GLAPI PFNGLTEXATTACHMEMORYNVPROC glTexAttachMemoryNV = nullptr;
	GLAPI PFNGLBUFFERATTACHMEMORYNVPROC glBufferAttachMemoryNV = nullptr;
	GLAPI PFNGLTEXTUREATTACHMEMORYNVPROC glTextureAttachMemoryNV = nullptr;
	GLAPI PFNGLNAMEDBUFFERATTACHMEMORYNVPROC glNamedBufferAttachMemoryNV = nullptr;

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
			glMultiDrawArraysIndirectCount = reinterpret_cast< PFNGLMULTIDRAWARRAYSINDIRECTCOUNTPROC >( context->getProcAddress ( "glMultiDrawArraysIndirectCount" ) );
			glMultiDrawElementsIndirectCount = reinterpret_cast< PFNGLMULTIDRAWELEMENTSINDIRECTCOUNTPROC >( context->getProcAddress ( "glMultiDrawElementsIndirectCount" ) );
		}
		else
		{
			qWarning () << "GL_ARB_indirect_parameters extension not present" << Qt::endl;
		}

		if ( ctxextensions.contains ( "GL_ARB_gl_spirv" ) )
		{
			glSpecializeShader = reinterpret_cast< PFNGLSPECIALIZESHADERPROC >( context->getProcAddress ( "glSpecializeShader" ) );
		}
		else
		{
			qWarning () << "GL_ARB_gl_spirv extension not present" << Qt::endl;
		}

		if ( ctxextensions.contains ( "GL_ARB_polygon_offset_clamp" ) )
		{
			glPolygonOffsetClamp = reinterpret_cast< PFNGLPOLYGONOFFSETCLAMPPROC >( context->getProcAddress ( "glPolygonOffsetClamp" ) );
		}
		else
		{
			qWarning () << "GL_ARB_polygon_offset_clamp extension not present" << Qt::endl;
		}

		if ( ctxextensions.contains ( "GL_ARB_sparse_buffer" ) )
		{
			glBufferPageCommitmentARB = reinterpret_cast< PFNGLBUFFERPAGECOMMITMENTARBPROC >( context->getProcAddress ( "glBufferPageCommitmentARB" ) );
			glNamedBufferPageCommitmentARB = reinterpret_cast< PFNGLNAMEDBUFFERPAGECOMMITMENTARBPROC >( context->getProcAddress ( "glNamedBufferPageCommitmentARB" ) );
		}
		else
		{
			qWarning () << "GL_ARB_sparse_buffer extension not present" << Qt::endl;
		}

		if ( ctxextensions.contains ( "GL_ARB_shading_language_include" ) )
		{
			glCompileShaderIncludeARB = reinterpret_cast< PFNGLCOMPILESHADERINCLUDEARBPROC >( context->getProcAddress ( "glCompileShaderIncludeARB" ) );
			glDeleteNamedStringARB = reinterpret_cast< PFNGLDELETENAMEDSTRINGARBPROC >( context->getProcAddress ( "glDeleteNamedStringARB" ) );
			glGetNamedStringARB = reinterpret_cast< PFNGLGETNAMEDSTRINGARBPROC >( context->getProcAddress ( "glGetNamedStringARB" ) );
			glGetNamedStringivARB = reinterpret_cast< PFNGLGETNAMEDSTRINGIVARBPROC >( context->getProcAddress ( "glGetNamedStringivARB" ) );
			glIsNamedStringARB = reinterpret_cast< PFNGLISNAMEDSTRINGARBPROC >( context->getProcAddress ( "glIsNamedStringARB" ) );
			glNamedStringARB = reinterpret_cast< PFNGLNAMEDSTRINGARBPROC >( context->getProcAddress ( "glNamedStringARB" ) );
		}
		else
		{
			qWarning () << "GL_ARB_shading_language_include extension not present" << Qt::endl;
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

		if ( ctxextensions.contains ( "GL_NV_memory_attachment" ) )
		{
			glGetMemoryObjectDetachedResourcesuivNV = reinterpret_cast< PFNGLGETMEMORYOBJECTDETACHEDRESOURCESUIVNVPROC >( context->getProcAddress ( "glGetMemoryObjectDetachedResourcesuivNV" ) );
			glResetMemoryObjectParameterNV = reinterpret_cast< PFNGLRESETMEMORYOBJECTPARAMETERNVPROC >( context->getProcAddress ( "glResetMemoryObjectParameterNV" ) );
			glTexAttachMemoryNV = reinterpret_cast< PFNGLTEXATTACHMEMORYNVPROC >( context->getProcAddress ( "glTexAttachMemoryNV" ) );
			glBufferAttachMemoryNV = reinterpret_cast< PFNGLBUFFERATTACHMEMORYNVPROC >( context->getProcAddress ( "glBufferAttachMemoryNV" ) );
			glTextureAttachMemoryNV = reinterpret_cast< PFNGLTEXTUREATTACHMEMORYNVPROC >( context->getProcAddress ( "glTextureAttachMemoryNV" ) );
			glNamedBufferAttachMemoryNV = reinterpret_cast< PFNGLNAMEDBUFFERATTACHMEMORYNVPROC >( context->getProcAddress ( "glNamedBufferAttachMemoryNV" ) );
		}
		else
		{
			qWarning () << "GL_NV_memory_attachment extension not present" << Qt::endl;
		}

		g_extFunctionsInitialized = true;
		return true;
	}
}