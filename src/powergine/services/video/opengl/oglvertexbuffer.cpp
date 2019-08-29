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


#include <powergine/services/video/opengl/oglvertexbuffer.h>

namespace powergine {
   namespace services {
      namespace video {
         namespace opengl {


OGLVertexBuffer::OGLVertexBuffer( unsigned int uiNumVertices, const primitives::VertexFormat &rkFormat, unsigned char *pucVertexData ) :
   VertexBuffer( uiNumVertices, rkFormat, pucVertexData ),
   m_pPositionElement( 0 ),
   m_pDiffuseElement( 0 ),
   m_pNormalElement( 0 )
{
   for ( int iI = 0; iI < 9; iI++ ) {
      m_pTexCoordElement[ iI ] = 0;
   } // for

   if ( uiNumVertices > 0 ) {
      parseElements( );
   } // if
} // OGLVertexBuffer

OGLVertexBuffer::~OGLVertexBuffer( ) {
   delete m_pPositionElement;
   delete m_pDiffuseElement;
   delete m_pNormalElement;
   //delete [] m_pTexCoordElement;
} // ~OGLVertexBuffer

void OGLVertexBuffer::parseElements( ) {
   unsigned int uiNumElements = VertexBuffer::getFormat( ).getNumElements( );
   primitives::VertexElement *pElements = VertexBuffer::getFormat( ).getElements( );

   for( unsigned int uiElement = 0; uiElement < uiNumElements; ++uiElement ) {
      primitives::VertexElement *pElement = &pElements[ uiElement ];

      switch( pElement->getElementType( ) ) {
         case primitives::VertexElement::ELEMENT_POSITION: {
            m_pPositionElement = pElement;
         } break;
         case primitives::VertexElement::ELEMENT_NORMAL: {
            m_pNormalElement = pElement;
         } break;
         case primitives::VertexElement::ELEMENT_TEXCOORD: {
            m_pTexCoordElement[ pElement->getIndex( ) ] = pElement;
         } break;
         case primitives::VertexElement::ELEMENT_COLOR: {
            m_pDiffuseElement = pElement;
         } break;
         case primitives::VertexElement::ELEMENT_INVALID:
         default:
        	 break;
      } // switch
   } // for

} // parseElements


         }; // opengl
      }; // video
   }; // services
}; // namespace powergine
