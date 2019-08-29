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

#ifndef JOINT_H
#define JOINT_H

#include <powergine/sceneobjects/rigidbody.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * Represents a joint that can link two rigid bodies. A joint
		 * is used by the Physics manager during the forces integration
		 */
		class Joint {

		public:

		   Joint( RigidBody *pBody1, RigidBody *pBody2 );

		   virtual ~Joint( );

		   // Solve this joint
		   void solve( );

		   // Returns the first attached body
		   inline RigidBody* getBody1( ) { return m_pBody1; }

		   // Returns the second attached body
		   inline RigidBody* getBody2( ) { return m_pBody2; }

		private:
		   RigidBody *m_pBody1;
		   RigidBody *m_pBody2;
		};

	}; // sceneobjects
}; // powergine

#endif //JOINT_H
