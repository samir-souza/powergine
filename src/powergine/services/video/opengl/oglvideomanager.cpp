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


#include <powergine/services/video/opengl/oglvideomanager.h>
#include <powergine/primitives/vertextexturenormal.h>
#include <SDL/SDL.h>
#include <SDL/SDL_opengl.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glext.h>

namespace powergine {
   namespace services {
      namespace video {
         namespace opengl {

extern PFNGLACTIVETEXTUREARBPROC glActiveTextureARB;
extern PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB;

PFNGLACTIVETEXTUREARBPROC glActiveTextureARB = 0;
PFNGLCLIENTACTIVETEXTUREARBPROC glClientActiveTextureARB = 0;

void collectOGLError( ) {
   // check opengl runtime error
   GLenum eError = glGetError( );
   if ( eError != GL_NO_ERROR ) {
      std::cout << "OpenGL Error: ";
      switch( eError ) {
         case GL_INVALID_ENUM: {  std::cout << "INVALID ENUM"; } break;
         case GL_INVALID_VALUE: {  std::cout << "INVALID VALUE"; } break;
         case GL_INVALID_OPERATION: {  std::cout << "INVALID OPERATION"; } break;
         case GL_STACK_OVERFLOW: {  std::cout << "STACK OVERFLOW"; } break;
         case GL_STACK_UNDERFLOW: {  std::cout << "STACK UNDERFLOW"; } break;
         case GL_OUT_OF_MEMORY: {  std::cout << "OUT OF MEMORY"; } break;
         default: { std::cout << "UNKNOWN ERROR"; }
      } // switch
      std::cout << std::endl;
   } // if
} // collectOGLError

OGLVideoManager::OGLVideoManager( services::video::RenderMode *pRenderMode ) :
   VideoManager( pRenderMode ),
   m_iVideoProperties( SDL_OPENGL ),
   m_oAmbientLight( 0.0f, 0.0f, 0.0f, 1.0f ),
   m_oAllLights( 0.0f, 0.0f, 0.0f, 1.0f )
{

   // setup conversion render modes pointer
   m_pPrimitiveRenderModes = new GLenum[ 8 ];
   m_pPrimitiveRenderModes[ 0 ] = GL_LINES;
   m_pPrimitiveRenderModes[ 1 ] = GL_TRIANGLES;
   m_pPrimitiveRenderModes[ 2 ] = GL_LINE_STRIP;
   m_pPrimitiveRenderModes[ 3 ] = GL_TRIANGLE_STRIP;
   m_pPrimitiveRenderModes[ 4 ] = GL_POINTS;
   m_pPrimitiveRenderModes[ 5 ] = GL_QUADS;
   m_pPrimitiveRenderModes[ 6 ] = GL_QUAD_STRIP;
   m_pPrimitiveRenderModes[ 7 ] = GL_POLYGON;

   m_oPerspectiveProjection.buildProjection( *(getViewPort( )) );
   m_oOrthographicProjection.buildProjection( *(getViewPort( )) );
   activePerspectiveProjection( );
   updateVideoProperties( );
   try {
      initialize( );
   } catch ( std::string &ex ) {
      std::cout << "Error: " << ex << std::endl;
   } // catch
}

OGLVideoManager::~OGLVideoManager( ) {
} //

void OGLVideoManager::setMouseCursorVisibility( bool bVisibility ) {
   VideoManager::setMouseCursorVisibility( bVisibility );
   ( VideoManager::isMouseCursorVisible( ) ) ? SDL_ShowCursor( SDL_ENABLE ) : SDL_ShowCursor( SDL_DISABLE );
}

void OGLVideoManager::setProjectionMatrix( const primitives::Matrix4x4 &rkMatrix ) {
   //Setup projection matrix
   glMatrixMode( GL_PROJECTION );
   loadMatrix( rkMatrix );
}

void OGLVideoManager::updateVideoProperties( ) {
	services::video::VideoProperties *pProperties = getRenderWindow( )->getProperties( );

   if ( pProperties->isSet( services::video::VideoProperties::DOUBLEBUFFER ) ) {
      SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
   } else if ( ( m_iVideoProperties & SDL_DOUBLEBUF ) != 0 ) {
      SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 0 );
   } // else if

   if ( pProperties->isSet( services::video::VideoProperties::FULLSCREEN ) ) {
      m_iVideoProperties |= SDL_FULLSCREEN;
   } else if ( ( m_iVideoProperties & SDL_FULLSCREEN ) != 0 ) {
      m_iVideoProperties ^= SDL_FULLSCREEN;
   } // else if

   if ( pProperties->isSet( services::video::VideoProperties::HARDWAREACCELERATED ) ) {
      m_iVideoProperties |= SDL_HWSURFACE;
   } else if ( ( m_iVideoProperties & SDL_HWSURFACE ) != 0 ) {
      m_iVideoProperties ^= SDL_HWSURFACE;
   } // else if

   if ( pProperties->isSet( services::video::VideoProperties::RESIZABLE ) ) {
      m_iVideoProperties |= SDL_RESIZABLE;
   } else if ( ( m_iVideoProperties & SDL_RESIZABLE ) != 0 ) {
      m_iVideoProperties ^= SDL_RESIZABLE;
   } // else if

   if ( pProperties->isSet( services::video::VideoProperties::NOFRAME ) ) {
      m_iVideoProperties |= SDL_NOFRAME;
   } else if ( ( m_iVideoProperties & SDL_NOFRAME ) != 0 ) {
      m_iVideoProperties ^= SDL_NOFRAME;
   } // else if

}

void OGLVideoManager::initialize( ) {
   const SDL_VideoInfo* info = 0;

   // Get some video information.
   info = SDL_GetVideoInfo( );

   if( !info ) {
      // This should probably never happen.
      std::ostringstream sstrErrorMsg;
      sstrErrorMsg << "oglvideomanager.cpp(openWindow): Video query failed - ";
      sstrErrorMsg << SDL_GetError( );
      throw ( sstrErrorMsg.str( ) );
   } // if

   SDL_Rect **ppAvaliableVideoModes = SDL_ListModes( info->vfmt, SDL_FULLSCREEN | SDL_HWSURFACE );
   if( ppAvaliableVideoModes != (SDL_Rect **)0 && ppAvaliableVideoModes != (SDL_Rect **)-1 ) {
      for( int i=0; ppAvaliableVideoModes[i]; ++i ) {
         int iWidth = ppAvaliableVideoModes[ i ]->w;
         int iHeight = ppAvaliableVideoModes[ i ]->h;
         int iBpp = info->vfmt->BitsPerPixel;
         getRenderWindow( )->addRenderMode( new services::video::RenderMode( iWidth, iHeight, iBpp ) );
      } // for
   } // if

   try {
      startVideoMode( );
   } catch ( std::string &ex ) {
      std::cout << "Error: " << ex << std::endl;
   } // catch

   glGetIntegerv( GL_MAX_LIGHTS, (GLint*)&m_uiMaxLights );
   glGetIntegerv( GL_MAX_TEXTURE_UNITS, (GLint*)&m_uiMaxTextureUnits );
   glGetIntegerv( GL_MAX_TEXTURE_SIZE, (GLint*)&m_uiMaxTextureSize );

} // initialize

bool OGLVideoManager::openWindow( ) {
   return openWindow( m_oRenderWindow );
}

bool OGLVideoManager::openWindow( const services::video::RenderWindow &rkRenderWindow ) {
   float fRatio = static_cast<float>( getWidth( ) ) / getHeight( );

   glViewport( getViewPort( )->getX( ), getViewPort( )->getY( ), getWidth( ) , getHeight( ) );

   //Setup projection matrix
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity( );

   gluPerspective( getFOV( ), fRatio, getZNear( ), getZFar( ) );

   //Setup modelview transformation matrix
   glMatrixMode( GL_MODELVIEW );
   glLoadIdentity( );


   glEnable( GL_DEPTH_TEST );
   glEnable( GL_COLOR_MATERIAL );

   glShadeModel( GL_SMOOTH );
   glLightModeli( GL_LIGHT_MODEL_TWO_SIDE, GL_FALSE );
   glLightModeli( GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE );
   glLightModeli( GL_LIGHT_MODEL_COLOR_CONTROL, GL_SINGLE_COLOR );

   glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

   glDisable( GL_COLOR_MATERIAL );
   glColor3f( 1.0f, 1.0f, 1.0f );
   glDisable( GL_TEXTURE_2D );

   glEnableClientState( GL_VERTEX_ARRAY );
   glDisableClientState( GL_NORMAL_ARRAY );
   glDisableClientState( GL_COLOR_ARRAY );

   m_bNormalArrayEnabled   = false;
   m_bDiffuseArrayEnabled  = false;

   //State set by initialize method
   for( int i = 0; i < 8; ++i )
      m_bTexCoordArrayEnabled[ i ] = false;

   const std::string strExtensions = reinterpret_cast<const char*>( glGetString( GL_EXTENSIONS ) );

   std::cout << "....................................................................................." << std::endl;
   std::cout << "PowerGine v1.0 - Copyright 2005 by Samir Araujo " << std::endl;
   std::cout << "....................................................................................." << std::endl;
   std::cout << "::Window Info" << std::endl;
   std::cout << "Width: " << getWidth( ) << std::endl;
   std::cout << "Height: " << getHeight( ) << std::endl;
   std::cout << "BPP: " << getBPP( ) << std::endl;
   std::string strFullScreen = ( getRenderWindow( )->getProperties( )->isSet( services::video::VideoProperties::FULLSCREEN ) ) ? "Yes" : "No";
   std::cout << "Fullscreen: " << strFullScreen << std::endl;
   std::cout << "::GPU Info" << std::endl;
   std::cout << "Version: " << glGetString( GL_VERSION ) << std::endl;
   std::cout << "Renderer: " << glGetString( GL_RENDERER ) << std::endl;
   std::cout << "Vendor: " << glGetString( GL_VENDOR ) << std::endl;
   std::cout << "Max lights: " << m_uiMaxLights << std::endl;
   std::cout << "Max texture units: " << m_uiMaxTextureUnits << std::endl;
   std::cout << "Max texture size: " << m_uiMaxTextureSize << std::endl;
   std::cout << "...................." << std::endl;

   glActiveTextureARB =
      (PFNGLACTIVETEXTUREARBPROC)SDL_GL_GetProcAddress( "glActiveTextureARB" );
   glClientActiveTextureARB =
      (PFNGLCLIENTACTIVETEXTUREARBPROC)SDL_GL_GetProcAddress( "glClientActiveTextureARB" );
   // TODO: check if  everythings goes ok
   return true;
}

void OGLVideoManager::closeWindow( ) {
   SDL_Quit( );
}

void OGLVideoManager::beginFrame( const primitives::Matrix4x4 &rkProjectionMatrix ) {
   m_oCurrentViewMatrix = rkProjectionMatrix;

   m_oAmbientLight.setRed( 0.0f );
   m_oAmbientLight.setGreen( 0.0f );
   m_oAmbientLight.setBlue( 0.0f );
   m_oAmbientLight.setAlpha( 1.0f );

   m_oAllLights.setRed( 0.0f );
   m_oAllLights.setGreen( 0.0f );
   m_oAllLights.setBlue( 0.0f );
   m_oAllLights.setAlpha( 1.0f );

}

void OGLVideoManager::endFrame( ) {
   GLenum eMode = 0;
   primitives::RenderPrimitive *pRenderPrimitive = 0;
   bool bLighting;
   bool bMultiTexture = false;
   static primitives::Matrix4x4 s_oView;
   static primitives::Matrix4x4 s_oModel;

   // setup the lights
   std::list< sceneobjects::Light* >::iterator ppBegin = m_lisLights.begin( );
   std::list< sceneobjects::Light* >::iterator ppEnd = m_lisLights.end( );
   bLighting = ( ppBegin != ppEnd );

   if ( bLighting ) {
      unsigned int uiLightCounter = 0;
      while ( ppBegin != ppEnd ) {
         GLenum eLight = GLenum( GL_LIGHT0 + uiLightCounter );

         sceneobjects::Light *pLight = (*ppBegin);
         primitives::Color oAmbient = pLight->getAmbient( );
         primitives::Color oDiffuse = pLight->getDiffuse( );
         primitives::Color oSpecular = pLight->getSpecular( );

         glLightfv( eLight, GL_AMBIENT, reinterpret_cast<float*>( &oAmbient ) );
         glLightfv( eLight, GL_DIFFUSE, reinterpret_cast<float*>( &oDiffuse ) );
         glLightfv( eLight, GL_SPECULAR, reinterpret_cast<float*>( &oSpecular ) );

         glLightf( eLight, GL_CONSTANT_ATTENUATION, pLight->getConstantAttenuation( ) );
         glLightf( eLight, GL_LINEAR_ATTENUATION, pLight->getLinearAttenuation( ) );
         glLightf( eLight, GL_QUADRATIC_ATTENUATION, pLight->getQuadraticAttenuation( ) );

         if( pLight->getType( ) == sceneobjects::Light::DIRECTIONAL ) {
            primitives::Vector3D *pLightPosition;
            if ( pLight->getParentSceneNode( ) ) {
               // must get the world transform ? ?
               pLightPosition = new primitives::Vector3D( primitives::Vector3D::ORIGO );
            } else {
               pLightPosition = new primitives::Vector3D( 0.0f, 0.0f, -1.0f );
            } // else
            glLightfv( eLight, GL_POSITION, reinterpret_cast<float*>( pLightPosition ) );
         } else if ( pLight->getType( ) == sceneobjects::Light::POINT ) {
            primitives::Vector3D *pLightPosition = 0;
            if ( pLight->getParentSceneNode( ) ) {
               // must get the world transformation RTS
               *pLightPosition = pLight->getParentSceneNode( )->getWorldTranslation( );
            } else {
               pLightPosition = new primitives::Vector3D( primitives::Vector3D::ORIGO );
            } // else
            glLightfv( eLight, GL_POSITION, reinterpret_cast<float*>( pLightPosition ) );
         } // else if

         glEnable( eLight );
         ++ppBegin;
         ++uiLightCounter;
      } // while

      glLightModelfv( GL_LIGHT_MODEL_AMBIENT, reinterpret_cast<const float*>( &m_oAmbientLight ) );
   } // if

   // render all primitives queued
   for ( unsigned int uiI = 0; uiI < m_uiNumQueueElements; ++uiI ) {
      // get the first primitive from queue
      pRenderPrimitive = m_ppRenderQueue[ uiI ];

      // get render mode
      eMode = m_pPrimitiveRenderModes[ pRenderPrimitive->getMode( ) ];
      switch( eMode ) {
         case GL_LINES:
         case GL_LINE_STRIP: {
            glLineWidth( pRenderPrimitive->getEdgeLinesSize( ) );
         } break;
         case GL_POINTS: {
            glPointSize( pRenderPrimitive->getEdgeLinesSize( ) );
         } break;
         default: break;
      } // switch

      //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	if ( !pRenderPrimitive->getModelViewMatrix( ) ) {
      	s_oView = *getViewMatrix( );
	} else {
		s_oView = *pRenderPrimitive->getModelViewMatrix( );
	} // else


      if ( !pRenderPrimitive->isPermitTranslation( ) ) {
         s_oView.setElement( 0, 3, 0.0f );
         s_oView.setElement( 1, 3, 0.0f );
         s_oView.setElement( 2, 3, 0.0f );
      } // else

      glMatrixMode( GL_MODELVIEW );
      loadMatrix( s_oView );


      // apply the current model view to primitive
            /*
      if ( pRenderPrimitive->getModelViewMatrix( ) ) {
         // apply the model transformations for RenderPrimitive
         s_oModel = *pRenderPrimitive->getModelViewMatrix( );
         if ( !pRenderPrimitive->isPermitTranslation( ) ) {
            s_oModel.setElement( 0, 3, 0.0f );
            s_oModel.setElement( 1, 3, 0.0f );
            s_oModel.setElement( 2, 3, 0.0f );
         } // if
         glMatrixMode( GL_MODELVIEW );
         glPushMatrix( );
         multMatrix( s_oModel );
      } // if

      */


      primitives::Material *pMaterial = pRenderPrimitive->getMaterial( );
      if( pMaterial ) {
         bMultiTexture = ( pMaterial->getNumTextures( ) > 1 );

         // setup material properties if defined and at least 1 light is defined
         if ( bLighting && pRenderPrimitive->isPermitTranslation( ) ) {

            glMaterialfv( GL_FRONT_AND_BACK, GL_AMBIENT,
               reinterpret_cast<const float*>( &( pMaterial->getAmbient( ) ) ) );
            glMaterialfv( GL_FRONT_AND_BACK, GL_DIFFUSE,
               reinterpret_cast<const float*>( &( pMaterial->getDiffuse( ) ) ) );
            glMaterialfv( GL_FRONT_AND_BACK, GL_SPECULAR,
               reinterpret_cast<const float*>( &( pMaterial->getSpecular( ) ) ) );
            glMaterialfv( GL_FRONT_AND_BACK, GL_EMISSION,
               reinterpret_cast<const float*>( &( pMaterial->getEmission( ) ) ) );
            glMaterialf(  GL_FRONT_AND_BACK, GL_SHININESS,
               pMaterial->getShininess( ) );

            glEnable( GL_COLOR_MATERIAL );

         } else {
            glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
         } // else

         int iNumTextures = utils::MathHelper::get( )->min<int>(
            m_uiMaxTextureUnits, pMaterial->getNumTextures( )
         );

         if ( bMultiTexture ) {

            // TODO: automatize this
            glActiveTextureARB( GL_TEXTURE0_ARB );
            glTexEnvi( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE );
            // Replace with modulated lightmap


            glActiveTextureARB( GL_TEXTURE1_ARB );
            // We use GL_COMBINE_EXT to combine the modulated lightmap with
            // the base texture, it allows us to set the following properties
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_COMBINE_EXT);

            // This tells OpenGL to set source 1 as the base texture which
            // was drawn using GL_REPLACE, so "as is"
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE0_RGB_EXT, GL_PREVIOUS_EXT);

            // This tells OpenGL to operand 1 to use the source color
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND0_RGB_EXT, GL_SRC_COLOR);

            // This tells OpenGL that we want to modulate the two textures
            // based on our new settings
            glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB_EXT, GL_MODULATE);

            // This tells OpenGL to set source 2 as the lightmap texture
            glTexEnvi(GL_TEXTURE_ENV, GL_SOURCE1_RGB_EXT, GL_TEXTURE);

            // This tells OpenGL to operand 2 to use the source color
            glTexEnvi(GL_TEXTURE_ENV, GL_OPERAND1_RGB_EXT, GL_SRC_COLOR);

            // Double the values on the RGB channel of our final texture
            glTexEnvf(GL_TEXTURE_ENV, GL_RGB_SCALE_EXT, 2.0f);

         } // if

         for ( int iJ = 0; iJ < iNumTextures; iJ++ ) {
            try {
               // get the current texture
               primitives::Texture *pTexture = pMaterial->getTexture( iJ );
               // check it texture is loaded
               if ( pTexture ) {
				   if ( pTexture->mustRepeat( ) ) {
				      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
					  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );
				   } else {
				      glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP );
					  glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP );
				   } // else

                  glActiveTextureARB( GL_TEXTURE0_ARB + iJ );
                  glBindTexture( GL_TEXTURE_2D, pTexture->getID( ) );
                  glEnable( GL_TEXTURE_2D );

                  //collectOGLError( );
               } // if
            } catch ( std::string &ex ) {
               std::cerr << "Error: " << ex << std::endl;
            } // catch
         } // for

      	if ( iNumTextures < 1 ) {
      		glDisable( GL_TEXTURE_2D );
      	} // if

      } else {
       	glDisable( GL_COLOR_MATERIAL );
       	glDisable( GL_TEXTURE_2D );
      } // else

      OGLVertexBuffer *pVertexBuffer =
         static_cast<OGLVertexBuffer*>( pRenderPrimitive->getVertexBuffer( ) );

      unsigned char *pucRenderData = pVertexBuffer->getVertexData( );
      int iTypeSize = pVertexBuffer->getFormat( ).getTypeSize( );
      int iNumElements = pVertexBuffer->m_pPositionElement->getDataType( );

      // setup position data pointer
      glVertexPointer( iNumElements, GL_FLOAT, iTypeSize, pucRenderData );

      if ( pVertexBuffer->m_pNormalElement ) {
         unsigned int uiOffset = pVertexBuffer->m_pNormalElement->getOffset( );
         iNumElements = pVertexBuffer->m_pNormalElement->getDataType( );
         // setup normal data pointer
         glNormalPointer( GL_FLOAT, iTypeSize, pucRenderData + uiOffset );
         if ( !m_bNormalArrayEnabled ) {
            glEnableClientState( GL_NORMAL_ARRAY );
            m_bNormalArrayEnabled = true;
         } // if
      } else {
      	glDisableClientState( GL_NORMAL_ARRAY );
      	m_bNormalArrayEnabled = false;
      } // else


      if ( pVertexBuffer->m_pDiffuseElement ) {
         unsigned int uiOffset = pVertexBuffer->m_pDiffuseElement->getOffset( );
         iNumElements = pVertexBuffer->m_pDiffuseElement->getDataType( );
         glColorPointer( iNumElements, GL_FLOAT, iTypeSize, pucRenderData + uiOffset );
         if ( !m_bDiffuseArrayEnabled ) {
            glEnableClientState( GL_COLOR_ARRAY );
            m_bDiffuseArrayEnabled = true;
         } // if
      } else {
      	glDisableClientState( GL_COLOR_ARRAY );
      	m_bDiffuseArrayEnabled = false;
      } // else

      unsigned int uiTexCoordElements =
         primitives::VertexElement::getNumElements( primitives::VertexElement::ELEMENT_TEXCOORD );
      int iNumTexCoords = utils::MathHelper::get( )->min<int>(
         m_uiMaxTextureUnits, uiTexCoordElements
      );

      for ( int uI = 0; uI < iNumTexCoords; uI++ ) {
         if ( pVertexBuffer->m_pTexCoordElement[ uI ] ) {
            unsigned int uiOffset = pVertexBuffer->m_pTexCoordElement[ uI ]->getOffset( );
            iNumElements = pVertexBuffer->m_pTexCoordElement[ uI ]->getDataType( );
            glClientActiveTextureARB( GL_TEXTURE0_ARB + uI );
            glTexCoordPointer( iNumElements, GL_FLOAT, iTypeSize, pucRenderData + uiOffset );
            if ( !m_bTexCoordArrayEnabled[ uI ] ) {
               glEnableClientState( GL_TEXTURE_COORD_ARRAY );
               m_bTexCoordArrayEnabled[ uI ] = true;
            } // if
         } else if ( m_bTexCoordArrayEnabled[ uI ] ) {
            glClientActiveTextureARB( GL_TEXTURE0_ARB + uI );
            glDisableClientState( GL_TEXTURE_COORD_ARRAY );
            m_bTexCoordArrayEnabled[ uI ] = false;
         } // else if
      } // for

      primitives::PolygonBuffer *pPolygonBuffer = pRenderPrimitive->getPolygonBuffer( );
      int iNumVertices = pPolygonBuffer->getNumPolygons( ) * pPolygonBuffer->getNumPolygonVertices( );
      // draw all polygons
      glDrawElements( eMode, iNumVertices, GL_UNSIGNED_INT, pPolygonBuffer->getPolygonData( ) );

      glMatrixMode( GL_MODELVIEW );
      glPopMatrix( );
   } // for

   // reset primitives buffer
   m_uiNumQueueElements = 0;
}

void OGLVideoManager::flipBuffer( ) {
   SDL_GL_SwapBuffers( );
}

void OGLVideoManager::render( const primitives::RenderPrimitive &rkRenderPrimitive) {

   if ( m_uiNumQueueElements >= m_uiMaxQueueElements ) {
      primitives::RenderPrimitive **ppRenderQueue =
         new primitives::RenderPrimitive*[ m_uiMaxQueueElements * 2 ];

      std::memcpy( ppRenderQueue, m_ppRenderQueue, sizeof( primitives::RenderPrimitive* ) * m_uiMaxQueueElements );
      delete [] m_ppRenderQueue;
      m_uiMaxQueueElements *= 2;
      m_ppRenderQueue = ppRenderQueue;
   } // if

   m_ppRenderQueue[ m_uiNumQueueElements++ ] =
      const_cast<primitives::RenderPrimitive*>( &rkRenderPrimitive );
}

void OGLVideoManager::clear( unsigned int uiBufferBits, const primitives::Color &rkColor, float fDepthValue, unsigned int uiStencilValue ) {
   unsigned int uiBits = 0;
   if( uiBufferBits & VideoManager::COLOR_BUFFER ) {
      primitives::Color oColor = rkColor;
      glClearColor( oColor.getRed( ), oColor.getGreen( ), oColor.getBlue( ), oColor.getAlpha( ) );
      uiBits |= GL_COLOR_BUFFER_BIT;
   } // if
   if( uiBufferBits & VideoManager::DEPTH_BUFFER ) {
      // m_kZBufferState.SetMode( m_kZBufferState.m_uiTestMode, ZBufferMode::ENABLED );
      glClearDepth( fDepthValue );
      uiBits |= GL_DEPTH_BUFFER_BIT;
   } // if
   if( uiBufferBits & VideoManager::STENCIL_BUFFER ) {
      glStencilMask( 0xFFFFFFFF );
      glClearStencil( uiStencilValue );
      uiBits |= GL_STENCIL_BUFFER_BIT;
   } // if
   glClear( uiBits );
}

void OGLVideoManager::addLight( sceneobjects::Light *pLight ) {
   assert( !( m_lisLights.size( ) > m_uiMaxLights ) );
   float fR, fG, fB;
   if ( pLight->getType( ) == sceneobjects::Light::AMBIENT ) {
      fR = m_oAmbientLight.getRed( ) + pLight->getAmbient( ).getRed( );
      fG = m_oAmbientLight.getGreen( ) + pLight->getAmbient( ).getGreen( );
      fB = m_oAmbientLight.getBlue( ) + pLight->getAmbient( ).getBlue( );

      m_oAmbientLight.setRed( utils::MathHelper::get( )->min<float>( fR, 1.0f ) );
      m_oAmbientLight.setGreen( utils::MathHelper::get( )->min<float>( fG, 1.0f ) );
      m_oAmbientLight.setBlue( utils::MathHelper::get( )->min<float>( fB, 1.0f ) );
   } else {
      if ( m_uiMaxLights > 0 && m_lisLights.size( ) == m_uiMaxLights ) {
         // remove the first pointer to light
         m_lisLights.pop_front( );
      } // if
      m_lisLights.push_back( pLight );
   } // else

   fR = m_oAllLights.getRed( ) + pLight->getAmbient( ).getRed( );
   fG = m_oAllLights.getGreen( ) + pLight->getAmbient( ).getGreen( );
   fB = m_oAllLights.getBlue( ) + pLight->getAmbient( ).getBlue( );

   m_oAllLights.setRed( utils::MathHelper::get( )->min<float>( fR, 1.0f ) );
   m_oAllLights.setGreen( utils::MathHelper::get( )->min<float>( fG, 1.0f ) );
   m_oAllLights.setBlue( utils::MathHelper::get( )->min<float>( fB, 1.0f ) );

}

primitives::Color* OGLVideoManager::getAmbientLight( ) {
   return static_cast<primitives::Color*>( &m_oAmbientLight );
}

primitives::Color* OGLVideoManager::getAllLights( ) {
   return static_cast<primitives::Color*>( &m_oAllLights );
}

void OGLVideoManager::refreshVideoMode( ) {
   updateVideoProperties( );
   startVideoMode( );
}

primitives::VertexBuffer *OGLVideoManager::createVertexBuffer( int iNumVertices, const primitives::VertexFormat &rkFormat, unsigned char *pucData ) {
   return new OGLVertexBuffer( iNumVertices, rkFormat, pucData );
} // createVertexBuffer

primitives::PolygonBuffer* OGLVideoManager::createPolygonBuffer( int iNumPolygons, int iNumPolygonVertices, unsigned char *pucData ) {
   return new primitives::PolygonBuffer( iNumPolygons, iNumPolygonVertices, pucData );
} // createPolygonBuffer

void OGLVideoManager::multMatrix( const primitives::Matrix4x4 &rkMatrix ) {
   static GLfloat glfMatrix[ 16 ];

   glfMatrix[ 0 ]  = rkMatrix.getElement( 0, 0 );
   glfMatrix[ 1 ]  = rkMatrix.getElement( 1, 0 );
   glfMatrix[ 2 ]  = rkMatrix.getElement( 2, 0 );
   glfMatrix[ 3 ]  = rkMatrix.getElement( 3, 0 );

   glfMatrix[ 4 ]  = rkMatrix.getElement( 0, 1 );
   glfMatrix[ 5 ]  = rkMatrix.getElement( 1, 1 );
   glfMatrix[ 6 ]  = rkMatrix.getElement( 2, 1 );
   glfMatrix[ 7 ]  = rkMatrix.getElement( 3, 1 );

   glfMatrix[ 8 ]  = rkMatrix.getElement( 0, 2 );
   glfMatrix[ 9 ]  = rkMatrix.getElement( 1, 2 );
   glfMatrix[ 10 ] = rkMatrix.getElement( 2, 2 );
   glfMatrix[ 11 ] = rkMatrix.getElement( 3, 2 );

   glfMatrix[ 12 ] = rkMatrix.getElement( 0, 3 );
   glfMatrix[ 13 ] = rkMatrix.getElement( 1, 3 );
   glfMatrix[ 14 ] = rkMatrix.getElement( 2, 3 );
   glfMatrix[ 15 ] = rkMatrix.getElement( 3, 3 );

   glMultMatrixf( glfMatrix );
}

void OGLVideoManager::loadMatrix( const primitives::Matrix4x4 &rkMatrix ) {
   static GLfloat glfMatrix[ 16 ];

   glfMatrix[ 0 ]  = rkMatrix.getElement( 0, 0 );
   glfMatrix[ 1 ]  = rkMatrix.getElement( 1, 0 );
   glfMatrix[ 2 ]  = rkMatrix.getElement( 2, 0 );
   glfMatrix[ 3 ]  = rkMatrix.getElement( 3, 0 );

   glfMatrix[ 4 ]  = rkMatrix.getElement( 0, 1 );
   glfMatrix[ 5 ]  = rkMatrix.getElement( 1, 1 );
   glfMatrix[ 6 ]  = rkMatrix.getElement( 2, 1 );
   glfMatrix[ 7 ]  = rkMatrix.getElement( 3, 1 );

   glfMatrix[ 8 ]  = rkMatrix.getElement( 0, 2 );
   glfMatrix[ 9 ]  = rkMatrix.getElement( 1, 2 );
   glfMatrix[ 10 ] = rkMatrix.getElement( 2, 2 );
   glfMatrix[ 11 ] = rkMatrix.getElement( 3, 2 );

   glfMatrix[ 12 ] = rkMatrix.getElement( 0, 3 );
   glfMatrix[ 13 ] = rkMatrix.getElement( 1, 3 );
   glfMatrix[ 14 ] = rkMatrix.getElement( 2, 3 );
   glfMatrix[ 15 ] = rkMatrix.getElement( 3, 3 );

   glLoadMatrixf( glfMatrix );
}

bool OGLVideoManager::startVideoMode( ) {
   updateVideoProperties( );
   // Set the video mode
   if( SDL_SetVideoMode( getWidth( ), getHeight( ), getBPP( ), m_iVideoProperties ) == 0 ) {
      std::ostringstream sstrErrorMsg;
      sstrErrorMsg << "oglvideomanager.cpp(startVideoMode): Video mode set failed - ";
      sstrErrorMsg << SDL_GetError( );
      throw( sstrErrorMsg.str( ) );
   } // if
   return true;
}


primitives::Texture* OGLVideoManager::createTexture( const std::string &rkstrTextureName, primitives::Image *pImage, primitives::Texture::FILTER eFilter, bool bRepeat ) {
   const std::map< const std::string, primitives::Texture* >::iterator pkTexture = m_mapTextures.find( rkstrTextureName );
   if ( pkTexture != m_mapTextures.end( ) ) {
      return (*pkTexture).second;
   } // if

   try {
      primitives::Texture *pNewTexture = new OGLTexture( eFilter, pImage, bRepeat );
      m_mapTextures[ rkstrTextureName ] = pNewTexture;
      return pNewTexture;
   } catch( std::string &rstrError ) {
      throw( std::string( "oglvideomanager.cpp(createTexture): " ) + rstrError );
   } // catch
} // createTexture

primitives::Texture* OGLVideoManager::createTexture( const std::string &rkstrTextureName, const std::string &rkstrFileName, primitives::Texture::FILTER eFilter, bool bRepeat ) {
   try {
      primitives::Image *pNewImage = new SDLImage( rkstrFileName );
      return createTexture( rkstrTextureName, pNewImage, eFilter, bRepeat );
   } catch( std::string &rstrError ) {
      throw( rstrError );
   } // catch
} // createTexture

primitives::Texture* OGLVideoManager::getTexture( const std::string &rkstrTextureName ) {
   const std::map< const std::string, primitives::Texture* >::iterator pkTexture = m_mapTextures.find( rkstrTextureName );
   if ( (*pkTexture).second ) {
      return (*pkTexture).second;
   } // if
   throw( std::string( "oglvideomanager.cpp(getTexture): Cannot find texture - " ) + rkstrTextureName );
} // getTexture

         }; // opengl
      }; // services
   }; // video
}; // powergine


