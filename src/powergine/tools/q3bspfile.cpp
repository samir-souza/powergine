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


#include <powergine/tools/q3bspfile.h>

namespace powergine {
   namespace tools {
   
Q3BSPFile::Q3BSPFile( services::video::VideoManager *pVideoManager, const std::string &rkstrFileName, bool bDebug ) :
   m_bDebug( bDebug ),
   m_pfleData( 0 ),
   m_uiNumFaces( 0 ),
   m_uiNumLeafFaces( 0 ),
   m_uiNumLeafs( 0 ),
   m_uiNumLightMaps( 0 ),
   m_uiNumNodes( 0 ),
   m_uiNumPlanes( 0 ),
   m_uiNumTexturesInfo( 0 ),
   m_uiNumVertices( 0 ),
   m_uiNumMeshVertices( 0 ),
   m_uiNumLeafBrushes( 0 ),
   m_uiNumBrushes( 0 ),
   m_uiNumBrushSides( 0 ),
   m_piLeafFaces( 0 ),
   m_piMeshVerticesIndex( 0 ),      
   m_piLeafBrushes( 0 ),
   m_pVideoManager( pVideoManager )
   
{     
   
   if ( m_bDebug ) {
      std::cout << rkstrFileName << std::endl;
   } // if
   m_pfleData = new std::ifstream( rkstrFileName.c_str( ), std::ios_base::binary );
   
   if ( !m_pfleData->is_open( ) ) {
      std::string strErrorMsg( "Cant open file: " );
      strErrorMsg += rkstrFileName;
      throw( strErrorMsg );
   } // if    
   
   primitives::VertexElement *pElements = 
      primitives::VertexTextureDiffuseNormal::s_oFormat.getElements( );
   int iNumElements = 
      primitives::VertexTextureDiffuseNormal::s_oFormat.getNumElements( );
   // setup the custom vertex format
   for ( int iI = 0; iI < iNumElements; iI++ ) {
      m_oFormat.addElement( pElements + iI );
   } // for
   m_oFormat.addElement(
      new primitives::VertexElement(
         primitives::VertexElement::ELEMENT_TEXCOORD,
         primitives::VertexElement::DATA_FLOAT2,
         12 * sizeof( float )
      )
   );
   
      
   Q3BSPHeader oHeader;
   Q3BSPLump oLumps[ Q3BSPLump::TYPE_MAX ];
   char *pHandler = 0;
   
   pHandler = reinterpret_cast<char*>( &oHeader );
   m_pfleData->read( pHandler, sizeof( oHeader ) );
   pHandler = reinterpret_cast<char*>( &oLumps );
   m_pfleData->read( pHandler, sizeof( oLumps ) );

   if ( m_bDebug ) {
      std::cout << " Header Magic: " << oHeader.szMagic;
      std::cout << " Header Version: " << oHeader.uiVersion;      
      std::cout << std::endl;
   } // if
         
   m_uiNumVertices   = oLumps[ Q3BSPLump::TYPE_VERTICES ].iLength / sizeof( Q3BSPVertex );
   loadVertices( oLumps[ Q3BSPLump::TYPE_VERTICES ].iOffset );
      
   m_uiNumFaces      = oLumps[ Q3BSPLump::TYPE_FACES ].iLength / sizeof( Q3BSPFace );
   loadFaces( oLumps[ Q3BSPLump::TYPE_FACES ].iOffset );
   
   m_uiNumTexturesInfo   = oLumps[ Q3BSPLump::TYPE_TEXTURES ].iLength / sizeof( Q3BSPTexture );
   loadTextures( oLumps[ Q3BSPLump::TYPE_TEXTURES ].iOffset );

   m_uiNumLightMaps   = oLumps[ Q3BSPLump::TYPE_LIGHTMAPS ].iLength / sizeof( Q3BSPLightMap );
   loadLightMaps( oLumps[ Q3BSPLump::TYPE_LIGHTMAPS ].iOffset );
   
   m_uiNumNodes   = oLumps[ Q3BSPLump::TYPE_NODES ].iLength / sizeof( Q3BSPNode );
   loadNodes( oLumps[ Q3BSPLump::TYPE_NODES ].iOffset );

   m_uiNumLeafs   = oLumps[ Q3BSPLump::TYPE_LEAFS ].iLength / sizeof( Q3BSPLeaf );
   loadLeafs( oLumps[ Q3BSPLump::TYPE_LEAFS ].iOffset );

   m_uiNumPlanes   = oLumps[ Q3BSPLump::TYPE_PLANES ].iLength / sizeof( Q3BSPPlane );
   loadPlanes( oLumps[ Q3BSPLump::TYPE_PLANES ].iOffset );

   loadVisData( oLumps[ Q3BSPLump::TYPE_VIS_DATA ] );
      
   m_uiNumLeafBrushes = oLumps[ Q3BSPLump::TYPE_LEAF_BRUSHES ].iLength / sizeof( int );
   m_piLeafBrushes = new int[ m_uiNumLeafBrushes ];
   m_pfleData->seekg( oLumps[ Q3BSPLump::TYPE_LEAF_BRUSHES ].iOffset, std::ios::beg );
   
   pHandler = reinterpret_cast<char*>( m_piLeafBrushes );
   m_pfleData->read( pHandler, oLumps[ Q3BSPLump::TYPE_LEAF_BRUSHES ].iLength );
   
   m_uiNumBrushes = oLumps[ Q3BSPLump::TYPE_BRUSHES ].iLength / sizeof( Q3BSPBrush );
   loadBrushes( oLumps[ Q3BSPLump::TYPE_BRUSHES ].iOffset );
   
   m_uiNumBrushSides = oLumps[ Q3BSPLump::TYPE_BRUSH_SIDES ].iLength / sizeof( Q3BSPBrushSide );
   loadBrushSides( oLumps[ Q3BSPLump::TYPE_BRUSH_SIDES ].iOffset );
   
   m_uiNumLeafFaces = oLumps[ Q3BSPLump::TYPE_LEAF_FACES ].iLength / sizeof( int );
   m_piLeafFaces = new int[ m_uiNumLeafFaces ];      
   m_pfleData->seekg( oLumps[ Q3BSPLump::TYPE_LEAF_FACES ].iOffset, std::ios::beg );
   
   pHandler = reinterpret_cast<char*>( m_piLeafFaces );
   m_pfleData->read( pHandler, oLumps[ Q3BSPLump::TYPE_LEAF_FACES ].iLength );
               
   m_uiNumMeshVertices = oLumps[ Q3BSPLump::TYPE_MESH_VERTICES ].iLength / sizeof( int );
   m_piMeshVerticesIndex = new int[ m_uiNumMeshVertices ];   
   m_pfleData->seekg( oLumps[ Q3BSPLump::TYPE_MESH_VERTICES ].iOffset, std::ios::beg );
   
   pHandler = reinterpret_cast<char*>( m_piMeshVerticesIndex );
   m_pfleData->read( pHandler, oLumps[ Q3BSPLump::TYPE_MESH_VERTICES ].iLength );
   
   m_pfleData->close( );      
   
} // Q3BSPFile

Q3BSPFile::~Q3BSPFile( ) {
   delete m_pfleData;
   delete m_piMeshVerticesIndex;
   delete m_piLeafFaces;
   delete m_piLeafBrushes;
} // Q3BSPFile

void Q3BSPFile::loadVertices( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumVertices; ++uiI ) {
      Q3BSPVertex *pVertex = new Q3BSPVertex( );
      char *pHandler = reinterpret_cast<char*>( pVertex );
      m_pfleData->read( pHandler, sizeof( Q3BSPVertex ) );
      
      // Swap the y and z values, and negate the new z so Y is up.
      float fY = pVertex->oPosition.getY( );
      pVertex->oPosition.setY( pVertex->oPosition.getZ( ) );
      pVertex->oPosition.setZ( -fY );
      
      // Negate the V texture coordinate because it is upside down otherwise...
      pVertex->oTextureCoord.setV( pVertex->oTextureCoord.getV( ) * -1.0f );
      m_vecVertices.push_back( pVertex );
   } // for
} // loadVertices

void Q3BSPFile::loadFaces( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumFaces; uiI++ ) {
      Q3BSPFace *pFace = new Q3BSPFace( );
      char *pHandler = reinterpret_cast<char*>( pFace );
      m_pfleData->read( pHandler, sizeof( Q3BSPFace ) );
      m_vecFaces.push_back( pFace );
   } // for
} // loadFaces

void Q3BSPFile::loadTextures( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumTexturesInfo; ++uiI ) {
      Q3BSPTexture *pTexture = new Q3BSPTexture( );
      char *pHandler = reinterpret_cast<char*>( pTexture );
      m_pfleData->read( pHandler, sizeof( Q3BSPTexture ) );
      m_vecTexturesInfo.push_back( pTexture );            
      
      try {
         std::string strTextureName( pTexture->szName );
         std::string strFileName = strTextureName + ".jpg";                     
         m_vecTextures.push_back(
            m_pVideoManager->createTexture( strTextureName, strFileName, primitives::Texture::FILTER_BILINEAR )
         );
      } catch ( std::string &rstrError ) {
         m_vecTextures.push_back( 0 );
         std::cerr << rstrError << std::endl;
         // ignore
      } // catch
      
   } // for
} // loadTextures

void Q3BSPFile::loadLightMaps( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   
   for ( unsigned int uiI = 0; uiI < m_uiNumLightMaps; ++uiI ) {
      Q3BSPLightMap *pLightMap = new Q3BSPLightMap( );
      char *pHandler = reinterpret_cast<char*>( pLightMap );
      m_pfleData->read( pHandler, sizeof( Q3BSPLightMap ) );
      // TODO: Correct Gamma
      m_vecLightMapsInfo.push_back( pLightMap );

      
      try {         
         std::ostringstream ostrTextureName( "LightMap_" );
         ostrTextureName << uiI;
         
         char *pcImageData = &pLightMap->szImageBits[ 0 ];
         changeGamma( pcImageData, 128*128*3, 6.0f );
         primitives::Image *pImage = 
            new services::video::opengl::SDLImage( pcImageData, 128, 128 );

         primitives::Texture *pRealTexture = 
           m_pVideoManager->createTexture( ostrTextureName.str( ), pImage, primitives::Texture::FILTER_BILINEAR );
         m_vecLightMaps.push_back( pRealTexture );
      } catch ( std::string &rstrError ) {
         m_vecLightMaps.push_back( 0 );
         std::cerr << rstrError << std::endl;
         // ignore
      } // catch            
      
   } // for
} // loadLightMaps

void Q3BSPFile::loadNodes( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumNodes; ++uiI ) {
      Q3BSPNode *pNode = new Q3BSPNode( );
      char *pHandler = reinterpret_cast<char*>( pNode );
      m_pfleData->read( pHandler, sizeof( Q3BSPNode ) );
      
      // Swap the y and z values, and negate the new z so Y is up.
      int fY = pNode->oBBMinPos.y;
      pNode->oBBMinPos.y = pNode->oBBMinPos.z;
      pNode->oBBMinPos.z = -fY;
      
      fY = pNode->oBBMaxPos.y;
      pNode->oBBMaxPos.y = pNode->oBBMaxPos.z;
      pNode->oBBMaxPos.z = -fY;
      
      m_vecNodes.push_back( pNode );   
   } // for   
} // loadNodes

void Q3BSPFile::loadLeafs( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumLeafs; ++uiI ) {
      Q3BSPLeaf *pLeaf = new Q3BSPLeaf( );
      char *pHandler = reinterpret_cast<char*>( pLeaf );
      m_pfleData->read( pHandler, sizeof( Q3BSPLeaf ) );
      
      // Swap the y and z values, and negate the new z so Y is up.
      int fY = pLeaf->oBBMinPos.y;
      pLeaf->oBBMinPos.y = pLeaf->oBBMinPos.z;
      pLeaf->oBBMinPos.z = -fY;
      
      fY = pLeaf->oBBMaxPos.y;
      pLeaf->oBBMaxPos.y = pLeaf->oBBMaxPos.z;
      pLeaf->oBBMaxPos.z = -fY;
      
      m_vecLeafs.push_back( pLeaf );
   } // for   
} // loadLeafs

void Q3BSPFile::loadPlanes( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumPlanes; ++uiI ) {
      Q3BSPPlane *pPlane = new Q3BSPPlane( );
      char *pHandler = reinterpret_cast<char*>( pPlane );
      m_pfleData->read( pHandler, sizeof( Q3BSPPlane ) );
      
      float fY = pPlane->oNormal.getY( );
      pPlane->oNormal.setY( pPlane->oNormal.getZ( ) );
      pPlane->oNormal.setZ( -fY );
      
      m_vecPlanes.push_back( pPlane );   
   } // for   
} // loadPlanes

void Q3BSPFile::loadVisData( const Q3BSPLump &rkLump ) {   
   if ( rkLump.iLength > 0 ) {
      // move get cursor to lump offset point
      m_pfleData->seekg( rkLump.iOffset, std::ios::beg );
      // read the total number of clusters
      char *pHandler = reinterpret_cast<char*>( &m_oVisData.iNumClusters );
      m_pfleData->read( pHandler, sizeof( int ) );      
      // read the number of bytes per cluster
      pHandler = reinterpret_cast<char*>( &m_oVisData.iBytesPerCluster );
      m_pfleData->read(  pHandler, sizeof( int ) );      
      // find the amount of data required to store all cluster bitset
      int iBitSetSize = m_oVisData.iNumClusters * m_oVisData.iBytesPerCluster;      
      // allocate memory to pointer
      m_oVisData.pcBitSet = new char[ iBitSetSize ];
      // read bitset data
      m_pfleData->read( m_oVisData.pcBitSet, iBitSetSize );
      char *pCurrentClusterBitset = m_oVisData.pcBitSet;
            
      for ( unsigned int uiI = 0; uiI < m_oVisData.iNumClusters; uiI++ ) {         
         utils::BitSet *pBitSet = 
            new utils::BitSet( pCurrentClusterBitset, m_oVisData.iBytesPerCluster );                  
         m_vecBitSet.push_back( pBitSet );         
         pCurrentClusterBitset += m_oVisData.iBytesPerCluster;
      } // for
   } else {
      m_oVisData.pcBitSet = 0;
   } // else
} // loadVisData

void Q3BSPFile::loadBrushes( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumBrushes; ++uiI ) {
      Q3BSPBrush *pBrush = new Q3BSPBrush( );
      char *pHandler = reinterpret_cast<char*>( pBrush );
      m_pfleData->read( pHandler, sizeof( Q3BSPBrush) );
            
      m_vecBrushes.push_back( pBrush );
   } // for   
} // loadBrushes

void Q3BSPFile::loadBrushSides( int iOffset ) {
   m_pfleData->seekg( iOffset, std::ios::beg );
   for ( unsigned int uiI = 0; uiI < m_uiNumBrushSides; ++uiI ) {
      Q3BSPBrushSide *pBrushSide = new Q3BSPBrushSide( );
      char *pHandler = reinterpret_cast<char*>( pBrushSide );
      m_pfleData->read( pHandler, sizeof( Q3BSPBrushSide ) );
            
      m_vecBrushSides.push_back( pBrushSide );
   } // for   
} // loadBrushes

sceneobjects::BSPTree* Q3BSPFile::getBSPTree( ) {

   sceneobjects::BSPTree *pTree = new sceneobjects::BSPTree( );   
   //pTree->setNumLumps( m_uiNumFaces );
   loadNativeBSPTree( 0, pTree->getRootNode( ) );   
   return pTree;
} // powergine

void Q3BSPFile::loadNativeBSPTree( int iNodeIndex, sceneobjects::BSPNode *pNode ) {
   
   sceneobjects::BSPNode *pNewNode;
   Q3BSPNode *pCurrentNode = m_vecNodes[ iNodeIndex ];
   Q3BSPPlane *pPlane = m_vecPlanes[ pCurrentNode->iPlane ];
   
   pNode->getDivider( ).setDistanceToOrigo( -pPlane->fDistanceFromOrigo );
   pNode->getDivider( ).setNormal( pPlane->oNormal );

   // setup bounding volume for this node
   primitives::Vector3D oOBBDimension( 
      pCurrentNode->oBBMaxPos.x - pCurrentNode->oBBMinPos.x,
      pCurrentNode->oBBMaxPos.y - pCurrentNode->oBBMinPos.y,
      pCurrentNode->oBBMaxPos.z - pCurrentNode->oBBMinPos.z
   );    
   sceneobjects::OBB *pOBB = new sceneobjects::OBB( oOBBDimension );   
   pOBB->doTranslation( 
      primitives::Vector3D( 
         pCurrentNode->oBBMinPos.x, 
         pCurrentNode->oBBMinPos.y, 
         pCurrentNode->oBBMinPos.z 
      ) 
   );            
   pNode->setBoundingVolume( pOBB );          
   

   if ( pCurrentNode->iFront >= 0 ) {
      pNewNode = new sceneobjects::BSPNode( pNode->getParentTree( ), sceneobjects::BSPNode::NODE );        
      pNode->setLeftChild( pNewNode );
      loadNativeBSPTree( pCurrentNode->iFront, pNewNode );
   } else {      
      pNewNode = new sceneobjects::BSPNode( pNode->getParentTree( ), sceneobjects::BSPNode::LEAF );      
      pNode->setLeftChild( pNewNode );
      // the bit op ~ is necessary to find the complement number of the current index      
      loadNativeBSPTreeLumps( ~pCurrentNode->iFront, pNewNode );      
   } // else
   
   if ( pCurrentNode->iBack >= 0 ) {   
      pNewNode = new sceneobjects::BSPNode( pNode->getParentTree( ), sceneobjects::BSPNode::NODE );
      pNode->setRightChild( pNewNode );
      loadNativeBSPTree( pCurrentNode->iBack, pNewNode );
   } else {      
      pNewNode = new sceneobjects::BSPNode( pNode->getParentTree( ), sceneobjects::BSPNode::LEAF );
      pNode->setRightChild( pNewNode );
      // the bit op ~ is necessary to find the complement number of the current index      
      loadNativeBSPTreeLumps( ~pCurrentNode->iBack, pNewNode );     
   } // else
   
} // loadNativeBSPTree

void Q3BSPFile::loadNativeBSPTreeLumps( int iLeafIndex, sceneobjects::BSPNode* pNode ) {
   Q3BSPLeaf *pLeaf = m_vecLeafs[ iLeafIndex ];
   primitives::RenderPrimitive *pLumpRenderData;
   sceneobjects::BSPLump *pLump;
   
   if ( m_bDebug ) {
      std::cout << " iLeafIndex: " << iLeafIndex;
      std::cout << " ivecLeafSize: " << m_vecLeafs.size( );
      std::cout << " pLeaf: " << pLeaf;
      std::cout << " iNumLeafFaces: " << pLeaf->iNumLeafFaces;
      std::cout << " iLeafFaceStartIndex: " << pLeaf->iLeafFaceStartIndex;
      std::cout << std::endl;
   } // if

   // setup PVS for this node
   if ( m_oVisData.pcBitSet && pLeaf->iCluster >= 0 ) {
      pNode->setClusterData( 
         new sceneobjects::BSPVisData( pLeaf->iCluster, m_vecBitSet[ pLeaf->iCluster ] ) 
      );
   } // if
   
   
   // setup bounding volume for this Leaf
   primitives::Vector3D oOBBDimension( 
      pLeaf->oBBMaxPos.x - pLeaf->oBBMinPos.x,
      pLeaf->oBBMaxPos.y - pLeaf->oBBMinPos.y,
      pLeaf->oBBMaxPos.z - pLeaf->oBBMinPos.z
   );    
   sceneobjects::OBB *pOBB = new sceneobjects::OBB( oOBBDimension );   
   pOBB->doTranslation( 
      primitives::Vector3D( 
         pLeaf->oBBMinPos.x, 
         pLeaf->oBBMinPos.y, 
         pLeaf->oBBMinPos.z 
      ) 
   );
   pNode->setBoundingVolume( pOBB ); 
   
   // load leaf brushes
   for ( int iI = 0; iI < pLeaf->iNumLeafBrushes; iI++ ) {
      
      int index = m_piLeafBrushes[ pLeaf->iLeafBrushStartIndex + iI ];
      Q3BSPBrush *pBrush = m_vecBrushes[ index ];
      if ( pBrush->iNumBrushSides > 0 && ( m_vecTexturesInfo[ pBrush->iTextureID ]->iContents & 1 ) ) {
         std::cout << "B("<< iI<<"): " << iLeafIndex << std::endl;
        for( int iJ = 0; iJ < pBrush->iNumBrushSides; iJ++ ) {
            Q3BSPBrushSide *pBrushSide = m_vecBrushSides[ pBrush->iBrushSide + iJ ];
            Q3BSPPlane *pPlane = m_vecPlanes[ pBrushSide->iPlane ];
            primitives::Plane *pPGPlane = new primitives::Plane(
               pPlane->oNormal, pPlane->fDistanceFromOrigo 
            );            
            std::cout << pPGPlane->getNormal( ).toString( ) << std::endl;
        } // for
        std::cout << std::endl << std::endl;
      } // if      
   } // for
   
   for ( unsigned int uiI = 0; uiI < pLeaf->iNumLeafFaces; uiI++ ) {
      
      int iFaceIndex = m_piLeafFaces[ pLeaf->iLeafFaceStartIndex + uiI ];      
      if ( iFaceIndex > m_vecFaces.size( ) ) {
         if ( m_bDebug ) {         
            std::cout << " WARNING >> Face skipped: " << iFaceIndex;
            std::cout << " Max Face: " << ( m_vecFaces.size( ) - 1 );
            std::cout << std::endl;            
         } // if
         continue;
      } // if
      Q3BSPFace *pFace = m_vecFaces[ iFaceIndex ];        

      if ( m_bDebug ) {
         std::cout << " m_uiNumLeafFaces: " << m_uiNumLeafFaces;
         std::cout << " LeafFaceIndex: " << pLeaf->iLeafFaceStartIndex + uiI;
         std::cout << " ivecFacesSize: " << m_vecFaces.size( );
         std::cout << " iFaceIndex: " << iFaceIndex;
         std::cout << " pFace: " << pFace;
         std::cout << std::endl;
      } // if
            
      // ignore these two types of face because there is not a implementation to handle it
      if ( pFace->eType == Q3BSPFace::TYPE_BILLBOARD ) continue;
      if ( pFace->eType == Q3BSPFace::TYPE_PATCH ) continue;      
      
      int iNumPolygons = pFace->iNumMeshVertices / 3;
      int iNumVertices = pFace->iNumVertices;

      if ( m_bDebug ) {
         std::cout << " iNumPolygons: " << iNumPolygons;
         std::cout << " iNumVertices: " << pFace->iNumVertices;
         std::cout << " iNumMeshVertices: " << pFace->iNumMeshVertices;           
         std::cout << std::endl;
      } // if     
      
      utils::Buffer<VertexTextureDiffuseNormalTexture> *pVertexHandler =
         new utils::Buffer<VertexTextureDiffuseNormalTexture>( iNumVertices );

      primitives::TriangleBuffer *pPolygonHandler = 
         new primitives::TriangleBuffer( iNumPolygons );
               
      primitives::VertexBuffer *pVertexBuffer =
         Core::get( )->getVideoManager( )->createVertexBuffer(
            pVertexHandler->getNumElements( ),
            m_oFormat,
            pVertexHandler->getData( )
         );
         
      
      primitives::PolygonBuffer *pPolygonBuffer =
         Core::get( )->getVideoManager( )->createPolygonBuffer(
            pPolygonHandler->getNumElements( ),
            primitives::Triangle::getNumVertices( ),             
            pPolygonHandler->getData( )
         );      
                  
      pLumpRenderData = new primitives::RenderPrimitive(
         primitives::RenderPrimitive::MODE_TRIANGLES,
         primitives::RenderPrimitive::POLYGON_TRIANGLE        
      );      
      pLumpRenderData->setVertexBuffer( pVertexBuffer );
      pLumpRenderData->setPolygonBuffer( pPolygonBuffer );
      
      // set material
      primitives::Material *pMaterial = new primitives::Material( 
         std::string( m_vecTexturesInfo[ pFace->iTextureID ]->szName ),
         primitives::Color::WHITE, 
         primitives::Color::WHITE,
         primitives::Color::WHITE,
         primitives::Color::WHITE, 150.0
      );
      
      
      if ( pFace->iTextureID >= 0 && pFace->iTextureID < m_vecTextures.size( ) ) {
         // add first pass texture
         pMaterial->addTexture( m_vecTextures[ pFace->iTextureID ] );            
      } // if
      if ( pFace->iLightmapID >= 0 && pFace->iLightmapID < m_vecLightMaps.size( ) ) {
         // add second pass texture - lightmap
         pMaterial->addTexture( m_vecLightMaps[ pFace->iLightmapID ] );      
      } // if
         
      utils::Buffer<VertexTextureDiffuseNormalTexture>::iterator *pVIterator = pVertexHandler->makeIterator( );
            
      for ( unsigned int uiJ = 0; uiJ < pFace->iNumVertices; uiJ++ ) {               
         Q3BSPVertex *pVertex = m_vecVertices[ pFace->iVerticeStartIndex + uiJ ];                  
         
         pVIterator->getCurrent( ).setAll( 
            pVertex->oPosition,
            primitives::TextCoords( pVertex->oTextureCoord.getU( ), pVertex->oTextureCoord.getV( ) ),
            primitives::Color( pVertex->color ),
            pVertex->oNormal,
            primitives::TextCoords( pVertex->oLightmapCoord.getU( ), pVertex->oLightmapCoord.getV( ) )
         );         
         pVIterator->goNext( );
      } // for
            
                              
      primitives::TriangleBuffer::iterator *pPIterator = pPolygonHandler->makeIterator( );
      int iMeshVerticesIndex = pFace->iMeshVerticesStartIndex;   
      for ( unsigned int uiK=0; uiK < iNumPolygons; ++uiK ) {
         pPIterator->getCurrent( ).setAll( 
            m_piMeshVerticesIndex[ iMeshVerticesIndex++ ],
            m_piMeshVerticesIndex[ iMeshVerticesIndex++ ],
            m_piMeshVerticesIndex[ iMeshVerticesIndex++ ]
         );
         pPIterator->goNext( );   
      } // for            
      
      pLumpRenderData->setMaterial( pMaterial );
      pLump = new sceneobjects::BSPLump( iFaceIndex, pLumpRenderData, pNode );      
      pNode->addLump( pLump );
      
   } // for
   
} // loadNativeBSPTreeLumps

void Q3BSPFile::changeGamma( char *pcImage, int iSize, float fFactor ) {

// Go through every pixel in the lightmap
   for( int iI = 0; iI < iSize / 3; iI++, pcImage += 3) {
      float fScale = 1.0f, fTemp = 0.0f;
      float fR = 0, fG = 0, fB = 0;
   
      // extract the current RGB values
      fR = (float)pcImage[ 0 ];
      fG = (float)pcImage[ 1 ];
      fB = (float)pcImage[ 2 ];
   
      // Multiply the factor by the RGB values, while keeping it to a 255 ratio
      fR = fR * fFactor / 255.0f;
      fG = fG * fFactor / 255.0f;
      fB = fB * fFactor / 255.0f;
      
      // Check if the the values went past the highest value
      if(fR > 1.0f && (fTemp = (1.0f/fR)) < fScale) fScale=fTemp;
      if(fG > 1.0f && (fTemp = (1.0f/fG)) < fScale) fScale=fTemp;
      if(fB > 1.0f && (fTemp = (1.0f/fB)) < fScale) fScale=fTemp;
   
      // Get the scale for this pixel and multiply it by our pixel values
      fScale *= 255.0f;
      fR*=fScale;
      fG*=fScale;
      fB*=fScale;
   
      // Assign the new gamma'nized RGB values to our image
      pcImage[ 0 ] = (char)fR;
      pcImage[ 1 ] = (char)fG;
      pcImage[ 2 ] = (char)fB;
   } // for
} // changeGamma


   }; // tools
};




