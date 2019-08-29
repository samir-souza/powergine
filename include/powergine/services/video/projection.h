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

#ifndef PROJECTION_H
#define PROJECTION_H

#include <powergine/services/video/viewport.h>
#include <powergine/utils/mathhelper.h>
#include <powergine/primitives/matrix4x4.h>

namespace powergine {
	namespace services {
		namespace video {

			/**
			 * This class represents the projection configuration
			 * used by the video manager. It contains a projection
			 * matrix used during the projection transformation in
			 * render time.
			 */
			class Projection {

			public:
			   enum MODE {
				  INVALID = -1,
				  PERSPECTIVE = 0,
				  ORTHOGRAPHIC = 1,
				  CUSTOM = 2
			   };

			   Projection( );

			   virtual ~Projection( );

			   // Returns the distance of the near plane from
			   // the origin
			   float getZNear( ) const;

			   // Updates the distance of the near plane from
			   // the origin
			   void setZNear( float fZNear );

			   // Returns the distance of the far plane from
			   // the origin
			   float getZFar( ) const;

			   // Updates the distance of the far plane from
			   // the origin
			   void setZFar( float fZFar );

			   // Returns the current projection mode
			   MODE getMode( ) const;

			   // Updates the current projection mode
			   void setMode( MODE eMode );

			   // Returns the current projection matrix
			   const primitives::Matrix4x4& getProjectionMatrix( );

			   // Build a new projection matrix given the viewport configurations
			   virtual void buildProjection( const ViewPort &rkViewPort ) = 0;


			protected:
			   float m_fZNear;

			   float m_fZFar;

			   MODE m_eMode;

			   primitives::Matrix4x4 m_oProjectionMatrix;

			};

		}; // video
	}; // services
}; // namespace powergine

#endif //PROJECTION_H
