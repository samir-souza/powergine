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


#include <powergine/sceneobjects/aabb.h>

namespace powergine {
	namespace sceneobjects {

AABB::AABB( const primitives::Vector3D &rkDimension ) :
   m_oDimension( rkDimension )
{
}

AABB::~AABB( ) {
}

void AABB::setDimension( const primitives::Vector3D &rkDimension ) {
   m_oDimension = rkDimension;
}

const primitives::Vector3D& AABB::getDimension( ) const {
   return m_oDimension;
}

bool AABB::collide( const AABB &rkBoundingVolume, utils::ContactSet *pContactSet ) {
   //TODO: collide AABB-boundingbox
	assert(false);
   return false;
} // AABB::collide

bool AABB::collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet ) {
   //TODO: collide AABB-ray
	assert(false);
   return false;
} // AABB::collide

bool AABB::intersection( Frustum *pFrustum ) {
   primitives::Vector3D oTest;

   for( int iPlane = 0; iPlane < 6; ++iPlane ) {
      oTest = getTranslation( );
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

} // AABB::intersection

bool AABB::intersection( const primitives::Vector3D &rkPoint ) {
   primitives::Vector3D oTranslation = getTranslation( );

   return(  ( oTranslation.getX( ) + m_oDimension.getX( ) >= rkPoint.getX( ) ) &&
            ( oTranslation.getX( ) - m_oDimension.getX( ) <= rkPoint.getX( ) ) &&
            ( oTranslation.getY( ) + m_oDimension.getY( ) >= rkPoint.getY( ) ) &&
            ( oTranslation.getY( ) - m_oDimension.getY( ) <= rkPoint.getY( ) ) &&
            ( oTranslation.getZ( ) + m_oDimension.getZ( ) >= rkPoint.getZ( ) ) &&
            ( oTranslation.getZ( ) - m_oDimension.getZ( ) <= rkPoint.getZ( ) ) );
} // AABB::intersection

bool AABB::intersection( const primitives::Ray &rkLine ) {
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
} // AABB::intersection

bool AABB::intersection( const primitives::Plane &rkPlane ) {
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
} // AABB::intersection

void AABB::renderOutlines( const primitives::Color &rkColor ) {
   OBB oOBB( m_oDimension );
   oOBB.doTranslation( getTranslation( ) );
   oOBB.renderOutlines( rkColor );
} // renderOutlines

	}; // scenenode
}; // namespace powergine
