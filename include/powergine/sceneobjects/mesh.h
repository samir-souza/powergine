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

#ifndef MESH_H
#define MESH_H

#include <string>
#include <vector>
#include <algorithm>
#include <powergine/core.h>
#include <powergine/sceneobjects/frustum.h>
#include <powergine/sceneobjects/sceneentity.h>
#include <powergine/sceneobjects/skeleton.h>
#include <powergine/primitives/material.h>
#include <powergine/primitives/renderprimitive.h>


namespace powergine {
	namespace sceneobjects {

		/**
		 * A mesh is a representation of a physical object built with polygons.
		 * An external file can be loaded and converted to this class.
		 */
		class Mesh : public SceneEntity {

		public:
			Mesh( const std::string &rstrName, primitives::RenderPrimitive *pRenderPrimitive );

		   virtual ~Mesh( );

		   // Returns the mesh name
		   const std::string& getName( ) const;

		   // Adds a submesh to this mesh. A submesh will
		   // be attached to this one and transformed
		   void addSubMesh( Mesh* pSubMesh );

		   // Returns the submesh given its name
		   Mesh* getSubMesh( const std::string &rstrName );

		   // Excludes a submesh given its name
		   Mesh* removeSubMesh( const std::string &rstrName );

		   // Returns the mesh skeleton, if any is available
		   Skeleton* getSkeleton( );

		   // Updates the mesh skeleton
		   void setSkeleton( Skeleton *pSkeleton );

		   // Returns a render primitives corresponding to all polygons of
		   // this mesh
		   primitives::RenderPrimitive* getRenderPrimitive( );

		   // Updates the render primitive of this mesh
		   inline void setRenderPrimitive( primitives::RenderPrimitive* pPrimitive ) {
			   m_pRenderPrimitive = pPrimitive;
		   };

		   // Returns the material applied to this mesh
		   const primitives::Material* const getMaterial( ) const;

		   // Updates the mesh material
		   void setMaterial( primitives::Material *pMaterial );

		   // Executes an update in the mesh
		   void update( float fDeltaTime );

		   // Render the mesh
		   bool render ( Frustum *pFrustum = 0 );

		private:
		  // Fields
		   std::vector<Mesh*> m_vpSubMeshes;
		   std::string m_strName;
		   primitives::RenderPrimitive *m_pRenderPrimitive;
		   Skeleton *m_pSkeleton;

		};
	}; // scenenode
}; // namespace powergine

#endif //MESH_H
