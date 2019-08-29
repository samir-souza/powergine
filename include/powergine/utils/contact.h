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

#ifndef CONTACT_H
#define CONTACT_H

#include <powergine/primitives/vector3d.h>

namespace powergine {

	namespace sceneobjects {
		class AABB;
	};

	namespace utils {

	/**
	 * Contact point between two objects
	 */
	class Contact {

	public:
	   Contact( sceneobjects::AABB* objectA, sceneobjects::AABB* objectB );

	   void sort( );

	   const primitives::Vector3D getNormal( ) const;

	   void setNormal( const primitives::Vector3D &rkNormal );

	   unsigned int getNumberPoints( ) const;

	   void setNumberPoints( unsigned int uiNumberPoints );

	   const primitives::Vector3D &operator[ ]( int iIndex );

	private:
	   sceneobjects::AABB* objectA;
	   sceneobjects::AABB* objectB;
	   primitives::Vector3D m_oContactPoints[ 8 ];
	   primitives::Vector3D m_oNormal;
	   float m_fPenetrationDepths[ 8 ];
	   unsigned int m_uiNumberPoints;
	};

	}; // primitives
}; // namespace powergine

#endif //CONTACT_H
