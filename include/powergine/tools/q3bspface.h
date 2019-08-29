// Copyright (c) 2004 Samir Araujo <samir.araujo@gmail.com>
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

#ifndef Q3BSPFACE_H
#define Q3BSPFACE_H

#include <powergine/primitives/vector3d.h>

namespace powergine {
   namespace tools {

	/**
	 * This is part of the Quake 3 BSP loader tool
	 * It represents an object face
	 */
	class Q3BSPFace {

	public:

	   enum TYPE {
		  TYPE_POLYGON      = 1,
		  TYPE_PATCH        = 2,
		  TYPE_MESH         = 3,
		  TYPE_BILLBOARD    = 4
	   };

	   int iTextureID;    // The index into the texture array
	   int iEffect;     // The index for the effects (or -1 = n/a)
	   TYPE eType;     // 1=polygon, 2=patch, 3=mesh, 4=billboard
	   int iVerticeStartIndex;   // The starting index into this face's first vertex
	   int iNumVertices;    // The number of vertices for this face
	   int iMeshVerticesStartIndex;   // The index into the first meshvertex
	   int iNumMeshVertices;   // The number of mesh vertices
	   int iLightmapID;    // The texture index for the lightmap
	   int iLightMapCorner[ 2 ];   // The face's lightmap corner in the image
	   int iLightMapSize[ 2 ];   // The size of the lightmap section
	   primitives::Vector3D oLightMapPos;   // The 3D origin of lightmap.
	   primitives::Vector3D oLightMapVecs[ 2 ];  // The 3D space for s and t unit vectors.
	   primitives::Vector3D oNormal;   // The face normal.
	   int iSize[ 2 ];    // The bezier patch dimensions.
	};

   }; // tools
}; // powergine

#endif //Q3BSPFACE_H
