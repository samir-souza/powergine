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

#ifndef SDLIMAGE_H
#define SDLIMAGE_H

#include <sstream>
#include <cstring>
#include <powergine/primitives/image.h>

struct SDL_Surface;

namespace powergine {
   namespace services {
      namespace video {
         namespace opengl {

			 /**
			  * This is a SDL implementation of the class Image
			  * It uses the SDL resources for loading an image
			  * and making it suitable for using it in the Engine
			  * Methods
			  */
			class SDLImage : public primitives::Image {

			public:

				// Default constructor. It receives the image filename
			   SDLImage( const std::string &rkstrFileName );

			   SDLImage( char *pcData, int iWidth, int iHeight, int iDepth = 8 );

			   virtual ~SDLImage( );

			   // Returns the image width
			   int getWidth( ) const;

			   // Returns the image height
			   int getHeight( ) const;

			   // Returns the number of bits per pixels of the image
			   unsigned short getBpp( ) const;

			   // Returns a pointer to the raw image data
			   void* getData( );

			   // Updates a gamma correction factor
			   void setGamma( float fFactor );

			   // Returns the color components of a given pixel
			   unsigned int getPixel( unsigned int uiX, unsigned int uiY );

			   // Updates the color components of a given pixel
			   void putPixel( unsigned int uiX, unsigned int uiY, unsigned int uiPixel );

			private:
			   SDL_Surface *m_pImage;

			};

         }; // opengl
      }; // video
   }; // services
}; // namespace powergine

#endif //SDLIMAGE_H
