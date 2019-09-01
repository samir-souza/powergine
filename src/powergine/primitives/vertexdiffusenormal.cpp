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


#include <powergine/primitives/vertexdiffusenormal.h>

namespace powergine {  
	namespace primitives {
		
// Constructors/Destructors
// Methods
VertexFormat VertexDiffuseNormal::s_oFormat;

VertexDiffuseNormal::VertexDiffuseNormal( const Vector3D &rkPosition,
                                          const Color &rkDiffuseColor,
                                          const Vector3D &rkNormal ) :
   VertexDiffuse( rkPosition, rkDiffuseColor ),   
   m_oNormal( rkNormal )
{   
}

const Vector3D& VertexDiffuseNormal::getNormal( ) const {
   return m_oNormal;  
}

void VertexDiffuseNormal::setNormal( const Vector3D &rkNormal ) {
   m_oNormal = rkNormal;	
}

void VertexDiffuseNormal::setAll( const Vector3D &rkPosition, const Color &rkDiffuseColor, const Vector3D &rkNormal ) {
   VertexDiffuse::setPosition( rkPosition );
   VertexDiffuse::setDiffuseColor( rkDiffuseColor );
   setNormal( rkNormal );
} // setAll

std::string VertexDiffuseNormal::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << VertexDiffuse::toString( );   
   sstrDesc << "Normal[ " << m_oNormal.toString( ) << "] ";
   return sstrDesc.str( );
}

	}; // primitives
}; // namespace powergine
