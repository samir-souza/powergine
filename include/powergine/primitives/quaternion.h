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


#ifndef QUATERNION_H
#define QUATERNION_H

#include <iostream>
#include <sstream>
#include <cmath>
#include <cassert>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/matrix4x4.h>
#include <powergine/utils/mathhelper.h>

namespace powergine {
	namespace primitives {

	/**
	 * This class represents a Quaternion, a very powerful
	 * math tool used to controls rotations, orientations in
	 * a 3D space.
	 */
	class Quaternion {

	public:
		// The quaternion Identity
	   static const Quaternion IDENTITY;

	   // A factor used as threshold of some operations
	   static const float SQR_EPSILON;

	   // Constructors
	   Quaternion( );

	   Quaternion( float fAngle, const Vector3D &rkAxis );

	   Quaternion( const Matrix4x4 &rkMatrix );

	   Quaternion( float fX, float fY, float fZ, float fW );

	   Quaternion( const Vector3D &rkVector, float fW );

	   Quaternion( const Quaternion &rkQuat );

	   // Returns the quaternion magnitude
	   float magnitude( ) const;

	   // Normalize the quaternion
	   void normalize( );

	   // Returns the vector portion of the quaternion
	   Vector3D  getVector( ) const;

	   // Returns the scalar portion of the quaternion
	   float getScalar( ) const;

	   // Updates the vector portion of the quaternion
	   void setVector( const Vector3D &rkVector );

	   // Updates the scalar portion of the quaternion
	   void setScalar( float fScalar );

	   // Returns the rotation angle of the quaternion axis
	   float getAngle( ) const;

	   // Returns the quaterion axis
	   Vector3D getAxis( ) const;

	   // Applies the rotation of this quaternion to a given one
	   void rotate( const Quaternion &rkQuat );

	   // Applies the rotation of this quaterion to a given vector
	   Vector3D rotateVector3D( const Vector3D &rkVector ) const;

	   // Returns the Euler angles of all three axis
	   Vector3D toEulerAngles( );

	   // Update this quaternion from a given Euler angles
	   // and return a reference of this object
	   Quaternion& fromEulerAngles( const Vector3D &rkEulerAngles );

	   // Converts this quaternion to a 4x4 matrix
	   Matrix4x4 toMatrix4x4( ) const;

	   // Set this quaternion with the values generated from
	   // the conversion to quaternion of the given matrix
	   Quaternion& operator=( const Matrix4x4 &rkMatrix );

	   // Updates this quaternion with the given quaternion values
	   Quaternion& operator=( const Quaternion &rkQuat );

	   // Adds the given quaternion to this one
	   Quaternion operator+=( const Quaternion &rkQuat );

	   // Subtracts the given quaterion from this one
	   Quaternion operator-=( const Quaternion &rkQuat );

	   // Applies the rotation of the given quaternion to
	   // this one
	   Quaternion operator*=( const Quaternion &rkQuat );

	   // Multiplies this quaternion by a scalar
	   Quaternion operator*=( float fScalar );

	   // Divides this quaternion by a scalar
	   Quaternion operator/=( float fScalar );

	   // Transform this quaternion to its complement
	   Quaternion operator~( ) const;

	   // Adds two quaternions
	   Quaternion operator+( const Quaternion &rkQuat ) const;

	   // Subtracts two quaternions
	   Quaternion operator-( const Quaternion &rkQuat ) const;

	   // Multiplies two quaternions
	   Quaternion operator*( const Quaternion &rkQuat ) const;

	   // Multiplies this quaternion by a scalar
	   Quaternion operator*( float fScalar ) const;

	   // Multiplies this quaternion by a vector
	   Quaternion operator*( const Vector3D &rkVector ) const;

	   // Divides this quaternion by a scalar
	   Quaternion operator/( float fScalar ) const;

	   // Returns a description of this quaternion
	   std::string toString( ) const;

	private:
	   float m_fW;
	   Vector3D m_oVector;

	};

	}; // primitives
}; // namespace powergine

#endif //QUATERNION_H
