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

#ifndef RIGIDBODY_H
#define RIGIDBODY_H

#include <powergine/sceneobjects/massparticle.h>
#include <powergine/primitives/matrix3x3.h>
#include <powergine/primitives/vector3d.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A rigid body is the physical component of a body which lies
		 * inside the virtual world. It has a shape and is used to control
		 * the displacement of a given body
		 */
		class RigidBody : public MassParticle {

		public:
		   RigidBody( );

		   virtual ~RigidBody( );

		   // Updates the state of Body
		   void  update( float fDeltaTime );

		private:
		   // Mass moment of inertia in body coords
		   primitives::Matrix3x3 m_oBodyMassMomentInertia;

		   // Inverse mass moment of inertia in body coords
		   primitives::Matrix3x3 m_oBodyInverseMassMomentInertia;

		   // Inverse mass moment of inertia in earth coords
		   primitives::Matrix3x3 m_oInverseMomentInertia;

		   // Magnitude of the velocity
		   float m_fSpeed;

		   // Orientation in earth coords
		   primitives::Quaternion m_oOrientation;

		   // Velocity in body coords to calculate drag forces
		   primitives::Vector3D m_oBodyVelocity;

		   // Total moment on body
		   primitives::Vector3D m_oTorque;

		   // Angular acceleration in body coords
		   primitives::Vector3D m_oBodyAngularAcceleration;

		   // Acceleration of Gravity Center of the body in earth coords
		   primitives::Vector3D m_oAcceleration;
		};

	}; // sceneobjects
}; // powergine

#endif //RIGIDBODY_H
