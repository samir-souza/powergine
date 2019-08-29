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


#ifndef OGLVERTEXBUFFER_H
#define OGLVERTEXBUFFER_H

#include <powergine/primitives/vertexbuffer.h>
#include <powergine/primitives/vertexformat.h>
#include <powergine/primitives/vertexelement.h>

namespace powergine {
   namespace services {
      namespace video {
         namespace opengl {

			 /**
			  * Implementation of a OpenGL vertex buffer
			  */
			class OGLVertexBuffer : public primitives::VertexBuffer {

			public:
			   /**
				* Simple constructor
				* uiNumvVertices Number of vertices in data buffer
				* rkFormat Vertex Format
				* pucData Data buffer pointer
				*/
			   OGLVertexBuffer( unsigned int uiNumvVertices, const primitives::VertexFormat &rkFormat, unsigned char *pucVertexData );

			   virtual ~OGLVertexBuffer( );

			   // position element pointer
			   primitives::VertexElement *m_pPositionElement;
			   // diffuse element pointer
			   primitives::VertexElement *m_pDiffuseElement;
			   // tex coord element pointer
			   primitives::VertexElement *m_pTexCoordElement[ 8 ];
			   // normal element pointer
			   primitives::VertexElement *m_pNormalElement;

			private:
				// Breaks down the vertex elements in position, diffuse color, tex
				// coords and normal
			   void parseElements( );

			};
         }; // opengl
      }; // video
   }; // services
}; // namespace powergine

#endif //OGLVERTEXBUFFER_H
