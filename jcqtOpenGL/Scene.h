/*****************************************************************//**
 * \file   Scene.h
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
#ifndef __SCENE_H__
#define __SCENE_H__

#include "jcqtopengl_global.h"

#include <QList>
#include <QHash>
#include <QByteArrayList>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

using glm::mat4;

namespace jcqt
{
	constexpr const qint32 MAX_NODE_LEVEL = 16;

	struct JCQTOPENGL_EXPORT Hierarchy
	{
		// parent for this node (or -1 for root)
		qint32 parent_;
		// first child for a node (or - 1)
		qint32 firstChild_;
		// next sibling for a node (or - 1)
		qint32 nextSibling_;
		// last added node (or - 1)
		qint32 lastSibling_;
		// cached node level
		qint32 level_;
	};

	struct JCQTOPENGL_EXPORT SceneNode
	{
		qint32 mesh_;
		qint32 material_;
		qint32 parent_;
		qint32 firstChild_;
		qint32 rightSibling_;
	};

	struct JCQTOPENGL_EXPORT Scene
	{
		/* Local transformations for each node and global transforms and an array of 'dirty/changed' local transforms */
		QList<mat4> localTransforms_;
		QList<mat4> globalTransforms_;

		// list of nodes whose global transform must be recalculated
		QList<qint32> changedAtThisFrame_ [ MAX_NODE_LEVEL ];

		// Hierarchy components
		QList<Hierarchy> hierarchy_;

		// Meshes for nodes (Node -> Mesh)
		QHash<quint32, quint32> meshes_;

		// Materials for nodes (Node -> Material) 
		QHash<quint32, quint32> materialForNode_;

		/* Useful for debugging */
		// Node names: which name is assigned to the node
		QHash<quint32, quint32> nameForNode_;

		// Collection of scene node names
		QByteArrayList names_;

		// Collection of debug material names
		QByteArrayList materialNames_;
	};

	qint32 JCQTOPENGL_EXPORT addNode ( Scene& scene, qint32 parent, qint32 level );

	// markAsChanged() routine starts with a given node and recursively descends to each and every child node, adding it to the changedAtLevel_ arrays. 
	void JCQTOPENGL_EXPORT markAsChanged ( Scene& scene, qint32 node );

	qint32 JCQTOPENGL_EXPORT findNodeByName ( const Scene& scene, const QByteArray& name );

	inline QByteArray JCQTOPENGL_EXPORT getNodeName ( const Scene& scene, qint32 node )
	{
		qint32 strID = scene.nameForNode_.contains ( node ) ? scene.nameForNode_.value ( node ) : -1;
		return ( strID > -1 ) ? scene.names_ [ strID ] : QByteArray();
	}

	inline void JCQTOPENGL_EXPORT setNodeName ( Scene& scene, qint32 node, const QByteArray& name )
	{
		quint32 stringID = ( quint32 ) scene.names_.size ();
		scene.names_.push_back ( name );
		scene.nameForNode_ [ node ] = stringID;
	}

	qint32 JCQTOPENGL_EXPORT getNodeLevel ( const Scene& scene, qint32 n );

	void JCQTOPENGL_EXPORT recalculateGlobalTransforms ( Scene& scene );

	void JCQTOPENGL_EXPORT loadScene ( const char* filename, Scene& scene );
	void JCQTOPENGL_EXPORT saveScene ( const char* filename, const Scene& scene );

	void JCQTOPENGL_EXPORT dumpTransformations ( const char* filename, const Scene& scene );
//	void JCQTOPENGL_EXPORT printChagedNodes ( const Scene& scene );

	void JCQTOPENGL_EXPORT dumpSceneToDot ( const char* filename, const Scene& scene, qint32* visited = nullptr );

	void JCQTOPENGL_EXPORT mergeScenes ( Scene& scene, const QList<Scene*>& scenes, const QList<mat4>& rootTransforms, const QList<quint32>& meshCounts, bool mergeMeshes = true, bool mergeMaterials = true );

	// Delete a collection of nodes from a scenegraph
	void JCQTOPENGL_EXPORT deleteSceneNodes ( Scene& scene, const QList<quint32>& nodesToDelete );
}

#endif // !__SCENE_H__