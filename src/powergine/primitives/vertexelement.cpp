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

 
#include <powergine/primitives/vertexelement.h>

namespace powergine {   
	namespace primitives {
 
VertexElement::VertexElement( ) :
   m_eElementType( ELEMENT_INVALID ), m_eDataType( DATA_INVALID ),
   m_uiIndex( 0 ), m_uiOffset( 0 ) 
{
}

VertexElement::VertexElement( ELEMENT_TYPE eElementType, DATA_TYPE eDataType, unsigned int uiOffset ) :
   m_eElementType( eElementType ), m_eDataType( eDataType ),      
   m_uiIndex( s_uiIndexCounter[ eElementType ]++ ), 
   m_uiOffset( uiOffset ) 
{ 
}   
   
VertexElement& VertexElement::operator=( const VertexElement &rkElement ) { 
   m_eElementType = rkElement.getElementType( );
   m_eDataType = rkElement.getDataType( );
   m_uiIndex = rkElement.getIndex( );
   m_uiOffset = rkElement.getOffset( );
   return *this;
} // operator=

unsigned int VertexElement::getNumElements( ELEMENT_TYPE eElementType ) {
   return s_uiIndexCounter[ eElementType ];
} // getNumElements
 
unsigned int VertexElement::s_uiIndexCounter[ ] = { 0, 0, 0, 0 };

	}; // primitives
}; // namespace powergine

