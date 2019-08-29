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

#ifndef TEXTCOORDS_H
#define TEXTCOORDS_H

namespace powergine {
   namespace primitives {

   /**
    * Representation of a given texture mapping coords
    */
	class TextCoords {

	public:
	   static const int NUM_COMPONENTS = 2;

	   static const int TYPE_SIZE = NUM_COMPONENTS * sizeof( float );

	   // Create a new text coord with the U and V values
	   inline TextCoords( float fU, float fV ) : m_fU( fU ), m_fV( fV ) { }

	   inline TextCoords( ) : m_fU( 0.0f ), m_fV( 0.0f ) { }

	   // Copy constructor
	   inline TextCoords( const TextCoords &rkCoords ) : m_fU( rkCoords.getU( )  ), m_fV( rkCoords.getV( ) ) { }

	   // Update the U and V coords
	   inline void set( float fU, float fV ) { m_fU = fU; m_fV = fV; }

	   // Update the U coord
	   inline void setU( float fU ) { m_fU = fU; }

	   // Returns the U coord
	   inline float getU( ) const { return m_fU; }

	   // Update the V coord
	   inline void setV( float fV ) { m_fV = fV; }

	   // Returns the V coord
	   inline float getV( ) const { return m_fV; }

	private:
	   float m_fU;
	   float m_fV;
	};

   }; // primitives
}; // powergine

#endif //TEXTCOORDS_H

