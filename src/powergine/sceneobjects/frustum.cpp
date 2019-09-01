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


#include <powergine/sceneobjects/frustum.h>
#include <powergine/core.h>


namespace powergine {
	namespace sceneobjects {

// Constructors/Destructors
// Methods
Frustum::Frustum( ) :
   SRTNode( ),
   m_oViewMatrix( primitives::Matrix4x4::IDENTITY ),
   m_oViewDirection( primitives::Vector3D::ORIGO ),
   m_oTransformation( primitives::Matrix4x4::IDENTITY ),
   m_fZNear( 0.0f ),
   m_fZFar( 0.0f )
{
  
}

bool Frustum::intersection( const primitives::Vector3D &rkPoint ) {
   for ( int i=0; i < 6; i++ ) {
      if ( m_oPlanes[ i ].getDistanceToPoint( rkPoint ) > 0.0f ) {
         return false;
      } // if
   } // for
   return true;
}
bool Frustum::intersection( const primitives::Plane &rkPlane ) {
  return false; // arrumar
}
bool Frustum::intersection( const primitives::Line &rkLine ) {
  return false;
}
bool Frustum::intersection( const primitives::Triangle &rkTriangle ) {
  return false;
}

primitives::Plane& Frustum::getPlane( PLANE ePlane ) {
   return m_oPlanes[ ePlane ];
} // getPlane

float Frustum::getZNear( ) const {
   return m_fZNear;
}
   
void Frustum::setZNear( float fZNear ) {
   m_fZNear = fZNear;
}
   
float Frustum::getZFar( ) const {
   return m_fZFar;
}
   
void Frustum::setZFar( float fZFar ) {
   m_fZFar = fZFar;
}

const primitives::Vector3D& Frustum::getViewDirection( ) const {
   return m_oViewDirection;
}

void Frustum::setViewDirection( const primitives::Vector3D &rkViewDirection ) {
   m_oViewDirection = rkViewDirection;
}

Frustum::PLANE Frustum::operator[]( int iPlane ) const {
   switch ( iPlane ) {
      case 0: return PLANE_LEFT;
      case 1: return PLANE_RIGHT;
      case 2: return PLANE_TOP;
      case 3: return PLANE_BOTTOM;
      case 4: return PLANE_NEAR;
      case 5: return PLANE_FAR;
      default:
      throw( std::string( "Invalid plane!" ) );
   } // switch
} // operator[]

	}; // sceneobjects
}; // namespace powergine
