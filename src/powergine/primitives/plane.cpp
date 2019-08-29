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


#include <powergine/primitives/plane.h>

namespace powergine {
	namespace primitives {
	
// Constructors/Destructors
// Methods

Plane::Plane ( ) {
   m_fDistanceToOrigo = 0.0f;
   m_oNormal = Vector3D::ORIGO;
} // Plane

Plane::Plane ( const Vector3D &rkNormal, float fDistanceToOrigo ) {
   m_fDistanceToOrigo = fDistanceToOrigo;
   m_oNormal = rkNormal;
} // Plane

Plane::Plane ( const Vector3D &rkNormal, const Vector3D &rkPointInPlane ) {
   m_oNormal = rkNormal;   
   // Use Dot Product to find distance
   m_fDistanceToOrigo = -( rkPointInPlane * m_oNormal );	
} // Plane

void Plane::setNormal ( const Vector3D &rkNormal ) {
   m_oNormal = rkNormal;
} // setNormal

const Vector3D &Plane::getNormal ( ) const {
   return m_oNormal;
} // getNormal

void Plane::setDistanceToOrigo( float fDistance ) {
   m_fDistanceToOrigo = fDistance;
} // setDistance

float Plane::getDistanceFromOrigo( ) const {
   return -m_fDistanceToOrigo;
} // getDistanceFromOrigo

float Plane::getDistanceToPoint( const Vector3D &rkPoint ) const {   
   return ( m_oNormal * rkPoint + m_fDistanceToOrigo );
} // getDistanceFromOrigo

void Plane::normalize( ) {
   float fMag = m_oNormal.magnitude( );
   m_oNormal /= fMag;
   m_fDistanceToOrigo /= fMag;
} // normalize

Vector3D Plane::getPointOnPlane ( ) const{
   return ( m_oNormal * -m_fDistanceToOrigo );
} // getPointInPlane

bool Plane::operator==( const Plane &rkPlane ) const {   
   return( ( m_oNormal == rkPlane.getNormal( ) ) && 
      ( getDistanceFromOrigo( ) == rkPlane.getDistanceFromOrigo( ) ) );
} // operator==

	}; // primitives
}; // namespace powergine
