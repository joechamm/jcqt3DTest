#include "MeshIndirect.h"

#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>

#include <q20functional.h>

#include "SceneData.h"

namespace jcqt
{
	using glm::vec2;

	IndirectBuffer::IndirectBuffer ( size_t maxDrawCommands )
		: m_drawCommands ( maxDrawCommands )
		, m_bufferIndirect(0)
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		const GLsizei kBufferSize = static_cast< GLsizei >(maxDrawCommands * sizeof ( DrawElementsIndirectCommand ) );

		funcs->glCreateBuffers ( 1, &m_bufferIndirect );
		funcs->glNamedBufferStorage ( m_bufferIndirect, kBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT );
	}

	IndirectBuffer::~IndirectBuffer ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glDeleteBuffers ( 1, &m_bufferIndirect );
	}

	void IndirectBuffer::uploadIndirectBuffer ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		const GLsizei kBufferSize = static_cast< GLsizei >( m_drawCommands.size () * sizeof ( DrawElementsIndirectCommand ) );

		funcs->glNamedBufferSubData ( m_bufferIndirect, 0, kBufferSize, m_drawCommands.constData () );
	}

	void IndirectBuffer::selectTo ( IndirectBuffer & buff, const std::function<bool ( const DrawElementsIndirectCommand& )>&predicate )
	{
		buff.m_drawCommands.clear ();
		foreach ( const DrawElementsIndirectCommand & cmd, m_drawCommands )
		{
			if ( predicate ( cmd ) )
				buff.m_drawCommands.push_back ( cmd );
		}

		buff.uploadIndirectBuffer ();
	}

	template<typename SceneDataType>
	MeshIndirect<SceneDataType>::MeshIndirect ( const SceneDataType& data )
		: m_vao(0)
		, m_numIndices(data.header_.indexDataSize / sizeof(quint32))
		, m_indexBuffer(0)
		, m_vertexBuffer(0)
		, m_materialsBuffer(0)
		, m_modelMatricesBuffer(0)
		, m_indirectBuffer(data.shapes_.size())
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		const GLsizei kIndexBufferSize = static_cast< GLsizei >( data.header_.indexDataSize );
		const GLsizei kVertexBufferSize = static_cast< GLsizei >( data.header_.vertexDataSize );
		const GLsizei kMaterialsBufferSize = static_cast< GLsizei >( data.materials_.size () * sizeof ( MaterialDescription ) );
		const GLsizei kModelMatricesBufferSize = static_cast< GLsizei >( data.shapes_.size () * sizeof ( mat4 ) );

		funcs->glCreateBuffers ( 1, &m_indexBuffer );
		funcs->glCreateBuffers ( 1, &m_vertexBuffer );
		funcs->glCreateBuffers ( 1, &m_materialsBuffer );
		funcs->glCreateBuffers ( 1, &m_modelMatricesBuffer );

		funcs->glNamedBufferStorage ( m_indexBuffer, kIndexBufferSize, data.meshData_.indexData_.constData (), 0 );
		funcs->glNamedBufferStorage ( m_vertexBuffer, kVertexBufferSize, data.meshData_.vertexData_.constData (), 0 );
		funcs->glNamedBufferStorage ( m_materialsBuffer, kMaterialsBufferSize, data.materials_.constData (), GL_DYNAMIC_STORAGE_BIT );
		funcs->glNamedBufferStorage ( m_modelMatricesBuffer, kModelMatricesBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT );

		funcs->glCreateVertexArrays ( 1, &m_vao );
		funcs->glVertexArrayElementBuffer ( m_vao, m_indexBuffer );
		funcs->glVertexArrayVertexBuffer ( m_vao, kIdxBind_VBOTightBuffer, m_vertexBuffer, 0, sizeof ( vec3 ) + sizeof ( vec3 ) + sizeof ( vec2 ) );

		// position
		funcs->glEnableVertexArrayAttrib ( m_vao, kIdxLoc_POSITION );
		funcs->glVertexArrayAttribFormat ( m_vao, kIdxLoc_POSITION, 3, GL_FLOAT, GL_FALSE, 0 );
		funcs->glVertexArrayAttribBinding ( m_vao, kIdxLoc_POSITION, kIdxBind_VBOTightBuffer );

		// uv 
		funcs->glEnableVertexArrayAttrib ( m_vao, kIdxLoc_TEXCOORD_0 );
		funcs->glVertexArrayAttribFormat ( m_vao, kIdxLoc_TEXCOORD_0, 2, GL_FLOAT, GL_FALSE, sizeof ( vec3 ) );
		funcs->glVertexArrayAttribBinding ( m_vao, kIdxLoc_TEXCOORD_0, kIdxBind_VBOTightBuffer );


		// normal
		funcs->glEnableVertexArrayAttrib ( m_vao, kIdxLoc_NORMAL );
		funcs->glVertexArrayAttribFormat ( m_vao, kIdxLoc_NORMAL, 3, GL_FLOAT, GL_FALSE, sizeof ( vec3 ) + sizeof ( vec2 ) );
		funcs->glVertexArrayAttribBinding ( m_vao, kIdxLoc_NORMAL, kIdxBind_VBOTightBuffer );

		QList<mat4> matrices ( data.shapes_.size () );

		// prepare indirect commands buffer
		for ( qsizetype i = 0; i != data.shapes_.size (); i++ )
		{
			const quint32 meshIdx = data.shapes_ [ i ].meshIndex;
			const quint32 lod = data.shapes_ [ i ].LOD;
			m_indirectBuffer.m_drawCommands [ i ] = {
				.m_count = data.meshData_.meshes_ [ meshIdx ].getLODIndicesCount ( lod ),
				.m_instanceCount = 1,
				.m_firstIndex = data.shapes_ [ i ].indexOffset,
				.m_baseVertex = data.shapes_ [ i ].vertexOffset,
				.m_baseInstance = data.shapes_ [ i ].materialIndex + ( quint32 ( i ) << 16 )
			};
			matrices [ i ] = data.scene_.globalTransforms_ [ data.shapes_ [ i ].transformIndex ];
		}

		m_indirectBuffer.uploadIndirectBuffer ();

		funcs->glNamedBufferSubData ( m_modelMatricesBuffer, 0, matrices.size () * sizeof ( mat4 ), matrices.constData () );
	}

	template <typename SceneDataType>
	void MeshIndirect<SceneDataType>::updateMaterialsBuffer ( const SceneDataType& data )
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glNamedBufferSubData ( m_materialsBuffer, 0, sizeof ( MaterialDescription ) * data.materials_.size (), data.materials_.constData () );
	}

	template <typename SceneDataType>
	void MeshIndirect<SceneDataType>::draw ( qsizetype numDrawCommands, const IndirectBuffer* buffer ) const
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glBindVertexArray ( m_vao );
		funcs->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kIdxBind_SSBOMaterials, m_materialsBuffer );
		funcs->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kIdxBind_SSBOModelMatrices, m_modelMatricesBuffer );
		funcs->glBindBuffer ( GL_DRAW_INDIRECT_BUFFER, ( buffer ? *buffer : m_indirectBuffer ).handle () );
		funcs->glMultiDrawElementsIndirect ( GL_TRIANGLES, GL_UNSIGNED_INT, nullptr, ( GLsizei ) numDrawCommands, 0 );
	}

	template <typename SceneDataType>
	MeshIndirect<SceneDataType>::~MeshIndirect ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glDeleteVertexArrays ( 1, &m_vao );
		funcs->glDeleteBuffers ( 1, &m_indexBuffer );
		funcs->glDeleteBuffers ( 1, &m_materialsBuffer );
		funcs->glDeleteBuffers ( 1, &m_modelMatricesBuffer );
		funcs->glDeleteBuffers ( 1, &m_vertexBuffer );
	}
}
