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

#ifndef BITSET_H
#define BITSET_H

#include <iostream>
#include <cstring>

namespace powergine {
	namespace utils {

	/**
	 * Represents a collection of bits
	 */
	class BitSet {

	public:
	   // constructors
	   BitSet( unsigned int uiSize = 0 );

	   BitSet( char *pcBits, unsigned int uiSize );
	   //destructor
	   ~BitSet( );
	   // set all bits to 1
	   void set( );
	   // set specific bit to 1
	   void set( unsigned int uiBitIndex );
	   // set all bits to 0
	   void reset( );
	   // set specific bit to 0
	   void reset( unsigned int uiBitIndex );
	   // toggle value ( 0 or 1 ) of a specific bit
	   void toggle( unsigned int uiBitIndex );
	   // resize the bit buffer
	   void resize( unsigned int uiNumElements );
	   // test if the bit is set or not
	   bool isSet( unsigned int uiBitIndex );
	   // get the size of bitset
	   unsigned int getSize( );
	   // load bits from pointer
	   void loadBitSet( char *pcBits, unsigned int uiSize );
	   // the maximum number of bits handled
	   unsigned int getMaxNumBits( );
	private:
	   // size of bitset ( num of bits handled bit the bitset )
	   unsigned int m_uiSize;
	   // bit buffer
	   char *m_pcBits;
	};

		}; // utils
	}; //namespace powergine

#endif //BITSET_H
