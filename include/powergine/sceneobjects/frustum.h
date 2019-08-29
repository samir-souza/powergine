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

#ifndef FRUSTUM_H
#define FRUSTUM_H

#include <string>
#include <powergine/sceneobjects/srtnode.h>
#include <powergine/primitives/matrix4x4.h>
#include <powergine/primitives/line.h>
#include <powergine/primitives/plane.h>
#include <powergine/primitives/triangle.h>
#include <powergine/primitives/renderprimitive.h>
#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/primitives/color.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A Frustum is an area enclosed by planes
		 */
		class Frustum : public SRTNode {

		// Public stuff
		public:

		   enum PLANE {
			  PLANE_LEFT,
			  PLANE_RIGHT,
			  PLANE_TOP,
			  PLANE_BOTTOM,
			  PLANE_NEAR,
			  PLANE_FAR
		   };

		   Frustum( );

		   virtual ~Frustum( ) { };


		   // Check if the given point lies inside the frustum
		   bool intersection( const primitives::Vector3D &rkPoint );

		   // Check if the given plane intersects the frustum
		   bool intersection( const primitives::Plane &rkPlane );

		   // Check if the given line intersects the frustum
		   bool intersection( const primitives::Line &rkLine );

		   // Check if the given triangle intersects the frustum
		   bool intersection( const primitives::Triangle &rkTriangle );

		   // Returns a given plane
		   primitives::Plane& getPlane( PLANE ePlane );

		   // Returns the distance of the near plane from origin
		   float getZNear( ) const;

		   // Updates the distance of the near plane from origin
		   void setZNear( float fZNear );

		   // Returns the distance of the far plane from origin
		   float getZFar( ) const;

		   // // Updates the distance of the far plane from origin
		   void setZFar( float fZFar );

		   // Returns a vector that points to the direction of the Frustum
		   const primitives::Vector3D& getViewDirection( ) const;

		   // Updates the frustum direction
		   void setViewDirection( const primitives::Vector3D &rkViewDirection );

		   // Returns the type of the plane given its index
		   PLANE operator[]( int iPlane ) const;


		private:
		   primitives::Matrix4x4 m_oViewMatrix;
		   primitives::Plane m_oPlanes[ 6 ];
		   primitives::Vector3D m_oViewDirection;
		   primitives::Matrix4x4 m_oTransformation;
		   float m_fZNear;
		   float m_fZFar;
		};

	}; // sceneobjects
}; // namespace powergine

#endif //FRUSTUM_H
