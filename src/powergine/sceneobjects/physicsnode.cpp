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


#include <powergine/sceneobjects/physicsnode.h>


namespace powergine {
	namespace sceneobjects {
	
// Constructors/Destructors
// Methods

PhysicsNode::PhysicsNode( const std::string &rkstrName ) :
   SceneNode( rkstrName )
{
}

PhysicsNode::PhysicsNode( const PhysicsNode &rkNode ) {
   *this = rkNode;
}

primitives::Vector3D& PhysicsNode::getLinearVelocity( ) {
   return m_oLinearVelocity;
}

primitives::Vector3D& PhysicsNode::getAngularVelocity( ) {
   return m_oAngularVelocity;
}

primitives::Vector3D& PhysicsNode::getPosition( ) {
   return m_oPosition;
}

PhysicsNode& PhysicsNode::operator=( const PhysicsNode &rkNode ) {
   PhysicsNode oNode = rkNode;   
   m_oLinearVelocity = oNode.getLinearVelocity( );
   m_oAngularVelocity = oNode.getAngularVelocity( );
   m_oPosition = oNode.getPosition( );
   setName( oNode.getName( ) );
   return *this;
}

PhysicsNode* PhysicsNode::clone( ) {	
   return new PhysicsNode( *this );
}

std::string PhysicsNode::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << "Linear Velo.(" << m_oLinearVelocity.toString( );
   sstrDesc << ") Angular Velo.(" << m_oAngularVelocity.toString( );
   sstrDesc << ") Position(" << m_oPosition.toString( );
   sstrDesc << ") ";
   return sstrDesc.str( );
}

/**
 * Apply some force to node
 */
void PhysicsNode::applyForce (const primitives::Vector3D &rkForce) {
   m_oLinearVelocity += rkForce;
}
/**
 * Apply some impulse to node(Angular Velocity)
 */
void PhysicsNode::applyImpulse (const primitives::Vector3D &rkImpulse) {
   m_oAngularVelocity += rkImpulse;	
}
/**
 * 
 */
void PhysicsNode::setPosition (const primitives::Vector3D &rkPosition) {
   m_oPosition = rkPosition;
}


	}; // sceneobjects
}; // powergine
