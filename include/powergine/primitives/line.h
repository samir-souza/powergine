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

#ifndef LINE_H
#define LINE_H

#include <sstream>
#include <cassert>
#include <powergine/utils/buffer.h>

namespace powergine {
   namespace primitives {


   /**
    * Basic representation of a indexed line
    * An indexed line is used to identify which
    * 3D Vectors, stored into an array, composes a given line
    */
	class Line {

	public:

		// Copy constructor
	   Line( const Line &rkLine );

	   // Receives the indexes of the Vectors which composes this line
	   Line( unsigned int uiV1=0, unsigned int uiV2=1 );

	   // Helper method used to identify the number of indexed elements
	   // It is used during the rendering process
	   static int getNumVertices( );

	   // Helper operator to retrieve the indexes
	   unsigned int& operator[]( int iIndex ) const;

	   // Setter to redefine the line
	   void setAll( unsigned int uiV1, unsigned int uiV2 );

	   // Returns a string description of the line
	   std::string toString( ) const;


	private:
	   unsigned int m_uiVertices[ 2 ];
	};

	typedef utils::Buffer< Line > LineBuffer;

	}; // primitives
}; // namespace powergine

#endif //LINE_H
