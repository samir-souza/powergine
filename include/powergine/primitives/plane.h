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


#ifndef PLANE_H
#define PLANE_H

#include <powergine/primitives/vector3d.h>

namespace powergine {
	namespace primitives {

	/**
	 * Represents a 3D plane
	 */
	class Plane {

	public:

		// Default constructor
	   Plane( );

	   // Builds the plane using a given normal and a distance from (0,0,0)
	   Plane( const Vector3D &rkNormal, float fDistanceFromOrigo );

	   // Builds the plane using a given normal and a point in space
	   Plane( const Vector3D &rkNormal, const Vector3D &rkPointInPlane );

	   // Update the plane normal
	   void setNormal( const Vector3D &rkNormal );

	   // Returns the current plane normal
	   const Vector3D &getNormal( ) const;

	   // Update the distance of the plane to (0,0,0)
	   void setDistanceToOrigo( float fDistance );

	   // Returns the distance of the plane to (0,0,0)
	   float getDistanceFromOrigo( ) const;

	   // Returns the distance of the plane to a given point
	   float getDistanceToPoint( const Vector3D &rkPoint ) const;

	   // Normalize the plane
	   void normalize( );

	   // Returns a point that lies on this plane
	   Vector3D getPointOnPlane( ) const;

	   // Operator which compares two planes and 'tells' if they
	   // are equals
	   bool operator==( const Plane &rkPlane ) const;

	private:
	   Vector3D m_oNormal;
	   float m_fDistanceToOrigo;

	};

	}; // primitives
}; // namespace powergine

#endif //PLANE_H
