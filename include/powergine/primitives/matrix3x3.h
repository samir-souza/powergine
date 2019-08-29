// Copyright (c) 2004 Samir Araujo <samir.araujo@gmail.com>
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


#ifndef MATRIX3X3_H
#define MATRIX3X3_H

#include <powergine/primitives/vector3d.h>

namespace powergine {
	namespace primitives {

	/**
	 * Represents a 3x3 matrix
	 */
	class Matrix3x3 {

	public:
		// Constant which represents an identity matrix
	   static const Matrix3x3 IDENTITY;

	   // Constructors
	   Matrix3x3( );
	   Matrix3x3( float f11, float f12, float f13,
				  float f21, float f22, float f23,
				  float f31, float f32, float f33 );
	   Matrix3x3( const float kfData[ ][ 3 ] );

	   virtual ~Matrix3x3( );

	   // Returns the matrix determinant
	   float determinant( );

	   // Returns the transposed matrix
	   Matrix3x3 transpose ( );

	   // Returns the inverse matrix, when possible
	   Matrix3x3 inverse ( );

	   // Getter of the elements which uses the row and col index
	   const float getElement( int iRow, int iCol ) const;


	   // Sum two matrix
	   Matrix3x3& operator+=( const Matrix3x3 &rkMatrix );
	   // Subtract two matrix
	   Matrix3x3& operator-=( const Matrix3x3 &rkMatrix );
	   // Multiply all values of a matrix by a factor
	   Matrix3x3& operator*=( const float fScalar );
	   // Divide all values of a matrix by a factor
	   Matrix3x3& operator/=( const float fScalar );

	   // Apply the matrix transformations to a given vector
	   // and returns a copy of the modified vector
	   Vector3D operator*( const Vector3D &rkVector );

	   // Set 0.0 to all the matrix values
	   void reset( );

	private:
	   float m_fData[3][3];

	};

	}; // primitives
}; // namespace powergine

#endif //MATRIX3X3_H
