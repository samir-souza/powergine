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


#include <powergine/utils/bitset.h>

namespace powergine {
	namespace utils {
        
BitSet::BitSet( unsigned int uiSize ) :
   m_uiSize( 0 ),
   m_pcBits( 0 )
{
   resize( uiSize );
} // BitSet

BitSet::BitSet( char *pcBits, unsigned int uiSize ) :
   m_uiSize( 0 ),
   m_pcBits( 0 )
{   
   // copy memset to bitset pointer
   loadBitSet( pcBits, uiSize );
} // BitSet

BitSet::~BitSet( ) {
   delete [] m_pcBits;
}


void BitSet::set( ) {
   std::memset( m_pcBits, 1, sizeof( char ) * m_uiSize );
} // set

void BitSet::set( unsigned int uiBitIndex ) {
   m_pcBits[ uiBitIndex >> 3 ] |= ( 1 << ( uiBitIndex & 7 ) );
}

void BitSet::reset( ) {   
   std::memset( m_pcBits, 0, sizeof( char ) * m_uiSize );   
} // reset

void BitSet::reset( unsigned int uiBitIndex ) {   
   m_pcBits[ uiBitIndex >> 3 ] &= ~( 1 << ( uiBitIndex & 7 ) );
} // reset

void BitSet::toggle( unsigned int uiBitIndex ) {
   ( isSet( uiBitIndex ) ) ? reset( uiBitIndex ) : set( uiBitIndex );
} // toggle

void BitSet::resize( unsigned int uiNumElements ) {
   unsigned int uiNewSize = ( uiNumElements >> 3 ) + 1;
   if ( uiNewSize != m_uiSize ) {
      m_uiSize = uiNewSize;
      if ( m_pcBits ) {
         delete [] m_pcBits;
      } // if
      m_pcBits = new char[ m_uiSize ];
      reset( );
   } // if
} // resize

bool BitSet::isSet( unsigned int uiBitIndex ) {
   return m_pcBits[ uiBitIndex >> 3 ] & ( 1 << ( uiBitIndex & 7 ) );
} // isSet

unsigned int BitSet::getSize( ) {
   return m_uiSize;
} // getEdgeLinesSize

void BitSet::loadBitSet( char *pcBits, unsigned int uiSize ) {
   m_uiSize = uiSize;
   if ( m_pcBits ) {
      delete [] m_pcBits;
   } // if
   m_pcBits = new char[ m_uiSize ];
   std::memcpy( m_pcBits, pcBits, uiSize );
} // loadBitSet

unsigned int BitSet::getMaxNumBits( ) {
   return m_uiSize * 8;
} // getMaxNumBits

	}; // utils
}; //namespace powergine
