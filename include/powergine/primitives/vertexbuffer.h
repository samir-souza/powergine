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


#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H

#include <powergine/primitives/vertexformat.h>
#include <powergine/primitives/vertexelement.h>

namespace powergine {
	namespace primitives {


	/**
	 * Buffer used to hold all the primitive object vertices
	 */
	class VertexBuffer {

	public:
	   /**
		* Simple constructor
		* uiNumvVertices Number of vertices in data buffer
		* rkFormat Vertex Format
		* pucData Data buffer pointer
		*/
	   VertexBuffer( unsigned int uiNumvVertices, const VertexFormat &rkFormat, unsigned char *pucData = 0 );

	   /**
		* Destructor
		*/
	   virtual ~VertexBuffer( );

	   /**
		* Getter for Vertex Format
		*/
	   inline const VertexFormat& getFormat( ) const { return m_oFormat; }

	   /**
		* Getter for Number of vertices
		*/
	   inline unsigned int getNumVertices( ) const { return m_uiNumVertices; }

	   /**
		* Getter for vertex data pointer
		*/
	   inline unsigned char* getVertexData( ) { return m_pucVertexData; }


	private:
	   // Number of vertices in data buffer
	   unsigned int m_uiNumVertices;
	   // Vertex format
	   VertexFormat m_oFormat;
	   // Vertices data buffer
	   unsigned char *m_pucVertexData;
	};

	}; // primitives
}; // namespace powergine

#endif //VERTEXBUFFER_H
