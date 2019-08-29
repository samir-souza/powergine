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


#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <sstream>
#include <cmath>
#include <powergine/config.h>

namespace powergine {
   namespace primitives {

   /**
    * Default 3D vector representation
    */
	class Vector3D {

	public:

		// Number of elements (3)
	   static const int NUM_COMPONENTS;

	   // Sizeof a given vector 3D
	   static const int TYPE_SIZE;

	   // Threshold used in some operations
	   static const float TOLERANCE;

	   // Vector which represents the position(0,0,0)
	   static const Vector3D ORIGO;

	   // Copy constructor
	   Vector3D( const Vector3D &rkVector );

	   // Default constructor
	   Vector3D( float fX = 0.0f, float fY = 0.0f, float fZ = 0.0f );

	   // Returns the length of the vector
	   float magnitude( ) const;

	   // Transform this vector into a unitary one
	   void normalize( );

	   // Makes this vector point out to the opposite side
	   void reverse( );

	   // *arithmetic operations
	   Vector3D& operator+=( const Vector3D &rkVec );

	   Vector3D& operator-=( const Vector3D &rkVec );

	   // dot product
	   float operator*( const Vector3D &rkVec ) const;

	   // Multiplies a copy all three coords by a scalar
	   Vector3D operator*( float fScalar ) const;

	   // Multiplies all three coords by a scalar
	   Vector3D& operator*=( float fScalar );

	   // Divides all three coords by a scalar
	   Vector3D& operator /=( float fScalar );

	   // Add two vectors
	   Vector3D operator+( const Vector3D &rkVector ) const;

	   // Subtract two vectors
	   Vector3D operator-( const Vector3D &rkVector ) const;

	   // Reverse this vector
	   Vector3D operator-( ) const;

	   // Update this vector by using the values of a given one
	   Vector3D& operator=( const Vector3D &rkVector );

	   // Divides a copy of this vector by a scalar
	   Vector3D operator/ ( float fScalar ) const;

	   // cross product
	   Vector3D operator^( const Vector3D &rkVec );

	   // Check if two vectors are equals
	   bool operator==( const Vector3D &rkVec ) const;

	   // Check if two vectors differs
	   inline bool operator!=( const Vector3D &rkVec ) const {
			return ( !(*this == rkVec ) );
	   };

	   // Coords setters
	   float getX( ) const;
	   float getY( ) const;
	   float getZ( ) const;

	   // Coords getters
	   void setX( float fX );
	   void setY( float fY );
	   void setZ( float fZ );

	   // Returns a description of the vector
	   std::string toString( ) const;

	private:
	   float m_fX;
	   float m_fY;
	   float m_fZ;
	};

   }; // primitives
}; // powergine

#endif //VECTOR3D_H
