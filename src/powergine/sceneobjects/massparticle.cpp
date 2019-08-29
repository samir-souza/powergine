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


#include <powergine/sceneobjects/massparticle.h>

namespace powergine {
	namespace sceneobjects {
	
// Constructors/Destructors
// Methods
MassParticle::MassParticle( ) :
   m_fMass( 0.0f ),
   m_fInverseMass( 0.0f ),
   m_oAppliedForces( primitives::Vector3D::ORIGO ),
   m_bLocked( false )
{  
}

float MassParticle::getMass( ) const {
   return m_fMass;
}

void MassParticle::setMass( float fMass ) {
   m_fMass = fMass;
   m_fInverseMass = ( fMass > 0.0f ) ? ( 1.0f / fMass ) : 0.0f;
}

float MassParticle::getInverseMass( ) const {
   return m_fInverseMass;
}

primitives::Vector3D& MassParticle::getAppliedForces( ) {
   return m_oAppliedForces;
}

void MassParticle::setAppliedForces( const primitives::Vector3D &rkForces ) {
	m_oAppliedForces = rkForces;
}

void MassParticle::setLocked( bool bLocked ) {
   m_bLocked = bLocked;
}

bool MassParticle::isLocked( ) const {
   return m_bLocked;
}

void MassParticle::update( float fDeltaTime ) {
   // calculate acceleration
   primitives::Vector3D oAcceleration = getAppliedForces( ) / getMass( );
   
   // update velocity
   applyForce( oAcceleration * fDeltaTime );
   
   // update position
   setPosition( getPosition( ) + ( getLinearVelocity( ) * fDeltaTime ) );
}

	}; // sceneobjects
}; // powergine
