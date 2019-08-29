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

#ifndef COLOR_H
#define COLOR_H

#include <sstream>
#include <cassert>
#include <powergine/config.h>

namespace powergine {
   namespace primitives {

   /**
	* This class represents a color by holding the three color
	* components (RGB) plus alpha (for transparency)
	*/
	class Color {

	public:

	   PGEXPORT static const int NUM_COMPONENTS;
	   PGEXPORT static const int TYPE_SIZE;

	   // Static consts
	   PGEXPORT static const Color BLACK;
	   PGEXPORT static const Color WHITE;
	   PGEXPORT static const Color RED;
	   PGEXPORT static const Color GREEN;
	   PGEXPORT static const Color BLUE;

	   // Basic constructor which receives the color components
	   PGEXPORT Color( unsigned int uiColor );

	   // Default constructor. A default value for each component and alpha is given
	   Color( float fRed=0.0f, float fGreen=0.0f, float fBlue=0.0f, float fAlpha=1.0f );

	   // Getters of all color components and alpha
	   PGEXPORT float getRed( ) const;
	   PGEXPORT float getGreen( ) const;
	   PGEXPORT float getBlue( ) const;
	   PGEXPORT float getAlpha( ) const;

	   // Setters of each color component and alpha
	   PGEXPORT void setRed( float fRed );
	   PGEXPORT void setGreen( float fGreen );
	   PGEXPORT void setBlue( float fBlue );
	   PGEXPORT void setAlpha( float fAlpha );

	   // Setter of all three components plus alpha
	   PGEXPORT void setColor( unsigned int uiColor );

	   // Getter of the current color representation
	   PGEXPORT unsigned int getColor( );

	   // Returns the string representation of the color
	   PGEXPORT std::string toString( ) const;

	private:

	   float m_fRed;
	   float m_fGreen;
	   float m_fBlue;
	   float m_fAlpha;

	};

   }; // primitives
}; // powergine

#endif //COLOR_H

