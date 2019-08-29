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

#ifndef CAMERA_H
#define CAMERA_H

#include <string>
#include <powergine/core.h>
#include <powergine/sceneobjects/room.h>
#include <powergine/sceneobjects/frustum.h>
#include <powergine/sceneobjects/scenenode.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/matrix4x4.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A Camera is an customized area. That area can be translated into
		 * the environment. Every object that lies inside that area will be
		 * considered visible and will be evaluated during the rendering
		 * process
		 * More than one camera can exists inside the environment, but depending
		 * on the viewport (it can be split to render two or more cameras),
		 * only one can be active at a time
		 */
		class Camera : public SceneNode {

		public:

		   Camera( std::string strName = "" );

		   inline virtual ~Camera( ) { delete m_pRoom; }

		   // Points the camera out ot a given position
		   void lookAt( const primitives::Vector3D &rkViewingDirection, const primitives::Vector3D &rkUpDirection );

		   // Returns the current active camera
		   static Camera* getActive( );

		   // Activate this camera
		   void setActive( );

		   // Updates this camera
		   virtual void update( float fDeltaTime );

		   // Renders the content of this camera
		   bool render( Frustum *pFrustum = 0 );

		   // Returns the specific transformation of this camera
		   // Translations, rotations and scalings
		   virtual primitives::Matrix4x4* getTransformation( );

		private:
		   static Camera *s_pCurrentActiveCamera;
		};

	}; // scenenode
}; // namespace powergine

#endif //CAMERA_H
