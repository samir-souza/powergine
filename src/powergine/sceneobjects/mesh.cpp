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


#include <powergine/sceneobjects/mesh.h>


namespace powergine {
	namespace sceneobjects {

// Constructors/Destructors
// Methods
Mesh::Mesh( const std::string &rstrName, primitives::RenderPrimitive *pRenderPrimitive ) :
   m_strName( rstrName ),
   m_pRenderPrimitive( pRenderPrimitive ),
   m_pSkeleton( 0 )
{
}

Mesh::~Mesh( ) {
   if ( m_pSkeleton ) {
      delete m_pSkeleton;
   } // if
   if ( m_pRenderPrimitive ) {
      delete m_pRenderPrimitive;
   } // if
   for ( unsigned int uiI = 0; uiI < m_vpSubMeshes.size( ); uiI++ ) {
      if ( m_vpSubMeshes[ uiI ] ) {
         delete m_vpSubMeshes[ uiI ];
      } // if
   } // for
} // ~Mesh

const std::string& Mesh::getName( ) const {
   return m_strName;
}

void Mesh::addSubMesh( Mesh* pSubMesh ) {
   m_vpSubMeshes.push_back( pSubMesh );
}

Mesh* Mesh::getSubMesh( const std::string &rstrName ) {
   std::vector<Mesh*>::iterator ppBegin = m_vpSubMeshes.begin( );
   std::vector<Mesh*>::iterator ppEnd  = m_vpSubMeshes.end( );

   while( ppBegin != ppEnd ) {
      if( (*ppBegin)->getName( ) == rstrName ) {
            return (*ppBegin);
      } // if
      ppBegin++;
   } // while
   return 0;
}

Mesh* Mesh::removeSubMesh( const std::string &rstrName ) {
   std::vector<Mesh*>::iterator ppBegin = m_vpSubMeshes.begin( );
   std::vector<Mesh*>::iterator ppEnd  = m_vpSubMeshes.end( );

   while( ppBegin != ppEnd ) {
      if( (*ppBegin)->getName( ) == rstrName ) {
            Mesh* pRemovedMesh = (*ppBegin);
            m_vpSubMeshes.erase( ppBegin );
            return pRemovedMesh;
      } // if
      ppBegin++;
   } // while
   return 0;
}

Skeleton* Mesh::getSkeleton( ) {
   return m_pSkeleton;
}
void Mesh::setSkeleton( Skeleton *pSkeleton ) {
   m_pSkeleton = pSkeleton;
}

primitives::RenderPrimitive* Mesh::getRenderPrimitive( ) {
   return m_pRenderPrimitive;
} // getRenderPrimitive


const primitives::Material* const Mesh::getMaterial( ) const {
   return m_pRenderPrimitive->getMaterial( );
}

void Mesh::setMaterial( primitives::Material *pMaterial ) {
   m_pRenderPrimitive->setMaterial( pMaterial );
}

void Mesh::update( float fDeltaTime ) {
   std::vector<Mesh*>::iterator ppBegin = m_vpSubMeshes.begin( );
   std::vector<Mesh*>::iterator ppEnd  = m_vpSubMeshes.end( );

   while( ppBegin != ppEnd ) {
      if( (*ppBegin)->isActive( )  ) {
            (*ppBegin)->update( fDeltaTime );
      } // if
      ppBegin++;
   } // while
}

bool Mesh::render( Frustum *pFrustum ) {
   if ( !SceneEntity::render( pFrustum ) ) {
      return false;
   } // if

   if ( m_pRenderPrimitive ) {

      if ( !getBoundingVolume( ) || getBoundingVolume( )->intersection( pFrustum ) ) {
         Core::get( )->getVideoManager( )->render( *m_pRenderPrimitive );
      } // if

      for ( unsigned int uiI = 0; uiI < m_vpSubMeshes.size( ); uiI++ ) {
         if ( !m_vpSubMeshes[ uiI ]->render( pFrustum ) ) {
            return false;
         } // if
      } // for

      return true;
   } // if
   return false;
} // render

	}; // scenenode
}; // namespace powergine
