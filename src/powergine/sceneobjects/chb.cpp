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


#include <powergine/sceneobjects/chb.h>

namespace powergine {
	namespace sceneobjects {

CHB::CHB( ) : BoundingVolume( )
{
}

CHB::~CHB( ) {
   std::vector<primitives::Plane*>::iterator ppBegin = m_vecPlanes.begin( );
   std::vector<primitives::Plane*>::iterator ppEnd = m_vecPlanes.end( );

   while( ppBegin != ppEnd ) {
      delete *ppBegin;
      ppBegin++;
   } // while
} // ~CHB

void CHB::addPlane( primitives::Plane *pPlane ) {
   std::vector<primitives::Plane*>::iterator ppBegin = m_vecPlanes.begin( );
   std::vector<primitives::Plane*>::iterator ppEnd = m_vecPlanes.end( );

   while( ppBegin != ppEnd ) {
      if ( *ppBegin == pPlane ) {
         return;
      } // if
      ppBegin++;
   } // while
   m_vecPlanes.push_back( pPlane );
} // addPlane

void CHB::removePlane( primitives::Plane *pPlane ) {
   std::vector<primitives::Plane*>::iterator ppBegin = m_vecPlanes.begin( );
   std::vector<primitives::Plane*>::iterator ppEnd = m_vecPlanes.end( );

   while( ppBegin != ppEnd ) {
      if ( *ppBegin == pPlane ) {
         m_vecPlanes.erase( ppBegin );
      } // if
      ppBegin++;
   } // while
} // removePlane

bool CHB::collide( const AABB &rkBoundingVolume, utils::ContactSet *pContactSet ) {
   std::vector<primitives::Plane*>::iterator ppBegin = m_vecPlanes.begin( );
   std::vector<primitives::Plane*>::iterator ppEnd = m_vecPlanes.end( );

   primitives::Vector3D oCandidateToHitNormal;
   primitives::Vector3D oAABBMin = rkBoundingVolume.getTranslation( );
   primitives::Vector3D oAABBMax = rkBoundingVolume.getTranslation( ) +
      rkBoundingVolume.getDimension( );
   bool bStartsOut = false;
   bool bEndsOut = false;

   float fStartFraction = -1.0f;	// The S in the pictures
   float fEndFraction = 1.0f;		// The E in the pictures

   while( ppBegin != ppEnd ) {
      primitives::Plane *pPlane = *ppBegin;
      primitives::Vector3D oOffset;
      primitives::Vector3D oNormal = pPlane->getNormal( );
      float fStartDistance, fEndDistance;

      oOffset.setX(
         ( oNormal.getX( ) < 0 ) ? oAABBMax.getX( ) : oAABBMin.getX( )
      );
      oOffset.setY(
         ( oNormal.getY( ) < 0 ) ? oAABBMax.getY( ) : oAABBMin.getY( )
      );
      oOffset.setZ(
         ( oNormal.getZ( ) < 0 ) ? oAABBMax.getZ( ) : oAABBMin.getZ( )
      );

      fStartDistance = ( oAABBMin.getX( ) + oOffset.getX( ) ) * pPlane->getNormal( ).getX( ) +
                       ( oAABBMin.getY( ) + oOffset.getY( ) ) * pPlane->getNormal( ).getY( ) +
                       ( oAABBMin.getZ( ) + oOffset.getZ( ) ) * pPlane->getNormal( ).getZ( ) - pPlane->getDistanceFromOrigo( );

      fEndDistance = ( oAABBMax.getX( ) + oOffset.getX( ) ) * pPlane->getNormal( ).getX( ) +
                     ( oAABBMax.getY( ) + oOffset.getY( ) ) * pPlane->getNormal( ).getY( ) +
                     ( oAABBMax.getZ( ) + oOffset.getZ( ) ) * pPlane->getNormal( ).getZ( ) - pPlane->getDistanceFromOrigo( );

	  if ( fStartDistance > 0 ) {
		bStartsOut = true;
	  } // if
	  if ( fEndDistance > 0 ) {
		bEndsOut = true;
	  } // if

	  if ( fStartDistance > 0  && fEndDistance > 0 ) {
	  		return false;
	  } // if

	  if ( fStartDistance <= 0  && fEndDistance <= 0 ) {
	  		continue;
	  } // if

		if ( fStartDistance > fEndDistance )		{
			float fFraction = ( fStartDistance - primitives::Quaternion::SQR_EPSILON ) / (fStartDistance - fEndDistance);
			if ( fFraction > fStartFraction){
				fStartFraction = fFraction;
				oCandidateToHitNormal = pPlane->getNormal( );
			} // if
		} else {
			float fFraction = ( fStartDistance + primitives::Quaternion::SQR_EPSILON ) / (fStartDistance - fEndDistance);
			if (fFraction < fEndFraction) {
				fEndFraction = fFraction;
			} // if
		} // else

      ++ppBegin;
   } // while

   	// After checking all sides if startOut remain false, then the Start Point is complete in the brush

	if ( bStartsOut == false ) {
		//MoveData.StartOut = false;
		// if also the EndPoint is in this brush, then the ray is complete in this brush
		if ( bEndsOut == false) {
			//MoveData.AllSolid = true;
		} // if
		return true;
	} // if

	// if there was collision against the brush (S < E)
	if ( fStartFraction < fEndFraction) {
		// And of course if we move S (if we don't then we don't enter the brush
		// and we don't collide with some nearest brush
		/*
		if ( fStartFraction > -1 && fStartFraction < MoveData.Fraction) {
			// UpDate OutPut values
			if (startFraction < 0)  {
				startFraction = 0;
			} // if
			MoveData.Fraction		 = startFraction;
			MoveData.CollisionNormal = CandidateToHitNormal; // The candidate gets postulate!
		}
		*/
	} // if

   return false;
} // collide

bool CHB::collide( const CHB &rkBoundingVolume, utils::ContactSet *pContactSet ) {
   //TODO: collide CHB-boundingbox
	assert(false);
   return false;
} // CHB::collide

bool CHB::collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet ) {
   //TODO: collide CHB-ray
	assert(false);
   return false;
} // CHB::collide

bool CHB::intersection( Frustum *pFrustum ) {
/*
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
   */
	// TODO: must be implemented
	assert(false);
   return false;

} // CHB::intersection

bool CHB::intersection( const primitives::Vector3D &rkPoint ) {
   return false;
} // CHB::intersection

bool CHB::intersection( const primitives::Ray &rkLine ) {
   primitives::Ray oLine = rkLine;
   primitives::Vector3D oAbsDir;
   float fAbsWCrossDdU, fRhs;

   primitives::Vector3D oDiff = oLine.getOrigin( ) - getTranslation( );
   primitives::Vector3D oDirection = oLine.getDirection( );
   primitives::Vector3D oWCrossD = oDirection ^ oDiff;

   oAbsDir.setY( fabsf( oLine.getDirection( ).getY( ) ) );
   oAbsDir.setZ( fabsf( oLine.getDirection( ).getZ( ) ) );
   fAbsWCrossDdU = fabsf( oWCrossD.getX( ) );
//   fRhs = m_oDimension.getY( ) * oAbsDir.getZ( ) + m_oDimension.getZ( ) * oAbsDir.getY( );

   if( fAbsWCrossDdU > fRhs ) {
      return false;
   } // if

   oAbsDir.setX( fabsf( oLine.getDirection( ).getZ( ) ) );
   fAbsWCrossDdU = fabsf( oWCrossD.getY( ) );
//   fRhs = m_oDimension.getX( ) * oAbsDir.getZ( ) + m_oDimension.getZ( ) * oAbsDir.getX( );

   if( fAbsWCrossDdU > fRhs ) {
      return false;
   } // if

   fAbsWCrossDdU = fabsf( oWCrossD.getZ( ) );
   //fRhs = m_oDimension.getX( ) * oAbsDir.getY( ) + m_oDimension.getY( ) * oAbsDir.getX( );

   if( fAbsWCrossDdU > fRhs ) {
      return false;
   } // if

   return true;
} // CHB::intersection

bool CHB::intersection( const primitives::Plane &rkPlane ) {
   primitives::Plane oPlane = rkPlane;
   primitives::Vector3D oTranslation = getTranslation( );
   primitives::Vector3D oPlaneNormal = oPlane.getNormal( );

   //Test most negative point
   float fX = oTranslation.getX( );
   float fY = oTranslation.getY( );
   float fZ = oTranslation.getZ( );

/*
   fX -= ( oPlaneNormal.getX( ) < 0.0f ) ? -m_oDimension.getX( ) : m_oDimension.getX( );
   fY -= ( oPlaneNormal.getY( ) < 0.0f ) ? -m_oDimension.getY( ) : m_oDimension.getY( );
   fZ -= ( oPlaneNormal.getZ( ) < 0.0f ) ? -m_oDimension.getZ( ) : m_oDimension.getZ( );
*/
   oTranslation.setX( fX );
   oTranslation.setY( fY );
   oTranslation.setZ( fZ );

   float fDistance = oPlane.getDistanceToPoint( oTranslation );

   if( fDistance > 0.0f ) {
      return false;
   } // if

   //Test most positive point
   oTranslation = getTranslation( );

/*
   fX += ( oPlaneNormal.getX( ) < 0.0f ) ? -m_oDimension.getX( ) : m_oDimension.getX( );
   fY += ( oPlaneNormal.getY( ) < 0.0f ) ? -m_oDimension.getY( ) : m_oDimension.getY( );
   fZ += ( oPlaneNormal.getZ( ) < 0.0f ) ? -m_oDimension.getZ( ) : m_oDimension.getZ( );
*/
   fDistance = oPlane.getDistanceToPoint( oTranslation );

   if( fDistance < 0.0f ) {
      return false;
   } // if

   return true;
} // CHB::intersection

void CHB::renderOutlines( const primitives::Color &rkColor ) {
	// TODO: must be implemented
} // renderOutlines

	}; // scenenode
}; // namespace powergine
