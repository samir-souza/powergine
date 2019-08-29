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


#include <powergine/primitives/vertexdiffuse.h>

namespace powergine {  
	namespace primitives {
		
// Constructors/Destructors
// Methods

VertexFormat VertexDiffuse::s_oFormat;

PGEXPORT VertexDiffuse::VertexDiffuse( const Vector3D &rkPosition,
                              const Color &rkDiffuseColor ) :
   Vertex( rkPosition ),
   m_oDiffuseColor( rkDiffuseColor )
{   
}

PGEXPORT const Color& VertexDiffuse::getDiffuseColor( ) const {
   return m_oDiffuseColor;
} // getDiffuseColor

PGEXPORT void VertexDiffuse::setDiffuseColor( const Color &rkDiffuseColor ) {
   m_oDiffuseColor = rkDiffuseColor;
} // setDiffuseColor

PGEXPORT void VertexDiffuse::setAll( const Vector3D &rkPosition, const Color &rkDiffuseColor ) {
   Vertex::setPosition( rkPosition );
   setDiffuseColor( rkDiffuseColor );   
} // setAll

PGEXPORT std::string VertexDiffuse::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << Vertex::toString( );
   sstrDesc << "DiffuseColor[ " << m_oDiffuseColor.toString( ) << "] ";   
   return sstrDesc.str( );
} // toString

	}; // primitives
}; // namespace powergine
