#include "VtxData.h"

#include <QFile>
#include <QFileInfo>
#include <q20algorithm.h>

namespace jcqt
{
	MeshFileHeader loadMeshData ( const char* meshFilename, MeshData& out )
	{
		MeshFileHeader header;
		/* Open mesh file as raw binary*/
		QFile f ( meshFilename );

		if ( !f.open ( QIODeviceBase::ReadOnly ) )
		{
			qWarning ( "Cannot open %s. Did you forget to run MeshConvert?\n", meshFilename );
			exit ( EXIT_FAILURE );
		}

		/* read the header file */
		f.read ( ( char* ) &header, sizeof ( header ) );

		/* resize the mesh descriptors arrray and read in all the Mesh descriptions */
		out.meshes_.resize ( header.meshCount );

		f.read ( ( char* ) out.meshes_.data (), sizeof ( Mesh ) * header.meshCount );

		out.boxes_.resize ( header.meshCount );

		f.read ( ( char* ) out.boxes_.data (), sizeof ( BoundingBox ) * header.meshCount );

		out.indexData_.resize ( static_cast< qsizetype >( header.indexDataSize / sizeof ( quint32 ) ) );
		out.vertexData_.resize ( static_cast< qsizetype >( header.vertexDataSize / sizeof ( float ) ) );

		f.read ( ( char* ) out.indexData_.data (), header.indexDataSize );
		f.read ( ( char* ) out.vertexData_.data (), header.vertexDataSize );

		f.close ();

		return header;
	}

	void saveMeshData ( const char* filename, const MeshData& m )
	{
		QFile f ( filename );

		if ( !f.open ( QIODeviceBase::WriteOnly ) )
		{
			qWarning ( "Cannot open %s. Exiting...\n", filename );
			exit ( EXIT_FAILURE );
		}

		const MeshFileHeader header = {
			.magicValue = 0x12345678,
			.meshCount = static_cast< quint32 >( m.meshes_.size () ),
			.dataBlockStartOffset = static_cast< quint32 >( sizeof ( MeshFileHeader ) + m.meshes_.size () * sizeof ( Mesh ) ),
			.indexDataSize = static_cast<quint32 >( m.indexData_.size () * sizeof ( quint32 ) ),
			.vertexDataSize = static_cast< quint32 >( m.vertexData_.size () * sizeof ( float ) )
		};

		f.write ( ( const char* ) &header, sizeof ( header ) );
		f.write ( ( const char* ) m.meshes_.constData (), sizeof ( Mesh ) * header.meshCount );
		f.write ( ( const char* ) m.boxes_.constData (), sizeof ( BoundingBox ) * header.meshCount );
		f.write ( ( const char* ) m.indexData_.constData (), header.indexDataSize );
		f.write ( ( const char* ) m.vertexData_.constData (), header.vertexDataSize );

		f.close ();
	}

	void saveBoundingBoxes ( const char* filename, const QList<BoundingBox>& boxes )
	{
		QFile f ( filename );

		if ( !f.open ( QIODeviceBase::WriteOnly ) )
		{
			qWarning ( "Cannot open %s. Exiting...\n", filename );
			exit ( EXIT_FAILURE );
		}

		const quint32 sz = static_cast< quint32 >( boxes.size () );

		f.write ( ( const char* ) &sz, sizeof ( sz ) );
		f.write ( ( const char* ) boxes.constData (), sz * sizeof ( BoundingBox ) );

		f.close ();
	}

	void loadBoundingBoxes ( const char* filename, QList<BoundingBox>& boxes )
	{
		QFile f ( filename );

		if ( !f.open ( QIODeviceBase::ReadOnly ) )
		{
			qWarning ( "Cannot open %s. Did you forget to run MeshConvert?\n", filename );
			exit ( EXIT_FAILURE );
		}

		quint32 sz;
		f.read ( ( char* ) &sz, sizeof ( sz ) );

		// TODO: check file size, divide by bounding box size
		boxes.resize ( ( qsizetype ) sz );
		fread ( ( char* ) boxes.data (), sz * sizeof ( BoundingBox ) );

		f.close ();
	}

	// Combine a list of meshes to a single mesh container
	MeshFileHeader mergeMeshData ( MeshData& m, const QList<MeshData*> md )
	{
		quint32 totalVertexDataSize = 0;
		quint32 totalIndexDataSize = 0;

		quint32 offs = 0;
		for ( const MeshData* i : md )
		{
			mergeVectors ( m.indexData_, i->indexData_ );
			mergeVectors ( m.vertexData_, i->vertexData_ );
			mergeVectors ( m.meshes_, i->meshes_ );
			mergeVectors ( m.boxes_, i->boxes_ );

			quint32 vtxOffset = totalVertexDataSize / 8; /* 8 is the number of per-vertex attributes: position, normal + UV */

			for ( size_t j = 0; j < ( quint32 ) i->meshes_.size (); j++ )
			{
				// m.vertexCount, m.lodCount and m.streamCount do not change
				// m.vertexOffset also does not change, because vertex offsets are local (i.e., baked into the indices)
				m.meshes_ [ offs + j ].indexOffset += totalIndexDataSize;
			}

			// shift individual indices
			for ( size_t j = 0; j < i->indexData_.size (); j++ )
			{
				m.indexData_ [ totalIndexDataSize + j ] += vtxOffset;
			}

			offs += ( quint32 ) i->meshes_.size ();

			totalIndexDataSize += ( quint32 ) i->indexData_.size ();
			totalVertexDataSize += ( quint32 ) i->vertexData_.size ();
		}

		return MeshFileHeader {
			.magicValue = 0x12345678,
			.meshCount = static_cast< quint32 >( offs ),
			.dataBlockStartOffset = static_cast< quint32 >( sizeof ( MeshFileHeader ) + offs * sizeof ( Mesh ) ),
			.indexDataSize = static_cast< quint32 >( totalIndexDataSize * sizeof ( quint32 ) ),
			.vertexDataSize = static_cast< quint32 >( totalVertexDataSize * sizeof ( float ) )
		};
	}

	void recalculateBoundingBoxes ( MeshData& m )
	{
		m.boxes_.clear ();
		
		foreach ( const Mesh & mesh, m.meshes_ )
		{
			const quint32 numIndices = mesh.getLODIndicesCount ( 0 );

			vec3 vmin ( std::numeric_limits<float>::max () );
			vec3 vmax ( std::numeric_limits<float>::lowest () );

			for ( quint32 i = 0; i != numIndices; i++ )
			{
				quint32 vtxOffset = m.indexData_ [ mesh.indexOffset + i ] + mesh.vertexOffset;
				const float* vf = &m.vertexData_ [ vtxOffset * kMaxStreams ];
				vmin = glm::min ( vmin, vec3 ( vf [ 0 ], vf [ 1 ], vf [ 2 ] ) );
				vmax = glm::max ( vmax, vec3 ( vf [ 0 ], vf [ 1 ], vf [ 2 ] ) );
			}
		}
	}
}
