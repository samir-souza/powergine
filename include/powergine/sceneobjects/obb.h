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

#ifndef OBB_H
#define OBB_H

#include <powergine/sceneobjects/boundingvolume.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/core.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * An Oriented Bounding Box is a bounding box that can be rotated in all
		 * three axis. If you just need rotation in the up axis and translations
		 * its better to use an AABB, which is computational lighter than the OBB
		 */
		class OBB : public BoundingVolume {


		public:

		   OBB( const primitives::Vector3D &rkDimension = primitives::Vector3D::ORIGO );

		   virtual ~OBB( ) { };

		   // Updates the bounding box dimension
		   void setDimension( const primitives::Vector3D &rkDimension );

		   // Returns the current bounding box dimension
		   const primitives::Vector3D& getDimension( ) const;

		   // Returns the box radius. The distance from the box center
		   // to any corner
		   float getRadius( ) const;

		   // See BoundingVolume::collide
		   virtual bool collide( const OBB &rkBoundingVolume, utils::ContactSet *pContactSet );

		   // See BoundingVolume::collide
		   virtual bool collide( const primitives::Ray &rkRay, utils::ContactSet *pContactSet );

		   // See BoundingVolume::intersection
		   virtual bool intersection( Frustum *pFrustum );

		   // See BoundingVolume::intersection
		   virtual bool intersection( const primitives::Vector3D &rkPoint );

		   // See BoundingVolume::intersection
		   virtual bool intersection( const primitives::Ray &rkLine );

		   // See BoundingVolume::intersection
		   virtual bool intersection( const primitives::Plane &rkPlane );

		   // See BoundingVolume::renderOutlines
		   virtual void renderOutlines( const primitives::Color &rkColor );

		private:
		  // Fields
		   primitives::Vector3D m_oDimension;
		   float m_fRadius;
		   primitives::Matrix4x4 m_oTransformation;
		};

	}; // scenenode
}; // namespace powergine

#endif //OBB_H
