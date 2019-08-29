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

#ifndef BUFFER_H
#define BUFFER_H

#include <iostream>
#include <stdexcept>
#include <memory>
#include <sstream>
#include <powergine/utils/collection.h>
#include <powergine/utils/iterator.h>

namespace powergine {
	namespace utils {


	/**
	 * Generic buffer used by several classes to store specific
	 * data.
	 */
	template<class ClassType> class Buffer : public Collection<ClassType> {

	private:
	   std::unique_ptr<ClassType> m_pucBuffer;
	   int m_iNumElements;
	   int m_iTypeSize;


	   /**
	    * Implementation of a buffer iterator
	    */
	   class BufferIterator : public Iterator<ClassType> {

	   public:
		  inline BufferIterator( const Buffer<ClassType> *pBuffer );

		  // See Iterator::hasMore
		  inline bool hasMore( ) const;

		  // See Iterator::goFirst
		  inline void goFirst( );

		  // See Iterator::goNext
		  inline void goNext( );

		  // See Iterator::getCurrent
		  inline ClassType& getCurrent( ) const;

	   private:
		  const Buffer<ClassType> *m_pBuffer;
		  unsigned int m_uiCursor;
	   };


	public:

	   typedef BufferIterator iterator;

	   inline Buffer ( int iNumElements );

	   // Returns the size of the type of the object stored by the buffer
	   inline int getTypeSize( ) const { return m_iTypeSize; }

	   // Returns the number of stored elements
	   inline int getNumElements( ) const { return m_iNumElements; }

	   // Returns a element positioned at a given index
	   inline ClassType& getElementAt( int iIndex ) const;

	   // Returns a pointer to the contiguous data of the elements stored in
	   // this buffer
	   inline unsigned char *getData( );

	   // Create a new iterator
	   inline iterator *makeIterator( );

	};

	// inline implementation of the buffer
	#include "buffer_inl.h"

	}; // utils
}; // namespace powergine

#endif //BUFFER_H
