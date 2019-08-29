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

#ifndef QUAD_H
#define QUAD_H

#include <sstream>
#include <cassert>
#include <powergine/utils/buffer.h>

namespace powergine {
	namespace primitives {

	/**
	 * This is an indexed quad representation. It holds
	 * the indexes of the Vertices (of a given polygon buffer)
	 * which composes a quad
	 */
	class Quad {

	public:

		// Constructor. Receives the indexes of the vertices
	   Quad( unsigned int uiV1=0, unsigned int uiV2=0, unsigned int uiV3=0, unsigned int uiV4=0 );

	   // Helper function which returns the number of vertices
	   // a quad has. It is used by the rendering mechanism
	   static int getNumVertices( );

	   // Helper operator which returns the vertex index
	   unsigned int& operator[]( int iIndex ) const;

	   // Setter to redefine all the indexes
	   void setAll( unsigned int uiV1, unsigned int uiV2, unsigned int uiV3, unsigned int uiV4 );

	   // Returns a string representation of the quad
	   std::string toString( ) const;

	private:
	   unsigned int m_uiVertices[ 4 ];
	};

	typedef utils::Buffer< Quad > QuadBuffer;

	}; // primitives
}; // namespace powergine

#endif //SQUARE_H
