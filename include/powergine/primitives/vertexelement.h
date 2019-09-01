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

#ifndef VERTEXELEMENT_H
#define VERTEXELEMENT_H

namespace powergine {
	namespace primitives {


	/**
	 * A vertex element is a information which can be added
	 * to a vertex to be used during its rendering.
	 */
	class VertexElement {

	public:

	   enum ELEMENT_TYPE {
		  ELEMENT_POSITION  = 0,
		  ELEMENT_NORMAL    = 1,
		  ELEMENT_TEXCOORD  = 2,
		  ELEMENT_COLOR     = 3,
		  ELEMENT_INVALID   = -1
	   };

	   enum DATA_TYPE {
		  DATA_INVALID = 0,
		  DATA_FLOAT1 = 1,
		  DATA_FLOAT2 = 2,
		  DATA_FLOAT3 = 3,
		  DATA_FLOAT4 = 4
	   };
	   // simple constructor
	   VertexElement( );

	   VertexElement( ELEMENT_TYPE eElementType, DATA_TYPE eDataType, unsigned int uiOffset );

	   /**
		* Getter for element type
		*/
	   inline ELEMENT_TYPE getElementType( ) const { return m_eElementType; }

	   /**
		* Getter for data type
		*/
	   inline DATA_TYPE getDataType( ) const { return m_eDataType; }

	   /**
		* Getter for index
		*/
	   inline unsigned int getIndex( ) const { return m_uiIndex; }

	   /**
		* Getter for offset
		*/
	   inline unsigned int getOffset( ) const { return m_uiOffset; }

	   /**
	    * Set this element with the values of a given one
	    */
	   VertexElement& operator=( const VertexElement &rkElement );

	   // Returns the number of elements of each type
	   static unsigned int getNumElements( ELEMENT_TYPE eElementType );

	private:
	   // Elemennt type
	   ELEMENT_TYPE m_eElementType;
	   // Element data type
	   DATA_TYPE m_eDataType;
	   // Element Index for multi element type
	   unsigned int m_uiIndex;
	   // Element offset of dataBuffer
	   unsigned int m_uiOffset;
	   // autoincrement index counter
	   static unsigned int s_uiIndexCounter[ ];
	};


	}; // primitives
}; // namespace powergine

#endif //VERTEXELEMENT_H
