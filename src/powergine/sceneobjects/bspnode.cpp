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


#include <powergine/sceneobjects/bspnode.h>

namespace powergine {
	namespace sceneobjects {
	
// Constructors/Destructors
// Methods
BSPNode::BSPNode( BSPTree *pParent, BSPNode::TYPE eType ) :   
   m_uiID( 0 ),
   m_pClusterData( 0 ),
   m_eType( eType ),   
   m_pBoundingVolume( 0 ),
   m_pParentTree( pParent ),
   m_pLeftChild( 0 ),
   m_pRightChild( 0 )
{
   static unsigned int s_uiIndex = 0;
   m_uiID = s_uiIndex++;
}

BSPNode::~BSPNode( ) {
   delete m_pBoundingVolume;      
   delete m_pLeftChild;
   delete m_pRightChild;
   m_pParentTree = 0;
}

void BSPNode::setParentTree( BSPTree *pBSPTree ) {
   m_pParentTree = pBSPTree;
} // setParentTree

BSPTree* BSPNode::getParentTree( ) {
   return m_pParentTree;
} // getParentTree

bool BSPNode::render( Frustum *pFrustum ) {         
   std::vector< sceneobjects::BSPLump* >::iterator ppBegin = m_vecLumps.begin( );
   std::vector< sceneobjects::BSPLump* >::iterator ppEnd = m_vecLumps.end( );                           
   
   while ( ppBegin != ppEnd ) {            
      if ( !getParentTree( )->isLumpDrawn( (*ppBegin)->getID( ) ) ) {
         getParentTree( )->setLumpDrawn( (*ppBegin)->getID( ) );               
         (*ppBegin)->render( pFrustum );         
      } // if           
      ++ppBegin;
   } // while
   return SceneNode::render( pFrustum );      
} // render

bool BSPNode::addLump( sceneobjects::BSPLump* pLump ) {
   std::vector< sceneobjects::BSPLump* >::iterator ppBegin = m_vecLumps.begin( );
   std::vector< sceneobjects::BSPLump* >::iterator ppEnd = m_vecLumps.end( );
   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pLump ) {
         return false;
      } // if
      ++ppBegin;
   } // while
   getParentTree( )->setNumLumps( pLump->getID( ) );
   m_vecLumps.push_back( pLump );
   return true;
} // addLump

void BSPNode::setLeftChild( BSPNode* pNode ) {
   m_pLeftChild = pNode;
   if ( pNode->getType( ) == BSPNode::LEAF ) {
      getParentTree( )->setupLeaf( pNode );
   } // if
} // setLeftChild

BSPNode* BSPNode::getLeftChild( ) {
   return m_pLeftChild;   
} // getLeftChild

void BSPNode::setRightChild( BSPNode* pNode ) {
   m_pRightChild = pNode;
   if ( pNode->getType( ) == BSPNode::LEAF ) {
      getParentTree( )->setupLeaf( pNode );
   } // if   
} // setRightChild

BSPNode* BSPNode::getRightChild( ) {
   return m_pRightChild;
} // getRightChild

primitives::Plane& BSPNode::getDivider( ) {
   return m_oDivider;
} // getDivider

void BSPNode::setID( unsigned int uiID ) {
   m_uiID = uiID;
} // setID

unsigned int BSPNode::getID( ) {
   return m_uiID;
}  // getID

void BSPNode::setClusterData( BSPVisData* pClusterData ) {
   m_pClusterData = pClusterData;
} // setClusterData

BSPVisData* BSPNode::getClusterData( ) {
   return m_pClusterData;
} // getClusterData

BSPNode::TYPE BSPNode::getType( ) {
   return m_eType;
} // getType

void BSPNode::setBoundingVolume( sceneobjects::BoundingVolume *pBoundingVolume ) {
   m_pBoundingVolume = pBoundingVolume;
} // setBoundingVolume

sceneobjects::BoundingVolume* BSPNode::getBoundingVolume( ) {
   return m_pBoundingVolume;
} // getBoundingVolume


	}; // sceneobjects
}; // powergine
