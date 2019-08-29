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


#include <powergine/services/physics/physicsmanager.h>

namespace powergine {
   namespace services {
      namespace physics {

const float PhysicsManager::DEFAULT_GRAVITY = -32.174f;
const float PhysicsManager::LINEAR_DRAG_COEF = 5.0f;
const float PhysicsManager::ANGULAR_DRAG_COEF = 1200.0f;
const float PhysicsManager::COLLISION_TOLERANCE = 0.9f;
const float PhysicsManager::RESTITUTION_COEF = 0.5f;
const float PhysicsManager::RESTITUTION_GROUND_COEF = 0.025f;
const float PhysicsManager::VELOCITY_TOLERANCE = 0.05f;
const float PhysicsManager::FRICTION_COEF = 0.9f;

PhysicsManager::PhysicsManager (sceneobjects::Room *pRoom) :
   m_pRoom( pRoom )
   //m_oGravity( DEFAULT_GRAVITY )
{
}

void PhysicsManager::addRigidBody (sceneobjects::RigidBody *pRigidBody) {
   std::vector<sceneobjects::RigidBody*>::iterator pResult = std::find( m_vecRigidBodies.begin( ), m_vecRigidBodies.end( ), pRigidBody );
   if ( pResult == m_vecRigidBodies.end( ) ) {
      m_vecRigidBodies.push_back( pRigidBody );
   } // if
}

void PhysicsManager::removeRigidBody (sceneobjects::RigidBody *pRigidBody) {
   std::vector<sceneobjects::RigidBody*>::iterator pResult = std::find( m_vecRigidBodies.begin( ), m_vecRigidBodies.end( ), pRigidBody );
   if ( pResult != m_vecRigidBodies.end( ) ) {
      m_vecRigidBodies.erase( pResult );
   } // if
}

void PhysicsManager::addJoint (sceneobjects::Joint *pJoint) {
   std::vector<sceneobjects::Joint*>::iterator pResult = std::find( m_vecJoints.begin( ), m_vecJoints.end( ), pJoint );
   if ( pResult == m_vecJoints.end( ) ) {
      m_vecJoints.push_back( pJoint );
   } // if
}

void PhysicsManager::removeJoint (sceneobjects::Joint *pJoint) {
   std::vector<sceneobjects::Joint*>::iterator pResult = std::find( m_vecJoints.begin( ), m_vecJoints.end( ), pJoint );
   if ( pResult != m_vecJoints.end( ) ) {
      m_vecJoints.erase( pResult );
   } // if
}

std::vector<sceneobjects::RigidBody*>& PhysicsManager::getRigidBodies () {
   return m_vecRigidBodies;
}

void PhysicsManager::setGravity (primitives::Vector3D &rkGravity) {
   m_oGravity = rkGravity;
}

void PhysicsManager::resolveCollisions( ) {
	// TODO: implement
}

void PhysicsManager::calculateBodyForces( ) {
	// TODO: implement
}

void PhysicsManager::update( float fDeltaTime ) {
   calculateBodyForces( );

   std::vector< sceneobjects::RigidBody* >::iterator ppBegin = m_vecRigidBodies.begin( );
   std::vector< sceneobjects::RigidBody* >::iterator ppEnd = m_vecRigidBodies.end( );

   while( ppBegin != ppEnd ) {
      (*ppBegin)->update( fDeltaTime );

      ++ppBegin;
   } // while


   resolveCollisions( );
}

      }; //namespace
   }; //namespace
}; //namespace
