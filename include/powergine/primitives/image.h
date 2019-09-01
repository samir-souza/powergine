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

#ifndef IMAGE_H
#define IMAGE_H

#include <string>

namespace powergine {
	namespace primitives {

	/**
	 * Abstract representation of an image
	 */
	class Image {

	public:

		// Default constructor receives the image filename
		inline Image( const std::string &rkstrFileName ) : m_strFileName( rkstrFileName ) { };

		inline virtual ~Image( ) { };

		// Returns the image width
		virtual int getWidth( ) const = 0;

		// Returns the image height
		virtual int getHeight( ) const = 0;

		// Returns the number of bits per pixes of the image
		virtual unsigned short getBpp( ) const = 0;

		// Returns the image data pointer
		virtual void* getData( ) = 0;

		// Gamma correction of the image
		virtual void setGamma( float fFactor ) = 0;

		// Getter of the image filename
		inline const std::string& getFileName( ) { return m_strFileName; }

	private:
		std::string m_strFileName;

	};

	}; // primitives
}; // powergine

#endif //IMAGE_H
