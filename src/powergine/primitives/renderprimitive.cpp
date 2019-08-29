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


#include <powergine/primitives/renderprimitive.h>

namespace powergine {
	namespace primitives {

RenderPrimitive::RenderPrimitive( MODE eMode,
                                  POLYGON_TYPE ePolygonType,
                                  Material *pMaterial ) :
   m_bPermitTranslation( true ),
   m_eMode( eMode ),
   m_ePolygonType( ePolygonType ),
   m_pModelView( 0 ),
   m_pVertexBuffer( 0 ),
   m_pPolygonBuffer( 0 ),
   m_pMaterial( pMaterial ),
   m_fSize( 1.0f )
{

} // RenderPrimitive

RenderPrimitive::~RenderPrimitive( ) {
   // let the auto pointer from Buffer<> destroy this pointers
   m_pVertexBuffer = 0;
   m_pPolygonBuffer = 0;
   m_pMaterial = 0;
   m_pModelView = 0;
} // ~RenderPrimitive

RenderPrimitive::MODE RenderPrimitive::getMode( ) const {
   return m_eMode;
}

RenderPrimitive::POLYGON_TYPE RenderPrimitive::getPolygonType( ) const {
   return m_ePolygonType;
}

void RenderPrimitive::setMaterial( Material *pMaterial ) {
   m_pMaterial = pMaterial;
}

Material* const RenderPrimitive::getMaterial( ) const {
   return m_pMaterial;
}

void RenderPrimitive::setModelViewMatrix( Matrix4x4 *pModelView ) {
   m_pModelView = pModelView;
}

const Matrix4x4* RenderPrimitive::getModelViewMatrix( ) const {
   return m_pModelView;
}

bool RenderPrimitive::isPermitTranslation( ) const {
   return m_bPermitTranslation;
}

void RenderPrimitive::setPermitTranslation( bool bPermitTranslation ) {
   m_bPermitTranslation = bPermitTranslation;
}

void RenderPrimitive::setEdgeLinesSize( float fSize ) {
   m_fSize = fSize;
} // setLineSize

float RenderPrimitive::getEdgeLinesSize( ) {
   return m_fSize;
} // getLineSize

void RenderPrimitive::setVertexBuffer( VertexBuffer *pVertexBuffer ) {
   m_pVertexBuffer = pVertexBuffer;
} // setVertexBuffer

VertexBuffer *RenderPrimitive::getVertexBuffer( ) {
   return m_pVertexBuffer;
} // getVertexBuffer

void RenderPrimitive::setPolygonBuffer( PolygonBuffer *pPolygonBuffer ) {
   m_pPolygonBuffer = pPolygonBuffer;
} // setPolygonBuffer

PolygonBuffer *RenderPrimitive::getPolygonBuffer( ) {
   return m_pPolygonBuffer;
} // getPolygonBuffer

	}; // primitives
};  // namespace powergine
