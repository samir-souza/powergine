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

#ifndef RAY_H
#define RAY_H

#include <powergine/primitives/vector3d.h>

namespace powergine {
   namespace primitives {

   /**
    * Represents a ray shot by some object. A ray is normally used to
    * detects that polygons where hit by a projectile
    */
	class Ray {

	public:

		// Specifies a ray given the origin point and a direction vector
	   Ray ( const Vector3D &rkOrigin, const Vector3D &rkDirection );

	   Ray ( );

	   // Returns the ray origin
	   const Vector3D getOrigin( );
	   // Returns the ray direction
	   const Vector3D getDirection( );

	   // Updates the ray origin
	   void setOrigin( const Vector3D &rkOrigin );
	   // Updates the ray direction
	   void setDirection( const Vector3D &rkDirection );


	private:
	   Vector3D m_oOrigin;
	   Vector3D m_oDirection;
	};

	}; // primitives
}; // namespace powergine

#endif //RAY_H
