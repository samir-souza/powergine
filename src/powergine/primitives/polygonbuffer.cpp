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


#include <powergine/primitives/polygonbuffer.h>

namespace powergine {   
	namespace primitives {

PolygonBuffer::PolygonBuffer( unsigned int uiNumPolygons, unsigned int uiNumPolygonVertices, unsigned char *pucData ) :
   m_uiNumPolygons( uiNumPolygons ),
   m_uiNumPolygonVertices( uiNumPolygonVertices ),
   m_pucPolygonData( pucData )
{
   if ( !m_pucPolygonData ) {
      m_pucPolygonData = new unsigned char[ uiNumPolygons * uiNumPolygonVertices * sizeof( int ) ];
   } // if
} // PolygonBuffer

PolygonBuffer::~PolygonBuffer( ) {
   if ( m_pucPolygonData ) {
      delete [] m_pucPolygonData;
   } // if
} // ~PolygonBuffer

        
	}; // primitives
}; // namespace powergine
