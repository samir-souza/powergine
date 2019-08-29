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


#include <powergine/services/video/projection.h>

namespace powergine {
	namespace services {
		namespace video {

Projection::Projection( ) {
   m_eMode = CUSTOM;
}

Projection::~Projection( ) {
}

float Projection::getZNear( ) const {
   return m_fZNear;
}

float Projection::getZFar( ) const {
   return m_fZFar;
}

void Projection::setZNear( float fZNear ) {
   m_fZNear = fZNear;
}

void Projection::setZFar( float fZFar ) {
   m_fZFar = fZFar;
}

Projection::MODE Projection::getMode( ) const {
   return m_eMode;
}

void Projection::setMode( Projection::MODE eMode ) {
   m_eMode = eMode;
}

const primitives::Matrix4x4& Projection::getProjectionMatrix( ) {
   return m_oProjectionMatrix;
}

		}; // video
	}; // services
}; // namespace powergine
