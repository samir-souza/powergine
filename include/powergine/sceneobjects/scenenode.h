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


#ifndef SCENENODE_H
#define SCENENODE_H

#include <iostream>
#include <string>
#include <vector>

#include <powergine/sceneobjects/srtnode.h>
#include <powergine/sceneobjects/renderentity.h>
#include <powergine/sceneobjects/frustum.h>
#include <powergine/utils/entityvisitor.h>

namespace powergine {
	namespace sceneobjects {

		class Room;

		/**
		 * A Scene node is a basic node of the scene graph
		 * A Scene entity can be attached to a SceneNode to be rendered
		 * by the render manager. All the trasformations applied to this node
		 * will be propagated to its attached elements and to its children
		 */
		class SceneNode : public SRTNode {

		public:
		   SceneNode( const std::string &rkstrName = "" );

		   void setRenderEntity( RenderEntity *pRenderEntity );

		   RenderEntity* getRenderEntity( );

		   virtual ~SceneNode( );

		   // Updates the node's name
		   virtual void setName( const std::string &rstrName );

		   // Returns the node's name
		   virtual const std::string &getName( );

		   // Returns the room which holds this node
		   virtual Room* getRoom( );

		   // Updates the room which holds this node
		   virtual void setRoom( Room *pRoom );

		   // Return a pointer to the parent scene node, if any exists
		   virtual SceneNode *getParentNode( );

		   // Updates the parent scene node
		   virtual void setParentNode( SceneNode* pParentNode );

		   // Adds a new child scene node
		   virtual bool addChildNode( SceneNode* pChildNode );

		   // Removes a child sene node
		   virtual bool removeChildNode( SceneNode* pChildNode );

		   // Detach this node from the parent
		   virtual bool removeFromParent( );

		   // Returns a list wich the pointers of all child nodes
		   virtual const std::vector<SceneNode*>& getChildrenNodes( );

		   // RTTI mechanism which accepts a visitor design pattern
		   virtual void accept( const utils::EntityVisitor &rkEntityVisitor );

		   // Return the global world scaling factor
		   virtual float getWorldScaling( );

		   // Returns the global world translation
		   virtual primitives::Vector3D& getWorldTranslation( );

		   // Returns the global world rotation
		   virtual primitives::Quaternion& getWorldRotation( );

		   // Applies a world translation to this node
		   virtual void doWorldTranslation( const primitives::Vector3D &rkTranslation );

		   // Applies a world rotation to this node
		   virtual void doWorldRotation( const primitives::Quaternion &rkRotation );

		   // Applies a scaling to this node
		   virtual void doScaling( float fScaling );

		   // Applies a translation to this node
		   virtual void doTranslation( const primitives::Vector3D &rkTranslation );

		   // Applies a rotation to this node
		   virtual void doRotation( const primitives::Quaternion &rkRotation );

		   // Using a lazy evaluation approach, this method checks if
		   // any update is needed and executes it
		   virtual bool updateTransformation( );

		   // Updates the node
		   virtual void update( float fDeltaTime );

		   // Returns the node's transformation matrix
		   virtual primitives::Matrix4x4* getTransformation( );

		   // Returns the node's inverted transformation matrix
		   virtual primitives::Matrix4x4* getInverseTransformation( );

		   // Render this node
		   bool render ( Frustum *pFrustum = 0 );

		protected:
		   Room* m_pRoom;

		private:
		   bool m_bNeedUpdateTransformation;
		   std::vector<SceneNode*> m_vpChildrenNodes;
		   SceneNode *m_pParentNode;
		   RenderEntity *m_pRenderEntity;

		   std::string m_strName;
		   float m_fWorldScaling; // cached
		   primitives::Quaternion m_oWorldRotation; // cached
		   primitives::Vector3D m_oWorldTranslation; // cached

		   // cached node transformation
		   primitives::Matrix4x4 m_oTransformation;
		   primitives::Matrix4x4 m_oInverseTransformation;

		};

	}; // scenenode
}; // namespace powergine

#endif //SCENENODE_H
