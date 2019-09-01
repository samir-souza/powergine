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

#ifndef PHYSICSNODE_H
#define PHYSICSNODE_H

#include <sstream>
#include <powergine/sceneobjects/scenenode.h>
#include <powergine/primitives/vector3d.h>

namespace powergine {
      namespace sceneobjects {

      /**
       * A physics node is part of the physics engine. It has several
       * properties used to determine the position of a given body in the
       * next cycles.
       */
      class PhysicsNode : public SceneNode {

		public:

		   PhysicsNode( const std::string &rkstrName = "" );

		   PhysicsNode( const PhysicsNode &rkNode );

		   virtual ~PhysicsNode( ) { };

		   // Returns the current Linear velocity of the body
		   primitives::Vector3D& getLinearVelocity( );

		   // Returns the current Angular velocity of the body
		   primitives::Vector3D& getAngularVelocity( );

		   // Returns the current position of the body
		   primitives::Vector3D& getPosition( );

		   // Attribution operator. Makes this node equals to another
		   PhysicsNode& operator=( const PhysicsNode &rkNode );

		   // Creates a clone of this node
		   PhysicsNode* clone( );

		   // Returns a string representation of this node
		   std::string toString( ) const;

		   // Apply some force to node
		   void  applyForce (const primitives::Vector3D &rkForce);

		   // Apply some impulse to node(Angular Velocity)
		   void  applyImpulse (const primitives::Vector3D &rkImpulse);

		   // Updates the node position
		   void  setPosition (const primitives::Vector3D &rkPosition);

		private:
		  // Fields
		   primitives::Vector3D m_oLinearVelocity;
		   primitives::Vector3D m_oAngularVelocity;
		   primitives::Vector3D m_oPosition;
		};

	}; // sceneobjects
}; // powergine

#endif //PHYSICSNODE_H
