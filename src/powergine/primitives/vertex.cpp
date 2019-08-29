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


#include <powergine/primitives/vertex.h>

namespace powergine {
	namespace primitives {
		
// Constructors/Destructors
// Methods

VertexFormat Vertex::s_oFormat;

Vertex::Vertex( const Vector3D &rkPosition ) :
   m_oPosition( rkPosition )
{   
} // Vertex

const Vector3D& Vertex::getPosition( ) const {
   return m_oPosition;
} // getPosition

void Vertex::setPosition( const Vector3D &rkPosition ) {
   m_oPosition = rkPosition;
} // setPosition

std::string Vertex::toString( ) const {   
   std::ostringstream sstrDesc;
   sstrDesc << "Position[ " << m_oPosition.toString( ) << "] ";
   return sstrDesc.str( );
}

	}; // primitives
}; // namespace powergine
