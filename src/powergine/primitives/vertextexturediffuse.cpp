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


#include <powergine/primitives/vertextexturediffuse.h>

namespace powergine {  
	namespace primitives {
		
// Constructors/Destructors
// Methods

VertexFormat VertexTextureDiffuse::s_oFormat;

VertexTextureDiffuse::VertexTextureDiffuse( const Vector3D &rkPosition,
                                            float fUTextCoord, 
                                            float fVTextCoord,
                                            const Color &rkColor ) :
   VertexTexture( rkPosition, fUTextCoord, fVTextCoord ),
   m_oDiffuseColor( rkColor )
{

} // VertexTextureDiffuse
                    
const Color& VertexTextureDiffuse::getDiffuseColor( ) const {
   return m_oDiffuseColor;
} // getDiffuseColor

void VertexTextureDiffuse::setDiffuseColor( const Color &rkDiffuseColor ) {
   m_oDiffuseColor = rkDiffuseColor;
} // setDiffuseColor

void VertexTextureDiffuse::setAll( const Vector3D &rkPosition, const TextCoords &rkTextCoords, const Color &rkDiffuseColor ) {
   VertexTexture::setPosition( rkPosition );
   VertexTexture::setTextureCoords( rkTextCoords );
   setDiffuseColor( rkDiffuseColor );
} // setAll

std::string VertexTextureDiffuse::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << VertexTexture::toString( );
   sstrDesc << "DiffuseColor[ " << m_oDiffuseColor.toString( ) << "] ";
   return sstrDesc.str( );
} // toString

	}; // primitives
}; // namespace powergine
