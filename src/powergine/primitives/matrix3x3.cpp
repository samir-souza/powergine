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


#include <powergine/primitives/matrix3x3.h>

namespace powergine {
	namespace primitives {
	
const Matrix3x3 Matrix3x3::IDENTITY( 1.0f, 0.0f, 0.0f,
                                     0.0f, 1.0f, 0.0f,
                                     0.0f, 0.0f, 1.0f );
// Constructors/Destructors
// Methods

Matrix3x3::Matrix3x3( ) {
   for ( int iRow = 0; iRow < 3; iRow++ ) {
      for ( int iCol = 0; iCol < 3; iCol++ ) {
         m_fData[ iRow ][ iCol ] = 0.0f;
      } // for
   } // for
} // Matrix3x3

Matrix3x3::Matrix3x3( const float kfData[ ][ 3 ] ) {
   for ( int iRow = 0; iRow < 3; iRow++ ) {
      for ( int iCol = 0; iCol < 3; iCol++ ) {
         m_fData[ iRow ][ iCol ] = kfData[ iRow ][ iCol ];
      } // for
   } // for
} // Matrix3x3

Matrix3x3::Matrix3x3( float f11, float f12, float f13, 
                             float f21, float f22, float f23, 
                             float f31, float f32, float f33 ) {
   m_fData[ 0 ][ 0 ] = f11; m_fData[ 0 ][ 1 ] = f12; m_fData[ 0 ][ 2 ] = f13;
   m_fData[ 1 ][ 0 ] = f21; m_fData[ 1 ][ 1 ] = f22; m_fData[ 1 ][ 2 ] = f23;
   m_fData[ 2 ][ 0 ] = f31; m_fData[ 2 ][ 1 ] = f32; m_fData[ 2 ][ 2 ] = f33;   
} // Matrix3x3

Matrix3x3::~Matrix3x3( ) {
} // ~Matrix3x3

float Matrix3x3::determinant ( ) {
   return ( m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 2 ] +
            m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 0 ] +
            m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 1 ] -
            
            m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 2 ] -
            m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 1 ] -
            m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 0 ] );
} // determinant

Matrix3x3 Matrix3x3::transpose ( ) {
   return Matrix3x3( m_fData[ 0 ][ 0 ], m_fData[ 1 ][ 0 ], m_fData[ 2 ][ 0 ], 
                     m_fData[ 0 ][ 1 ], m_fData[ 1 ][ 1 ], m_fData[ 2 ][ 1 ], 
                     m_fData[ 0 ][ 2 ], m_fData[ 1 ][ 2 ], m_fData[ 2 ][ 2 ] );
} // transpose

Matrix3x3 Matrix3x3::inverse ( ) {
   float fDet = ( m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 2 ] +
                  m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 0 ] +
                  m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 1 ] -
            
                  m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 2 ] -
                  m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 1 ] -
                  m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 0 ] );
   if ( fDet == 0 ) fDet = 1;
   
   return Matrix3x3( ( m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 2 ] - m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 1 ] ) / fDet,
                     ( m_fData[ 0 ][ 1 ] * m_fData[ 2 ][ 2 ] - m_fData[ 0 ][ 2 ] * m_fData[ 2 ][ 1 ] ) / fDet,
                     ( m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 2 ] - m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 1 ] ) / fDet,
                       
                     ( m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 2 ] - m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 0 ] ) / fDet,
                     ( m_fData[ 0 ][ 0 ] * m_fData[ 2 ][ 2 ] - m_fData[ 0 ][ 2 ] * m_fData[ 2 ][ 0 ] ) / fDet,
                     ( m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 2 ] - m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 0 ] ) / fDet,
                       
                     ( m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 1 ] - m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 0 ] ) / fDet,
                     ( m_fData[ 0 ][ 0 ] * m_fData[ 2 ][ 1 ] - m_fData[ 0 ][ 1 ] * m_fData[ 2 ][ 0 ] ) / fDet,
                     ( m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 1 ] - m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 0 ] ) / fDet );
  
} // inverse

const float Matrix3x3::getElement( int iRow, int iCol ) const {
   return m_fData[ iRow ][ iCol ];
} // getElement

Matrix3x3& Matrix3x3::operator+=( const Matrix3x3 &rkMatrix ) {	
   for ( int iRow = 0; iRow < 3; iRow++ ) {
      for ( int iCol = 0; iCol < 3; iCol++ ) {
         m_fData[ iRow ][ iCol ] += rkMatrix.getElement( iRow, iCol );
      } // for
   } // for   
   return *this;
} // operator+=

Matrix3x3& Matrix3x3::operator-=( const Matrix3x3 &rkMatrix ) {
   for ( int iRow = 0; iRow < 3; iRow++ ) {
      for ( int iCol = 0; iCol < 3; iCol++ ) {
         m_fData[ iRow ][ iCol ] -= rkMatrix.getElement( iRow, iCol );
      } // for
   } // for     
   return *this;
} // operator-=

Matrix3x3& Matrix3x3::operator*=( const float fScalar ) {
   for ( int iRow = 0; iRow < 3; iRow++ ) {
      for ( int iCol = 0; iCol < 3; iCol++ ) {
         m_fData[ iRow ][ iCol ] *= fScalar;
      } // for
   } // for     
   return *this;  
} // operator*=

Matrix3x3& Matrix3x3::operator/=( const float fScalar ) {
   for ( int iRow = 0; iRow < 3; iRow++ ) {
      for ( int iCol = 0; iCol < 3; iCol++ ) {
         m_fData[ iRow ][ iCol ] /= fScalar;
      } // for
   } // for     
   return *this;    
} // operator/=

Vector3D Matrix3x3::operator*( const Vector3D &rkVector ) {
   float fX  = m_fData[0][0]*rkVector.getX( );
         fX += m_fData[0][1]*rkVector.getY( );
         fX += m_fData[0][2]*rkVector.getZ( );
   float fY  = m_fData[1][0]*rkVector.getX( );
         fY += m_fData[1][1]*rkVector.getY( );
         fY += m_fData[1][2]*rkVector.getZ( );
   float fZ  = m_fData[2][0]*rkVector.getX( );
         fZ += m_fData[2][1]*rkVector.getY( );
         fZ += m_fData[2][2]*rkVector.getZ( );
         
   return Vector3D( fX, fY, fZ ); 
}

void Matrix3x3::reset( ) {
   for ( int iRow = 0; iRow < 3; iRow++ ) {
      for ( int iCol = 0; iCol < 3; iCol++ ) {
         m_fData[ iRow ][ iCol ] = 0.0f;
      } // for
   } // for
} // reset
	}; // primitives
}; // namespace powergine
