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


#ifndef AABB_H
#define AABB_H

#include <iostream>

#include <powergine/sceneobjects/boundingvolume.h>
#include <powergine/sceneobjects/obb.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/vertexbuffer.h>
#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/primitives/color.h>
#include <powergine/primitives/line.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * Axis Alignd Bounding Box
		 */
		class AABB : public BoundingVolume {

		public:
		   AABB( const primitives::Vector3D &rkDimension = primitives::Vector3D::ORIGO );

		   virtual ~AABB( );

		   // Update the bounding box dimension. The axis represents the
		   // width, height and length of the box
		   void setDimension( const primitives::Vector3D &rkDimension );

		   // Returns the box dimension
		   const primitives::Vector3D& getDimension( ) const;

		   // Checks if a bounding box collided with another
		   virtual bool collide( const AABB &rkBoundingVolume, utils::ContactSet *pContactSet );

		   // Checks if a ray collided with this bounding box
		   virtual bool collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet );

		   // Checks if this bounding box intersects a given frustum
		   virtual bool intersection( Frustum *pFrustum );

		   // Checks if this bounding box intersects a given point
		   virtual bool intersection( const primitives::Vector3D &rkPoint );

		   // Checks if this bounding box intersects a given line
		   virtual bool intersection( const primitives::Ray &rkLine );

		   // Checks if this bounding box intersects a given plane
		   virtual bool intersection( const primitives::Plane &rkPlane );

		   // Render the box outlines in a given color
		   virtual void renderOutlines( const primitives::Color &rkColor );

		private:
			primitives::Vector3D m_oDimension;

		};

	}; // scenenode
}; // namespace powergine

#endif //AABB_H
