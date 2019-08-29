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

#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <vector>
#include <powergine/sceneobjects/scenenode.h>
#include <powergine/sceneobjects/frustum.h>


namespace powergine {
	namespace sceneobjects {

		/**
		 * A room is a container which can hold one or more elements
		 * It is useful to classify, organize and render elements
		 * A room organizes its content in a tree
		 */
		class Room : public SceneNode {
		// Public stuff
		public:

		   Room( const std::string &rstrName="" );

		   virtual ~Room( );

		   // Register a new global child node. A global child
		   // will be present in any part of the room
		   bool addGlobalChildNode( SceneNode *pGlobalChildNode );

		   // Removes a registered global child node
		   bool removeGlobalChildNode( SceneNode *pGlobalChildNode );

		   // Registers a new child node. A child node considered
		   // not visible or outside the room can be removed from
		   // the rendering pipeline
		   bool addChildNode( SceneNode *pChildNode );

		   // Removes a registered child node
		   bool removeChildNode( SceneNode *pChildNode );

		   // Renders the room
		   bool render( Frustum *pFrustum );

		   // Update all the room elements
		   void update( float fDeltaTime );

		private:
		  // Fields
		  // Nodes that must be rendered
		   std::vector<SceneNode*> m_vpGlobalChildren;

		};

	}; // scenenode
}; // namespace powergine

#endif //ROOM_H
