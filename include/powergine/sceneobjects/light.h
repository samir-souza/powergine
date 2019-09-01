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

#ifndef LIGHT_H
#define LIGHT_H

#include <powergine/sceneobjects/sceneentity.h>
#include <powergine/primitives/color.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A light can be added to the scene. This class represents
		 * an instance of a light that will be inserted in the scene
		 */
		class Light : public SceneEntity {

		public:

			enum TYPE {
				  DIRECTIONAL,
				  POINT,
				 AMBIENT
			};

			Light( TYPE eType );

			virtual ~Light( );

			// Returns the light type
			TYPE getType( ) const;

			// Returns the colors of the lights which composes this light
			primitives::Color getAmbient( );
			primitives::Color getDiffuse( );
			primitives::Color getSpecular( );

			// Updates the colors of the lights which composes this light
			void setAmbient( const primitives::Color &rkColor );
			void setDiffuse( const primitives::Color &rkColor );
			void setSpecular( const primitives::Color &rkColor );

			// Returns the attenuation factors of the light
			float getConstantAttenuation( );
			float getLinearAttenuation( );
			float getQuadraticAttenuation( );

			// Updates the attenuation factors of the light
			void setConstantAttenuation( float fConstantAttenuation );
			void setLinearAttenuation( float fLinearAttenuation );
			void setQuadraticAttenuation( float fQuadraticAttenuation );

		private:
		   TYPE m_eType;
		   primitives::Color m_oAmbient;
		   primitives::Color m_oDiffuse;
		   primitives::Color m_oSpecular;
		   float m_fConstantAttenuation;
		   float m_fLinearAttenuation;
		   float m_fQuadraticAttenuation;

		};


	}; // scenenode
}; // namespace powergine

#endif //LIGHT_H
