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

#ifndef BSPLUMP_H
#define BSPLUMP_H

#include <powergine/sceneobjects/sceneentity.h>
#include <powergine/sceneobjects/frustum.h>
#include <powergine/primitives/color.h>
#include <powergine/primitives/renderprimitive.h>
#include <powergine/core.h>

namespace powergine {
	namespace sceneobjects {

		class BSPNode;

		/**
		 * A BSP Lump is part of the BSP (Binary Spatial Partition) tree toolkit
		 * it is a renderable object which has a body inside the scene
		 */
		class BSPLump : public SceneEntity {

		public:

		   BSPLump( unsigned int uiID, primitives::RenderPrimitive *pRenderData, BSPNode *pParentNode );

		   virtual ~BSPLump( );

		   // Returns the pointer of the SceneNode which is parent of this
		   // Lump
		   BSPNode* getParentNode( );

		   // Returns the lump id
		   unsigned int getID( );

		   // Render method
		   bool render( Frustum *pFrustum = 0 );

		private:
		   unsigned int m_uiID;
		   primitives::RenderPrimitive *m_pRenderData;
		   BSPNode *m_pParentNode;

		};

	}; // sceneobjects
}; // powergine

#include <powergine/sceneobjects/bspnode.h>

#endif //BSPLUMP_H
