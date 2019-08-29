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


#include <powergine/primitives/material.h>

namespace powergine {
	namespace primitives {

// Constructors/Destructors
// Methods
Material::Material( const std::string &rkstrName ) :
   m_strName( rkstrName ),
   m_oAmbient( Color::BLACK ),
   m_oDiffuse( Color::BLACK ),
   m_oSpecular( Color::BLACK ),
   m_oEmission( Color::BLACK ),
   m_fShininess( 0.0f )   
{   
}

Material::Material( const std::string &rkstrName,
            const Color &rkAmbient,
            const Color &rkDiffuse,
            const Color &rkSpecular,
            const Color &rkEmission,
            float fShininess ) :
   
   m_strName( rkstrName ),
   m_oAmbient( rkAmbient ),
   m_oDiffuse( rkDiffuse ),
   m_oSpecular( rkSpecular ),
   m_oEmission( rkEmission ),
   m_fShininess( fShininess )               
{

}

Material::~Material( ) {   
   for ( unsigned int uiI = 0; uiI < m_vecTextures.size( ); uiI++ ) {
      if ( m_vecTextures[ uiI ] ) {      
         delete m_vecTextures[ uiI ];
      } // if
   } // for
} // ~Material

void Material::addTexture( Texture *pTexture ) {
   if ( pTexture ) {
      m_vecTextures.push_back( pTexture );
   } // if
} // addTexture

Texture* const Material::getTexture( unsigned int uiTextureIndex ) const {
   int iRealIndex = m_vecTextures.size( ) - 1;
   int iIndex = uiTextureIndex;
   if ( uiTextureIndex < 0 || iIndex > iRealIndex ) {
      throw( std::string( "Invalid texture index" ) );
   } // if
   
   return m_vecTextures[ uiTextureIndex ];
} // getTexture

const Color& Material::getAmbient( ) const {
   return m_oAmbient;
}

const Color& Material::getDiffuse( ) const {
   return m_oDiffuse;
}

const Color& Material::getSpecular( ) const {
   return m_oSpecular;
}

const Color& Material::getEmission( ) const {
   return m_oEmission;
}

const std::string& Material::getName( ) const {
   return m_strName;
}

float Material::getShininess( ) const {
   return m_fShininess;
}

void Material::setAmbient( const Color &rkAmbient ) {
   m_oAmbient = rkAmbient;
}

void Material::setDiffuse( const Color &rkDiffuse ) {
   m_oDiffuse = rkDiffuse;
}

void Material::setSpecular( const Color &rkSpecular ) {
   m_oSpecular = rkSpecular;
}

void Material::setEmission( const Color &rkEmission ) {
   m_oEmission = rkEmission;
}

void Material::setShininess( float fShininess ) {
   m_fShininess = fShininess;
}

int Material::getNumTextures( ) const {
   return m_vecTextures.size( );
}  // getNumTextures

std::string Material::toString( ) const {
   std::ostringstream sstrDesc;
   sstrDesc << "Name: " << getName( ) << std::endl;
   sstrDesc << "Ambient: " << getAmbient( ).toString( );
   sstrDesc << " Specular: " << getSpecular( ).toString( ) << std::endl;
   sstrDesc << "Diffuse: " << getDiffuse( ).toString( );
   sstrDesc << " Emission: " << getEmission( ).toString( ) << std::endl;
   sstrDesc << "Shininess: " << getShininess( );
   sstrDesc << " Num textures: " << getNumTextures( ) << std::endl;
   return sstrDesc.str( );
} // toString

	}; // primitives
};  // powergine
