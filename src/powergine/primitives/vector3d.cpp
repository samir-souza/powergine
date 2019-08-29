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


#include <powergine/primitives/vector3d.h>
 
namespace powergine {
   namespace primitives {  

// Copy constructor
Vector3D::Vector3D( const Vector3D &rkVector ) :
   m_fX( rkVector.getX( ) ),
   m_fY( rkVector.getY( ) ),
   m_fZ( rkVector.getZ( ) )
{
} // Vector3D

// Custom constructor
Vector3D::Vector3D( float fX, float fY, float fZ ) :
   m_fX( fX ),
   m_fY( fY ),
   m_fZ( fZ )
{
} // Vector3D


float Vector3D::magnitude( ) const {
   return static_cast<float>( sqrt( m_fX*m_fX + m_fY*m_fY + m_fZ*m_fZ ) );
} // magnitude

void Vector3D::normalize( ) {
   float fMagnitude = static_cast<float>( sqrt( m_fX*m_fX + m_fY*m_fY + m_fZ*m_fZ ) );
   if( fMagnitude <= TOLERANCE ) {
      fMagnitude = 1.0f;
   } // if
   m_fX /= fMagnitude;
   m_fY /= fMagnitude;
   m_fZ /= fMagnitude;
   
   if( fabs( m_fX ) < TOLERANCE ) m_fX = 0.0f;
   if( fabs( m_fY ) < TOLERANCE ) m_fY = 0.0f;
   if( fabs( m_fZ ) < TOLERANCE ) m_fZ = 0.0f;
} // normalize

void Vector3D::reverse( ) {
   m_fX = -m_fX;
   m_fY = -m_fY;
   m_fZ = -m_fZ;
} // reverse

Vector3D& Vector3D::operator+=( const Vector3D &rkVec ) {
   m_fX += rkVec.getX( );
   m_fY += rkVec.getY( );
   m_fZ += rkVec.getZ( );
   return *this;
} // operator+=

Vector3D& Vector3D::operator-=( const Vector3D &rkVec ) {
   m_fX -= rkVec.getX( );
   m_fY -= rkVec.getY( );
   m_fZ -= rkVec.getZ( );
   return *this;
} // operator-=

float Vector3D::operator*( const Vector3D &rkVec ) const {
   return( m_fX * rkVec.getX( ) + m_fY * rkVec.getY( ) + m_fZ * rkVec.getZ( ) );
} // operator*

Vector3D& Vector3D::operator*=( float fScalar ) {
   m_fX *= fScalar;
   m_fY *= fScalar;
   m_fZ *= fScalar;
   return *this;
} // operator*=

Vector3D Vector3D::operator*( float fScalar ) const {
   return Vector3D( m_fX * fScalar, m_fY * fScalar, m_fZ * fScalar );   
} // operator*

Vector3D& Vector3D::operator/=( float fScalar ) {
   m_fX /= fScalar;
   m_fY /= fScalar;
   m_fZ /= fScalar;
   return *this;
} // operator/=

Vector3D Vector3D::operator-( ) const {
   return Vector3D( -m_fX, -m_fY, -m_fZ );
} // operator-

Vector3D Vector3D::operator+( const Vector3D &rkVector ) const {
   return Vector3D( m_fX + rkVector.getX( ), m_fY + rkVector.getY( ), m_fZ + rkVector.getZ( ) );
} // operator+

Vector3D Vector3D::operator-( const Vector3D &rkVector ) const {
   return Vector3D( m_fX - rkVector.getX( ), m_fY - rkVector.getY( ), m_fZ - rkVector.getZ( ) );
} // operator-

Vector3D& Vector3D::operator=( const Vector3D &rkVector ) {
   m_fX = rkVector.getX( );
   m_fY = rkVector.getY( );
   m_fZ = rkVector.getZ( );
   return *this;
} // operator=

Vector3D Vector3D::operator/ ( float fScalar ) const {
   return Vector3D( m_fX / fScalar, m_fY / fScalar, m_fZ / fScalar );
} // operator/

Vector3D Vector3D::operator^( const Vector3D &rkVec ) {
   return Vector3D( m_fY * rkVec.getZ( ) - m_fZ * rkVec.getY( ),
                    m_fZ * rkVec.getX( ) - m_fX * rkVec.getZ( ),
                    m_fX * rkVec.getY( ) - m_fY * rkVec.getX( ) );
} // operator*

bool Vector3D::operator==( const Vector3D &rkVec ) const {
   return(( m_fX == rkVec.getX( ) ) &&( m_fY == rkVec.getY( ) ) &&( m_fZ == rkVec.getZ( ) ) );
} // operator==


float Vector3D::getX( ) const {   
   return m_fX;
} // tX

float Vector3D::getY( ) const {
   return m_fY;
} // getY

float Vector3D::getZ( ) const {
   return m_fZ;
} // getZ

void Vector3D::setX( float fX ) {
   m_fX = fX;
} // setX

void Vector3D::setY( float fY ) {
   m_fY = fY;
} // setY

void Vector3D::setZ( float fZ ) {
   m_fZ = fZ;
} // setZ

std::string Vector3D::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << "X(" << m_fX;
   sstrDesc << ") Y(" << m_fY;
   sstrDesc << ") Z(" << m_fZ;   
   sstrDesc << ") ";
   return sstrDesc.str( );        
} // toString

const float Vector3D::TOLERANCE = 0.0001f;
const Vector3D Vector3D::ORIGO = Vector3D( 0.0f, 0.0f, 0.0f );
const int Vector3D::NUM_COMPONENTS = 3;
const int Vector3D::TYPE_SIZE = Vector3D::NUM_COMPONENTS * sizeof( float );

   }; // primitives
}; // powergine
