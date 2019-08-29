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


#include <powergine/sceneobjects/light.h>
 
 
namespace powergine {
	namespace sceneobjects {
 
Light::Light( Light::TYPE eType ) :
   SceneEntity( ),
   m_oAmbient( 1.0f, 1.0f, 1.0f ),
   m_oDiffuse( 1.0f, 1.0f, 1.0f ),
   m_oSpecular( 0.0f, 0.0f, 0.0f )
{
   m_eType  = eType;

   m_fConstantAttenuation  = 1.0f;
   m_fLinearAttenuation    = 0.0f;
   m_fQuadraticAttenuation = 0.0f;
}

Light::~Light( ) {
}

Light::TYPE Light::getType( ) const {
   return m_eType;
}

primitives::Color Light::getAmbient( ) {
   return m_oAmbient;
}

primitives::Color Light::getDiffuse( ) {
   return m_oDiffuse;
}

primitives::Color Light::getSpecular( ) {
   return m_oSpecular;
}

void Light::setAmbient( const primitives::Color &rkColor ) {
   m_oAmbient = rkColor;
}

void Light::setDiffuse( const primitives::Color &rkColor ) {
   m_oDiffuse = rkColor;
}

void Light::setSpecular( const primitives::Color &rkColor ) {
   m_oSpecular = rkColor;
}

float Light::getConstantAttenuation( ) {
   return m_fConstantAttenuation;
}

float Light::getLinearAttenuation( ) {
   return m_fLinearAttenuation;
}

float Light::getQuadraticAttenuation( ) {
   return m_fQuadraticAttenuation;  
}

void Light::setConstantAttenuation( float fConstantAttenuation ) {
   m_fConstantAttenuation = fConstantAttenuation;
}

void Light::setLinearAttenuation( float fLinearAttenuation ) {
   m_fLinearAttenuation = fLinearAttenuation;
}

void Light::setQuadraticAttenuation( float fQuadraticAttenuation ) {
   m_fQuadraticAttenuation = fQuadraticAttenuation;
}


	}; // scenenode
}; // namespace powergine
