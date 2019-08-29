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


#include <powergine/core.h>
#include <SDL/SDL_net.h>

namespace powergine {

Core::~Core( ) {
   if ( m_pSingleton ) {
      delete m_pSingleton;
   } // if
   if ( m_pVideoManager ) {
      delete m_pVideoManager;
   } // if
   finalize( );
}

int Core::initialize( int argc, char * argv[] ) {
   // setup position elements
   primitives::VertexElement *pPositionElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_POSITION, primitives::VertexElement::DATA_FLOAT3, 0
   );
   primitives::Vertex::s_oFormat.addElement( pPositionElement );
   primitives::VertexDiffuse::s_oFormat.addElement( pPositionElement );
   primitives::VertexNormal::s_oFormat.addElement( pPositionElement );
   primitives::VertexTexture::s_oFormat.addElement( pPositionElement );
   primitives::VertexDiffuseNormal::s_oFormat.addElement( pPositionElement );
   primitives::VertexTextureDiffuse::s_oFormat.addElement( pPositionElement );
   primitives::VertexTextureNormal::s_oFormat.addElement( pPositionElement );
   primitives::VertexTextureDiffuseNormal::s_oFormat.addElement( pPositionElement );



   // setup diffuse elements
   primitives::VertexElement *pDiffuseElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_COLOR, primitives::VertexElement::DATA_FLOAT4, 3 * sizeof( float )
   );
   primitives::VertexDiffuse::s_oFormat.addElement( pDiffuseElement );
   primitives::VertexDiffuseNormal::s_oFormat.addElement( pDiffuseElement );

   pDiffuseElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_COLOR, primitives::VertexElement::DATA_FLOAT4, 5 * sizeof( float )
   );
   primitives::VertexTextureDiffuse::s_oFormat.addElement( pDiffuseElement );
   primitives::VertexTextureDiffuseNormal::s_oFormat.addElement( pDiffuseElement );



   // setup normal elements
   primitives::VertexElement *pNormalElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_NORMAL, primitives::VertexElement::DATA_FLOAT3, 3 * sizeof( float )
   );
   primitives::VertexNormal::s_oFormat.addElement( pNormalElement );

   pNormalElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_NORMAL, primitives::VertexElement::DATA_FLOAT3, 7 * sizeof( float )
   );
   primitives::VertexDiffuseNormal::s_oFormat.addElement( pNormalElement );

   pNormalElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_NORMAL, primitives::VertexElement::DATA_FLOAT3, 5 * sizeof( float )
   );
   primitives::VertexTextureNormal::s_oFormat.addElement( pNormalElement );

   pNormalElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_NORMAL, primitives::VertexElement::DATA_FLOAT3, 9 * sizeof( float )
   );
   primitives::VertexTextureDiffuseNormal::s_oFormat.addElement( pNormalElement );



   // setup texture elemnts
   primitives::VertexElement *pTextureElement = new primitives::VertexElement(
      primitives::VertexElement::ELEMENT_TEXCOORD, primitives::VertexElement::DATA_FLOAT2, 3 * sizeof( float )
   );
   primitives::VertexTexture::s_oFormat.addElement( pTextureElement );
   primitives::VertexTextureDiffuse::s_oFormat.addElement( pTextureElement );
   primitives::VertexTextureNormal::s_oFormat.addElement( pTextureElement );
   primitives::VertexTextureDiffuseNormal::s_oFormat.addElement( pTextureElement );
   return 0;
} // initialize

services::video::VideoManager* Core::getVideoManager( ) const {
   if ( !m_pVideoManager ) {
      get( )->createVideoManager( services::video::VideoManager::DEFAULT_RENDER_MODE );
   } // if
   return m_pVideoManager;
} // getVideoManager

services::input::InputManager* Core::getInputManager( ) const {
   if ( !m_pInputManager ) {
      get( )->createInputManager( );
   } // if
   return m_pInputManager;
} // getInputManager

services::comm::CommunicationManager *powergine::Core::getCommManager( ) {
   if ( !m_pCommManager ) {
      m_pCommManager = new services::comm::CommunicationManager( );
   } // if
   return m_pCommManager;
}

void Core::createVideoManager( services::video::RenderMode *pRenderMode,
                               services::video::VideoManager::MANAGER_TYPE eManagerType ) {
   switch ( eManagerType ) {
      case services::video::VideoManager::MANAGER_OPENGL: {
         m_pVideoManager = new services::video::opengl::OGLVideoManager( pRenderMode );
      } break;

      case services::video::VideoManager::MANAGER_DIRECT3D:
      case services::video::VideoManager::MANAGER_SOFTWARE:
      default:
         throw( std::string( "VideoManager not implemented!" ) );
   } // switch

} // createVideoManager

void Core::createInputManager( services::input::InputManager::MANAGER_TYPE eManagerType ) {
   switch( eManagerType ) {
      case services::input::InputManager::MANAGER_SDL: {
         m_pInputManager = new services::input::sdl::SDLInputManager( );
      } break;

      case services::input::InputManager::MANAGER_DIRECT_INPUT:
      default:
         throw( std::string( "InputManager not implemented!" ) );
   } // switch
} // createInputManager


class SDLCore : public Core {
   public:

      inline SDLCore( ) : Core( ) { }

      inline void sleep( long lMilliseconds ) { SDL_Delay( lMilliseconds ); }

      inline int initialize(int argc, char* argv[] ) {
         int iReturnCode = Core::initialize( argc, argv );
         // Initialize SDL's video subsystem.
         if ( SDL_Init( SDL_INIT_EVERYTHING | SDL_INIT_NOPARACHUTE ) < 0 ) {
            std::ostringstream sstrErrorMsg;
            sstrErrorMsg << "core.cpp (initialize): Video initialization failed - ";
            sstrErrorMsg << SDL_GetError( );
            throw ( sstrErrorMsg.str( ) );
         } // if

         if ( SDLNet_Init( ) == -1 ) {
            std::ostringstream sstrErrorMsg;
            sstrErrorMsg << "core.cpp (initialize): Network initialization failed - ";
            sstrErrorMsg << SDLNet_GetError( );
            throw ( sstrErrorMsg.str( ) );
         } // if
         return iReturnCode;
      } // initialize

      inline void finalize( ) {
         SDLNet_Quit( );
         SDL_Quit( );
      } // finalize
};


Core* Core::m_pSingleton = 0;

Core* Core::get( ) {
   if ( !m_pSingleton ) {
      m_pSingleton = new SDLCore( );
   } // if
   return m_pSingleton;
}


};  // powergine
