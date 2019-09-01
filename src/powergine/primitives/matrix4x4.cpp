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


#include <powergine/primitives/matrix4x4.h>

namespace powergine {
	namespace primitives {
	
const Matrix4x4 Matrix4x4::IDENTITY( 1.0f, 0.0f, 0.0f, 0.0f,
                                     0.0f, 1.0f, 0.0f, 0.0f,
                                     0.0f, 0.0f, 1.0f, 0.0f,
                                     0.0f, 0.0f, 0.0f, 1.0f );
       
// Constructors/Destructors
// Methods
Matrix4x4::Matrix4x4( ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] = 0.0f;
      } // for
   } // for
} // Matrix4x4

Matrix4x4::Matrix4x4( const float kfData[ ][ 4 ] ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] = kfData[ iRow ][ iCol ];
      } // for
   } // for
} // Matrix4x4


Matrix4x4::Matrix4x4( float f11, float f12, float f13, float f14,
                      float f21, float f22, float f23, float f24, 
                      float f31, float f32, float f33, float f34,
                      float f41, float f42, float f43, float f44 ) {                             
   m_fData[ 0 ][ 0 ] = f11; m_fData[ 0 ][ 1 ] = f12; m_fData[ 0 ][ 2 ] = f13; m_fData[ 0 ][ 3 ] = f14;
   m_fData[ 1 ][ 0 ] = f21; m_fData[ 1 ][ 1 ] = f22; m_fData[ 1 ][ 2 ] = f23; m_fData[ 1 ][ 3 ] = f24;
   m_fData[ 2 ][ 0 ] = f31; m_fData[ 2 ][ 1 ] = f32; m_fData[ 2 ][ 2 ] = f33; m_fData[ 2 ][ 3 ] = f34;
   m_fData[ 3 ][ 0 ] = f41; m_fData[ 3 ][ 1 ] = f42; m_fData[ 3 ][ 2 ] = f43; m_fData[ 3 ][ 3 ] = f44;
   
} // Matrix4x4

Matrix4x4::Matrix4x4( const Matrix4x4 &rkMatrix ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] = rkMatrix.getElement( iRow, iCol );
      } // for
   } // for
} // Matrix4x4

Matrix4x4::~Matrix4x4( ) {
} // ~Matrix4x4

float Matrix4x4::determinant( ) {
   return ( m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 2 ] * m_fData[ 3 ][ 3 ] +
            m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 3 ] * m_fData[ 3 ][ 0 ] +
            m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 3 ] * m_fData[ 2 ][ 0 ] * m_fData[ 3 ][ 1 ] +
            m_fData[ 0 ][ 3 ] * m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 1 ] * m_fData[ 3 ][ 2 ] -
            
            m_fData[ 0 ][ 2 ] * m_fData[ 1 ][ 1 ] * m_fData[ 2 ][ 0 ] * m_fData[ 3 ][ 3 ] -
            m_fData[ 0 ][ 1 ] * m_fData[ 1 ][ 0 ] * m_fData[ 2 ][ 3 ] * m_fData[ 3 ][ 2 ] -
            m_fData[ 0 ][ 0 ] * m_fData[ 1 ][ 3 ] * m_fData[ 2 ][ 2 ] * m_fData[ 3 ][ 1 ] -
            m_fData[ 0 ][ 3 ] * m_fData[ 1 ][ 2 ] * m_fData[ 2 ][ 1 ] * m_fData[ 3 ][ 0 ] );
} // determinant

Matrix4x4 Matrix4x4::transpose( ) {
   return Matrix4x4( m_fData[ 0 ][ 0 ], m_fData[ 1 ][ 0 ], m_fData[ 2 ][ 0 ], m_fData[ 3 ][ 0 ], 
                     m_fData[ 0 ][ 1 ], m_fData[ 1 ][ 1 ], m_fData[ 2 ][ 1 ], m_fData[ 3 ][ 1 ], 
                     m_fData[ 0 ][ 2 ], m_fData[ 1 ][ 2 ], m_fData[ 2 ][ 2 ], m_fData[ 3 ][ 2 ],
                     m_fData[ 0 ][ 3 ], m_fData[ 1 ][ 3 ], m_fData[ 2 ][ 3 ], m_fData[ 3 ][ 3 ] );
} // transpose

Matrix4x4 Matrix4x4::inverse( ) {
   assert( !"nao implementado" );
   return 0;
} // inverse

Vector3D Matrix4x4::operator*( const Vector3D &rkVector ) const {
   return Vector3D(
      m_fData[0][0] * rkVector.getX( ) + m_fData[0][1] * rkVector.getY( ) + m_fData[0][2] * rkVector.getZ( ) + m_fData[0][3],
      m_fData[1][0] * rkVector.getX( ) + m_fData[1][1] * rkVector.getY( ) + m_fData[1][2] * rkVector.getZ( ) + m_fData[1][3],
      m_fData[2][0] * rkVector.getX( ) + m_fData[2][1] * rkVector.getY( ) + m_fData[2][2] * rkVector.getZ( ) + m_fData[2][3]
   );
}

Matrix4x4 Matrix4x4::operator*( const Matrix4x4 &rkMatrix ) const {
   Matrix4x4 oResult;
   
   for( int iRow = 0; iRow < 4; ++iRow ) {
      for( int iCol = 0; iCol < 4; ++iCol ) {
         oResult.setElement( iRow, iCol,
            m_fData[ iRow ][ 0 ] * rkMatrix.getElement( 0, iCol ) +
            m_fData[ iRow ][ 1 ] * rkMatrix.getElement( 1, iCol ) +
            m_fData[ iRow ][ 2 ] * rkMatrix.getElement( 2, iCol ) +
            m_fData[ iRow ][ 3 ] * rkMatrix.getElement( 3, iCol ) 
         );      
      } // for
   } // for
      
   return oResult;
}

float Matrix4x4::getElement( int iRow, int iCol ) const {
   return m_fData[ iRow ][ iCol ];
} // getElement

void Matrix4x4::setElement( int iRow, int iCol, float fValue ) {
	m_fData[ iRow ][ iCol ] = fValue;
} // setElement
      

Matrix4x4& Matrix4x4::operator+=( const Matrix4x4 &rkMatrix ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] += rkMatrix.getElement( iRow, iCol );
      } // for
   } // for   
   return *this;
} // operator+=

Matrix4x4& Matrix4x4::operator-=( const Matrix4x4 &rkMatrix ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] -= rkMatrix.getElement( iRow, iCol );
      } // for
   } // for     
   return *this;
} // operator-=

Matrix4x4& Matrix4x4::operator*=( const float fScalar ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] *= fScalar;
      } // for
   } // for     
   return *this;  
} // operator*=

Matrix4x4& Matrix4x4::operator/=( const float fScalar ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] /= fScalar;
      } // for
   } // for     
   return *this;    
} // operator/=

void Matrix4x4::reset( ) {
   for ( int iRow = 0; iRow < 4; iRow++ ) {
      for ( int iCol = 0; iCol < 4; iCol++ ) {
         m_fData[ iRow ][ iCol ] = 0.0f;
      } // for
   } // for
} // reset

std::string Matrix4x4::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << "[" << m_fData[ 0 ][ 0 ] << "] ";
   sstrDesc << "[" << m_fData[ 0 ][ 1 ] << "] ";
   sstrDesc << "[" << m_fData[ 0 ][ 2 ] << "] ";
   sstrDesc << "[" << m_fData[ 0 ][ 3 ] << "] ";   
   sstrDesc << std::endl;
   
   sstrDesc << "[" << m_fData[ 1 ][ 0 ] << "] ";
   sstrDesc << "[" << m_fData[ 1 ][ 1 ] << "] ";
   sstrDesc << "[" << m_fData[ 1 ][ 2 ] << "] ";
   sstrDesc << "[" << m_fData[ 1 ][ 3 ] << "] ";   
   sstrDesc << std::endl;

   sstrDesc << "[" << m_fData[ 2 ][ 0 ] << "] ";
   sstrDesc << "[" << m_fData[ 2 ][ 1 ] << "] ";
   sstrDesc << "[" << m_fData[ 2 ][ 2 ] << "] ";
   sstrDesc << "[" << m_fData[ 2 ][ 3 ] << "] ";   
   sstrDesc << std::endl;

   sstrDesc << "[" << m_fData[ 3 ][ 0 ] << "] ";
   sstrDesc << "[" << m_fData[ 3 ][ 1 ] << "] ";
   sstrDesc << "[" << m_fData[ 3 ][ 2 ] << "] ";
   sstrDesc << "[" << m_fData[ 3 ][ 3 ] << "] ";   
   sstrDesc << std::endl;
   
   return sstrDesc.str( );        
} // toString


	}; // primitives
}; // namespace powergine
