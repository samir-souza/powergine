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


#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <sstream>
#include <cassert>
#include <powergine/utils/buffer.h>

namespace powergine {
	namespace primitives {

	/**
	 * Representation of a indexed triangle.
	 * It can be used to identifies which vertices
	 * composes a given triangle
	 */
	class Triangle {

	public:

		// Copy constructor
	   Triangle( const Triangle &rkTriangle );

	   // Receive all the three indexes
	   Triangle( unsigned int uiV1=0, unsigned int uiV2=1, unsigned int uiV3=3 );

	   // Helper function which identifies the number of
	   // indexes held by this class
	   static int getNumVertices( );

	   // Helper operator which allows accessing the indexes
	   unsigned int& operator[]( int iIndex ) const;

	   // Update all the three indexes
	   void setAll( unsigned int uiV1, unsigned int uiV2, unsigned int uiV3 );

	   // Returns a description of this class
	   std::string toString( ) const;

	private:
	   unsigned int m_uiVertices[ 3 ];

	};

	typedef utils::Buffer< Triangle > TriangleBuffer;

	}; // primitives
}; // namespace powergine

#endif //TRIANGLE_H
