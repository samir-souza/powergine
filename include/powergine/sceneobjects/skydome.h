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

#ifndef SKYDOME_H
#define SKYDOME_H

#include <cmath>
#include <iostream>
#include <powergine/primitives/color.h>
#include <powergine/primitives/material.h>
#include <powergine/primitives/matrix4x4.h>
#include <powergine/primitives/triangle.h>
#include <powergine/primitives/vertextexture.h>
#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/primitives/renderprimitive.h>
#include <powergine/sceneobjects/sceneentity.h>
#include <powergine/sceneobjects/frustum.h>
#include <powergine/utils/mathhelper.h>
#include <powergine/core.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A Sky dome is a huge sphere that surrounds the whole world and gives
		 * the impression a sky exists in that world
		 */
		class SkyDome : public SceneEntity {

		public:
		   // High Resolution = better look but slow down performance and vice-versa
		   SkyDome( primitives::Material *pMaterial,  int iRadius = 150 );

		   virtual ~SkyDome( );

		   // Updates the state of the sky dome
		   void update( float fDeltaTime );

		   // Renders the sky dome
		   virtual bool render( Frustum *pFrustum = 0 );

		private:
		   // Fields
		   primitives::RenderPrimitive *m_pRenderPrimitive;
		   primitives::Matrix4x4 *m_pModelView;
		   void buildTextCoords( const primitives::Vector3D &rkVertice, float &rfU, float &rfV );
		   void buildDome( int iRadius, primitives::Material *pMaterial );

		};

	}; // scenenode
}; // namespace powergine

#endif //SKYDOME_H
