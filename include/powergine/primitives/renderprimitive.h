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

#ifndef RENDERPRIMITIVE_H
#define RENDERPRIMITIVE_H

#include <map>
#include <string>
#include <memory>
#include <typeinfo>

#include <powergine/primitives/line.h>
#include <powergine/primitives/triangle.h>
#include <powergine/primitives/quad.h>
#include <powergine/primitives/matrix4x4.h>

#include <powergine/primitives/material.h>

#include <powergine/primitives/vertexbuffer.h>
#include <powergine/primitives/polygonbuffer.h>

namespace powergine {
	namespace primitives {


	/**
	 * This class is a representation of all
	 * renderable objects. It is used to compose 3D objects
	 * which will be rendered by the renderer of the engine
	 */
	class RenderPrimitive {

	public:

	   enum MODE {
		  MODE_LINES           = 0,
		  MODE_TRIANGLES,
		  MODE_LINE_STRIP,
		  MODE_TRIANGLE_STRIP,
		  MODE_POINTS,
		  MODE_QUADS,
		  MODE_QUAD_STRIP,
		  MODE_POLYGON
	   };

	   enum POLYGON_TYPE {
		  POLYGON_LINE        = 0,
		  POLYGON_TRIANGLE    = 1,
		  POLYGON_QUAD        = 2
	   };


	   RenderPrimitive( MODE eMode = MODE_TRIANGLES,
						POLYGON_TYPE ePolygonType = POLYGON_TRIANGLE,
						Material *pMaterial = 0 );

	   virtual ~RenderPrimitive( );

	   // Getter of the mode
	   MODE getMode( ) const;

	   // Returns the polygon type
	   POLYGON_TYPE getPolygonType( ) const;

	   // Update the primitive material
	   void setMaterial( Material *pMaterial );

	   // Getter of the primitive material
	   Material* const getMaterial( ) const;

	   // Set the transformation matrix that will be used
	   // to render this primitive
	   void setModelViewMatrix( Matrix4x4 *pModelView );

	   // Returns the current transformation matrix
	   const Matrix4x4* getModelViewMatrix( ) const;

	   // Updates a flag which indicates if this primitive can
	   // has its position translated or not
	   void setPermitTranslation( bool bPermitTranslation );

	   // True if translations are allowed to this object, false otherwise
	   bool isPermitTranslation( ) const;

	   // Update the size of the edge lines which surrounds this primitive
	   void setEdgeLinesSize( float fEdgeLinesSize );

	   // Returns the current edge lines size
	   float getEdgeLinesSize( );

	   // Update the current vertex buffer of this primitive
	   void setVertexBuffer( VertexBuffer *pVertexBuffer );

	   // Returns the current vertex buffer
	   VertexBuffer *getVertexBuffer( );

	   // Update the indexes buffer
	   void setPolygonBuffer( PolygonBuffer *pPolygonBuffer );

	   // Returns the current polygon indexes buffer
	   PolygonBuffer *getPolygonBuffer( );

	private:
	   // fields
	   bool m_bPermitTranslation;
	   MODE m_eMode;
	   POLYGON_TYPE m_ePolygonType;
	   Matrix4x4 *m_pModelView;
	   VertexBuffer *m_pVertexBuffer;
	   PolygonBuffer *m_pPolygonBuffer;
	   Material *m_pMaterial;
	   float m_fSize;

	};

	}; // primitives
}; // namespace powergine

#endif //RENDERPRIMITIVE_H
