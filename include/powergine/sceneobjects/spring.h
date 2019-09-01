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

#ifndef SPRING_H
#define SPRING_H

#include <string>

#include <powergine/primitives/vector3d.h>
#include <powergine/sceneobjects/massparticle.h>


namespace powergine {
	namespace sceneobjects {

		/**
		 * A spring is a connection between two physical particles that
		 * applies a given force to keep them in a given position.
		 * This class is part of the physics engine and it is processed
		 * by the physics manager
		 */
		class Spring {

		public:

		   Spring( float fTensileConstant, float fDampingFactor );

		   virtual ~Spring( ) { };

		   // Updates the connected particles
		   void setParticles( MassParticle *pLeftParticle, MassParticle *pRightParticle );

		   // Returns a pointer to the left particle
		   MassParticle* getLeftParticle( );

		   // Returns a pointer to the right particle
		   MassParticle* getRightParticle( );


		private:
		   // pointer to particles attached in this spring
		   MassParticle *m_pLeftParticle;
		   MassParticle *m_pRightParticle;
		   // tensile spting constant
		   float m_fTensileConstant;
		   float m_fDampingFactor;
		   // length of this spring in rest state
		   float m_fRestLength;
		};

	}; // sceneobjects
}; // powergine

#endif //SPRING_H
