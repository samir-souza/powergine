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


#include <powergine/tools/objmtllib.h> 
 
namespace powergine {
   namespace tools {

OBJMtlLib::OBJMtlLib( const std::string& rkFileName, bool bDebug ) {
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
   
   char *pcBuffer = new char[ 1024 ];
   
   primitives::Material *pMaterial;
   while( !m_pfleData->eof( ) ) {
      m_pfleData->getline( pcBuffer, 1024 );      
      std::istringstream streamData( pcBuffer );
      std::string strCommand = "";
      streamData >> strCommand;
      
      if ( strCommand == "newmtl" ) {
         // Material Name - new material
         std::string strMaterialName = "";
         streamData >> strMaterialName;
         pMaterial = new primitives::Material( strMaterialName );
         pMaterial->setEmission( primitives::Color::BLACK );
         if ( m_bDebug ) {         
            std::cout << "Name: " << strMaterialName << std::endl;
         } // if
      } else if ( strCommand == "Ka" ) {
         // Ambient Color
         float fR = 0.0f, fG = 0.0f, fB = 0.0f;
         streamData >> fR >> fG >> fB;
         pMaterial->setAmbient( primitives::Color( fR, fG, fB, 1.0 ) );
         if ( m_bDebug ) {         
            std::cout << "Ambient Color: " << pMaterial->getAmbient( ).toString( ) << std::endl;
         } // if
      } else if ( strCommand == "Kd" ) {
         // Diffuse Color
         float fR = 0.0f, fG = 0.0f, fB = 0.0f;
         streamData >> fR >> fG >> fB;
         pMaterial->setDiffuse( primitives::Color( fR, fG, fB, 1.0 ) );
         if ( m_bDebug ) {         
            std::cout << "Diffuse Color: " << pMaterial->getDiffuse( ).toString( ) << std::endl;
         } // if      
      } else if ( strCommand == "Ks" ) {
         // Specular Color
         float fR = 0.0f, fG = 0.0f, fB = 0.0f;
         streamData >> fR >> fG >> fB;
         pMaterial->setSpecular( primitives::Color( fR, fG, fB, 1.0 ) );
         if ( m_bDebug ) {         
            std::cout << "Specular Color: " << pMaterial->getSpecular( ).toString( ) << std::endl;
         } // if         
      } else if ( strCommand == "Ns" ) {
         // Shininess
         float fShininess = 0.0f;
         streamData >> fShininess;
         pMaterial->setShininess( fShininess );
         if ( m_bDebug ) {         
            std::cout << "Shininess: " << pMaterial->getShininess( ) << std::endl;
         } // if         
      } else if ( strCommand == "" ) {
         // End of Material Setup
         if ( pMaterial ) {
            m_mapMaterials[ pMaterial->getName( ) ] = pMaterial;            
            pMaterial = 0;
         } // if
      } // else if            
   } // while
   
} // OBJMtlLib

OBJMtlLib::~OBJMtlLib( ) {
   delete m_pfleData;
} // ~OBJMtlLib

primitives::Material* OBJMtlLib::getMaterial( const std::string &rkstrName ) {
   return m_mapMaterials[ rkstrName ];
} // if
   
   }; // tools
}; // powergine


