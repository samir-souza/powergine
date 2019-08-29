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

#ifndef PHYSICSMANAGER_H
#define PHYSICSMANAGER_H

#include <powergine/sceneobjects/rigidbody.h>
#include <powergine/sceneobjects/joint.h>
#include <powergine/sceneobjects/spring.h>
#include <powergine/sceneobjects/room.h>
#include <powergine/primitives/vector3d.h>

#include <string>
#include <algorithm>

namespace powergine {
   namespace services {
      namespace physics {

		/**
		 * This is a rudimentary implementation of a Physics Engine
		 * It is highly experimental and incomplete. So if you want
		 * to use a definitive physics tool don't use it.
		 */
		class PhysicsManager {

		public:

		   static const float DEFAULT_GRAVITY;
		   static const float LINEAR_DRAG_COEF;
		   static const float ANGULAR_DRAG_COEF;
		   static const float COLLISION_TOLERANCE;
		   static const float RESTITUTION_COEF;
		   static const float RESTITUTION_GROUND_COEF;
		   static const float VELOCITY_TOLERANCE;
		   static const float FRICTION_COEF;

		   // Configure a room
			PhysicsManager( sceneobjects::Room *pRoom );

		   inline virtual ~PhysicsManager( ) { }

		   // Adds a new rigid body to the scene
		  void  addRigidBody ( sceneobjects::RigidBody *pRigidBody);

		  // Removes a rigid body from the scene
		  void  removeRigidBody (sceneobjects::RigidBody *pRigidBody);

		  // Adds a joint to the scene
		  void  addJoint (sceneobjects::Joint *pJoint);

		  // Removes a joint from the scene
		  void  removeJoint (sceneobjects::Joint *pJoint);

		  // Do a step update in the world
		  virtual void  update (float fDeltaTime);

		  // Returns a list of all rigid bodies of the scene
		  std::vector<sceneobjects::RigidBody*>&  getRigidBodies ();

		  // Updates the gravity vector force
		  void  setGravity (primitives::Vector3D &rkGravity);

		private:

		   sceneobjects::Room *m_pRoom;
		   primitives::Vector3D m_oGravity;
		   std::vector<sceneobjects::RigidBody*> m_vecRigidBodies;
		   std::vector<sceneobjects::Joint*> m_vecJoints;
		   std::vector<sceneobjects::Spring*> m_vecSprings;

		   void resolveCollisions( );
		   void calculateBodyForces( );
		};

      }; //namespace
   }; //namespace
}; //namespace


#endif //PHYSICSMANAGER_H

