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


#include <powergine/sceneobjects/skydome.h>

namespace powergine {
	namespace sceneobjects {

// Constructors/Destructors
// Methods

SkyDome::SkyDome( primitives::Material *pMaterial, int iRadius ) :
   SceneEntity( )
{
   m_pModelView = new primitives::Matrix4x4( primitives::Matrix4x4::IDENTITY );
   buildDome( iRadius, pMaterial );
}


void SkyDome::buildTextCoords( const primitives::Vector3D &rkVertice, float &rfU, float &rfV ) {
   primitives::Vector3D oVertice = rkVertice;
   oVertice.normalize( );
   float fX = oVertice.getX( );
   float fY = oVertice.getY( );
   float fZ = oVertice.getZ( );
   if ( fY < 0 ) {
      fY *= -1.0f;
   } // if
   rfU = static_cast<float>( ( atan2( fX, fY ) / ( utils::MathHelper::PI * 2) ) + 0.5f );
   rfV = static_cast<float>( ( asin( fZ ) / utils::MathHelper::PI ) + 0.5f );
} // buildTextCoords


void SkyDome::buildDome( int iRadius, primitives::Material *pMaterial ) {

   int iTheta, iPhi;
   int iDeltaTheta = 15;
   int iDeltaPhi = 15;

   int iAngleX = iDeltaPhi*13;
   int iAngleY = iDeltaTheta*24;

   int iLat = ( iAngleX / iDeltaPhi );
   int iLong = ( iAngleY / iDeltaTheta );

   int iNumVertices = ( iLong * iLat );
   int iNumPolygons = ( ( ( iLat * 2 ) - 2 ) * iLong );

   primitives::VertexTextureBuffer *pVertexHandler =
      new primitives::VertexTextureBuffer( iNumVertices );

   primitives::TriangleBuffer *pPolygonHandler =
      new primitives::TriangleBuffer( iNumPolygons );

   primitives::VertexBuffer *pVertexBuffer =
      Core::get( )->getVideoManager( )->createVertexBuffer(
         pVertexHandler->getNumElements( ),
         primitives::VertexTexture::s_oFormat,
         pVertexHandler->getData( )
      );

   primitives::PolygonBuffer *pPolygonBuffer =
      Core::get( )->getVideoManager( )->createPolygonBuffer(
         pPolygonHandler->getNumElements( ),
         primitives::Triangle::getNumVertices( ),
         pPolygonHandler->getData( )
      );

   m_pRenderPrimitive = new primitives::RenderPrimitive(
      primitives::RenderPrimitive::MODE_TRIANGLES,
      primitives::RenderPrimitive::POLYGON_TRIANGLE,
      pMaterial
   );

   m_pRenderPrimitive->setVertexBuffer( pVertexBuffer );
   m_pRenderPrimitive->setPolygonBuffer( pPolygonBuffer );

   m_pRenderPrimitive->setEdgeLinesSize( 4.0f );
   // do not translate sky with the scene nodes
   m_pRenderPrimitive->setPermitTranslation( false );
   m_pRenderPrimitive->setModelViewMatrix( m_pModelView );

   float fU = 0.0f, fV = 0.0f;
   int i = 0;
   // setup dome vertices
   primitives::VertexTextureBuffer::iterator *pVIterator = pVertexHandler->makeIterator( );
   for ( iPhi=0; iPhi <= iAngleX - iDeltaPhi; iPhi += iDeltaPhi ) {
      for ( iTheta=0; iTheta <= iAngleY - iDeltaTheta; iTheta += iDeltaTheta ) {
         double dPhiRad = utils::MathHelper::get( )->degree2Radians( static_cast<double>( iPhi ) );
         double dThetaRad = utils::MathHelper::get( )->degree2Radians( static_cast<double>( iTheta ) );

         float fSinPhi = sin( dPhiRad );   float fSinTheta = sin( dThetaRad );
         float fCosPhi = cos( dPhiRad );   float fCosTheta = cos( dThetaRad );

         float fX = ( static_cast<float>( iRadius ) * fSinPhi * fSinTheta );
         float fY = ( static_cast<float>( iRadius ) * fCosPhi );
         float fZ = ( static_cast<float>( iRadius ) * fSinPhi * fCosTheta );
         primitives::Vector3D oPosition( fX, fY, fZ );

         // Calculate the vertex at phi, theta
         buildTextCoords( oPosition, fU, fV );
         pVIterator->getCurrent( ).setAll( oPosition, primitives::TextCoords( fU, fV ) );
         pVIterator->goNext( );
         i++;
      } // for
   } // for

   // setup dome polygons
   int iJ, iK = iLong, iL;
   primitives::TriangleBuffer::iterator *pPIterator = pPolygonHandler->makeIterator( );
   for ( int iI = 0; iI < iNumPolygons/2; iI++ ) {

      if ( ( (iI+1) % iLong ) == 0 ) {
         iJ = iK;
         iK += iLong;
      } else {
         iJ =  iI+iLong+1;
      } // else

      iL = iI + iLong;
      pPIterator->getCurrent( ).setAll( iI, iJ, iL );
      pPIterator->goNext( );

      pPIterator->getCurrent( ).setAll( iI, iJ-iLong, iJ );
      pPIterator->goNext( );
   } // for

} // buildDome

SkyDome::~SkyDome( ) {
   delete m_pRenderPrimitive;
}

void SkyDome::update( float fDeltaTime ) {
   SceneEntity::update( fDeltaTime );
}

bool SkyDome::render( Frustum *pFrustum ) {
   if ( !SceneEntity::render( pFrustum ) ) return false;
   Core::get( )->getVideoManager( )->render( *m_pRenderPrimitive );

   return true;
}

	}; // scenenode
}; // namespace powergine
