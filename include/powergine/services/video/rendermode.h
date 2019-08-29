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

#ifndef RENDERMODE_H
#define RENDERMODE_H

#include <sstream>

namespace powergine {
	namespace services {
		namespace video {

			/**
			 * The render mode defines the window dimension and
			 * the number of bits used to render the color of
			 * each pixel
			 */
			class RenderMode {

			public:

				// Default constructor
			   RenderMode( int iWidth, int iHeight, int iBPP );
			   RenderMode( );

			   inline virtual ~RenderMode( ) { };

			   // Returns the mode screen width
			   int getWidth( ) const;

			   // Returns the mode screen height
			   int getHeight( ) const;

			   // Returns the mode BPP
			   int getBPP( ) const;

			   // Returns a description of the render mode
			   std::string toString( ) const;

			private:
			   int m_iWidth;
			   int m_iHeight;
			   int m_iBPP;
			};

		}; // video
	}; // services
}; // namespace powergine

#endif //RENDERMODE_H
