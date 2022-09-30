/*****************************************************************//**
 * \file   VtxData.h
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
#ifndef __VTX_DATA_H__
#define __VTX_DATA_H__

#include "jcqtopengl_global.h"
#include "UtilsMath.h"

namespace jcqt
{
	/**
	 * @brief we need two constants to define the limits on how many LODs and vertex streams we can have in a single mesh
	*/

	constexpr const quint32 kMaxLODs = 8;
	constexpr const quint32 kMaxStreams = 8;

	/**
	 * @brief Define an individual mesh description.
	 * We deliberately avoid using pointers that hide memory allocations and prohibit the simple saving and loading of data.
	 * We store offsets to individual data streams and LOD index buffers. They are equivalent to pointers but are more flexible and, most importantly, GPU-friendlier.
	 * All the offsets in the Mesh structure are given relative to the beginning of the data block.
	 * The LOD count, where the original mesh counts as one of the LODs, must be strictly less than kMaxLODs. This is because we do not store LOD index buffer sizes but calculate them from offsets.
	 * To calculate these sizes, we store one additional empty LOD level at the end. The number of vertex data streams is stored directly with no modifications.
	*/

	struct JCQTOPENGL_EXPORT Mesh final
	{
		/* Number of LODs in this mesh. Strictly less than MAX_LODS, last LOD offset is used as a marker only */
		quint32 lodCount = 1;

		/* Number of vertex data streams */
		quint32 streamCount = 0;

		/* The total count of all previous vertices in this mesh file */
		quint32 indexOffset = 0;

		quint32 vertexOffset = 0;

		/* Vertex count (for all LODs) */
		quint32 vertexCount = 0;

		/* Each mesh can potentially be displayed at different LODs. The file contains all the indices for all the LODs, and offsets to the beginning of each LOD are stored in the lodOffset array. This array contains one extra item at the end, which serves as a marker to calculate the size of the last LOD */
		quint32 lodOffset [ kMaxLODs ] = { 0 };

		/* Instead of storing the sizes of each LOD, we define a little helper function to calculate their sizes */
		inline quint32 getLODIndicesCount ( quint32 lod ) const
		{
			return lodOffset [ lod + 1 ] - lodOffset [ lod ];
		}

		/* streamOffset field stores offsets to all of the individual vertex data streams */
		/* IMPORTANT NOTE Besides the element size, we might want to store the element type, such as byte, short integer, or float. This information is important for performance reasons in real-world applications. To simplify the code in this book, we will not do it here */

		/* All the data "pointers" for all the streams */
		quint32 streamOffset [ kMaxStreams ] = { 0 };
		/* Information about stream element (size pretty much defines everything else, the "semantics" is defined by the shader) */
		quint32 streamElementSize [ kMaxStreams ] = { 0 };

		/*
		* We could have included the streamStride[] array here to allow interleaved storage of attributes. For this book we assume tightly-packed (non-interleaved) vertex attribute streams.
		*
		* Additional information, like mesh name, can be added here
		*/
	};

	struct JCQTOPENGL_EXPORT MeshFileHeader
	{
		/* To ensure data integrity and to check the validity of the header, a magic hexadecimal value of 0x12345678 is stored in the first 4 bytes of the header */
		quint32 magicValue;

		/* The number of different meshes in this file is stored in meshCount */
		quint32 meshCount;

		/* For convenience, store an offset to the the beginning of the mesh data */
		quint32 dataBlockStartOffset;

		/* store the sizes of index and vertex data in bytes to check the integrity of a mesh file */
		quint32 indexDataSize;
		quint32 vertexDataSize;
		/* Any additional meta data here*/
	};

	struct JCQTOPENGL_EXPORT DrawData
	{
		quint32 meshIndex;
		quint32 materialIndex;
		quint32 LOD;
		quint32 indexOffset;
		quint32 vertexOffset;
		quint32 transformIndex;
	};

	struct JCQTOPENGL_EXPORT MeshData
	{
		QList<quint32>		indexData_;
		QList<float>		vertexData_;
		QList<Mesh>			meshes_;
		QList<BoundingBox>	boxes_;
	};

	Q_STATIC_ASSERT ( sizeof ( DrawData ) == sizeof ( quint32 ) * 6 );
	Q_STATIC_ASSERT ( sizeof ( BoundingBox ) == sizeof ( float ) * 6 );

	MeshFileHeader JCQTOPENGL_EXPORT loadMeshData ( const char* meshFilename, MeshData& out );
	void JCQTOPENGL_EXPORT saveMeshData ( const char* filename, const MeshData& m );

	void JCQTOPENGL_EXPORT recalculateBoundingBoxes ( MeshData& m );

	// Combine a list of meshes to a single mesh container
	MeshFileHeader JCQTOPENGL_EXPORT mergeMeshData ( MeshData& m, const QList<MeshData*> md );
}

#endif // __VTX_DATA_H__