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

#ifndef ORTHOGRAPHICPROJECTION_H
#define ORTHOGRAPHICPROJECTION_H

#include <powergine/services/video/projection.h>

namespace powergine {
	namespace services {
		namespace video {

			/**
			 * This class implements the particularities of the
			 * orthografic projection.
			 */
			class OrthographicProjection : public Projection {

			public:

			   OrthographicProjection( );

			   virtual ~OrthographicProjection( ) { };

			   // Returns the distance of the TOP plane from the origin
			   float getTop( ) const;

			   void setTop( float fTop );

			   // Returns the distance of the BOTTOM plane from the origin
			   float getBottom( ) const;

			   // Updates the distance of the BOTTOM plane from the origin
			   void setBottom( float fBottom );

			   // Returns the distance of the LEFT plane from the origin
			   float getLeft( ) const;

			   // Updates the distance of the LEFT plane from the origin
			   void setLeft( float fLeft );

			   // Returns the distance of the RIGHT plane from the origin
			   float getRight( ) const;

			   // Updates the distance of the RIGHT plane from the origin
			   void setRight( float fRight );

			   // Build a new orthographic projection given the viewport configurations
			   virtual void buildProjection( const ViewPort &rkViewPort );

			private:

			   float m_fTop;
			   float m_fBottom;
			   float m_fLeft;
			   float m_fRight;

			};

		}; // video
	}; // utils
}; //namespace powergine

#endif //ORTHOGRAPHICPROJECTION_H
