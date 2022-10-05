#include "LineCanvas.h"

#include <QOpenGLContext>
#include <QOpenGLVersionFunctionsFactory>
#include <QOpenGLFunctions_4_5_Core>

namespace jcqt
{
	MeshPVP::MeshPVP ( const QList<quint32>& indices, const void* vertexData, quint32 verticesSize )
		: m_numIndices ( static_cast< quint32 >( indices.size () ) )
		, m_indexBuffer ( 0 )
		, m_vertexBuffer ( 0 )
		, m_vao(0)
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		f->glCreateVertexArrays ( 1, &m_vao );
		f->glCreateBuffers ( 1, &m_indexBuffer );
		f->glCreateBuffers ( 1, &m_vertexBuffer );

		const GLsizei kIndexBufferSize = static_cast< GLsizei >( indices.size () * sizeof ( quint32 ) );
		const GLsizei kVertexBufferSize = static_cast< GLsizei >( verticesSize );

		f->glNamedBufferStorage ( m_vertexBuffer, kVertexBufferSize, vertexData, GL_DYNAMIC_STORAGE_BIT );

		if ( kIndexBufferSize )
		{
			f->glNamedBufferStorage ( m_indexBuffer, kIndexBufferSize, indices.constData (), 0 );
			f->glVertexArrayElementBuffer ( m_vao, m_indexBuffer );
		}
	}

	MeshPVP::~MeshPVP ()
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		f->glDeleteVertexArrays ( 1, &m_vao );
		f->glDeleteBuffers ( 1, &m_indexBuffer );
		f->glDeleteBuffers ( 1, &m_vertexBuffer );
	}

	void MeshPVP::drawElements ( GLenum mode ) const
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		f->glBindVertexArray ( m_vao );
		f->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kIdxBind_SSBOVertices, m_vertexBuffer );
		f->glDrawElements ( mode, static_cast< GLsizei >( m_numIndices ), GL_UNSIGNED_INT, nullptr );
	}

	void MeshPVP::drawArrays ( GLenum mode, GLint first, GLint count )
	{
		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		f->glBindVertexArray ( m_vao );
		f->glBindBufferBase ( GL_SHADER_STORAGE_BUFFER, kIdxBind_SSBOVertices, m_vertexBuffer );
		f->glDrawArrays ( mode, first, count );
	}

	LineCanvas::LineCanvas ()
	{
		m_linesProgram.create ( QOpenGLContext::currentContext () );
		m_linesProgram->addShaderFromSourceFile ( QOpenGLShader::Vertex, ":/shaders/GL_lines.vert" );
		m_linesProgram->addShaderFromSourceFile ( QOpenGLShader::Fragment, ":/shaders/GL_lines.frag" );
		m_linesProgram->link ();

		QList<quint32> emptyList;

		m_mesh.create ( emptyList, nullptr, sizeof ( VertexData ) * kMaxLines );
	}

	LineCanvas::~LineCanvas ()
	{
		m_mesh.clear ();
		m_linesProgram.clear ();
	}

	void LineCanvas::line ( const vec3& p1, const vec3& p2, const vec4& c )
	{
		m_lines.push_back ( { .position = p1, .color = c } );
		m_lines.push_back ( { .position = p2, .color = c } );
	}

	void LineCanvas::flush ()
	{
		if ( m_lines.isEmpty () ) return;

		assert ( m_lines.size () < kMaxLines );

		QOpenGLContext* ctx = QOpenGLContext::currentContext ();
		auto f = QOpenGLVersionFunctionsFactory::get<QOpenGLFunctions_4_5_Core> ( ctx );

		f->glNamedBufferSubData ( m_mesh->m_vertexBuffer, 0, static_cast< GLsizei >( m_lines.size () * sizeof ( VertexData ) ), m_lines.constData () );

		m_linesProgram->bind ();
		m_mesh->drawArrays ( GL_LINES, 0, ( GLint ) m_lines.size () );

		m_lines.clear ();
	}
}
