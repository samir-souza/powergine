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


#include <powergine/services/video/perspectiveprojection.h>

namespace powergine {
	namespace services {
		namespace video {


PerspectiveProjection::PerspectiveProjection( ) :
   Projection( )
{
   m_eMode  = Projection::PERSPECTIVE;
   m_fFov   = 45.0f;
   m_fZNear = 0.5f;
   m_fZFar  = 1000.0f;
}

float PerspectiveProjection::getFOV( ) const {
   return m_fFov;
}

void PerspectiveProjection::setFOV( float fFov ) {
   m_fFov = fFov;
}

void PerspectiveProjection::buildProjection( const ViewPort &rkViewPort ) {
   float fTan =
      static_cast<float>( tan( utils::MathHelper::get( )->degree2Radians( m_fFov * 0.5f ) ) );
   float fHeight = 2.0f * ( m_fZNear * fTan );
   float fRatio = static_cast<float>( rkViewPort.getWidth( ) ) / rkViewPort.getHeight( );
   float fWidth = fHeight * fRatio;

   m_oProjectionMatrix.reset( );

   m_oProjectionMatrix.setElement( 0, 0, 2.0f * m_fZNear / fWidth );
   m_oProjectionMatrix.setElement( 1, 1, 2.0f * m_fZNear / fHeight );
   m_oProjectionMatrix.setElement( 2, 2, -( m_fZFar + m_fZNear ) / ( m_fZFar - m_fZNear ) );
   m_oProjectionMatrix.setElement( 3, 2, -1.0f );
   m_oProjectionMatrix.setElement( 2, 3, -2.0f * m_fZNear * m_fZFar / ( m_fZFar - m_fZNear ) );
   m_oProjectionMatrix.setElement( 3, 3, 0.0f );
}

		}; // video
	}; // services
}; // namespace powergine
