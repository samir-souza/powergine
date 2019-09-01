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

#ifndef VERTEXFORMAT_H
#define VERTEXFORMAT_H

#include <powergine/primitives/vertexelement.h>
#include <string>

namespace powergine {
	namespace primitives {


	/**
	 * The vertex format indicates how many elements will
	 * be used as additional information during the rendering
	 * time of a given vertex
	 */
	class VertexFormat {

	public:
	   // simple constructor
	   inline VertexFormat( unsigned int uiNumElements, VertexElement *pElementData ) :
		  m_uiNumElements( 0 ),
		  m_pElementData( pElementData ),
		  m_iTypeSize( 0 ) {
		  if ( !pElementData ) {
			 throw( std::string( "Invalid Element data" ) );
		  } // if
		  for ( unsigned int uiI = 0; uiI < uiNumElements; ++uiI ) {
			 m_iTypeSize += pElementData[ uiI ].getDataType( ) * sizeof( float );
		  } // for
	   } // VertexFormat

	   inline VertexFormat( ) :
		  m_uiNumElements( 0 ),
		  m_pElementData( 0 ),
		  m_iTypeSize( 0 ) {
	   } // VertexFormat

	   inline ~VertexFormat( ) {
		  if ( m_pElementData ) {
			 delete m_pElementData;
		  } // if
	   } // ~VertexFormat

	   inline void addElement( VertexElement *pElement ) {
		  // create a new array greater than old by 1
		  VertexElement *pTempData = new VertexElement[ m_uiNumElements + 1 ];
		  // copy the elemnts from old array
		  for ( unsigned int uiI = 0; uiI < m_uiNumElements; ++uiI ) {
			 pTempData[ uiI ] = m_pElementData[ uiI ];
		  } // for
		  // assign the new element to the end of array
		  pTempData[ m_uiNumElements++ ] = *pElement;
		  // cleam old memory allocation
		  delete [] m_pElementData;
		  // point to the new array
		  m_pElementData = pTempData; pTempData = 0;
		  // increment type size
		  m_iTypeSize += pElement->getDataType( ) * sizeof( float );
	   } // addElement

	   inline unsigned int getNumElements( ) const { return m_uiNumElements; }

	   inline VertexElement* getElements( ) const { return m_pElementData; }

	   inline int getTypeSize( ) const { return m_iTypeSize; }

	   inline VertexFormat& operator=( const VertexFormat &rkFormat ) {
		  if ( m_pElementData ) {
			 delete [] m_pElementData;
		  } // if
		  m_uiNumElements = rkFormat.getNumElements( );
		  m_pElementData = new VertexElement[ m_uiNumElements ];
		  VertexElement *pTempData = rkFormat.getElements( );
		  for ( unsigned int uiI = 0; uiI < m_uiNumElements; ++uiI ) {
			 m_pElementData[ uiI ] = pTempData[ uiI ];
		  } // for
		  return *this;
	   } // operator=

	private:
	   // Number of elemnts
	   unsigned int m_uiNumElements;
	   // VertexElement pointer to data
	   VertexElement *m_pElementData;
	   // data type size
	   int m_iTypeSize;
	};

	}; // primitives
}; // namespace powergine

#endif //VERTEXFORMAT_H
