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

#ifndef ITERATOR_H
#define ITERATOR_H

namespace powergine {
	namespace utils {

	/**
	 * Template class implemented by containers to iterate
	 * over the elements stored.
	 */
	template <class ClassType> class Iterator {

	public:

	   inline virtual ~Iterator( ) { };

	   // True if there still elements to iterate
	   virtual bool hasMore( ) const = 0;

	   // Go to the first element of the container
	   virtual void goFirst( ) = 0;

	   // Iterate to the next element of the container.
	   virtual void goNext( ) = 0;

	   // Returns the current element pointed by the iterator
	   virtual ClassType& getCurrent( ) const = 0;

	protected:
	   inline Iterator( ) { };

	};


	}; // utils
}; // namespace powergine

#endif //ITERATOR_H
