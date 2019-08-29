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

#ifndef VIEWPORT_H
#define VIEWPORT_H

namespace powergine {
	namespace services {
		namespace video {

			/**
			 * Implementation of a Window Viewport. Used to render
			 * a camera on screen
			 */
			class ViewPort {
			public:

				// X an Y are the screen point coord where the
				// Viewport will start and the width and height
				// will be relative to that point
				ViewPort( int iX, int iY, int iWidth, int Height );

				ViewPort( );

				// Returns the X of the start point
				int getX( ) const;

				// Returns the Y of the start point
				int getY( ) const;

				// Updates the X of the start point
				void setX( int iX );

				// Updates the Y of the start point
				void setY( int iY );

				// Returns the current viewport width
				int getWidth( ) const;

				// Returns the current viewport height
				int getHeight( ) const;

				// Updates the current viewport width
				void setWidth( int iWidth );

				// Updates the current viewport height
				void setHeight( int iHeight );

			private:

				int m_iX;
				int m_iY;
				int m_iWidth;
				int m_iHeight;

			};

		}; // video
	}; // services
}; //namespace powergine

#endif //VIEWPORT_H
