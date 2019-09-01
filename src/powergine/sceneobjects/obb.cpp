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


#include <powergine/sceneobjects/obb.h>

namespace powergine {
	namespace sceneobjects {

// Constructors/Destructors
// Methods
OBB::OBB( const primitives::Vector3D &rkDimension ) :
   BoundingVolume( ),
   m_oTransformation( primitives::Matrix4x4::IDENTITY )
{
   m_oDimension = rkDimension;
   m_fRadius = rkDimension.magnitude( )/2.0;
}

void OBB::setDimension( const primitives::Vector3D &rkDimension ) {
   m_oDimension = rkDimension;
   m_fRadius = rkDimension.magnitude( )/2.0;
}

const primitives::Vector3D& OBB::getDimension( ) const {
   return m_oDimension;
}

float OBB::getRadius( ) const {
   return m_fRadius;
}


bool OBB::collide( const OBB &rkBoundingVolume, utils::ContactSet *pContactSet ) {
   //TODO: collide OBB-boundingbox
   return false;
} // OBB::collide

bool OBB::collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet ) {
   //TODO: collide OBB-ray
   return false;
} // OBB::collide

bool OBB::intersection( Frustum *pFrustum ) {
   const primitives::Vector3D &rkDimension = getDimension( );

   primitives::Vector3D oPosition =
      getRotation( ).rotateVector3D( rkDimension );

   primitives::Vector3D oTest;

   for( int iPlane = 0; iPlane < 6; ++iPlane ) {
      oTest = oPosition;
      const primitives::Plane &rPlane = pFrustum->getPlane( (*pFrustum)[ iPlane ] );
      const primitives::Vector3D &rNormal = rPlane.getNormal( );

      float fX = oTest.getX( );
      float fY = oTest.getY( );
      float fZ = oTest.getZ( );

      //Test most negative point
      fX += ( rNormal.getX( ) > 0.0f ) ? -m_oDimension.getX( ) : m_oDimension.getX( );
      fY += ( rNormal.getY( ) > 0.0f ) ? -m_oDimension.getY( ) : m_oDimension.getY( );
      fZ += ( rNormal.getZ( ) > 0.0f ) ? -m_oDimension.getZ( ) : m_oDimension.getZ( );

      oTest.setX( fX );
      oTest.setY( fY );
      oTest.setZ( fZ );

      if( rPlane.getDistanceToPoint( oTest ) <= 0.0f ) {
         return true;
      } // if
   } // for
   return false;

} // OBB::intersection

bool OBB::intersection( const primitives::Vector3D &rkPoint ) {
   primitives::Vector3D oTranslation = getTranslation( );

   return(  ( oTranslation.getX( ) + m_oDimension.getX( ) >= rkPoint.getX( ) ) &&
            ( oTranslation.getX( ) - m_oDimension.getX( ) <= rkPoint.getX( ) ) &&
            ( oTranslation.getY( ) + m_oDimension.getY( ) >= rkPoint.getY( ) ) &&
            ( oTranslation.getY( ) - m_oDimension.getY( ) <= rkPoint.getY( ) ) &&
            ( oTranslation.getZ( ) + m_oDimension.getZ( ) >= rkPoint.getZ( ) ) &&
            ( oTranslation.getZ( ) - m_oDimension.getZ( ) <= rkPoint.getZ( ) ) );
} // OBB::intersection

bool OBB::intersection( const primitives::Ray &rkLine ) {
   primitives::Ray oLine = rkLine;
   primitives::Vector3D oAbsDir;
   float fAbsWCrossDdU, fRhs;

   primitives::Vector3D oDiff = oLine.getOrigin( ) - getTranslation( );
   primitives::Vector3D oDirection = oLine.getDirection( );
   primitives::Vector3D oWCrossD = oDirection ^ oDiff;

   oAbsDir.setY( fabsf( oLine.getDirection( ).getY( ) ) );
   oAbsDir.setZ( fabsf( oLine.getDirection( ).getZ( ) ) );
   fAbsWCrossDdU = fabsf( oWCrossD.getX( ) );
   fRhs = m_oDimension.getY( ) * oAbsDir.getZ( ) + m_oDimension.getZ( ) * oAbsDir.getY( );

   if( fAbsWCrossDdU > fRhs ) {
      return false;
   } // if

   oAbsDir.setX( fabsf( oLine.getDirection( ).getZ( ) ) );
   fAbsWCrossDdU = fabsf( oWCrossD.getY( ) );
   fRhs = m_oDimension.getX( ) * oAbsDir.getZ( ) + m_oDimension.getZ( ) * oAbsDir.getX( );

   if( fAbsWCrossDdU > fRhs ) {
      return false;
   } // if

   fAbsWCrossDdU = fabsf( oWCrossD.getZ( ) );
   fRhs = m_oDimension.getX( ) * oAbsDir.getY( ) + m_oDimension.getY( ) * oAbsDir.getX( );

   if( fAbsWCrossDdU > fRhs ) {
      return false;
   } // if

   return true;
} // OBB::intersection

bool OBB::intersection( const primitives::Plane &rkPlane ) {
   primitives::Plane oPlane = rkPlane;
   primitives::Vector3D oTranslation = getTranslation( );
   primitives::Vector3D oPlaneNormal = oPlane.getNormal( );

   //Test most negative point
   float fX = oTranslation.getX( );
   float fY = oTranslation.getY( );
   float fZ = oTranslation.getZ( );

   fX -= ( oPlaneNormal.getX( ) < 0.0f ) ? -m_oDimension.getX( ) : m_oDimension.getX( );
   fY -= ( oPlaneNormal.getY( ) < 0.0f ) ? -m_oDimension.getY( ) : m_oDimension.getY( );
   fZ -= ( oPlaneNormal.getZ( ) < 0.0f ) ? -m_oDimension.getZ( ) : m_oDimension.getZ( );

   oTranslation.setX( fX );
   oTranslation.setY( fY );
   oTranslation.setZ( fZ );

   float fDistance = oPlane.getDistanceToPoint( oTranslation );

   if( fDistance > 0.0f ) {
      return false;
   } // if

   //Test most positive point
   oTranslation = getTranslation( );

   fX += ( oPlaneNormal.getX( ) < 0.0f ) ? -m_oDimension.getX( ) : m_oDimension.getX( );
   fY += ( oPlaneNormal.getY( ) < 0.0f ) ? -m_oDimension.getY( ) : m_oDimension.getY( );
   fZ += ( oPlaneNormal.getZ( ) < 0.0f ) ? -m_oDimension.getZ( ) : m_oDimension.getZ( );

   fDistance = oPlane.getDistanceToPoint( oTranslation );

   if( fDistance < 0.0f ) {
      return false;
   } // if

   return true;
} // OBB::intersection

void OBB::renderOutlines( const primitives::Color &rkColor ) {
   primitives::RenderPrimitive *pOutlines;

   primitives::VertexDiffuseBuffer *pVertexHandler =
      new primitives::VertexDiffuseBuffer( 8 );

   primitives::LineBuffer *pPolygonHandler =
      new primitives::LineBuffer( 12 );

   primitives::VertexBuffer *pVertexBuffer =
      Core::get( )->getVideoManager( )->createVertexBuffer(
         pVertexHandler->getNumElements( ),
         primitives::VertexDiffuse::s_oFormat,
         pVertexHandler->getData( )
      );

   primitives::PolygonBuffer *pPolygonBuffer =
      Core::get( )->getVideoManager( )->createPolygonBuffer(
         pPolygonHandler->getNumElements( ),
         primitives::Line::getNumVertices( ),
         pPolygonHandler->getData( )
      );


   pOutlines = new primitives::RenderPrimitive(
      primitives::RenderPrimitive::MODE_LINES,
      primitives::RenderPrimitive::POLYGON_LINE
   );
   pOutlines->setVertexBuffer( pVertexBuffer );
   pOutlines->setPolygonBuffer( pPolygonBuffer );

   /*
         TFL------TFR
         /|      / |
        / |     /  |
      TBL-|----TBR |
       | BFL----|-BFR
       | /      | /
       |/       |/
      BBL------BBR
      first letter: T (Top) B (Bottom)
      second letter: B (Back) F (Front)
      third letter: F (Left) R (Right)
   */
   primitives::Vector3D oBottomBackLeft, oBottomBackRight, oBottomFrontLeft, oBottomFrontRight;
   primitives::Vector3D oTopBackLeft, oTopBackRight, oTopFrontLeft, oTopFrontRight;

   // setup OBB outlines vertex
   oBottomBackLeft = primitives::Vector3D::ORIGO;
   oTopFrontRight = m_oDimension;
   //oBottomBackLeft = m_oDimension;
   //oTopFrontRight = oBottomBackLeft * 2;

   oTopFrontLeft.setX( oBottomBackLeft.getX( ) );
   oTopFrontLeft.setY( oTopFrontRight.getY( ) );
   oTopFrontLeft.setZ( oTopFrontRight.getZ( ) );

   oBottomFrontLeft.setX( oBottomBackLeft.getX( ) );
   oBottomFrontLeft.setY( oBottomBackLeft.getY( ) );
   oBottomFrontLeft.setZ( oTopFrontRight.getZ( ) );

   oBottomFrontRight.setX( oTopFrontRight.getX( ) );
   oBottomFrontRight.setY( oBottomBackLeft.getY( ) );
   oBottomFrontRight.setZ( oTopFrontRight.getZ( ) );

   oTopBackLeft.setX( oBottomBackLeft.getX( ) );
   oTopBackLeft.setY( oTopFrontRight.getY( ) );
   oTopBackLeft.setZ( oBottomBackLeft.getZ( ) );

   oTopBackRight.setX( oTopFrontRight.getX( ) );
   oTopBackRight.setY( oTopFrontRight.getY( ) );
   oTopBackRight.setZ( oBottomBackLeft.getZ( ) );

   oBottomBackRight.setX( oTopFrontRight.getX( ) );
   oBottomBackRight.setY( oBottomBackLeft.getY( ) );
   oBottomBackRight.setZ( oBottomBackLeft.getZ( ) );

   // setup vertexes
   pVertexHandler->getElementAt( 0 ).setAll( oBottomBackLeft, rkColor );
   pVertexHandler->getElementAt( 1 ).setAll( oBottomBackRight, rkColor );
   pVertexHandler->getElementAt( 2 ).setAll( oBottomFrontLeft, rkColor );
   pVertexHandler->getElementAt( 3 ).setAll( oBottomFrontRight, rkColor );
   pVertexHandler->getElementAt( 4 ).setAll( oTopBackLeft, rkColor );
   pVertexHandler->getElementAt( 5 ).setAll( oTopBackRight, rkColor );
   pVertexHandler->getElementAt( 6 ).setAll( oTopFrontLeft, rkColor );
   pVertexHandler->getElementAt( 7 ).setAll( oTopFrontRight, rkColor );

   // setup lines
   pPolygonHandler->getElementAt( 0 ).setAll( 0, 1 );
   pPolygonHandler->getElementAt( 1 ).setAll( 0, 2 );
   pPolygonHandler->getElementAt( 2 ).setAll( 0, 4 );
   pPolygonHandler->getElementAt( 3 ).setAll( 7, 3 );
   pPolygonHandler->getElementAt( 4 ).setAll( 7, 5 );
   pPolygonHandler->getElementAt( 5 ).setAll( 7, 6 );
   pPolygonHandler->getElementAt( 6 ).setAll( 4, 5 );
   pPolygonHandler->getElementAt( 7 ).setAll( 4, 6 );
   pPolygonHandler->getElementAt( 8 ).setAll( 3, 1 );
   pPolygonHandler->getElementAt( 9 ).setAll( 3, 2 );
   pPolygonHandler->getElementAt( 10 ).setAll( 1, 5 );
   pPolygonHandler->getElementAt( 11 ).setAll( 6, 2 );

   m_oTransformation = getRotation( ).toMatrix4x4( );
   m_oTransformation.setElement( 0, 3, getTranslation( ).getX( ) );
   m_oTransformation.setElement( 1, 3, getTranslation( ).getY( ) );
   m_oTransformation.setElement( 2, 3, getTranslation( ).getZ( ) );

   pOutlines->setModelViewMatrix( &m_oTransformation );

   Core::get( )->getVideoManager( )->render( *pOutlines );

} // renderOutlines


	}; // scenenode
}; // namespace powergine
