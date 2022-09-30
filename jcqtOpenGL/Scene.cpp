#include "Scene.h"
#include "Utils.h"

#include <QFile>

namespace jcqt
{
	extern void saveStringList ( QFile* f, const QByteArrayList& lines );
	extern void loadStringList ( QFile* f, QByteArrayList& lines );

	qint32 addNode ( Scene& scene, qint32 parent, qint32 level )
	{
		qint32 node = ( qint32 ) scene.hierarchy_.size ();
		{
			// TODO: resize aux arrays (local/global etc.)
			scene.localTransforms_.push_back ( mat4 ( 1.0f ) );
			scene.globalTransforms_.push_back ( mat4 ( 1.0f ) );
		}

		scene.hierarchy_.push_back ( { .parent_ = parent, .lastSibling_ = -1 } );

		/*
		*	If we have a parent, we must fix its first child referenceand, potentially, the next sibling reference of some other node.
		*	If a parent node has no children, we must directly set its firstChild_ field; otherwise,
		*	we should run over the sibliings of this child to find out where to add the next sibling.
		*/
		if ( parent > -1 )
		{
			qint32 s = scene.hierarchy_ [ parent ].firstChild_;
			if ( s == -1 )
			{
				scene.hierarchy_ [ parent ].firstChild_ = node;
				scene.hierarchy_ [ node ].lastSibling_ = node;
			}
			else
			{
				qint32 dest = scene.hierarchy_ [ s ].lastSibling_;
				if ( dest <= -1 )
				{
					// no cached lastSibling, iterate nextSibling indices
					for ( dest = s; scene.hierarchy_ [ dest ].nextSibling_ != -1; dest = scene.hierarchy_ [ dest ].nextSibling_ );
				}

				/*
				* After the for loop, we assign our new node as the next sibling of the last child.
				*/

				scene.hierarchy_ [ dest ].nextSibling_ = node;
				scene.hierarchy_ [ s ].lastSibling_ = node;
			}
		}

		/* The level of this node is stored for correct global transformation updating. To keep the structure valid, we store the negative indices for the newly added node. */

		scene.hierarchy_ [ node ].level_ = level;
		scene.hierarchy_ [ node ].nextSibling_ = -1;
		scene.hierarchy_ [ node ].firstChild_ = -1;
		return node;
	}

	void markAsChanged ( Scene& scene, qint32 node )
	{
		// First, the node itself is marked as changed
		qint32 level = scene.hierarchy_ [ node ].level_;
		scene.changedAtThisFrame_ [ level ].push_back ( node );

		// start from the first child and advance to the next sibling, descending into the hierarchy.
		for ( qint32 s = scene.hierarchy_ [ node ].firstChild_; s != -1; s = scene.hierarchy_ [ s ].nextSibling_ )
		{
			markAsChanged ( scene, s );
		}
	}

	qint32 findNodeByName ( const Scene& scene, const QByteArray& name )
	{
		// Extremely simple linear search without any hierarchreference
		// To support DFS/BFS searches separate travertsal routines are needed
		for ( qsizetype i = 0; i < scene.localTransforms_.size (); i++ )
		{
			if ( scene.nameForNode_.contains ( i ) )
			{
				qint32 strID = scene.nameForNode_.value ( i );
				if ( strID > -1 )
				{
					if ( scene.names_ [ strID ] == name )
						return ( qint32 ) i;
				}
			}
		}

		return -1;
	}

	qint32 getNodeLevel ( const Scene& scene, qint32 n )
	{
		qint32 level = -1;
		for ( qint32 p = 0; p != -1; p = scene.hierarchy_ [ p ].parent_, level++ );
		return level;
	}

	bool mat4IsIdentity ( const mat4& m );
	void fprintfMat4 ( QFile* F, const mat4& m );

	// CPU version of global transforms update []
	void recalculateGlobalTransforms ( Scene& scene )
	{
		// Start from the root layer of the list of changed scene nodes, supposing we have only one root node. This is because root node global transforms coincide with their local transforms. The changed nodes list is then cleared.
		if ( !scene.changedAtThisFrame_ [ 0 ].empty () )
		{
			qint32 c = scene.changedAtThisFrame_ [ 0 ][ 0 ];
			scene.globalTransforms_ [ c ] = scene.localTransforms_ [ c ];
			scene.changedAtThisFrame_ [ 0 ].clear ();
		}

		/*
		*	For all the lower levels, we must ensure that we have parents so that the loops are linear and there are no conditions inside.
		*	We will start from level 1 because the root level is already being handled. The exit condition is the emptiness of the list at the current level.
		*	We will avoid descending deeper than our list allows.
		*/

		for ( qint32 i = 1; i < MAX_NODE_LEVEL && ( !scene.changedAtThisFrame_ [ i ].empty () ); i++ )
		{
			// Iterate all the changed nodes at this level. For each of the iterated nodes, we fetch the parent transform and multiply it by the local node transform.
			for ( const int& c : scene.changedAtThisFrame_ [ i ] )
			{
				qint32 p = scene.hierarchy_ [ c ].parent_;
				scene.globalTransforms_ [ c ] = scene.globalTransforms_ [ p ] * scene.localTransforms_ [ c ];
			}

			// Clear the list for this level once we're done.
			scene.changedAtThisFrame_ [ i ].clear ();
		}

		/* Since we start from the root layer of the scen graph tree, all the changed layers below the root acquire a valid global transformation for thier parents, and we do not have to recalculate any of the global transformations multiple times. */
	}

	void loadMap ( QFile* f, QHash<quint32, quint32>& map )
	{
		QList<quint32> ms;

		/* Read the count of {key, value} pairs and resize our temporary storage */
		quint32 sz = 0;
		f->read ( ( char* ) &sz, sizeof ( sz ) );
		ms.resize ( sz );

		/* Read all the key-value pairs into ms */
		f->read ( ( char* ) ms.data (), sizeof ( qint32 ) * sz );

		/* Convert the array into our hash table */
		for ( size_t i = 0; i < ( sz / 2 ); i++ )
		{
			map [ ms [ i * 2 + 0 ] ] = ms [ i * 2 + 1 ];
		}
	}

	void loadScene ( const char* filename, Scene& scene )
	{
		QFile f ( filename );
		if ( !f.open ( QIODeviceBase::ReadOnly ) )
		{
			qWarning ( "Cannot open scene file '%s'. Please run SceneConverter from Chapter7 and/or MergeMeshes from Chapter 9", filename );
			return;
		}

		quint32 sz;
		f.read ( ( char* ) &sz, sizeof ( sz ) );

		scene.hierarchy_.resize ( sz );
		scene.globalTransforms_.resize ( sz );
		scene.localTransforms_.resize ( sz );
		// TODO: check > -1
		// TODO: recalculate changedAtThisLevel() - find max depth of a node [or save scene.maxLevel]

		f.read ( ( char* ) scene.localTransforms_.data (), sizeof ( mat4 ) * sz );
		f.read ( ( char* ) scene.globalTransforms_.data (), sizeof ( mat4 ) * sz );
		f.read ( ( char* ) scene.hierarchy_.data (), sizeof ( Hierarchy ) * sz );

		// Mesh for node [index to some list of buffers]
		loadMap ( &f, scene.materialForNode_ );
		loadMap ( &f, scene.meshes_ );

		if ( !f.atEnd () )
		{
			loadMap ( &f, scene.nameForNode_ );
			loadStringList ( &f, scene.names_ );
			loadStringList ( &f, scene.materialNames_ );
		}

		f.close ();
	}

	void saveMap ( QFile* f, const QHash<quint32, quint32>& map )
	{
		/* our temporary storage structure */
		QList<quint32> ms;
		ms.reserve ( map.size () * 2 );

		/* copy the elements ouf our map to our temporary storage */
		QHashIterator<quint32, quint32> it ( map );
		while ( it.hasNext () )
		{
			it.next ();
			ms.push_back ( it.key () );
			ms.push_back ( it.value () );
		}

		/* write the number of {key,value} pairs to our file then write the data */
		const quint32 sz = static_cast< quint32 >( ms.size () );

		f->write ( ( const char* ) &sz, sizeof ( sz ) );
		f->write ( ( const char* ) ms.constData (), sizeof ( qint32 ) * ms.size () );
	}

	void saveScene ( const char* filename, const Scene& scene )
	{
		/* At the beginning of the file, we must write the count of scene nodes. */
		QFile f( filename );

		if ( !f.open ( QIODeviceBase::WriteOnly ) )
		{
			qWarning ( "Failed to open file %s. Cannot save scene.\nExiting...\n", filename );
			exit ( EXIT_FAILURE );
		}

		const quint32 sz = ( quint32 ) scene.hierarchy_.size ();
		f.write ( ( const char* ) &sz, sizeof ( sz ) );
		
		f.write ( (const char*)scene.localTransforms_.data (), sizeof ( mat4 ) * sz );
		f.write ( (const char*)scene.globalTransforms_.data (), sizeof ( mat4 ) * sz );
		f.write ((const char*) scene.hierarchy_.data (), sizeof ( Hierarchy ) * sz );

		// Mesh for node [index to some list of buffers]
		saveMap ( &f, scene.materialForNode_ );
		saveMap ( &f, scene.meshes_ );

		if ( !scene.names_.empty () && !scene.nameForNode_.empty () )
		{
			saveMap ( &f, scene.nameForNode_ );
			saveStringList ( &f, scene.names_ );
			saveStringList ( &f, scene.materialNames_ );
		}

		f.close ();
	}

	bool mat4IsIdentity ( const mat4& m )
	{
		return ( m [ 0 ][ 0 ] == 1 && m [ 0 ][ 1 ] == 0 && m [ 0 ][ 2 ] == 0 && m [ 0 ][ 3 ] == 0 &&
			m [ 1 ][ 0 ] == 0 && m [ 1 ][ 1 ] == 1 && m [ 1 ][ 2 ] == 0 && m [ 1 ][ 3 ] == 0 &&
			m [ 2 ][ 0 ] == 0 && m [ 2 ][ 1 ] == 0 && m [ 2 ][ 2 ] == 1 && m [ 2 ][ 3 ] == 0 &&
			m [ 3 ][ 0 ] == 0 && m [ 3 ][ 1 ] == 0 && m [ 3 ][ 2 ] == 0 && m [ 3 ][ 3 ] == 1 );
	}

	void fprintfMat4 ( QFile* f, const mat4& m )
	{
		if ( mat4IsIdentity ( m ) )
		{
			f->write ( "Identity\n" );
		}
		else
		{
			f->write ( "\n" );
			for ( qint32 i = 0; i < 4; i++ )
			{
				for ( qint32 j = 0; j < 4; j++ )
				{
					QByteArray el = QByteArray::number (( double ) m [i][j]) + " ;";
					f->write ( el );
				}
				f->write ( "\n" );				
			}
		}
	}

	void dumpTransformations ( const char* filename, const Scene& scene )
	{
		QFile f ( filename );
		if ( !f.open ( QIODeviceBase::Append ) )
		{
			qWarning ( "Failed to open file %s. Cannot dump transforms.\nExiting...\n", filename );
			exit ( EXIT_FAILURE );
		}

		for ( qsizetype i = 0; i < scene.localTransforms_.size (); i++ )
		{
			QByteArray nltStr = "Node[" + QByteArray::number ( i ) + "].localTransform: ";
			f.write ( nltStr );
			fprintfMat4 ( &f, scene.localTransforms_ [ i ] );

			QByteArray ngtStr = "Node[" + QByteArray::number ( i ) + "].globalTransform: ";
			f.write ( ngtStr );
			fprintfMat4 ( &f, scene.globalTransforms_ [ i ] );

			QByteArray ndetStr = "Node[" + QByteArray::number ( i ) + "].globalDet = " + QByteArray::number ( glm::determinant ( scene.globalTransforms_ [ i ] ) ) + "; localDet = " + QByteArray::number ( glm::determinant ( scene.localTransforms_ [ i ] ) ) + "\n";
			f.write ( ndetStr );
		}

		f.close ();
	}

	//void printChagedNodes ( const Scene& scene )
	//{
	//	for ( qint32 i = 0; i < MAX_NODE_LEVEL && ( !scene.changedAtThisFrame_ [ i ].empty () ); i++ )
	//	{
	//		printf ( "Changed at level(%d):\n", i );

	//		for ( const qint32& c : scene.changedAtThisFrame_ [ i ] )
	//		{
	//			qint32 p = scene.hierarchy_ [ c ].parent_;
	//			//scene.globalTransform_[c] = scene.globalTransform_[p] * scene.localTransform_[c];
	//			printf ( " Node %d. Parent = %d; LocalTransform: ", c, p );
	//			
	//			fprintfMat4 ( stdout, scene.localTransforms_ [ i ] );
	//			if ( p > -1 )
	//			{
	//				printf ( " ParentGlobalTransform: " );
	//				fprintfMat4 ( stdout, scene.globalTransforms_ [ p ] );
	//			}
	//		}
	//	}
	//}

	// Shift all hierarchy components in the nodes
	void shiftNodes ( Scene& scene, qint32 startOffset, qint32 nodeCount, qint32 shiftAmount )
	{
		auto shiftNode = [shiftAmount] ( Hierarchy& node )
		{
			if ( node.parent_ > -1 )
				node.parent_ += shiftAmount;
			if ( node.firstChild_ > -1 )
				node.firstChild_ += shiftAmount;
			if ( node.nextSibling_ > -1 )
				node.nextSibling_ += shiftAmount;
			if ( node.lastSibling_ > -1 )
				node.lastSibling_ += shiftAmount;
		};

		// If there two many nodes, we can use std::execution::par with std::transform
		// std::transform(scene.hierarchy_.begin() + startOffset, scene.hierarchy_.begin() + nodeCount, scene.hierarchy_.begin() + startOffset, shiftNode

		//for (auto i = scene.hierarchy_.begin() + startOffset ; i != scene.hierarchy_.begin() + nodeCount ; i++)
		//		shiftNode(*i);

		for ( qint32 i = 0; i < nodeCount; i++ )
			shiftNode ( scene.hierarchy_ [ i + startOffset ] );
	}

	// Add the items from otherMap shifting indices and values along the way
	void mergeMaps ( QHash<quint32,quint32>& m, const QHash<quint32,quint32>& otherMap, qint32 indexOffset, qint32 itemOffset )
	{
		QHashIterator<quint32, quint32> it ( otherMap );
		while ( it.hasNext () )
		{
			it.next ();
			m.insert ( it.key () + indexOffset, it.value () + itemOffset );
		}
	}

	/**
	 * @brief There are different use cases for scene merging. The simplest one is the direct "gluing" of multiple scenes into one [all the material lists and mesh lists are merged and indices in all scene nodes are shifted appropriately]. The second one is creating a "grid" of objects (or scenes) with the same material and mesh sets. For the second use case we need two flags: 'mergeMeshes' and 'mergeMaterials' to avoid shifting mesh indices
	 * @param scene
	 * @param scenes
	 * @param rootTransforms
	 * @param meshCounts
	 * @param mergeMeshes
	 * @param mergeMaterials
	*/

	void mergeScenes ( Scene& scene, const QList<Scene*>& scenes, const QList<mat4>& rootTransforms, const QList<quint32>& meshCounts, bool mergeMeshes, bool mergeMaterials )
	{
		// Create the new root node
		scene.hierarchy_ = {
			{
				.parent_ = -1,
				.firstChild_ = 1,
				.nextSibling_ = -1,
				.lastSibling_ = -1,
				.level_ = 0
			}
		};

		scene.nameForNode_ [ 0 ] = 0;
		scene.names_ = { "NewRoot" };

		scene.localTransforms_.push_back ( mat4 ( 1.0f ) );
		scene.globalTransforms_.push_back ( mat4 ( 1.0f ) );

		if ( scenes.empty () )
		{
			return;
		}

		qint32 offs = 1;
		qint32 meshOffs = 0;
		qint32 nameOffs = ( qint32 ) scene.names_.size ();
		qint32 materialOfs = 0;
		auto meshCount = meshCounts.begin ();

		if ( !mergeMaterials )
		{
			scene.materialNames_ = scenes [ 0 ]->materialNames_;
		}

		// FIXME: too much logic (for all the components in a scene, though mesh data and materials go separately - there are dedicated data lists)
		for ( const Scene* s : scenes )
		{
			mergeLists ( scene.localTransforms_, s->localTransforms_ );
			mergeLists ( scene.globalTransforms_, s->globalTransforms_ );

			mergeLists ( scene.hierarchy_, s->hierarchy_ );

			mergeLists ( scene.names_, s->names_ );
			if ( mergeMaterials )
			{
				mergeLists ( scene.materialNames_, s->materialNames_ );
			}

			qint32 nodeCount = ( qint32 ) s->hierarchy_.size ();

			shiftNodes ( scene, offs, nodeCount, offs );

			mergeMaps ( scene.meshes_, s->meshes_, offs, mergeMeshes ? meshOffs : 0 );
			mergeMaps ( scene.materialForNode_, s->materialForNode_, offs, mergeMaterials ? materialOfs : 0 );
			mergeMaps ( scene.nameForNode_, s->nameForNode_, offs, nameOffs );

			offs += nodeCount;

			materialOfs += ( qint32 ) s->materialNames_.size ();
			nameOffs += ( qint32 ) s->names_.size ();

			if ( mergeMeshes )
			{
				meshOffs += *meshCount;
				meshCount++;
			}
		}

		// fixing 'nextSibling' fields in the old roots (zero-index in all the scenes)
		offs = 1;
		qint32 idx = 0;
		for ( const Scene* s : scenes )
		{
			qint32 nodeCount = ( qint32 ) s->hierarchy_.size ();
			bool isLast = ( idx == scenes.size () - 1 );
			// calculate new next sibling for the old scene roots
			qint32 next = isLast ? -1 : offs + nodeCount;
			scene.hierarchy_ [ offs ].nextSibling_ = next;
			// attach to new root
			scene.hierarchy_ [ offs ].parent_ = 0;

			// transform old root nodes, if the transforms are given
			if ( !rootTransforms.empty () )
			{
				scene.localTransforms_ [ offs ] = rootTransforms [ idx ] * scene.localTransforms_ [ offs ];
			}

			offs += nodeCount;
			idx++;
		}

		// now shift levels of all nodes below the root
		for ( auto i = scene.hierarchy_.begin () + 1; i != scene.hierarchy_.end (); i++ )
		{
			i->level_++;
		}
	}

	void dumpSceneToDot ( const char* filename, const Scene& scene, qint32* visited )
	{
		//QFile* f = fopen ( filename, "w" );
		QFile f ( filename );

		if ( !f.open ( QIODeviceBase::WriteOnly | QIODeviceBase::Text ) )
		{
			qWarning ( "Failed to open file %s. Cannot dump scene to dot.\nExiting...\n", filename );
			exit ( EXIT_FAILURE );
		}

		f.write ( "digraph G\n{\n" );
		for ( qsizetype i = 0; i < scene.globalTransforms_.size (); i++ )
		{
			QByteArray name = "";
			QByteArray extra = "";
			if ( scene.nameForNode_.contains ( i ) )
			{
				qint32 strID = scene.nameForNode_.value ( i );
				name = scene.names_ [ strID ];
			}

			if ( visited )
			{
				if ( visited [ i ] )
					extra = ", color = red";
			}

			QByteArray str = "n" + QByteArray::number ( i ) + " [label=\"" + name + "\" " + extra + "]\n";
			f.write ( str );
		}

		for ( qsizetype i = 0; i < scene.hierarchy_.size (); i++ )
		{
			qint32 p = scene.hierarchy_ [ i ].parent_;
			if ( p > -1 )
			{
				QByteArray str = "\t n" + QByteArray::number ( p ) + "\n";
				f.write ( str );
			}
		}

		f.write ( "}\n" );
		f.close ();
	}

	/** A rather long algorithm (and the auxiliary routines) to delete a number of scene nodes from the hierarchy */

	// Add an index to a sorted index array
	static void addUniqueIdx ( QList<quint32>& v, quint32 index )
	{
		if ( !std::binary_search ( v.begin (), v.end (), index ) )
		{
			v.push_back ( index );
		}
	}

	// Recurse down from a node and collect all nodes which are already marked for deletion
	static void collectNodesToDelete ( const Scene& scene, qint32 node, QList<quint32>& nodes )
	{
		for ( qint32 n = scene.hierarchy_ [ node ].firstChild_; n != -1; n = scene.hierarchy_ [ n ].nextSibling_ )
		{
			addUniqueIdx ( nodes, n );
			collectNodesToDelete ( scene, n, nodes );
		}
	}

	qint32 findLastNonDeletedItem ( const Scene& scene, const QList<qint32>& newIndices, qint32 node )
	{
		// we have to be more subtle:
		//	if the (newIndices[firstChild_] == - 1), we should follow the link and extract the last non-removed item
		// ..
		if ( node == -1 )
		{
			return -1;
		}

		return ( newIndices [ node ] == -1 ) ? findLastNonDeletedItem ( scene, newIndices, scene.hierarchy_ [ node ].nextSibling_ ) : newIndices [ node ];
	}

	void shiftMapIndices ( QHash<quint32, quint32>& items, const QList<qint32>& newIndices )
	{
		QHash<quint32, quint32> newItems;
		QHashIterator<quint32, quint32> it ( items );
		while ( it.hasNext () )
		{
			it.next ();
			quint32 newIndex = newIndices [ it.key () ];
			if ( newIndex != -1 )
			{
				newItems [ newIndex ] = it.value ();
			}
		}

		items = newItems;
	}

	// Approximately an O ( N * Log(N) * Log(M)) algorithm (N = scene.size, M = nodesToDelete.size) to delete a collection of nodes from scene graph
	void deleteSceneNodes ( Scene& scene, const QList<quint32>& nodesToDelete )
	{
		// 0) Add all the nodes down below in the hierarchy
		auto indicesToDelete = nodesToDelete;
		for ( auto i : indicesToDelete )
		{
			collectNodesToDelete ( scene, i, indicesToDelete );
		}

		// aux array with node indices to keep track of the moved ones [moved = [](node) { return (node != nodes[node]); ]
		QList<int> nodes ( scene.hierarchy_.size () );
		std::iota ( nodes.begin (), nodes.end (), 0 );

		// 1.a) Move all the indicesToDelete to the end of 'nodes' array (and cut them off, a variation of swap'n'pop for multiple elements)
		auto oldSize = nodes.size ();
		eraseSelected ( nodes, indicesToDelete );

		// 1.b) Make a newIndices[oldIndex] mapping table
		QList<int> newIndices ( oldSize, -1 );
		for ( qint32 i = 0; i < nodes.size (); i++ )
		{
			newIndices [ nodes [ i ] ] = i;
		}

		// 2) Replace all non-null parent/firstChild/nextSibling pointers in all the nodes by new positions
		auto nodeMover = [&scene, &newIndices] ( Hierarchy& h ) {
			return Hierarchy {
				.parent_ = ( h.parent_ != -1 ) ? newIndices [ h.parent_ ] : -1,
				.firstChild_ = findLastNonDeletedItem ( scene, newIndices, h.firstChild_ ),
				.nextSibling_ = findLastNonDeletedItem ( scene, newIndices, h.nextSibling_ ),
				.lastSibling_ = findLastNonDeletedItem ( scene, newIndices, h.lastSibling_ )
			};
		};

		std::transform ( scene.hierarchy_.begin (), scene.hierarchy_.end (), scene.hierarchy_.begin (), nodeMover );

		// 3) Finally throw away the hierarchy items
		eraseSelected ( scene.hierarchy_, indicesToDelete );

		// 4) As in mergeScenes() routine we also have to adjust all the "components" (i.e., meshes, materials, names and transformations)

		// 4a) Transformations are stored in arrays, so we just erase the items as we did iwith the scene.hierarchy_
		eraseSelected ( scene.localTransforms_, indicesToDelete );
		eraseSelected ( scene.globalTransforms_, indicesToDelete );

		// 4b) All the maps should change the key values with the newIndices[] array
		shiftMapIndices ( scene.meshes_, newIndices );
		shiftMapIndices ( scene.materialForNode_, newIndices );
		shiftMapIndices ( scene.nameForNode_, newIndices );

		// 5) scene node names list is not modified, but in principle it can be (remove all non-used items and adjust the nameForNode_ map)
		// 6) Material names list is not modified also, but if some materials fell out of use
	}
}
