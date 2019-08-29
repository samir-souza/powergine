// Copyright (c) 2004 Samir Araujo <samir.araujo.com>
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


#include <powergine/primitives/line.h>


namespace powergine {
	namespace primitives {
// Constructors/Destructors
// Methods

int Line::getNumVertices( ){
   return 2;
}

Line::Line( const Line &rkLine ) {
   m_uiVertices[ 0 ] = rkLine[ 0 ];
   m_uiVertices[ 1 ] = rkLine[ 1 ];   
}

Line::Line( unsigned int uiV1, unsigned int uiV2 ) {
   m_uiVertices[ 0 ] = uiV1;
   m_uiVertices[ 1 ] = uiV2;   
}

unsigned int& Line::operator[]( int iIndex ) const {   
   assert( iIndex >= 0 && iIndex < 2 );
   return const_cast<unsigned int&>( m_uiVertices[ iIndex ] );
}

void Line::setAll( unsigned int uiV1, unsigned int uiV2 ) {
   m_uiVertices[ 0 ] = uiV1;
   m_uiVertices[ 1 ] = uiV2;
} // setAll

std::string Line::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << "V1(" << m_uiVertices[ 0 ];
   sstrDesc << ") V2(" << m_uiVertices[ 1 ];
   sstrDesc << ") ";
   return sstrDesc.str( );
}

	}; // primitives
}; // namespace powergine
