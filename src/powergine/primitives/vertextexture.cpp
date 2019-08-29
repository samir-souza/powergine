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


#include <powergine/primitives/vertextexture.h>

namespace powergine {  
	namespace primitives {
		
// Constructors/Destructors
// Methods

VertexFormat VertexTexture::s_oFormat;

VertexTexture::VertexTexture( const Vector3D &rkPosition, float fUTextCoord, float fVTextCoord ) {
   VertexTexture( rkPosition, TextCoords( fUTextCoord, fVTextCoord ) );
} // VertexTexture

VertexTexture::VertexTexture( const Vector3D &rkPosition, const TextCoords &rkTextCoords ) :
   Vertex( rkPosition ),
   m_oTextCoords( rkTextCoords )
{

} // VertexTexture

void VertexTexture::getUVTextCoord( float &rfU, float &rfV ) const {
   rfU = m_oTextCoords.getU( );
   rfV = m_oTextCoords.getV( );
} // getUTextCoord

float VertexTexture::getUTextCoord ( ) const {
   return m_oTextCoords.getU( );
} // getUTextCoord

void VertexTexture::setUTextCoord( float fUTextCoord ) {
   m_oTextCoords.setU( fUTextCoord );
} // setUTextCoord
   
float VertexTexture::getVTextCoord ( ) const {
   return m_oTextCoords.getV( );
} // getVTextCoord

void VertexTexture::setVTextCoord( float fVTextCoord ) {
   m_oTextCoords.setV( fVTextCoord );
} // setVTextCoord
   
void VertexTexture::setTextureCoords ( float fUTextCoord, float fVTextCoord ) {
   m_oTextCoords.set( fUTextCoord, fVTextCoord );
} // setTextureCoordss

void VertexTexture::setTextureCoords( const TextCoords &rkTextCoords ) {
   m_oTextCoords = rkTextCoords;
} // setTextureCoords

void VertexTexture::setAll( const Vector3D &rkPosition, const TextCoords &rkTextCoords ) {
   Vertex::setPosition( rkPosition );
   setTextureCoords( rkTextCoords );
} // setAll

std::string VertexTexture::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << Vertex::toString( );
   sstrDesc << "TextCoord[ U( " << getUTextCoord( );
   sstrDesc << ") V( " << getVTextCoord( );
   sstrDesc << ") ] ";
   return sstrDesc.str( );
} // toString

	}; // primitives
}; // namespace powergine
