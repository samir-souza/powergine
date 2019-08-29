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


#ifndef OGLVIDEOMANAGER_H
#define OGLVIDEOMANAGER_H

#include <map>
#include <list>
#include <iostream>
#include <string>
#include <cstdlib>

#include <powergine/services/video/videomanager.h>
#include <powergine/services/video/videoproperties.h>
#include <powergine/services/video/opengl/oglvertexbuffer.h>
#include <powergine/services/video/opengl/ogltexture.h>
#include <powergine/services/video/opengl/sdlimage.h>
#include <powergine/primitives/color.h>

#include <powergine/utils/mathhelper.h>

namespace powergine {
   namespace services {
      namespace video {
         namespace opengl {



/**
 * Class OGLVideoManager
 *
 */
class OGLVideoManager : public VideoManager {

public:

   OGLVideoManager( services::video::RenderMode *pRenderMode );

   ~OGLVideoManager( );

   // See VideoManager::setMouseCursorVisibility
   void setMouseCursorVisibility( bool bVisibility );

   // See VideoManager::setProjectionMatrix
   void setProjectionMatrix( const primitives::Matrix4x4 &rkMatrix );

   // See VideoManager::updateVideoProperties
   void updateVideoProperties( );

   // See VideoManager::initialize
   void initialize( );

   // See VideoManager::openWindow
   bool openWindow( );

   // See VideoManager::openWindow
   bool openWindow( const services::video::RenderWindow &rkRenderWindow );

   // See VideoManager::closeWindow
   void closeWindow( );

   // See VideoManager::beginFrame
   void beginFrame( const primitives::Matrix4x4 &rkProjectionMatrix );

   // See VideoManager::endFrame
   void endFrame( );

   // See VideoManager::flipBuffer
   void flipBuffer( );

   // See VideoManager::render
   void render( const primitives::RenderPrimitive &rkRenderPrimitive);

   // See VideoManager::clear
   void clear( unsigned int uiBufferBits, const primitives::Color &rkColor, float fDepthValue = 1.0f, unsigned int uiStencilValue = 0 );

   // See VideoManager::addLight
   void addLight( sceneobjects::Light *pLight);

   // Returns the color of the ambient light
   primitives::Color* getAmbientLight( );

   // Returns the color of all lights blended
   primitives::Color* getAllLights( );

   // See VideoManager::refreshVideoMode
   void refreshVideoMode( );

   // See VideoManager::createVertexBuffer
   primitives::VertexBuffer* createVertexBuffer( int iNumVertices, const primitives::VertexFormat &rkFormat, unsigned char *pucData = 0 );

   // See VideoManager::createPolygonBuffer
   primitives::PolygonBuffer* createPolygonBuffer( int iNumPolygons, int iNumPolygonVertices, unsigned char *pucData = 0 );

   // See VideoManager::multMatrix
   void multMatrix( const primitives::Matrix4x4 &rkMatrix );

   // See VideoManager::loadMatrix
   void loadMatrix( const primitives::Matrix4x4 &rkMatrix );

   // See VideoManager::createTexture
   primitives::Texture* createTexture( const std::string &rkstrTextureName, primitives::Image *pImage, primitives::Texture::FILTER eFilter, bool bRepeat = false );

   // See VideoManager::createTexture
   primitives::Texture* createTexture( const std::string &rkstrTextureName, const std::string &rkstrFileName, primitives::Texture::FILTER eFilter, bool bRepeat = false );

   // See VideoManager::getTexture
   primitives::Texture* getTexture( const std::string &rkstrTextureName );

private:

   int m_iVideoProperties;
   // Maximun number of lights
   unsigned int m_uiMaxLights;
   // Maximun number of texture for multitexture in one pass ( ARB extensions )
   unsigned int m_uiMaxTextureUnits;
   // Maximum amount of texture size
   unsigned int m_uiMaxTextureSize;
   // Active Lights
   std::list< sceneobjects::Light* > m_lisLights;
   // Total SUM of ambient lights
   primitives::Color m_oAmbientLight;
   //Total sum of ambient light from all lights, including directional and point lights
   primitives::Color m_oAllLights;
   // All Textures loaded
   std::map< const std::string, primitives::Texture* > m_mapTextures;

   bool startVideoMode( );

   unsigned int *m_pPrimitiveRenderModes;
   // base pointer clients
   bool m_bNormalArrayEnabled;
   bool m_bDiffuseArrayEnabled;
   bool m_bTexCoordArrayEnabled[ 8 ];
};

         }; // opengl
      }; // services
   }; // video
}; // powergine

#endif //SDLRENDERMANAGER_H

