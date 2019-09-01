// Copyright (c) 2004 Samir Araujo
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.

#ifndef BSPNODE_H
#define BSPNODE_H

#include <map>
#include <string>
#include <vector>
#include <powergine/core.h>
#include <powergine/sceneobjects/aabb.h>
#include <powergine/sceneobjects/scenenode.h>
#include <powergine/sceneobjects/bsplump.h>
#include <powergine/sceneobjects/bspvisdata.h>
#include <powergine/primitives/plane.h>
#include <powergine/primitives/renderprimitive.h>

namespace powergine {
	namespace sceneobjects {

		class BSPTree;

		/**
		 * A BSP Node is part of the BSP (Binary Spatial Partition) tree toolkit
		 * This class represents a node of the tree
		 */
		class BSPNode : public SceneNode {

		public:
		   enum TYPE {
			  NODE = 0,
			  LEAF = 1
		   };

		   BSPNode( BSPTree *pParent, TYPE eType = NODE );

		   virtual ~BSPNode( );

		   // Attach it to a tree
		   void setParentTree( BSPTree *pBSPTree );

		   // Returns the parent tree
		   BSPTree* getParentTree( );

		   // Renders this node
		   bool render( Frustum *pFrustum );

		   // Adds a new lump to this node
		   bool addLump( sceneobjects::BSPLump *pLump );

		   // Updates the left child node
		   void setLeftChild( BSPNode* pNode );

		   // Returns the left child node
		   BSPNode* getLeftChild( );

		   // Updates the right child node
		   void setRightChild( BSPNode* pNode );

		   // Returns the right child node
		   BSPNode* getRightChild( );

		   // Returns the plane which is partitioning the portion
		   // of the environment represented by this node
		   primitives::Plane& getDivider( );

		   // Update the node id
		   void setID( unsigned int uiID );

		   // Returns the node id
		   unsigned int getID( );

		   // Updates the visibility info of this node
		   void setClusterData( BSPVisData *pClusterData );

		   // Returns the visibility info of this node
		   BSPVisData *getClusterData( );

		   // Returns the node type
		   TYPE getType( );

		   // Updates the bounding box which encloses this node
		   void setBoundingVolume( sceneobjects::BoundingVolume *pBoundingVolume );

		   // Returns the bounding volume which encloses this node
		   sceneobjects::BoundingVolume* getBoundingVolume( );

		private:
		   unsigned int m_uiID;
		   BSPVisData *m_pClusterData;

		   TYPE m_eType;
		   // vis
		   sceneobjects::BoundingVolume *m_pBoundingVolume;
		   BSPTree *m_pParentTree;
		   BSPNode *m_pLeftChild;
		   BSPNode *m_pRightChild;
		   primitives::Plane m_oDivider;
		   std::vector< sceneobjects::BSPLump* > m_vecLumps;

		};

	}; // sceneobjects
}; // powergine

#include <powergine/sceneobjects/bsptree.h>

#endif //BSPNODE_H
