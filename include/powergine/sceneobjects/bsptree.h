// Copyright (c) 2004 Samir Araujo <samir.araujo.com>
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

#ifndef BSPTREE_H
#define BSPTREE_H

#include <map>
#include <string>
#include <vector>
#include <stack>
#include <iostream>

#include <powergine/sceneobjects/room.h>
#include <powergine/sceneobjects/bspnode.h>
#include <powergine/sceneobjects/frustum.h>
#include <powergine/primitives/renderprimitive.h>

#include <powergine/primitives/vertextexturediffusenormal.h>
#include <powergine/utils/bitset.h>

namespace powergine {
	namespace sceneobjects {

		class BSPNode;

		/**
		 * A BSP tree is part of the BSP (Binary Spatial Partition) tree toolkit
		 * An instance of this class can represent a huge environment and, given
		 * its characteristics, that environment can be rendered smoothly
		 *
		 */
		class BSPTree : public Room {

		public:
		   BSPTree( );

		   virtual ~BSPTree( );

		   // Returns the tree root
		   BSPNode* getRootNode( );

		   // Render the environment which lies inside the frustum
		   bool render( Frustum *pFrustum );

		   // Update the number of lumps
		   void setNumLumps( unsigned int uiNumLumps );

		   // Check if a lump was already rendered
		   bool isLumpDrawn( unsigned int uiLumpID );

		   // Updates the rendered lumps information
		   void setLumpDrawn( unsigned int uiLumpID );

		   // Checks if a given cluster is visible given the visibility
		   // info of the tree and its position
		   bool isClusterVisible( unsigned int uiClusterID );

		   // Adds a new leaf to the tree
		   void setupLeaf( BSPNode* pNode );

		private:
		   BSPNode *m_pRootNode;
		   utils::BitSet m_oLumpsDrawn;
		   BSPVisData *m_pCurrentCluster;
		   std::vector<BSPNode*> m_vecLeaves;
		   BSPVisData *getClusterFromCameraPosition( const primitives::Vector3D &rkCameraPosition );
		};

	}; // sceneobjects
}; // powergine

#endif //BSPTREE_H
