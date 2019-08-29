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


#ifndef RENDERENTITY_H
#define RENDERENTITY_H

#include <powergine/sceneobjects/baseentity.h>
#include <powergine/utils/entityvisitor.h>

namespace powergine {
	namespace sceneobjects {

		class Frustum;

		/**
		 * Common interface for creating renderable entities
		 */
		class RenderEntity : public BaseEntity {

		public:

		   RenderEntity( );

		   virtual ~RenderEntity( );

		   // Renders the object
		   virtual bool render ( Frustum *pFrustum = 0 );

		   // RTTI method which accepts a design patter visitor
		   // to execute a specific operation
		   virtual void accept( const utils::EntityVisitor &rkVisitor );
		};

	}; // sceneobjects
}; // namespace powergine

#endif //RENDERENTITY_H
