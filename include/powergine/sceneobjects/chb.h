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


#ifndef CHB_H
#define CHB_H

#include <iostream>
#include <vector>
#include <string>

#include <powergine/sceneobjects/boundingvolume.h>
#include <powergine/sceneobjects/aabb.h>
#include <powergine/sceneobjects/obb.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/vertexbuffer.h>
#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/primitives/plane.h>
#include <powergine/primitives/color.h>
#include <powergine/primitives/line.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * It builds a convex hull from planes. That convex hull can then
		 * be used as a bounding volume for collision detection and other
		 * operations
		 */
		class CHB : public BoundingVolume {

		public:

		   CHB( );

		   virtual ~CHB( );

		   // Adds a new plane to the convex hull
		   void addPlane( primitives::Plane *pPlane );

		   // Removes a plane from the hull
		   void removePlane( primitives::Plane *pPlane );

		   // Returns the number of planes
		   int getNumPlanes( ) const;

		   // Returns a plane given its index
		   primitives::Plane& operator[]( int iIndex );

		   // Checks if it collides with a AABB
		   virtual bool collide( const AABB &rkBoundingVolume, utils::ContactSet *pContactSet );

		   // Checks if it collides with another Convex Hull
		   virtual bool collide( const CHB &rkBoundingVolume, utils::ContactSet *pContactSet );

		   // Checks if it collides with a Ray
		   virtual bool collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet );

		   // See BoundingVolume::intersection
		   virtual bool intersection( Frustum *pFrustum );

		   // See BoundingVolume::intersection
		   virtual bool intersection( const primitives::Vector3D &rkPoint );

		   // See BoundingVolume::intersection
		   virtual bool intersection( const primitives::Ray &rkLine );

		   // See BoundingVolume::intersection
		   virtual bool intersection( const primitives::Plane &rkPlane );

		   // See BoundingVolume::intersection
		   virtual void renderOutlines( const primitives::Color &rkColor );

		private:
			std::vector<primitives::Plane*> m_vecPlanes;

		};

	}; // scenenode
}; // namespace powergine

#endif //CHB_H
