#include "DrawMesh.h"

#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>

#include "jcqtopengl_extension_functions.h"

namespace jcqt
{
	using glm::vec2;

	DrawMesh::DrawMesh ( const SceneData& data )
		: m_numIndices ( data.header_.indexDataSize / sizeof ( quint32 ) )
		, m_indexBuffer ( 0 )
		, m_vertexBuffer ( 0 )
		, m_vao ( 0 )
		, m_materialsBuffer ( 0 )
		, m_modelMatricesBuffer ( 0 )
		, m_indirectBuffer ( 0 )
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();

		if ( !g_extFunctionsInitialized )
		{
			initExtFunctions ( ctx );
		}

		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glCreateBuffers ( 1, &m_indexBuffer );
		funcs->glCreateBuffers ( 1, &m_vertexBuffer );
		funcs->glCreateBuffers ( 1, &m_materialsBuffer );
		funcs->glCreateBuffers ( 1, &m_modelMatricesBuffer );
		funcs->glCreateBuffers ( 1, &m_indirectBuffer );

		funcs->glNamedBufferStorage ( m_indexBuffer, data.header_.indexDataSize, data.meshData_.indexData_.constData (), 0 );
		funcs->glNamedBufferStorage ( m_vertexBuffer, data.header_.vertexDataSize, data.meshData_.vertexData_.constData (), 0 );
		funcs->glNamedBufferStorage ( m_materialsBuffer, sizeof ( MaterialDescription ) * data.materials_.size (), data.materials_.constData (), 0 );
		funcs->glNamedBufferStorage ( m_modelMatricesBuffer, sizeof ( mat4 ) * data.shapes_.size (), nullptr, GL_DYNAMIC_STORAGE_BIT );

		struct DrawElementsIndirectCommand
		{
			GLuint m_count;
			GLuint m_instanceCount;
			GLuint m_firstIndex;
			GLuint m_baseVertex;
			GLuint m_baseInstance;
		};

		funcs->glNamedBufferStorage ( m_indirectBuffer, sizeof ( DrawElementsIndirectCommand ) * data.shapes_.size () + sizeof ( GLsizei ), nullptr, GL_DYNAMIC_STORAGE_BIT );

		funcs->glCreateVertexArrays ( 1, &m_vao );
		funcs->glVertexArrayElementBuffer ( m_vao, m_indexBuffer );
		funcs->glVertexArrayVertexBuffer ( m_vao, kIdxBind_VBOTightBuffer, m_vertexBuffer, 0, sizeof ( vec3 ) + sizeof ( vec3 ) + sizeof ( vec2 ) );

		// position
		funcs->glEnableVertexArrayAttrib ( m_vao, kIdxLoc_POSITION );
		funcs->glVertexArrayAttribFormat ( m_vao, kIdxLoc_POSITION, 3, GL_FLOAT, GL_FALSE, 0 );
		funcs->glVertexArrayAttribBinding ( m_vao, kIdxLoc_POSITION, kIdxBind_VBOTightBuffer );

		// uv 
		funcs->glEnableVertexArrayAttrib ( m_vao, kIdxLoc_TEXCOORD_0 );
		funcs->glVertexArrayAttribFormat ( m_vao, kIdxLoc_TEXCOORD_0, 2, GL_FLOAT, GL_FALSE, sizeof(vec3) );
		funcs->glVertexArrayAttribBinding ( m_vao, kIdxLoc_TEXCOORD_0, kIdxBind_VBOTightBuffer );

	
		// normal
		funcs->glEnableVertexArrayAttrib ( m_vao, kIdxLoc_NORMAL );
		funcs->glVertexArrayAttribFormat ( m_vao, kIdxLoc_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof(vec3) + sizeof(vec2) );
		funcs->glVertexArrayAttribBinding ( m_vao, kIdxLoc_NORMAL, kIdxBind_VBOTightBuffer );

		QByteArray drawCommands;

		drawCommands.resize ( sizeof ( DrawElementsIndirectCommand ) * data.shapes_.size () + sizeof ( GLsizei ) );

		// store the number of draw commands in the very beginning of the buffer
		const GLsizei numCommands = ( GLsizei ) data.shapes_.size ();
		memcpy ( drawCommands.data (), &numCommands, sizeof ( numCommands ) );

		DrawElementsIndirectCommand* cmd = std::launder ( reinterpret_cast< DrawElementsIndirectCommand* >( drawCommands.data () + sizeof ( GLsizei ) ) );

		// prepare indirect commands buffer
		for ( qsizetype i = 0; i != data.shapes_.size (); i++ )
		{
			const quint32 meshIdx = data.shapes_ [ i ].meshIndex;
			const quint32 lod = data.shapes_ [ i ].LOD;
			*cmd++ = {
				.m_count = data.meshData_.meshes_ [ meshIdx ].getLODIndicesCount ( lod ),
				.m_instanceCount = 1,
				.m_firstIndex = data.shapes_ [ i ].indexOffset,
				.m_baseVertex = data.shapes_ [ i ].vertexOffset,
				.m_baseInstance = data.shapes_ [ i ].materialIndex
			};
		}

		funcs->glNamedBufferSubData ( m_indirectBuffer, 0, drawCommands.size (), drawCommands.constData () );

		QList<mat4> matrices ( data.shapes_.size () );
		qsizetype i = 0;
		foreach ( const DrawData & dd, data.shapes_ )
		{
			matrices [ i++ ] = data.scene_.globalTransforms_ [ dd.transformIndex ];
		}

		funcs->glNamedBufferSubData ( m_modelMatricesBuffer, 0, matrices.size () * sizeof ( mat4 ), matrices.constData () );	
	}

	DrawMesh::~DrawMesh ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glDeleteVertexArrays ( 1, &m_vao );
		funcs->glDeleteBuffers (1, &m_indexBuffer );
		funcs->glDeleteBuffers ( 1, &m_indirectBuffer );
		funcs->glDeleteBuffers ( 1, &m_modelMatricesBuffer );
		funcs->glDeleteBuffers ( 1, &m_materialsBuffer );
		funcs->glDeleteBuffers ( 1, &m_vertexBuffer );
	}

	void DrawMesh::draw ( const SceneData& data ) const
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();

		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glBindVertexArray ( m_vao );
		funcs->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kIdxBind_SSBOMaterials, m_materialsBuffer );
		funcs->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kIdxBind_SSBOModelMatrices, m_modelMatricesBuffer );
		funcs->glBindBuffer ( GL_DRAW_INDIRECT_BUFFER, m_indirectBuffer );
		funcs->glBindBuffer ( GL_PARAMETER_BUFFER, m_indirectBuffer );
//		funcs->glMultiDrawElementsIndirect ( GL_TRIANGLES, GL_UNSIGNED_INT, ( const void* ) sizeof ( GLsizei ), 0, 0 );
		glMultiDrawElementsIndirectCount ( GL_TRIANGLES, GL_UNSIGNED_INT, ( const void* ) sizeof ( GLsizei ), 0, ( GLsizei ) data.shapes_.size (), 0 );
	}
}
