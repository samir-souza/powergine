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


#ifndef VERTEXTEXTURE_H
#define VERTEXTEXTURE_H

#include <sstream>
#include <powergine/primitives/vertex.h>
#include <powergine/primitives/textcoords.h>


namespace powergine {
	namespace primitives {

	/**
	 * This is a special type of vertex which holds information about
	 * a texture that will cover the surface of the polygon composed
	 * by this vertex.
	 */
	class VertexTexture : public Vertex {

	public:
	   static VertexFormat s_oFormat;

	   VertexTexture( const Vector3D &rkPosition = Vector3D::ORIGO,
					  float fUTextCoord = 0.0f,
					  float fVTextCoord = 0.0f );

	   VertexTexture( const Vector3D &rkPosition,
					  const TextCoords &rkTextCoords );

	   // Returns the map coords (U & V) of the texture
	   void getUVTextCoord( float &rfU, float &rfV ) const;

	   // Returns the U coord
	   float getUTextCoord( ) const;

	   // Updates the U coord
	   void setUTextCoord( float fUTextCoord );

	   // Returns the V coord
	   float getVTextCoord( ) const;

	   // Updates the V coord
	   void setVTextCoord( float fVTextCoord );

	   // Update both texture coords U & V
	   void setTextureCoords( float fUTextCoord, float fVTextCoord );

	   // Update the texture coords
	   void setTextureCoords( const TextCoords &rkTextCoords );

	   // Update the vertex position and its texture coords
	   void setAll( const Vector3D &rkPosition, const TextCoords &rkTextCoords );

	   // Returns a description of the vertex
	   std::string toString( ) const;

	private:
	   TextCoords m_oTextCoords;
	};

	typedef utils::Buffer<VertexTexture> VertexTextureBuffer;

	}; // primitives
}; // namespace powergine

#endif //VERTEXTEXTURE_H
