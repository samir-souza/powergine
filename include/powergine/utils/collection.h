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


#ifndef COLLECTION_H
#define COLLECTION_H

namespace powergine {
	namespace utils {

	/**
	 * Generic collection template class. It can holds one or more
	 * elements of a given type
	 */
	template <class ClassType> class Collection {

	public:

	   inline Collection( ) { }

	   inline virtual ~Collection( ) { }

	   // Returns the total number of stored elements
	   virtual int getNumElements( ) const = 0;

	   // Returns an element positioned at a given index
	   virtual ClassType& getElementAt( int iIndex ) const = 0;
	};


	}; // utils
}; // namespace powergine

#endif //COLLECTION_H
