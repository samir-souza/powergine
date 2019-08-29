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


#include <powergine/primitives/quaternion.h>


namespace powergine {
	namespace primitives {
		
// Constructors/Destructors
// Methods

const Quaternion Quaternion::IDENTITY( 0.0f, 0.0f, 0.0f, 1.0f );

const float Quaternion::SQR_EPSILON = 0.000001f;
	
Quaternion::Quaternion( ) {
   m_oVector.setX( 0.0f );
   m_oVector.setY( 0.0f );
   m_oVector.setZ( 0.0f );
   m_fW = 1.0f;
}

Quaternion::Quaternion( float fAngle, const Vector3D &rkAxis ) {
   // the angle in degrees must be converted to radians
   double dRadAngle = utils::MathHelper::get( )->degree2Radians( fAngle );   

   Vector3D oAxis = rkAxis;
   oAxis.normalize( );
   
   float fSinAngle, fCosAngle, fX, fY, fZ;
   
   fSinAngle = sin( dRadAngle / 2.0f );
   fCosAngle = cos( dRadAngle / 2.0f );
   
   fX = oAxis.getX( ) * fSinAngle;
   fY = oAxis.getY( ) * fSinAngle;
   fZ = oAxis.getZ( ) * fSinAngle;
   
   m_oVector.setX( fX );
   m_oVector.setY( fY );
   m_oVector.setZ( fZ );      
   
   m_fW = fCosAngle;
   
   // if some attribute is very close to zero do a quaternion normalize
   if ( fX < SQR_EPSILON || fY < SQR_EPSILON || fZ < SQR_EPSILON || fCosAngle < SQR_EPSILON ) {
      normalize( );
   } // if   

}
   
Quaternion::Quaternion( const Matrix4x4 &rkMatrix ) {
   *this = rkMatrix;
}

Quaternion::Quaternion( float fX, float fY, float fZ, float fW ) {   
   m_oVector.setX( fX );
   m_oVector.setY( fY );
   m_oVector.setZ( fZ );
   m_fW = fW;
} // Quaternion

Quaternion::Quaternion( const Vector3D &rkVector, float fW ) {
   m_oVector = rkVector;
   m_fW = fW;
} // Quaternion

Quaternion::Quaternion( const Quaternion &rkQuat ) {
   m_oVector = rkQuat.getVector( );
   m_fW = rkQuat.getScalar( )   ;
} // Quaternion

float Quaternion::magnitude( ) const {
   return m_oVector.magnitude( );         
} // magnitude

void Quaternion::normalize( ) {   
   float fNorm = m_oVector.getX( ) * m_oVector.getX( ) + 
                 m_oVector.getY( ) * m_oVector.getY( ) + 
                 m_oVector.getZ( ) * m_oVector.getZ( ) + 
                 m_fW * m_fW;

   if( fNorm < SQR_EPSILON ) {
      m_oVector.setX( 0.0f );
      m_oVector.setY( 0.0f );
      m_oVector.setZ( 0.0f );
      m_fW = 1.0f;
   } else if( fabs( fNorm - 1.0f ) > SQR_EPSILON ) {
      float fScale = 1.0f / sqrtf( fNorm );
      m_oVector *= fScale;
      m_fW *= fScale;
   } // else if

} // normalize

Vector3D Quaternion::getVector( ) const {
   return m_oVector;
} // getVector

float Quaternion::getScalar( ) const {
   return m_fW;
} // getScalar

void Quaternion::setVector( const Vector3D &rkVector ) {
   m_oVector = rkVector;
} // setVector

void Quaternion::setScalar( float fScalar ) {
   m_fW = fScalar;
} // setScalar

float Quaternion::getAngle( ) const {
   return static_cast<float>( 2 * acos( m_fW ) );
} // getAngle
   
Vector3D Quaternion::getAxis( ) const {
   float fMag = m_oVector.magnitude( );
   Vector3D oVector;
   
   if ( fMag <= Vector3D::TOLERANCE ) {
      oVector = Vector3D( );
   } else {
      oVector = m_oVector / ( fMag );
   } // else
   return oVector;
} // getAxis
   
void Quaternion::rotate( const Quaternion &rkQuat ) {   
   *this *= ( rkQuat * ( ~(*this) ) );
} // rotate   

Vector3D Quaternion::rotateVector3D( const Vector3D &rkVector ) const {
   return Vector3D( ( *this * Quaternion( rkVector, 0.0f ) * ~(*this) ).getVector( ) );
} // rotateVector3D

Vector3D Quaternion::toEulerAngles( ) {
   assert( !"nao implementado" );
   return Vector3D( 0.0f, 0.0f, 0.0f );
} // toEulerAngles
   
Quaternion& Quaternion::fromEulerAngles( const Vector3D &rkEulerAngles ) {
   Quaternion oQuat;
   double dCosX, dCosY, dCosZ, dSinX, dSinY, dSinZ;
   double dCosZCosY, dSinZSinY, dCosZSinY, dSinZCosY;
   
   double dX = utils::MathHelper::get( )->degree2Radians( rkEulerAngles.getX( ) );
   double dY = utils::MathHelper::get( )->degree2Radians( rkEulerAngles.getY( ) );
   double dZ = utils::MathHelper::get( )->degree2Radians( rkEulerAngles.getZ( ) );

   dCosX = cos( 0.5f * dX );
   dCosY = cos( 0.5f * dY );
   dCosZ = cos( 0.5f * dZ );
   
   dSinX = sin( 0.5f * dX );
   dSinY = sin( 0.5f * dY );
   dSinZ = sin( 0.5f * dZ );
   
   dCosZCosY = dCosZ * dCosY;
   dSinZSinY = dSinZ * dSinY;
   dCosZSinY = dCosZ * dSinY;
   dSinZCosY = dSinZ * dCosY;
   
   m_oVector.setX( dCosZCosY * dSinX - dSinZSinY * dCosX );
   m_oVector.setY( dCosZSinY * dCosX + dSinZCosY * dSinX );
   m_oVector.setZ( dSinZCosY * dCosX - dCosZSinY * dSinX );
   m_fW =          dCosZCosY * dCosX + dSinZSinY * dSinX;
      
   return *this;
} // fromEulerAngles

Matrix4x4 Quaternion::toMatrix4x4( ) const {

   //     ¦       2     2							 ¦
   //     ¦ 1 - (2y  + 2z )   2xy + 2zw         2xz - 2yw		0	 ¦
   //     ¦								         ¦
   //     ¦                          2     2					 ¦
   // M = ¦ 2xy - 2zw         1 - (2x  + 2z )   2zy + 2xw		0	 ¦
   //     ¦									 ¦
   //     ¦                                            2     2			 ¦
   //     ¦ 2xz + 2yw         2yz - 2xw         1 - (2x  + 2y )	        0	 ¦
   //     ¦									 ¦
   //     ¦									 ¦
   //     ¦ 0		   0		     0				1	 ¦
   //     ¦									 ¦

   float fX = m_oVector.getX( );
   float fY = m_oVector.getY( );
   float fZ = m_oVector.getZ( );

   float f2x = fX * 2.0f;
   float f2y = fY * 2.0f;   
   float f2z = fZ * 2.0f;

   float f2xx = f2x * fX;
   float f2yy = f2y * fY;   
   float f2zz = f2z * fZ;   
      
   float f2xy = f2x * fY;
   float f2xz = f2x * fZ;   
   float f2xw = f2x * m_fW;
   
   float f2yz = f2y * fZ;
   float f2yw = f2y * m_fW;
   
   float f2zw = f2z * m_fW;
   
   Matrix4x4 oMatrix4x4;
   oMatrix4x4.setElement( 0, 0, 1.0f - ( f2yy + f2zz ) );
   oMatrix4x4.setElement( 0, 1, f2xy + f2zw );
   oMatrix4x4.setElement( 0, 2, f2xz - f2yw );
   oMatrix4x4.setElement( 0, 3, 0.0f );

   oMatrix4x4.setElement( 1, 0, f2xy - f2zw );
   oMatrix4x4.setElement( 1, 1, 1.0f - ( f2xx + f2zz ) );
   oMatrix4x4.setElement( 1, 2, f2yz + f2xw );
   oMatrix4x4.setElement( 1, 3, 0.0f );
   
   oMatrix4x4.setElement( 2, 0, f2xz + f2yw );
   oMatrix4x4.setElement( 2, 1, f2yz - f2xw );
   oMatrix4x4.setElement( 2, 2, 1.0f - ( f2xx + f2yy ) );
   oMatrix4x4.setElement( 2, 3, 0.0f );
   
   oMatrix4x4.setElement( 3, 0, 0.0f );
   oMatrix4x4.setElement( 3, 1, 0.0f );
   oMatrix4x4.setElement( 3, 2, 0.0f );
   oMatrix4x4.setElement( 3, 3, 1.0f );
   
   return oMatrix4x4;
   
}

Quaternion& Quaternion::operator=( const Matrix4x4 &rkMatrix ) {
   // Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
   // article "Quaternion Calculus and Fast Animation".

   float fTrace = rkMatrix.getElement( 0, 0 ) + 
                              rkMatrix.getElement( 1, 1 ) +
                              rkMatrix.getElement( 2, 2 );
   float fRoot;

   if( fTrace > 0.0 ) {
      fRoot = sqrtf( fTrace + 1.0f );

      m_fW = 0.5f * fRoot;

      fRoot = 0.5f / fRoot;

      m_oVector.setX( ( rkMatrix.getElement( 2, 1 ) - rkMatrix.getElement( 1, 2 ) ) * fRoot );
      m_oVector.setY( ( rkMatrix.getElement( 0, 2 ) - rkMatrix.getElement( 2, 0 ) ) * fRoot );
      m_oVector.setZ( ( rkMatrix.getElement( 1, 0 ) - rkMatrix.getElement( 0, 1 ) ) * fRoot );
   } else {
      int iNext[ 3 ] = { 1, 2, 0 };

      int i = 0;

      if( rkMatrix.getElement( 1, 1 ) > rkMatrix.getElement( 0, 0 ) ) {
            i = 1;
      } // if

      if( rkMatrix.getElement( 2, 2 ) > rkMatrix.getElement( i, i ) ) {
            i = 2;
      } // if

      int j = iNext[ i ];
      int k = iNext[ j ];

      fRoot = sqrtf( rkMatrix.getElement( i, i ) - rkMatrix.getElement( j, j ) - rkMatrix.getElement( k, k ) + 1.0f );

      float fQuat[ 3 ] = { m_oVector.getX( ),
                                             m_oVector.getY( ),
                                             m_oVector.getZ( ) };

      fQuat[ i ] = 0.5f * fRoot;

      fRoot = 0.5f / fRoot;

      m_fW = ( rkMatrix.getElement( k, j ) - rkMatrix.getElement( j, k ) ) * fRoot;

      fQuat[ j ] = ( rkMatrix.getElement( j, i ) + rkMatrix.getElement( i, j ) ) * fRoot;
      fQuat[ k ] = ( rkMatrix.getElement( k, i ) + rkMatrix.getElement( i, k ) ) * fRoot;
      
      m_oVector.setX( fQuat[ 0 ] );
      m_oVector.setX( fQuat[ 1 ] );
      m_oVector.setX( fQuat[ 2 ] );
   } // else

   normalize( );

   return *this;
}

Quaternion& Quaternion::operator=( const Quaternion &rkQuat ) {
   m_oVector = rkQuat.getVector( );
   m_fW = rkQuat.getScalar( );   
   return *this;
} // operator=

Quaternion Quaternion::operator+=( const Quaternion &rkQuat ) {
   m_fW += rkQuat.getScalar( );
   m_oVector += rkQuat.getVector( );
   return *this;
} // operator+=
   
Quaternion Quaternion::operator-=( const Quaternion &rkQuat ) {
   m_fW -= rkQuat.getScalar( );
   m_oVector -= rkQuat.getVector( );
   return *this;
} // operator-=

Quaternion Quaternion::operator*=( const Quaternion &rkQuat ) {   
   float fX1, fY1, fZ1, fW1;
   float fX2, fY2, fZ2, fW2;
   
   fX1 = m_oVector.getX( );
   fY1 = m_oVector.getY( );
   fZ1 = m_oVector.getZ( );
   fW1 = m_fW;
   
   fX2 = rkQuat.getVector( ).getX( );
   fY2 = rkQuat.getVector( ).getY( );
   fZ2 = rkQuat.getVector( ).getZ( );
   fW2 = rkQuat.getScalar( );
   
   m_oVector.setX( fW1*fX2 + fX1*fW2 + fY1*fZ2 - fZ1*fY2 );
   m_oVector.setY( fW1*fY2 + fY1*fW2 + fZ1*fX2 - fX1*fZ2 );
   m_oVector.setZ( fW1*fZ2 + fZ1*fW2 + fX1*fY2 - fY1*fX2 );
   m_fW = fW1*fW2 - fX1*fX2 - fY1*fY2 - fZ1*fZ2;

   return *this;
} // operator*=
   
Quaternion Quaternion::operator*=( float fScalar ) {
   m_fW *= fScalar;
   m_oVector *= fScalar;
   return *this;
} // operator*=
   
Quaternion Quaternion::operator/=( float fScalar ) {
   m_fW /= fScalar;
   m_oVector /= fScalar;
   return *this;
} // operator/=
   
Quaternion Quaternion::operator~ ( ) const {
   return Quaternion( -m_oVector, m_fW );
} // operator~
            
Quaternion Quaternion::operator+ ( const Quaternion &rkQuat ) const {
   return Quaternion( this->getVector( ) + rkQuat.getVector( ), this->getScalar( ) + rkQuat.getScalar( ) );
} // operator+
   
Quaternion Quaternion::operator- ( const Quaternion &rkQuat ) const {
   return Quaternion( this->getVector( ) - rkQuat.getVector( ), this->getScalar( ) - rkQuat.getScalar( ) );
} // operator-
   
Quaternion Quaternion::operator* ( const Quaternion &rkQuat ) const {
   
   float fX, fY, fZ, fW;
   float fX1, fY1, fZ1, fW1;
   float fX2, fY2, fZ2, fW2;
   
   fX1 = m_oVector.getX( );
   fY1 = m_oVector.getY( );
   fZ1 = m_oVector.getZ( );
   fW1 = m_fW;
   
   fX2 = rkQuat.getVector( ).getX( );
   fY2 = rkQuat.getVector( ).getY( );
   fZ2 = rkQuat.getVector( ).getZ( );
   fW2 = rkQuat.getScalar( );
   
   fX = fW1*fX2 + fX1*fW2 + fY1*fZ2 - fZ1*fY2;
   fY = fW1*fY2 + fY1*fW2 + fZ1*fX2 - fX1*fZ2;
   fZ = fW1*fZ2 + fZ1*fW2 + fX1*fY2 - fY1*fX2;
   fW = fW1*fW2 - fX1*fX2 - fY1*fY2 - fZ1*fZ2;

   return Quaternion( fX, fY, fZ, fW );
/*
   Vector3D oVec1 = m_oVector;
   Vector3D oVec2 = rkQuat.getVector( );
   Vector3D oVecResult = ( oVec1 ^ oVec2 ) + ( ( oVec1 * rkQuat.getScalar( ) + ( oVec2 * m_fW ) ) );
   
   return( Quaternion( oVecResult, ( ( m_fW * rkQuat.getScalar( ) ) - ( oVec1 * oVec2 ) ) ) );
 */
} // operator*
   
Quaternion Quaternion::operator* ( float fScalar ) const {
   return Quaternion( this->getVector( ).getX( ) * fScalar,
                      this->getVector( ).getY( ) * fScalar,
                      this->getVector( ).getZ( ) * fScalar,
                      this->getScalar( ) * fScalar );
} // operator*
     
Quaternion Quaternion::operator* ( const Vector3D &rkVector ) const {             
    float fX1, fY1, fZ1,  fX2, fY2, fZ2;
    fX1 = getVector( ).getX( );
    fY1 = getVector( ).getY( );
    fZ1 = getVector( ).getZ( );
    
    fX2 = rkVector.getX( );
    fY2 = rkVector.getY( );
    fZ2 = rkVector.getZ( );
    
    
    return Quaternion( m_fW*fX2 + fY1*fZ2 - fZ1*fY2,
                       m_fW*fY2 + fZ1*fX2 - fX1*fZ2, 
                       m_fW*fZ2 + fX1*fY2 - fY1*fX2, 
                       -( fX1*fX2 + fY1*fY2 + fZ1*fZ2 ) );
} // operator*
   
      
Quaternion Quaternion::operator/ ( float fScalar ) const {
   return Quaternion( this->getVector( ).getX( ) / fScalar,
                      this->getVector( ).getY( ) / fScalar,
                      this->getVector( ).getZ( ) / fScalar,
                      this->getScalar( ) / fScalar );
} // operator/
   
std::string Quaternion::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << m_oVector.toString( );
   sstrDesc << "W (" << m_fW;
   sstrDesc << ") ";
   return sstrDesc.str( );        
} // toString

	}; // primitives
}; // namespace powergine
