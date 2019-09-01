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


#include <powergine/tools/objfile.h> 
 
namespace powergine {
   namespace tools {

OBJFile::OBJFile( const std::string &rkFileName, bool bDebug ) :
   m_pMesh( 0 ),
   m_pMaterialLib( 0 )
{
   m_bDebug = bDebug;
   if ( m_bDebug ) {
      std::cout << rkFileName << std::endl;
   } // if
   m_pfleData = new std::ifstream( rkFileName.c_str( ) );
   
   if ( !m_pfleData->is_open( ) ) {
      std::string strErrorMsg( "Cant open file: " );
      strErrorMsg += rkFileName;
      throw( strErrorMsg );
   } // if
   
   char szBuffer[ 1024 ];
   std::string strCurrentMaterial = "";   
   std::vector<std::string> vecMaterials;
   
   while( !m_pfleData->eof( ) ) {
      m_pfleData->getline( szBuffer, 1024 );
      std::istringstream streamData( &szBuffer[ 0 ] );
      std::string strCommand;
      streamData >> strCommand;
      
      if ( strCommand == "mtllib" ) {         
         std::string strMtlLibFileName = "";
         streamData >> strMtlLibFileName;         
         m_pMaterialLib = new OBJMtlLib( strMtlLibFileName, bDebug );         
      } else if ( strCommand == "usemtl" ) {
         streamData >> strCurrentMaterial;
         vecMaterials.push_back( strCurrentMaterial );
      } else if ( strCommand == "usemat" ) {
         std::string strTexture = "";
         streamData >> strTexture;
         m_mapTextures[ strCurrentMaterial ] = strTexture;
      } else if ( strCommand == "#" ) {
         // ignore comments
      } else if ( strCommand == "v" ) {
         float fX, fY, fZ;
         
         fX = fY = fZ = 0.0f;
         streamData >> fX >> fY >> fZ;
         primitives::Vector3D *pVertice = new primitives::Vector3D( fX, fY, fZ );
         if ( m_bDebug ) {
            std::cout << "v: " << pVertice->toString( ) << std::endl;
         } // if
         m_vecVertices.push_back( pVertice );
      } else if ( strCommand == "vt" ) {
         float fU, fV;
         
         fU = fV = 0;         
         streamData >> fU >> fV;
         primitives::TextCoords *pTextCoords = new primitives::TextCoords( fU, fV );
         if ( m_bDebug ) {
            std::cout << "vt: U) " << pTextCoords->getU( ) << " V) " << pTextCoords->getV( ) << std::endl;
         } // if
         m_vecTextCoords.push_back( pTextCoords );
      
      } else if ( strCommand == "vn" ) {
         float fX, fY, fZ;
         
         fX = fY = fZ = 0;

         streamData >> fX >> fY >> fZ;
         primitives::Vector3D *pNormal = new primitives::Vector3D( fX, fY, fZ );
         if ( m_bDebug ) {
            std::cout << "vn: " << pNormal->toString( ) << std::endl;                  
         } // if
         m_vecNormals.push_back( pNormal );
      } else if ( strCommand == "f" ) {
         int iV1, iV2, iV3;
         int iN1, iN2, iN3;
         int iT1, iT2, iT3;
         iV1 = iV2 = iV3 = iN1 = iN2 = iN3 = iT1 = iT2 = iT3 = 0;
         
         OBJFace *pFace;
         // skip white space
         streamData.get( );
         
         
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iV1; streamData.get( ); // skip slash
            iV1--;
         } // if
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iT1; streamData.get( ); // skip slash
            iT1--;
         } // if
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iN1; streamData.get( ); // skip space
            iN1--;
         } // if

         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iV2; streamData.get( ); // skip slash               
            iV2--;
         } // if
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iT2; streamData.get( ); // skip slash
            iT2--;
         } // if
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iN2; streamData.get( ); // skip space
            iN2--;
         } // if
         
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iV3; streamData.get( ); // skip slash               
            iV3--;
         } // if
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iT3; streamData.get( ); // skip slash
            iT3--;
         } // if
         if ( isdigit( streamData.get( ) ) != 0 ) {
            streamData.unget( ); streamData >> iN3; streamData.get( ); // skip space
            iN3--;
         } // if
         if ( m_bDebug ) {            
            std::cout << "V1: " << iV1<< " T1: " << iT1<< " N1: " << iN1;           
            std::cout << "V2: " << iV2<< " T2: " << iT2<< " N2: " << iN2;
            std::cout << "V3: " << iV3<< " T3: " << iT3<< " N3: " << iN3 << std::endl;
         } // if
         
         pFace = new OBJFace( );
         pFace->v1 = iV1;
         pFace->v2 = iV2;
         pFace->v3 = iV3;
                     
         pFace->t1 = iT1;
         pFace->t2 = iT2;
         pFace->t3 = iT3;
         
         pFace->n1 = iN1;            
         pFace->n2 = iN2;
         pFace->n3 = iN3;
         
         m_mapFaces[ strCurrentMaterial ].push_back( pFace );
      } // else if
      
   } // while

   std::vector<std::string>::iterator ppBegin = vecMaterials.begin( );
   std::vector<std::string>::iterator ppEnd = vecMaterials.end( );   
   
   while ( ppBegin != ppEnd ) {      
      int iNumPolygons = m_mapFaces[ *ppBegin ].size( );
      int iNumVertices = iNumPolygons * 3;

      primitives::VertexTextureNormalBuffer *pVertexHandler = 
         new primitives::VertexTextureNormalBuffer( iNumVertices );
      
      primitives::TriangleBuffer *pPolygonHandler =
         new primitives::TriangleBuffer( iNumPolygons );
               
      primitives::VertexBuffer *pVertexBuffer = 
         Core::get( )->getVideoManager( )->createVertexBuffer(
            pVertexHandler->getNumElements( ),
            primitives::VertexTextureNormal::s_oFormat, 
            pVertexHandler->getData( )
         );      
         
      primitives::PolygonBuffer *pPolygonBuffer = 
         Core::get( )->getVideoManager( )->createPolygonBuffer(
            pPolygonHandler->getNumElements( ),
            primitives::Triangle::getNumVertices( ), 
            pPolygonHandler->getData( )
         );      
            
      primitives::RenderPrimitive *pRenderMesh = new primitives::RenderPrimitive(
         primitives::RenderPrimitive::MODE_TRIANGLES,
         primitives::RenderPrimitive::POLYGON_TRIANGLE
      );               
      
      pRenderMesh->setVertexBuffer( pVertexBuffer );
      pRenderMesh->setPolygonBuffer( pPolygonBuffer );
      
      primitives::VertexTextureNormalBuffer::iterator *pVIterator = pVertexHandler->makeIterator( );
      primitives::TriangleBuffer::iterator *pPIterator = pPolygonHandler->makeIterator( );
      
      int iVertexCounter = 0;      
      for ( unsigned int uiJ = 0 ; uiJ < iNumPolygons; uiJ++ ) {
         OBJFace *pFace = ( m_mapFaces[ *ppBegin ] )[ uiJ ];
         
         pVIterator->getCurrent( ).setAll( 
            *m_vecVertices[ pFace->v1 ], 
            *m_vecTextCoords[ pFace->t1 ], 
            *m_vecNormals[ pFace->n1 ] 
         );
         pVIterator->goNext( );
         pVIterator->getCurrent( ).setAll( 
            *m_vecVertices[ pFace->v2 ], 
            *m_vecTextCoords[ pFace->t2 ], 
            *m_vecNormals[ pFace->n2 ] 
         );
         pVIterator->goNext( );
         pVIterator->getCurrent( ).setAll( 
            *m_vecVertices[ pFace->v3 ], 
            *m_vecTextCoords[ pFace->t3 ], 
            *m_vecNormals[ pFace->n3 ] 
         );
         pVIterator->goNext( );
                           
         pPIterator->getCurrent( ).setAll( iVertexCounter, iVertexCounter+1, iVertexCounter+2 );
         pPIterator->goNext( );
         iVertexCounter += 3;
      } // for
      
      // setup material      
      if ( m_pMaterialLib ) {
         primitives::Material *pMaterial = m_pMaterialLib->getMaterial( *ppBegin );
         if ( pMaterial ) {
            
            if ( m_mapTextures[ *ppBegin ].length( ) > 0 ) {
               pMaterial->addTexture( 
                  Core::get( )->getVideoManager( )->createTexture(
                     m_mapTextures[ *ppBegin ],
                     m_mapTextures[ *ppBegin ],
                     primitives::Texture::FILTER_TRILINEAR
                  )
               );
            } // if
            pRenderMesh->setMaterial( pMaterial );
         } // if
      } // if
      
      if ( !m_pMesh ) {
         m_pMesh = new sceneobjects::Mesh( *ppBegin, pRenderMesh );
      } else {
         m_pMesh->addSubMesh( new sceneobjects::Mesh( *ppBegin, pRenderMesh ) );
      } // else
      
      ++ppBegin;
   } // while
                        
   m_pfleData->close( );   
}

OBJFile::~OBJFile( ) {
   if ( m_pfleData ) {
      delete m_pfleData;
   } // if
}
   
std::vector<primitives::Vector3D*>& OBJFile::getVertices( ) {
   return m_vecVertices;
}

std::map<std::string, std::vector<OBJFace*> >& OBJFile::getFaces( ) {
   return m_mapFaces;
}

std::vector<primitives::TextCoords*>& OBJFile::getTexturesCoords( ) {
   return m_vecTextCoords;
}

std::vector<primitives::Vector3D*>& OBJFile::getNormals( ) {
   return m_vecNormals;
}

sceneobjects::Mesh* OBJFile::getMesh( ) {
   return m_pMesh;
} // getMesh

   }; // tools
}; // powergine
