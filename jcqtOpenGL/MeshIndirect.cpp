#include "MeshIndirect.h"

#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>

namespace jcqt
{
	IndirectBuffer::IndirectBuffer ( size_t maxDrawCommands )
		: m_drawCommands ( maxDrawCommands )
		, m_bufferIndirect(0)
	{
		initBuffer ();
	}

	void IndirectBuffer::uploadIndirectBuffer ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		funcs->glNamedBufferSubData ( m_bufferIndirect, 0, sizeof ( DrawElementsIndirectCommand ) * m_drawCommands.size (), m_drawCommands.constData () );
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

	void IndirectBuffer::initBuffer ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto funcs = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		const GLsizei kBufferSize = static_cast< GLsizei >( m_drawCommands.size () * sizeof ( DrawElementsIndirectCommand ) );

		funcs->glCreateBuffers ( 1, &m_bufferIndirect );

		funcs->glNamedBufferStorage ( m_bufferIndirect, kBufferSize, nullptr, GL_DYNAMIC_STORAGE_BIT );
	}

	template<typename SceneDataType>
	MeshIndirect<SceneDataType>::MeshIndirect ( const SceneDataType& data )
		: m_vao(0)
		, m_numIndices(data.m_header.indexDataSize / sizeof(quint32))
		, m_indexBuffer(0)
		, 
		, m_indirectBuffer(data.m_shapes.size())
	{}


	template<typename SceneDataType>
	inline MeshIndirect<SceneDataType>::~MeshIndirect ()
	{}
	template<typename SceneDataType>
	inline void MeshIndirect<SceneDataType>::draw ( size_t numDrawCommands, const IndirectBuffer* buffer ) const
	{}
	template<typename SceneDataType>
	inline void MeshIndirect<SceneDataType>::updateShaderStorageBuffer ( const SceneDataType& data, qsizetype index )
	{}
}
