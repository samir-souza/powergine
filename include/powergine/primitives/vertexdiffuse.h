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

#ifndef VERTEXDIFFUSE_H
#define VERTEXDIFFUSE_H

#include <sstream>
#include <powergine/primitives/vertex.h>
#include <powergine/primitives/color.h>
#include <powergine/config.h>

namespace powergine {
	namespace primitives {

	/**
	 * A special type of vertex which holds the diffuse
	 * color information.
	 */
	class VertexDiffuse : public Vertex {
	// Public stuff
	public:

	   PGEXPORT static VertexFormat s_oFormat;

	   PGEXPORT VertexDiffuse( const Vector3D &rkPosition = Vector3D::ORIGO,
					  const Color &rkDiffuseColor = Color::WHITE );

	   // Returns the difuse color
	   PGEXPORT const Color& getDiffuseColor( ) const;

	   // Update the difuse color
	   PGEXPORT void setDiffuseColor( const Color &rkDiffuseColor );

	   // Update the difuse color and the vertex position
	   PGEXPORT void setAll( const Vector3D &rkPosition, const Color &rkDiffuseColor );

	   // Returns a description of the vertex
	   PGEXPORT std::string toString( ) const;

	private:
	  // Fields
	   Color m_oDiffuseColor;
	};

	typedef utils::Buffer<VertexDiffuse> VertexDiffuseBuffer;

	}; // primitives
}; // namespace powergine

#endif //VERTEXDIFFUSE_H
