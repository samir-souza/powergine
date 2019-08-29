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

#ifndef VERTEXTEXTUREDIFFUSENORMAL_H
#define VERTEXTEXTUREDIFFUSENORMAL_H

#include <sstream>
#include <powergine/primitives/vertextexturediffuse.h>
#include <powergine/primitives/color.h>
#include <powergine/primitives/vector3d.h>

namespace powergine {
	namespace primitives {

	/**
	 * This is a special case of vertex which holds information about
	 * the texture which will cover the polygon composed by this vertex,
	 * the diffuse color and the vertex normal
	 */
	class VertexTextureDiffuseNormal : public VertexTextureDiffuse {

	public:
	   static VertexFormat s_oFormat;

	   VertexTextureDiffuseNormal( const Vector3D &rkPosition = Vector3D::ORIGO,
								   float fUTextCoord=0.0f,
								   float fVTextCoord=0.0f,
								   const Color &rkDiffuseColor = Color::WHITE,
								   const Vector3D &rkNormal = Vector3D::ORIGO );

	   // Returns the current normal
	   const Vector3D& getNormal( ) const;

	   // Updates the vertex normal
	   void setNormal( const Vector3D &rkNormal );

	   // Updates the vertex position, texture coords, diffuse color and normal
	   void setAll( const Vector3D &rkPosition, const TextCoords &rkTextCoords, const Color &rkDiffuseColor, const Vector3D &rkNormal );

	   // Returns a description of the vertex
	   std::string toString( ) const;

	private:
	   Vector3D m_oNormal;
	};

	typedef utils::Buffer<VertexTextureDiffuseNormal> VertexTextureDiffuseNormalBuffer;

	}; // primitives
}; // namespace powergine

#endif //VERTEXTEXTUREDIFFUSENORMAL_H
