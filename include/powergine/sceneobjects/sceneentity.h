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


#ifndef SCENEENTITY_H
#define SCENEENTITY_H

#include <powergine/sceneobjects/frustum.h>
#include <powergine/sceneobjects/renderentity.h>
#include <powergine/sceneobjects/sceneentity.h>
#include <powergine/sceneobjects/scenenode.h>
#include <powergine/sceneobjects/boundingvolume.h>
#include <powergine/primitives/ray.h>
#include <powergine/utils/contactset.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A scene entity is an implementation of the render entity
		 * which contains information about the body that must be rendered
		 */
		class SceneEntity : public RenderEntity {

		public:
		   SceneEntity( SceneNode *pParentSceneNode = 0 );

		   virtual ~SceneEntity( );

		   // Returns the scene node which has attached this one
		   SceneNode* getParentSceneNode( );

		   // Updates the parent scene node
		   void setParentSceneNode( SceneNode* pkParentSceneNode );

		   // Returns the node's bounding box
		   BoundingVolume* getBoundingVolume( );

		   // Updates the node' s bounding box
		   void setBoundingVolume( BoundingVolume* pkBoundingVolume );

		   // Creates a clone of this node
		   virtual SceneEntity* clone ( );

		   // Updates the state of the node
		   virtual void update( float fDeltaTime );

		   // Checks if this entity has collided with a ray
		   virtual bool collide ( const primitives::Ray &rkRay, utils::ContactSet *pContactSet );

		   // Render this node
		   virtual bool render ( Frustum *pFrustum = 0 );

		private:

		   SceneNode *m_pParentSceneNode;

		   BoundingVolume *m_pBoundingVolume;
		};

	}; // sceneobjects
}; // namespace powergine

#endif //SCENEENTITY_H
