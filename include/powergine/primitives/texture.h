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

#ifndef TEXTURE_H
#define TEXTURE_H

#include <powergine/primitives/image.h>

namespace powergine {
	namespace primitives {

	/**
	 * Represents a texture which can compose a material
	 */
	class Texture {

	public:

	   enum FILTER {
		  FILTER_NEAREST,   // min=mag=nearest
		  FILTER_LINEAR,    // min=mag=linear
		  FILTER_NO_FILTER, // min=nearest mag=linear mipmap=linear
		  FILTER_BILINEAR,  // min=linear mag=linear mipmap=nearest
		  FILTER_TRILINEAR  // min=linear mag=linear mipmap=linear
	   };

	   Texture( FILTER eFilter, Image *pImage, bool bRepeat = false );

	   virtual ~Texture( );

	   // Returns the image reference used in this texture
	   const Image* const getImage( ) const;

	   // Returns the texture id
	   virtual unsigned int getID( ) const = 0;

	   // Indicates if this texture must be repeated
	   // when appied in a surface bigger than the image
	   // dimension
	   inline bool mustRepeat( ) {
			return m_bRepeat;
	   };

	protected:
	   FILTER m_eFilter;
	   Image *m_pImage;
	   bool m_bRepeat;
	};

	}; // primitives
}; // powergine

#endif //TEXTURE_H
