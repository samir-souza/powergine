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


#include <powergine/sceneobjects/room.h>

namespace powergine {
	namespace sceneobjects {
	
// Constructors/Destructors
Room::Room( const std::string &rstrName ) :
   SceneNode( rstrName )
{
}


Room::~Room( ) {
   std::vector< SceneNode* >::iterator ppBegin = m_vpGlobalChildren.begin( );
   std::vector< SceneNode* >::iterator ppEnd = m_vpGlobalChildren.end( );
   
   while( ppBegin != ppEnd ) {
      delete( *ppBegin );
      ppBegin++;
   } // while
}


bool Room::addGlobalChildNode( SceneNode *pGlobalChildNode ) {
   pGlobalChildNode->setRoom( this );

   std::vector<SceneNode*>::iterator ppBegin = m_vpGlobalChildren.begin();
   std::vector<SceneNode*>::iterator ppEnd  = m_vpGlobalChildren.end();

   while( ppBegin != ppEnd ) {
      if( *ppBegin == pGlobalChildNode ) {
               return false;
      } // if
      ppBegin++;
   } // while

   m_vpGlobalChildren.push_back( pGlobalChildNode );
   return true;
}


bool Room::removeGlobalChildNode( SceneNode *pGlobalChildNode ) {
   if( pGlobalChildNode->getRoom( ) == this ) {
            pGlobalChildNode->setRoom( 0 );
   } // if

   std::vector<SceneNode*>::iterator ppBegin = m_vpGlobalChildren.begin();
   std::vector<SceneNode*>::iterator ppEnd  = m_vpGlobalChildren.end();

   while( ppBegin != ppEnd ) {
            if( *ppBegin == pGlobalChildNode ) {
                     m_vpGlobalChildren.erase( ppBegin );
                     return true;
            } // if
            ppBegin++;
   } // while
   return false;
}


bool Room::addChildNode( SceneNode *pChildNode ) {
   pChildNode->setRoom( this );

   return SceneNode::addChildNode( pChildNode );
}


bool Room::removeChildNode( SceneNode *pChildNode ) {
   if( pChildNode->getRoom( ) == this )
            pChildNode->setRoom( 0 );

   return SceneNode::removeChildNode( pChildNode );
}


bool Room::render( Frustum *pFrustum ) {
   if( !SceneNode::render( pFrustum ) ) {
      return false;
   } // if

   std::vector<SceneNode*>::iterator ppBegin = m_vpGlobalChildren.begin();
   std::vector<SceneNode*>::iterator ppEnd  = m_vpGlobalChildren.end();

   while( ppBegin != ppEnd ) {      
      if ( ( (*ppBegin)->isActive( ) ) ) {         
         (*ppBegin)->render( pFrustum );
      } // if
      ppBegin++;
   } // while
   return true;
}


void Room::update( float fDeltaTime ) {
   std::vector<SceneNode*>::iterator ppBegin = m_vpGlobalChildren.begin();
   std::vector<SceneNode*>::iterator ppEnd  = m_vpGlobalChildren.end();

   while( ppBegin != ppEnd ) {
      (*ppBegin)->update( fDeltaTime );
   } // while
   SceneNode::update( fDeltaTime );
}



	}; // scenenode
}; // namespace powergine
