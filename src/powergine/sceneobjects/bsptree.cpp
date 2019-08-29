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


#include <powergine/sceneobjects/bsptree.h>

namespace powergine {
	namespace sceneobjects {
	
// Constructors/Destructors
// Methods

BSPTree::BSPTree( ) :
   m_pRootNode( new BSPNode( this, BSPNode::NODE ) ) 
{   
}

BSPTree::~BSPTree( ) {
   delete m_pRootNode;   
}

BSPNode* BSPTree::getRootNode( ) {
   return m_pRootNode;
} // getRootNode

bool BSPTree::render( Frustum *pFrustum ) {   
   primitives::Vector3D oCameraPosition = pFrustum->getTranslation( );      
   m_pCurrentCluster = getClusterFromCameraPosition( oCameraPosition );      
   m_oLumpsDrawn.reset( );
   bool bResult = true;
   
   if ( m_pCurrentCluster ) {
      for ( unsigned int uiI = 0; uiI < m_vecLeaves.size( ); uiI++ ) {
         BSPNode* pNode = m_vecLeaves[ uiI ];
         if ( !pNode->getClusterData( ) || !isClusterVisible( pNode->getClusterData( )->getID( ) ) ) {
            continue;
         } // if
         if ( !pNode->getBoundingVolume( ) || pNode->getBoundingVolume( )->intersection( pFrustum ) ) {
            bResult &= pNode->render( pFrustum );
         } // if         
      } // for
   } else {
      BSPNode *pCurrentNode = m_pRootNode;
      std::stack<BSPNode*> stkNodes;
      
      while( pCurrentNode ) {      
         if ( pCurrentNode->getType( ) == BSPNode::NODE ) {            
            /*float fFarDividerDotProduct = 
               pCurrentNode->getDivider( ).getNormal( ) * 
                  pFrustum->getPlane( Frustum::PLANE_NEAR ).getNormal( );
              */ 
               //if ( fFarDividerDotProduct >= 0.0f ) {
                  if ( pCurrentNode->getLeftChild( ) && (
                        ( !pCurrentNode->getLeftChild( )->getBoundingVolume( ) || 
                           pCurrentNode->getLeftChild( )->getBoundingVolume( )->intersection( pFrustum ) ) 
                        )
                     ) { stkNodes.push( pCurrentNode->getLeftChild( ) ); }
                  
                  if ( pCurrentNode->getRightChild( ) && ( 
                        ( !pCurrentNode->getRightChild( )->getBoundingVolume( ) || 
                           pCurrentNode->getRightChild( )->getBoundingVolume( )->intersection( pFrustum ) )
                        )
                     ) { stkNodes.push( pCurrentNode->getRightChild( ) ); }
                  
               /*} else {               
                  if ( pCurrentNode->getRightChild( ) && (
                        ( !pCurrentNode->getRightChild( )->getBoundingVolume( ) || 
                           pCurrentNode->getRightChild( )->getBoundingVolume( )->intersection( pFrustum ) )
                        )
                     ) { stkNodes.push( pCurrentNode->getRightChild( ) ); }
                  
                  if ( pCurrentNode->getLeftChild( ) && (
                        ( !pCurrentNode->getLeftChild( )->getBoundingVolume( ) || 
                           pCurrentNode->getLeftChild( )->getBoundingVolume( )->intersection( pFrustum ) )
                        ) 
                     ) { stkNodes.push( pCurrentNode->getLeftChild( ) ); }
                  
               } // else               */
         } else {
            bResult &= pCurrentNode->render( pFrustum );
         } // else
         
         pCurrentNode = ( stkNodes.empty( ) == false ) ? stkNodes.top( ) : 0;
         stkNodes.pop( );
      } // while
      
   } // else
   return Room::render( pFrustum ) & bResult;   
}

void BSPTree::setNumLumps( unsigned int uiNumLumps ) {
   if ( m_oLumpsDrawn.getMaxNumBits( ) < uiNumLumps ) {   
      m_oLumpsDrawn.resize( uiNumLumps );   
   } // if
} // setNumLumps

bool BSPTree::isLumpDrawn( unsigned int uiLumpID ) {      
   return m_oLumpsDrawn.isSet( uiLumpID );
   
} // isLumpDrawn

void BSPTree::setLumpDrawn( unsigned int uiLumpID ) {
   m_oLumpsDrawn.set( uiLumpID );
} // setLumpDrawn

bool BSPTree::isClusterVisible( unsigned int uiClusterID ) {
   if ( m_pCurrentCluster ) {      
      return m_pCurrentCluster->isClusterVisible( uiClusterID );
   } // if
   return true;
} // isClusterVisible

BSPVisData* BSPTree::getClusterFromCameraPosition( const primitives::Vector3D &rkCameraPosition ) {
   BSPNode *pCurrentNode = getRootNode( );
   float fDistance = 0.0f;
   
   while ( pCurrentNode && pCurrentNode->getType( ) == BSPNode::NODE ) {
      primitives::Plane oPlane = pCurrentNode->getDivider( );
      
      fDistance = oPlane.getNormal( ).getX( ) * rkCameraPosition.getX( ) + 
                  oPlane.getNormal( ).getY( ) * rkCameraPosition.getY( ) + 
                  oPlane.getNormal( ).getZ( ) * rkCameraPosition.getZ( ) - 
                  oPlane.getDistanceFromOrigo( );
      
      if ( fDistance > 0 ) {
         // camere is in front of the plane
         pCurrentNode = pCurrentNode->getLeftChild( );
      } else {
         // camere is behind of the plane
         pCurrentNode = pCurrentNode->getRightChild( );
      } // else
   } // while
   
   return ( pCurrentNode ) ? pCurrentNode->getClusterData( ) : 0;
   
} // getClusterFromCameraPosition

void BSPTree::setupLeaf( BSPNode *pNode ) {
   m_vecLeaves.push_back( pNode );
} // setupLeaf

	}; // sceneobjects
}; // powergine
