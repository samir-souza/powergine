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


#include <powergine/primitives/color.h>

namespace powergine {
   namespace primitives {

const int NUM_COMPONENTS = 4;
const int TYPE_SIZE = NUM_COMPONENTS * sizeof( float );
const Color Color::BLACK = Color( 0.0f, 0.0f, 0.0f, 1.0f );
const Color Color::RED   = Color( 1.0f, 0.0f, 0.0f, 1.0f );
const Color Color::GREEN = Color( 0.0f, 1.0f, 0.0f, 1.0f );
const Color Color::BLUE  = Color( 0.0f, 0.0f, 1.0f, 1.0f );
const Color Color::WHITE = Color( 1.0f, 1.0f, 1.0f, 1.0f );
   
   
// Constructors/Destructors
// Methods
PGEXPORT Color::Color( unsigned int uiColor ) :
   m_fRed( static_cast<float>( uiColor & 0xFF ) * 0.0039215686f ),
   m_fGreen( static_cast<float>( ( uiColor >> 8 ) & 0xFF ) * 0.0039215686f ),
   m_fBlue( static_cast<float>( ( uiColor >> 16 ) & 0xFF ) * 0.0039215686f ),
   m_fAlpha( static_cast<float>( ( uiColor >> 24 ) & 0xFF ) * 0.0039215686f )   
{
}

PGEXPORT Color::Color( float fRed, float fGreen, float fBlue, float fAlpha ) :
   m_fRed( fRed ),
   m_fGreen( fGreen ),
   m_fBlue( fBlue ),
   m_fAlpha( fAlpha )

{
}

PGEXPORT float Color::getRed( ) const {
   return m_fRed;
}

PGEXPORT float Color::getGreen( ) const {
   return m_fGreen;
}

PGEXPORT float Color::getBlue( ) const {
   return m_fBlue;
}

PGEXPORT float Color::getAlpha( ) const {
   return m_fAlpha;
}

PGEXPORT void Color::setRed( float fRed ) {
   m_fRed = fRed;
}

PGEXPORT void Color::setGreen( float fGreen ) {
   m_fGreen = fGreen;
}

PGEXPORT void Color::setBlue( float fBlue ) {
   m_fBlue = fBlue;
}

PGEXPORT void Color::setAlpha( float fAlpha ) {
   m_fAlpha = fAlpha;
}

PGEXPORT void Color::setColor( unsigned int uiColor ) {
   m_fRed   = static_cast<float>( uiColor & 0xFF ) * 0.0039215686f;
   m_fGreen = static_cast<float>( ( uiColor >> 8 ) & 0xFF ) * 0.0039215686f;
   m_fBlue  = static_cast<float>( ( uiColor >> 16 ) & 0xFF ) * 0.0039215686f;
   m_fAlpha = static_cast<float>( ( uiColor >> 24 ) & 0xFF ) * 0.0039215686f;   
}

PGEXPORT unsigned int Color::getColor( ) {
   assert( "Not implemented");
   return 0;
} // getColor

PGEXPORT std::string Color::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << "R(" << m_fRed;
   sstrDesc << ") G(" << m_fGreen;
   sstrDesc << ") B(" << m_fBlue;
   sstrDesc << ") A(" << m_fAlpha;
   sstrDesc << ") ";   
   return sstrDesc.str( );
} // toString

   }; // primitives
}; // powergine
