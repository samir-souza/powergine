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

#ifndef PERSPECTIVEPROJECTION_H
#define PERSPECTIVEPROJECTION_H

#include <powergine/services/video/projection.h>

namespace powergine {
	namespace services {
		namespace video {

			/**
			 * This class implements the particularities of the
			 * perspective projection.
			 */
			class PerspectiveProjection : public Projection {

			public:

			   PerspectiveProjection( );

			   virtual ~PerspectiveProjection( ) { };

			   // Returns the Field of View angle
			   float getFOV( ) const;

			   // Updates the Field of View angle
			   void setFOV( float fFov );

			   // Builds a new projection matrixs given the viewport configurations
			   virtual void buildProjection( const ViewPort &rkViewPort );

			private:

			   float m_fFov;
			};

		}; // video
	}; // services
}; //namespace powergine

#endif //PERSPECTIVEPROJECTION_H
