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


#include <powergine/sceneobjects/sceneentity.h>

namespace powergine {
	namespace sceneobjects {

// Constructors/Destructors
// Methods
SceneEntity::SceneEntity( SceneNode *pParentSceneNode ) :
	RenderEntity( ), 
	m_pParentSceneNode( pParentSceneNode ),
	m_pBoundingVolume( 0 )	
{

} // SceneEntity

SceneEntity::~SceneEntity( ) {
   m_pParentSceneNode = 0;
   if ( m_pBoundingVolume ) {
      delete m_pBoundingVolume;
   } // if
} // ~SceneEntity

SceneNode* SceneEntity::getParentSceneNode( ) {
  return m_pParentSceneNode;
} // getParentSceneNode

BoundingVolume* SceneEntity::getBoundingVolume( ) {
   return m_pBoundingVolume;
} // getBoundingVolume

void SceneEntity::setParentSceneNode( SceneNode* pParentSceneNode ) {
   m_pParentSceneNode = pParentSceneNode;   
} // setParentSceneNode

void SceneEntity::setBoundingVolume( BoundingVolume* pBoundingVolume ) {
   delete m_pBoundingVolume;
   m_pBoundingVolume = pBoundingVolume;   
} // setBoundingVolume

SceneEntity* SceneEntity::clone ( ) {
   return new SceneEntity( *this );
}
    
void SceneEntity::update( float fDeltaTime ) {
   if ( m_pParentSceneNode ) {
      m_pParentSceneNode->update( fDeltaTime );
   } // if
}
    /*
bool SceneEntity::collide( const BoundingVolume &rkBoundingVolume, utils::ContactSet *pContactSet ) {
   if ( m_pBoundingVolume ) {
      return m_pBoundingVolume->collide( rkBoundingVolume, pContactSet );
   } // if
   return false;
}
    */
bool SceneEntity::collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet ) {
   if ( m_pBoundingVolume ) {
      return m_pBoundingVolume->collide( rkRay, pContactSet );
   } // if
   return false;
}

bool SceneEntity::render( Frustum *pFrustum ) {
   return RenderEntity::render( pFrustum );
} // render
	}; // scenenode
}; // namespace powergine
