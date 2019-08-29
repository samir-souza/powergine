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

#ifndef BOUNDINGVOLUME_H
#define BOUNDINGVOLUME_H

#include <string>

#include <powergine/sceneobjects/frustum.h>
#include <powergine/sceneobjects/srtnode.h>
#include <powergine/utils/contactset.h>
#include <powergine/primitives/ray.h>
#include <powergine/primitives/line.h>
#include <powergine/primitives/plane.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/color.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * Bounding box interface that must be implemented by a concrete
		 * bounding box manager. It is used to limit the boundaries of a given
		 * object
		 */
		class BoundingVolume : public SRTNode {

		public:

		   inline BoundingVolume( ) : SRTNode( ) { }

		   inline virtual ~BoundingVolume( ) { };

		   // Checks if a ray collided with this bounding box
		   virtual bool collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet ) = 0;

		   // Checks if this bounding box intersects a given frustum
		   virtual bool intersection( Frustum *pFrustum ) = 0;

		   // Checks if this bounding box intersects a given point
		   virtual bool intersection( const primitives::Vector3D &rkPoint ) = 0;

		   // Checks if this bounding box intersects a given line
		   virtual bool intersection( const primitives::Ray &rkLine ) = 0;

		   // Checks if this bounding box intersects a given plane
		   virtual bool intersection( const primitives::Plane &rkPlane ) = 0;

		   // Render the box outlines in a given color
		   virtual void renderOutlines( const primitives::Color &rkColor ) = 0;
		};

	}; // sceneobjects
}; // namespace powergine

#endif //BOUNDINGVOLUME_H
