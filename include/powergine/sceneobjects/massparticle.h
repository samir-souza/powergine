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

#ifndef MASSPARTICLE_H
#define MASSPARTICLE_H

#include <string>

#include <powergine/sceneobjects/physicsnode.h>
#include <powergine/primitives/vector3d.h>


namespace powergine {
	namespace sceneobjects {

		/**
		 * A mass particle is a body with a given mass. It
		 * is also used by the Physics manager to controls
		 * the objects bodies.
		 */
		class MassParticle : public PhysicsNode {

		public:
		   MassParticle( );

		   virtual ~MassParticle( ) { };

		   // Returns the body mass
		   float getMass( ) const;

		   // Updates the body mass
		   void setMass( float fMass );

		   // Returns the inversed mass 1/mass
		   float getInverseMass( ) const;

		   // Returns the applied forces to this body mass
		   primitives::Vector3D& getAppliedForces( );

		   // Updates the applied forces to this body
		   void setAppliedForces( const primitives::Vector3D &rkForces );

		   // Updates the locked status. When true, the particle
		   // remains unaffected by any kind of external force
		   void setLocked( bool bLocked );

		   // Checks if the particle is locked or not
		   bool isLocked( ) const;

		   // Updates the mass particle
		   virtual void update( float fDeltaTime );

		private:
		   float m_fMass;
		   float m_fInverseMass;
		   // Sum of all forces applied to this particle
		   primitives::Vector3D m_oAppliedForces;
		   // if locked, do not ignore applied forces
		   bool m_bLocked;
		  // Operations
		};

	}; // sceneobjects
}; // powergine

#endif //MASSPARTICLE_H
