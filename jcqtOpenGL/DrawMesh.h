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

#include <QList>

#include "jcqtopengl_global.h"
#include "SceneData.h"

namespace jcqt
{
	/*struct JCQTOPENGL_EXPORT DrawElementsIndirectCommand
	{
		quint32 m_count;
		quint32 m_instanceCount;
		quint32 m_firstInstance;
		quint32 m_baseVertex;
		quint32 m_baseInstance;
	};*/

	class JCQTOPENGL_EXPORT DrawMesh final
	{
		quint32 m_vao = 0;
		quint32 m_indexBuffer;
		quint32 m_vertexBuffer;
		quint32 m_materialsBuffer;
		quint32 m_modelMatricesBuffer;
		quint32 m_indirectBuffer;
		quint32 m_numIndices;

	public:
		explicit DrawMesh ( const SceneData& data );
		~DrawMesh ();
		DrawMesh ( const DrawMesh& ) = delete;
		DrawMesh ( DrawMesh&& ) = default;

		void draw ( const SceneData& data ) const;		

		quint32 vao () const { return m_vao;  }
		quint32 indexBuffer () const { return m_indexBuffer;  }
		quint32 vertexBuffer () const { return m_vertexBuffer; }
		quint32 materialsBuffer () const { return m_materialsBuffer; }
		quint32 modelMatricesBuffer () const { return m_modelMatricesBuffer; }
		quint32 indirectBuffer () const { return m_indirectBuffer; }
		quint32 numIndices () const { return m_numIndices; }
	};
}

#endif // !__MESH_H__
