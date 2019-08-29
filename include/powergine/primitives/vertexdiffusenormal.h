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

#ifndef VERTEXDIFFUSENORMAL_H
#define VERTEXDIFFUSENORMAL_H

#include <sstream>
#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/primitives/vector3d.h>

namespace powergine {
	namespace primitives {

	/**
	 * A special case of vertex which holds information about
	 * a normal and the diffuse color of the vertex
	 */
	class VertexDiffuseNormal : public VertexDiffuse {
	// Public stuff
	public:

	   static VertexFormat s_oFormat;

	   VertexDiffuseNormal( const Vector3D &rkPosition = Vector3D::ORIGO,
							const Color &rkDiffuseColor = Color::WHITE,
							const Vector3D &rkNormal = Vector3D::ORIGO );

	   // Returns the vertex normal
	   const Vector3D& getNormal( ) const;

	   // Updates the vertex normal
	   void setNormal( const Vector3D &rkNormal );

	   // Updates the vertex position, diffuse color and normal
	   void setAll( const Vector3D &rkPosition, const Color &rkDiffuseColor, const Vector3D &rkNormal );

	   // Returns a description of the vertex
	   std::string toString( ) const;

	private:
	  // Fields

	   Vector3D m_oNormal;
	};

	typedef utils::Buffer<VertexDiffuseNormal> VertexDiffuseNormalBuffer;

	}; // primitives
}; // namespace powergine

#endif //VERTEXDIFFUSENORMAL_H
