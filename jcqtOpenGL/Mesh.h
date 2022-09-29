/*****************************************************************//**
 * \file   Mesh.h
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
#ifndef __MESH_H__
#define __MESH_H__

#include <q20functional.h>

#include <QOpenGLContext>
#include <QList>

#include "jcqtopengl_global.h"

namespace jcqt
{
	struct JCQTOPENGL_EXPORT DrawElementsIndirectCommand
	{
		GLuint m_count;
		GLuint m_instanceCount;
		GLuint m_firstInstance;
		GLuint m_baseVertex;
		GLuint m_baseInstance;
	};

	class JCQTOPENGL_EXPORT IndirectBuffer final
	{
	public:
		explicit IndirectBuffer ( size_t maxDrawCommands );

		GLuint handle () const { return m_bufferIndirect; }

		void uploadIndirectBuffer ();

		void selectTo ( IndirectBuffer& buff, const std::function<bool ( const DrawElementsIndirectCommand& )>& predicate );

	private:
		void initBuffer ();

	private:
		GLuint m_bufferIndirect = 0;

	public:
		QList<DrawElementsIndirectCommand> m_drawCommands;
	};

	class JCQTOPENGL_EXPORT DrawMesh final
	{
		GLuint m_vao = 0;
		GLuint m_indexBuffer;
		GLuint m_vertexBuffer;
		GLuint m_materialsBuffer;
		GLuint m_modelMatricesBuffer;
		quint32 m_numIndices;
		IndirectBuffer m_indirectBuffer;

	public:
		
	};

	template <typename SceneDataType>
	class JCQTOPENGL_EXPORT MeshIndirect final
	{
	public:
		explicit MeshIndirect ( const SceneDataType& data );
		MeshIndirect ( const MeshIndirect& ) = delete;
		MeshIndirect ( MeshIndirect&& ) = default;
		~MeshIndirect ();

		void draw ( size_t numDrawCommands, const IndirectBuffer* buffer = nullptr ) const;

		void updateShaderStorageBuffer ( const SceneDataType& data, qsizetype index );

	private:
		GLuint m_vao = 0;
		GLuint m_indexBuffer = 0;
		quint32 m_numIndices = 0;
		IndirectBuffer m_indirectBuffer;
		QList<GLuint> m_vertexBuffers;
		QList<GLuint> m_shaderStorageBuffers;
		QList<GLuint> m_vertexBufferBindings;
		QList<GLuint> m_shaderStorageBufferBindings;
	};

}

#endif // !__MESH_H__
