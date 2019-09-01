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


#ifndef VERTEX_H
#define VERTEX_H

#include <sstream>
#include <powergine/primitives/vector3d.h>
#include <powergine/utils/buffer.h>
#include <powergine/primitives/vertexformat.h>

namespace powergine {
	namespace primitives {

	/**
	 * This class is a representation of a primitive
	 * object vertex. It has a position and a format, used
	 * during the rendering process.
	 */
	class Vertex {

	public:
	   static VertexFormat s_oFormat;

	   // Constructor which receives the vertex position
	   Vertex( const Vector3D &rkPosition = Vector3D::ORIGO );

	   // Returns the vertex position
	   const Vector3D& getPosition( ) const;

	   // Updates the vertex position
	   void setPosition( const Vector3D &rkPosition );

	   // Returns a description of the vertex
	   std::string toString( ) const;

	private:

	   Vector3D m_oPosition;

	};

	typedef utils::Buffer<Vertex> VertexSimpleBuffer;

	}; // primitives
}; // namespace powergine

#endif //VERTEX_H
