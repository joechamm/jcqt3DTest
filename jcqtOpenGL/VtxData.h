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

#include <QList>
#include <glm/glm.hpp>

using glm::mat4;
using glm::vec4;
using glm::vec3;

namespace jcqt
{
	struct JCQTOPENGL_EXPORT BoundingBox
	{
		vec3 min_;
		vec3 max_;
		BoundingBox () = default;
		BoundingBox ( const vec3& min, const vec3& max ) : min_ ( glm::min ( min, max ) ), max_ ( glm::max ( min, max ) ) {}
		BoundingBox ( const vec3* points, size_t numPoints )
		{
			vec3 vmin ( std::numeric_limits<float>::max () );
			vec3 vmax ( std::numeric_limits<float>::lowest () );

			for ( size_t i = 0; i != numPoints; i++ )
			{
				vmin = glm::min ( vmin, points [ i ] );
				vmax = glm::max ( vmax, points [ i ] );
			}

			min_ = vmin;
			max_ = vmax;
		}

		vec3 getSize () const { return vec3 ( max_ [ 0 ] - min_ [ 0 ], max_ [ 1 ] - min_ [ 1 ], max_ [ 2 ] - min_ [ 2 ] ); }
		vec3 getCenter () const { return 0.5f * vec3 ( max_ [ 0 ] + min_ [ 0 ], max_ [ 1 ] + min_ [ 1 ], max_ [ 2 ] + min_ [ 2 ] ); }

		void transform ( const mat4& t )
		{
			vec3 corners [] = {
				vec3 ( min_.x, min_.y, min_.z ),
				vec3 ( min_.x, max_.y, min_.z ),
				vec3 ( min_.x, min_.y, max_.z ),
				vec3 ( min_.x, max_.y, max_.z ),
				vec3 ( max_.x, min_.y, min_.z ),
				vec3 ( max_.x, max_.y, min_.z ),
				vec3 ( max_.x, min_.y, max_.z ),
				vec3 ( max_.x, max_.y, max_.z )
			};
			for ( auto& v : corners )
				v = vec3 ( t * vec4 ( v, 1.0f ) );

			*this = BoundingBox ( corners, 8 );
		}

		BoundingBox getTransformed ( const mat4& t ) const
		{
			BoundingBox b = *this;
			b.transform ( t );
			return b;
		}
		void combinePoint ( const vec3& p )
		{
			min_ = glm::min ( min_, p );
			max_ = glm::max ( max_, p );
		}
	};


	inline void JCQTOPENGL_EXPORT getFrustumPlanes ( const mat4& mvp, vec4* planes )
	{
		const mat4 trMVP = glm::transpose ( mvp );
		planes [ 0 ] = vec4 ( trMVP [ 3 ] + trMVP [ 0 ] ); // left
		planes [ 1 ] = vec4 ( trMVP [ 3 ] - trMVP [ 0 ] ); // right
		planes [ 2 ] = vec4 ( trMVP [ 3 ] + trMVP [ 1 ] ); // bottom
		planes [ 3 ] = vec4 ( trMVP [ 3 ] - trMVP [ 1 ] ); // top
		planes [ 4 ] = vec4 ( trMVP [ 3 ] + trMVP [ 2 ] ); // near
		planes [ 5 ] = vec4 ( trMVP [ 3 ] - trMVP [ 2 ] ); // far
	}

	inline void JCQTOPENGL_EXPORT getFrustumCorners ( const mat4& mvp, vec4* points )
	{
		const vec4 corners [] = {
			vec4 ( -1, -1, -1, 1 ), vec4 ( 1, -1, -1, 1 ),
			vec4 ( 1, 1, -1, 1 ), vec4 ( -1, 1, -1, 1 ),
			vec4 ( -1, -1, 1, 1 ), vec4 ( 1, -1, 1, 1 ),
			vec4 ( 1, 1, 1, 1 ), vec4 ( -1, 1, 1, 1 )
		};

		const mat4 invMVP = glm::inverse ( mvp );

		for ( int i = 0; i != 8; i++ )
		{
			const vec4 q = invMVP * corners [ i ];
			points [ i ] = q / q.w;
		}
	}

	inline bool JCQTOPENGL_EXPORT isBoxInFrustum ( vec4* frustumPlanes, vec4* frustumCorners, const BoundingBox& box )
	{
		using glm::dot;		

		for ( int i = 0; i < 6; i++ )
		{
			int r = 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.min_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.min_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.max_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.max_.y, box.min_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.min_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.min_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.min_.x, box.max_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			r += ( dot ( frustumPlanes [ i ], vec4 ( box.max_.x, box.max_.y, box.max_.z, 1.0f ) ) < 0.0 ) ? 1 : 0;
			if ( r == 8 ) return false;
		}

		// check frustum outside/inside box
		int r = 0;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].x > box.max_.x ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].x < box.min_.x ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].y > box.max_.y ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].y < box.min_.y ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].z > box.max_.z ) ? 1 : 0 ); if ( r == 8 ) return false;
		r = 0; for ( int i = 0; i < 8; i++ ) r += ( ( frustumCorners [ i ].z > box.min_.z ) ? 1 : 0 ); if ( r == 8 ) return false;

		return true;
	}

	inline BoundingBox JCQTOPENGL_EXPORT combineBoxes ( const QList<BoundingBox>& boxes )
	{
		QList<vec3> allPoints;
		allPoints.reserve ( boxes.size () * 8 );

		foreach ( const BoundingBox & b, boxes )
		{
			allPoints.emplace_back ( b.min_.x, b.min_.y, b.min_.z );
			allPoints.emplace_back ( b.min_.x, b.min_.y, b.max_.z );
			allPoints.emplace_back ( b.min_.x, b.max_.y, b.min_.z );
			allPoints.emplace_back ( b.min_.x, b.max_.y, b.max_.z );

			allPoints.emplace_back ( b.max_.x, b.min_.y, b.min_.z );
			allPoints.emplace_back ( b.max_.x, b.min_.y, b.max_.z );
			allPoints.emplace_back ( b.max_.x, b.max_.y, b.min_.z );
			allPoints.emplace_back ( b.max_.x, b.max_.y, b.max_.z );
		}

		return BoundingBox ( allPoints.data (), allPoints.size () );
	}

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

	struct Mesh final
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

	struct MeshFileHeader
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

	struct DrawData
	{
		quint32 meshIndex;
		quint32 materialIndex;
		quint32 LOD;
		quint32 indexOffset;
		quint32 vertexOffset;
		quint32 transformIndex;
	};

	struct MeshData
	{
		QList<quint32>		indexData_;
		QList<float>			vertexData_;
		QList<Mesh>			meshes_;
		QList<BoundingBox>	boxes_;
	};

	static_assert( sizeof ( DrawData ) == sizeof ( quint32 ) * 6 );
	static_assert( sizeof ( BoundingBox ) == sizeof ( float ) * 6 );

	MeshFileHeader loadMeshData ( const char* meshFilename, MeshData& out );
	void saveMeshData ( const char* filename, const MeshData& m );

	void recalculateBoundingBoxes ( MeshData& m );

	// Combine a list of meshes to a single mesh container
	MeshFileHeader mergeMeshData ( MeshData& m, const QList<MeshData*> md );
}

#endif // __VTX_DATA_H__