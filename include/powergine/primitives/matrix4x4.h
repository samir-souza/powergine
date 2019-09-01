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

#ifndef MATRIX4X4_H
#define MATRIX4X4_H

#include <sstream>
#include <cassert>
#include <powergine/primitives/vector3d.h>

namespace powergine {
	namespace primitives {

	/**
	 * Represents a 4x4 matrix
	 */
	class Matrix4x4 {

	public:
		// Constant which represents an identity matrix
	   static const Matrix4x4 IDENTITY;

	   // Constructors
	   Matrix4x4( );
	   Matrix4x4( float f11, float f12, float f13, float f14,
				  float f21, float f22, float f23, float f24,
				  float f31, float f32, float f33, float f34,
				  float f41, float f42, float f43, float f44 );

	   Matrix4x4( const float kfData[ ][ 4 ] );

	   Matrix4x4( const Matrix4x4 &rkMatrix );

	   virtual ~Matrix4x4( );

	   // Getter of the elements which uses the row and col index
	   float getElement( int iRow, int iCol ) const;

	   // Setter of the elements which uses the row and col index
	   void setElement( int iRow, int iCol, float fValue );

	   // Returns the matrix determinant
	   float determinant ( );

	   // Returns a transposed version of this matrix
	   Matrix4x4 transpose ( );

	   // Returns an inversed version of this matrix, when possible
	   Matrix4x4 inverse ( );

	   // Applies the transformation of this matrix in a given vertex
	   // and returns a copy of it
	   Vector3D operator*( const Vector3D &rkVector ) const;

	   // Multiplies a given matrix by another
	   Matrix4x4 operator*( const Matrix4x4 &rkMatrix ) const;

	   // Add a given matrix to this one
	   Matrix4x4& operator+=( const Matrix4x4 &rkMatrix );

	   // Subtracts a given matrix to this one
	   Matrix4x4& operator-=( const Matrix4x4 &rkMatrix );

	   // Multiplies a given factor to all values of this matrix
	   Matrix4x4& operator*=( const float fScalar );

	   // Divides a given factor to all values of this matrix
	   Matrix4x4& operator/=( const float fScalar );

	   // Set all values of this matrix to 0
	   void reset( );

	   // Returns a description of this matrix
	   std::string toString( ) const;

	private:
	   float m_fData[4][4];
	};

	}; // primitives
}; // namespace powergine

#endif //MATRIX4X4_H
