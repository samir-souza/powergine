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

#ifndef Q3BSPLUMP_H
#define Q3BSPLUMP_H

namespace powergine {
   namespace tools {

	/**
	 * This is part of the Quake 3 BSP loader tool
	 * It represents a lump. A Lump can be any element
	 * attached to the tree. Check the possibilities bellow.
	 */
	class Q3BSPLump {

	public:

	enum TYPE {
		TYPE_ENTITIES = 0,    // Stores player/object positions, etc...
		TYPE_TEXTURES,     // Stores texture information
		TYPE_PLANES,        // Stores the splitting planes
		TYPE_NODES,      // Stores the BSP nodes
		TYPE_LEAFS,      // Stores the leafs of the nodes
		TYPE_LEAF_FACES,     // Stores the leaf's indices into the faces
		TYPE_LEAF_BRUSHES,    // Stores the leaf's indices into the brushes
		TYPE_MODELS,     // Stores the info of world models
		TYPE_BRUSHES,     // Stores the brushes info (for collision)
		TYPE_BRUSH_SIDES,    // Stores the brush surfaces info
		TYPE_VERTICES,     // Stores the level vertices
		TYPE_MESH_VERTICES,     // Stores the model vertices offsets
		TYPE_SHADERS,     // Stores the shader files (blending, anims..)
		TYPE_FACES,      // Stores the faces for the level
		TYPE_LIGHTMAPS,     // Stores the lightmaps for the level
		TYPE_LIGHT_VOLUMES,    // Stores extra world lighting information
		TYPE_VIS_DATA,     // Stores PVS and cluster info (visibility)

		TYPE_MAX
	};


	   int iOffset;
	   int iLength;
	};

   }; // tools
}; // powergine

#endif //Q3BSPLUMP_H
