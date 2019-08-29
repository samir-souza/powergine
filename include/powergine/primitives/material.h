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

#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include <sstream>
#include <powergine/primitives/color.h>
#include <powergine/primitives/texture.h>

namespace powergine {
	namespace primitives {

	/**
	 * Material Representation. Used to compose a object texture
	 */
	class Material {

	public:

		// Receives the material name, which identifies it
	   Material( const std::string &rkstrName );

	   // Receives the material name and the lighting
	   // information
	   Material( const std::string &rkstrName,
				 const Color &rkAmbient,
				 const Color &rkDiffuse,
				 const Color &rSpecular,
				 const Color &rkEmission,
				 float fShininess );

	   virtual ~Material( );

	   // Add a texture to this material. Multitexture is
	   // supported
	   void addTexture( Texture *pTexture );

	   // Retrieves a texture pointer given its index (multitexture)
	   Texture* const getTexture( unsigned int uiTextureIndex ) const throw( std::string );

	   // Getters of the lighting colors
	   const Color& getAmbient( ) const;
	   const Color& getDiffuse( ) const;
	   const Color& getSpecular( ) const;
	   const Color& getEmission( ) const;

	   // Returns the material shininess
	   float getShininess( ) const;

	   // Setters of the lighting colors
	   void setAmbient( const Color &rkAmbient );
	   void setDiffuse( const Color &rkDiffuse );
	   void setSpecular( const Color &rkSpecular );
	   void setEmission( const Color &rkEmission );

	   // Setter of the shininess
	   void setShininess( float fShininess );

	   // Returns the material name
	   const std::string& getName( ) const;

	   // Returns the number of textures (multitexture)
	   // registered in this material
	   int getNumTextures( ) const;

	   // Returns a description of the material
	   std::string toString( ) const;

	private:
	   std::string m_strName;
	   std::vector<Texture*> m_vecTextures;
	   Color m_oAmbient;
	   Color m_oDiffuse;
	   Color m_oSpecular;
	   Color m_oEmission;
	   float m_fShininess;
	};

	}; // primitives
}; // powergine

#endif //MATERIAL_H
