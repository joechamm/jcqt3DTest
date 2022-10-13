/*****************************************************************//**
 * \file   LineCanvas.h
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
#ifndef __LINE_CANVAS_H__
#define __LINE_CANVAS_H__

#include "jcqtopengl_global.h"
#include "VtxData.h"

#include <QOpenGLShaderProgram>
#include <QSharedPointer>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

namespace jcqt
{
	using glm::mat4;
	using glm::vec4;
	using glm::vec3;
	using glm::vec2;

	struct VertexData
	{
		vec3 pos;
		vec3 n;
		vec2 tc;
	};

	class JCQTOPENGL_EXPORT MeshPVP final
	{
	public:
		GLuint m_vao;

		quint32 m_numIndices;

		GLuint m_indexBuffer;
		GLuint m_vertexBuffer;

	public:
		MeshPVP ( const QList<quint32>& indices, const void* vertexData, quint32 verticesSize );
		~MeshPVP ();

		void drawElements ( GLenum mode = GL_TRIANGLES ) const;
		void drawArrays ( GLenum mode, GLint first, GLint count );
	};

	class JCQTOPENGL_EXPORT LineCanvas final
	{
		static constexpr quint32 kMaxLines = 1024 * 1024;

		struct VertexData
		{
			vec3 position;
			vec4 color;
		};

		QList<VertexData>						m_lines;
		QSharedPointer<QOpenGLShaderProgram>	m_linesProgram;
		QSharedPointer<MeshPVP>					m_mesh;

	public:
		LineCanvas ();
		~LineCanvas ();

		void line ( const vec3& p1, const vec3& p2, const vec4& c );
		void flush ();
	};

	inline void JCQTOPENGL_EXPORT renderCameraFrustum ( LineCanvas& canvas, const mat4& camView, const mat4& camProj, const vec4& color, qint32 numSegments = 1 )
	{
		const vec4 corners [] = {
			vec4 ( -1.f, -1.f, -1.f, 1.f ), vec4 ( 1.f, -1.f, -1.f, 1.f ),
			vec4 ( 1.f, 1.f, -1.f, 1.f ), vec4 ( -1.f, 1.f, -1.f, 1.f ),
			vec4 ( -1.f, -1.f, 1.f, 1.f ), vec4 ( 1.f, -1.f, 1.f, 1.f ),
			vec4 ( 1.f, 1.f, 1.f, 1.f ), vec4 ( -1.f, 1.f, 1.f, 1.f )
		};

		vec3 pp [ 8 ];

		const mat4 invMVP = glm::inverse ( camProj * camView );

		for ( qint32 i = 0; i < 8; i++ )
		{
			const vec4 q = invMVP * corners [ i ];
			pp [ i ] = vec3 ( q ) / q.w;
		}

		canvas.line ( pp [ 0 ], pp [ 4 ], color );
		canvas.line ( pp [ 1 ], pp [ 5 ], color );
		canvas.line ( pp [ 2 ], pp [ 6 ], color );
		canvas.line ( pp [ 3 ], pp [ 7 ], color );
		// near
		canvas.line ( pp [ 0 ], pp [ 1 ], color );
		canvas.line ( pp [ 1 ], pp [ 2 ], color );
		canvas.line ( pp [ 2 ], pp [ 3 ], color );
		canvas.line ( pp [ 3 ], pp [ 0 ], color );
		// x
		canvas.line ( pp [ 0 ], pp [ 2 ], color );
		canvas.line ( pp [ 1 ], pp [ 3 ], color );
		// far
		canvas.line ( pp [ 4 ], pp [ 5 ], color );
		canvas.line ( pp [ 5 ], pp [ 6 ], color );
		canvas.line ( pp [ 6 ], pp [ 7 ], color );
		canvas.line ( pp [ 7 ], pp [ 4 ], color );
		// x
		canvas.line ( pp [ 4 ], pp [ 6 ], color );
		canvas.line ( pp [ 5 ], pp [ 7 ], color );

		const float dimFactor = 0.7f;

		// bottom
		{
			vec3 p1 = pp [ 0 ];
			vec3 p2 = pp [ 1 ];
			const vec3 s1 = glm::normalize ( pp [ 4 ] - pp [ 0 ] );
			const vec3 s2 = glm::normalize ( pp [ 5 ] - pp [ 1 ] );
			for ( qint32 i = 0; i != numSegments; i++, p1 += s1, p2 += s2 )
			{
				canvas.line ( p1, p2, color * dimFactor );
			}
		}

		// left
		{
			vec3 p1 = pp [ 0 ];
			vec3 p2 = pp [ 3 ];
			const vec3 s1 = glm::normalize ( pp [ 4 ] - pp [ 0 ] );
			const vec3 s2 = glm::normalize ( pp [ 7 ] - pp [ 3 ] );
			for ( qint32 i = 0; i != numSegments; i++, p1 += s1, p2 += s2 )
			{
				canvas.line ( p1, p2, color * dimFactor );
			}
		}

		// right
		{
			vec3 p1 = pp [ 1 ];
			vec3 p2 = pp [ 2 ];
			const vec3 s1 = glm::normalize ( pp [ 5 ] - pp [ 1 ] );
			const vec3 s2 = glm::normalize ( pp [ 6 ] - pp [ 2 ] );
			for ( qint32 i = 0; i != numSegments; i++, p1 += s1, p2 += s2 )
			{
				canvas.line ( p1, p2, color * dimFactor );
			}
		}
	}

	inline void JCQTOPENGL_EXPORT drawBox ( LineCanvas& canvas, const mat4& m, const BoundingBox& box, const vec4& color )
	{
		QVarLengthArray<vec3, 8> pp = {
			vec3 ( box.max_.x, box.max_.y, box.max_.z ),
			vec3 ( box.max_.x, box.max_.y, box.min_.z ),
			vec3 ( box.max_.x, box.min_.y, box.max_.z ),
			vec3 ( box.max_.x, box.min_.y, box.min_.z ),

			vec3 ( box.min_.x, box.max_.y, box.max_.z ),
			vec3 ( box.min_.x, box.max_.y, box.min_.z ),
			vec3 ( box.min_.x, box.min_.y, box.max_.z ),
			vec3 ( box.min_.x, box.min_.y, box.min_.z )
		};

		for ( vec3& p : pp )
		{
			p = vec3 ( m * vec4 ( p, 1.0f ) );
		}

		canvas.line ( pp [ 0 ], pp [ 1 ], color );
		canvas.line ( pp [ 2 ], pp [ 3 ], color );
		canvas.line ( pp [ 4 ], pp [ 5 ], color );
		canvas.line ( pp [ 6 ], pp [ 7 ], color );

		canvas.line ( pp [ 0 ], pp [ 2 ], color );
		canvas.line ( pp [ 1 ], pp [ 3 ], color );
		canvas.line ( pp [ 4 ], pp [ 6 ], color );
		canvas.line ( pp [ 5 ], pp [ 7 ], color );

		canvas.line ( pp [ 0 ], pp [ 4 ], color );
		canvas.line ( pp [ 1 ], pp [ 5 ], color );
		canvas.line ( pp [ 2 ], pp [ 6 ], color );
		canvas.line ( pp [ 3 ], pp [ 7 ], color );
	}
}

#endif // !__LINE_CANVAS_H__
