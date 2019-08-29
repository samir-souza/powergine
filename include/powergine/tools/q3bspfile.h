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

#ifndef Q3BSPFILE_H
#define Q3BSPFILE_H

#include <fstream>
#include <iostream>
#include <ios>
#include <string>
#include <sstream>
#include <vector>

#include <powergine/tools/q3bspheader.h>
#include <powergine/tools/q3bsplump.h>
#include <powergine/tools/q3bspvertex.h>
#include <powergine/tools/q3bsptexture.h>
#include <powergine/tools/q3bspface.h>
#include <powergine/tools/q3bsplightmap.h>
#include <powergine/tools/q3bspnode.h>
#include <powergine/tools/q3bspleaf.h>
#include <powergine/tools/q3bspplane.h>
#include <powergine/tools/q3bspvisdata.h>
#include <powergine/tools/q3bspbrush.h>
#include <powergine/tools/q3bspbrushside.h>
#include <powergine/primitives/texture.h>
#include <powergine/primitives/material.h>
#include <powergine/primitives/renderprimitive.h>
#include <powergine/primitives/color.h>
#include <powergine/primitives/triangle.h>
#include <powergine/primitives/vertextexturediffusenormal.h>
#include <powergine/primitives/vertexdiffusenormal.h>
#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/sceneobjects/bsptree.h>
#include <powergine/sceneobjects/bspnode.h>
#include <powergine/sceneobjects/bspvisdata.h>
#include <powergine/sceneobjects/aabb.h>
#include <powergine/services/video/videomanager.h>
#include <powergine/utils/bitset.h>
#include <powergine/utils/buffer.h>


namespace powergine {
   namespace tools {

	/**
	 * This is part of the Quake 3 BSP loader tool
	 * This is the main file of the Q3 BSP tool
	 */
	class Q3BSPFile {

	public:

		// Default constructor. It receives a video manager and the .bsp filename
	   Q3BSPFile( services::video::VideoManager *pVideoManager, const std::string &rkstrFileName, bool bDebug = false );

	   // Return a parsed BSPTree
	   sceneobjects::BSPTree* getBSPTree( );

	   virtual ~Q3BSPFile( );

	private:

	   bool m_bDebug;
	   std::ifstream *m_pfleData;
	   unsigned int m_uiNumVertices;
	   unsigned int m_uiNumFaces;
	   unsigned int m_uiNumTexturesInfo;
	   unsigned int m_uiNumLightMaps;
	   unsigned int m_uiNumNodes;
	   unsigned int m_uiNumLeafs;
	   unsigned int m_uiNumLeafFaces;
	   unsigned int m_uiNumPlanes;
	   unsigned int m_uiNumMeshVertices;
	   unsigned int m_uiNumLeafBrushes;
	   unsigned int m_uiNumBrushes;
	   unsigned int m_uiNumBrushSides;

	   std::vector<Q3BSPVertex*> m_vecVertices;
	   std::vector<Q3BSPFace*> m_vecFaces;
	   std::vector<Q3BSPTexture*> m_vecTexturesInfo;
	   std::vector<Q3BSPLightMap*> m_vecLightMapsInfo;
	   std::vector<Q3BSPNode*> m_vecNodes;
	   std::vector<Q3BSPLeaf*> m_vecLeafs;
	   std::vector<Q3BSPPlane*> m_vecPlanes;
	   std::vector<Q3BSPBrush*> m_vecBrushes;
	   std::vector<Q3BSPBrushSide*> m_vecBrushSides;
	   std::vector<utils::BitSet*> m_vecBitSet;
	   int *m_piLeafFaces;
	   int *m_piMeshVerticesIndex;
	   int *m_piLeafBrushes;

	   services::video::VideoManager *m_pVideoManager;
	   std::vector<primitives::Texture*> m_vecTextures;
	   std::vector<primitives::Texture*> m_vecLightMaps;
	   Q3BSPVisData m_oVisData;

	   void loadVertices( int iOffset );
	   void loadFaces( int iOffset );
	   void loadTextures( int iOffset );
	   void loadLightMaps( int iOffset );
	   void loadNodes( int iOffset );
	   void loadLeafs( int iOffset );
	   void loadPlanes( int iOffset );
	   void loadBrushes( int iOffset );
	   void loadBrushSides( int iOffset );
	   void loadVisData( const Q3BSPLump &rkLump );

	   void loadNativeBSPTree( int iNodeIndex, sceneobjects::BSPNode *pNode );
	   void loadNativeBSPTreeLumps( int iLeafIndex, sceneobjects::BSPNode *pNode );

	   void changeGamma( char *pcImage, int iSize, float fFactor );

	   primitives::VertexFormat m_oFormat;

	   /**
	    * Customized Vertex texture helper class
	    * The customization was necessary to support specific requirements of
	    * the BSP loader
	    */
	   class VertexTextureDiffuseNormalTexture : public primitives::VertexTextureDiffuseNormal {
		  public:

			 inline void setTextureCoords2( const primitives::TextCoords &rkTextCoords ) {
				m_oTextCoords2 = rkTextCoords;
			 } // setTextureCoords2

			 inline void setAll(
				const primitives::Vector3D &rkPosition,
				const primitives::TextCoords &rkTextCoords,
				const primitives::Color &rkDiffuseColor,
				const primitives::Vector3D &rkNormal,
				const primitives::TextCoords &rkTextCoords2 ) {
				VertexTextureDiffuseNormal::setAll(
				   rkPosition,
				   rkTextCoords,
				   rkDiffuseColor,
				   rkNormal
				);
				setTextureCoords2( rkTextCoords2 );
			 } // setAll

		  private:
			 // customize vertex format for multitexture
			 primitives::TextCoords m_oTextCoords2;
	   };

	};

   }; // tools
}; // powergine

#endif //Q3BSPFILE_H
