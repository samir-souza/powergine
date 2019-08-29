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

#include <powergine/services/video/viewport.h>

namespace powergine {
	namespace services {
		namespace video {


ViewPort::ViewPort( int iX, int iY, int iWidth, int iHeight ) {
   m_iX = iX;
   m_iY = iY;
   m_iWidth = iWidth;
   m_iHeight = iHeight;
}

ViewPort::ViewPort( ) {
   m_iX = 0;
   m_iY = 0;
   m_iWidth = 0;
   m_iHeight = 0;
}

int ViewPort::getX( ) const {
   return m_iX;
}

int ViewPort::getY( ) const {
   return m_iY;
}

void ViewPort::setX( int iX ) {
   m_iX = iX;
}

void ViewPort::setY( int iY ) {
   m_iY = iY;
}

int ViewPort::getWidth( ) const {
   return m_iWidth;
}

int ViewPort::getHeight( ) const {
   return m_iHeight;
}

void ViewPort::setWidth( int iWidth ) {
   m_iWidth = iWidth;
}

void ViewPort::setHeight( int iHeight ) {
   m_iHeight = iHeight;
}

		}; // video
	}; // services
}; // namespace powergine
