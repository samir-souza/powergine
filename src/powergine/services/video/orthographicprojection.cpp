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


#include <powergine/services/video/orthographicprojection.h>

namespace powergine {
	namespace services {
		namespace video {


OrthographicProjection::OrthographicProjection( ) :
   Projection( )
{
   m_eMode    = Projection::ORTHOGRAPHIC;
   m_fZNear   = 0.0f;
   m_fZFar    = 1.0f;
   m_fLeft    = 0.0f;
   m_fTop     = 0.0f;
   m_fRight   = 1.0f;
   m_fBottom  = 1.0f;
}

float OrthographicProjection::getTop( ) const {
   return m_fTop;
}

void OrthographicProjection::setTop( float fTop ) {
   m_fTop = fTop;
}

float OrthographicProjection::getBottom( ) const {
   return m_fBottom;
}

void OrthographicProjection::setBottom( float fBottom ) {
   m_fBottom = fBottom;
}

float OrthographicProjection::getLeft( ) const {
   return m_fLeft;
}

void OrthographicProjection::setLeft( float fLeft ) {
   m_fLeft = fLeft;
}

float OrthographicProjection::getRight( ) const {
   return m_fRight;
}

void OrthographicProjection::setRight( float fRight ) {
   m_fRight = fRight;
}

void OrthographicProjection::buildProjection( const ViewPort &rkViewPort ) {
   m_oProjectionMatrix.reset( );

   m_oProjectionMatrix.setElement( 0, 0, 2.0f / ( m_fRight - m_fLeft   ) );
   m_oProjectionMatrix.setElement( 1, 1, 2.0f / ( m_fTop   - m_fBottom ) );

   float fFactor = 1.0f / ( m_fZNear - m_fZFar );

   m_oProjectionMatrix.setElement( 2, 2, fFactor );

   m_oProjectionMatrix.setElement( 0, 3, ( m_fLeft + m_fRight  ) / ( m_fLeft   - m_fRight ) );
   m_oProjectionMatrix.setElement( 1, 3, ( m_fTop  + m_fBottom ) / ( m_fBottom - m_fTop   ) );
   m_oProjectionMatrix.setElement( 2, 3, m_fZNear * fFactor );
}

		}; // video
	}; // services
}; // namespace powergine
