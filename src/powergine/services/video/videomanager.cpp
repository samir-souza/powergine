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


#include <powergine/services/video/videomanager.h>


namespace powergine {
	namespace services {
		namespace video {

services::video::RenderMode *VideoManager::DEFAULT_RENDER_MODE = new services::video::RenderMode( 640, 480, 16 );

VideoManager::VideoManager( services::video::RenderMode *pRenderMode ) :
   m_oCurrentViewMatrix( primitives::Matrix4x4::IDENTITY ),
   m_oViewPort( 0, 0, pRenderMode->getWidth( ), pRenderMode->getHeight( ) ),
   m_oRenderWindow( pRenderMode, false ),
   m_bMouseVisible( false ),
   m_uiMaxQueueElements( 50 ),
   m_ppRenderQueue( new primitives::RenderPrimitive*[ m_uiMaxQueueElements ] ),
   m_uiNumQueueElements( 0 )
{

}

VideoManager::~VideoManager( ) {
   delete m_pProjection;
}


void VideoManager::setMouseCursorVisibility( bool bVisibility ) {
   m_bMouseVisible = bVisibility;
}

bool VideoManager::isMouseCursorVisible( ) {
   return m_bMouseVisible;
}

void VideoManager::setPerspectiveProjection( const services::video::PerspectiveProjection &rkPerspectiveProjection ) {
   m_oPerspectiveProjection = rkPerspectiveProjection;
   if ( m_pProjection != &rkPerspectiveProjection ) {
      activePerspectiveProjection( );
   } // if
}

void VideoManager::setPerspectiveProjection( float fFOV, float fZNear, float fZFar ) {
   // setup new projection values
   m_oPerspectiveProjection.setFOV( fFOV );
   m_oPerspectiveProjection.setZNear( fZNear );
   m_oPerspectiveProjection.setZFar( fZFar );

   // rebuild projection with the new values
   m_oPerspectiveProjection.buildProjection( *getViewPort( ) );

   // active the new projection
   activePerspectiveProjection( );
}

/*
utils::PerspectiveProjection& VideoManager::getPerspectiveProjectionset( ) {
   return m_oPerspectiveProjection;
}
*/
void VideoManager::setOrthoGraphicProjection( const services::video::OrthographicProjection &rkOrthographicProjection ) {
   m_oOrthographicProjection = rkOrthographicProjection;
   if ( m_pProjection != &rkOrthographicProjection ) {
      activeOrthographicProjection( );
   } // if
}

void VideoManager::setOrthoGraphicProjection( float fLeft, float fRight, float fTop, float fBottom, float fZNear, float fZFar ) {
   // setup new projection values
   m_oOrthographicProjection.setLeft( fLeft );
   m_oOrthographicProjection.setRight( fRight );
   m_oOrthographicProjection.setTop( fTop );
   m_oOrthographicProjection.setBottom( fBottom );
   m_oOrthographicProjection.setZNear( fZNear );
   m_oOrthographicProjection.setZFar( fZFar );

   // rebuild projection with the new values
   m_oOrthographicProjection.buildProjection( *getViewPort( ) );

   // active the new projection
   activeOrthographicProjection( );
}

/*
utils::OrthographicProjection& VideoManager::getOrthoGraphicProjection( ) {
   return m_oOrthographicProjection;
}
*/
void VideoManager::activePerspectiveProjection( ) {
   m_pProjection = &m_oPerspectiveProjection;
   setProjectionMatrix( getProjectionMatrix( ) );
}

void VideoManager::activeOrthographicProjection( ) {
   m_pProjection = &m_oOrthographicProjection;
   setProjectionMatrix( getProjectionMatrix( ) );
}

void VideoManager::toggleProjection( ) {
   if ( m_pProjection == &m_oPerspectiveProjection ) {
      activeOrthographicProjection( );
   } else {
      activePerspectiveProjection( );
   } // if
}

services::video::ViewPort* VideoManager::getViewPort( ) const {
   return const_cast<services::video::ViewPort*>( &m_oViewPort );
}

void VideoManager::setViewPort( const services::video::ViewPort &rkViewPort ) {
   m_oViewPort = rkViewPort;
}

primitives::Matrix4x4* VideoManager::getViewMatrix( ) const {
   return const_cast<primitives::Matrix4x4*>( &m_oCurrentViewMatrix );
}

services::video::RenderWindow* VideoManager::getRenderWindow( ) {
   return &m_oRenderWindow;
}

float VideoManager::getZNear( ) {
   return m_pProjection->getZNear( );
}

float VideoManager::getZFar( ) {
  return m_pProjection->getZFar( );
}

int VideoManager::getWidth( ) {
   return m_oRenderWindow.getCurrentRenderMode( )->getWidth( );
}

int VideoManager::getHeight( ) {
   return m_oRenderWindow.getCurrentRenderMode( )->getHeight( );
}

int VideoManager::getBPP( ) {
   return m_oRenderWindow.getCurrentRenderMode( )->getBPP( );
}

float VideoManager::getFOV( ) {
   return m_oPerspectiveProjection.getFOV( );
}

const primitives::Matrix4x4& VideoManager::getProjectionMatrix( ) {
   return m_pProjection->getProjectionMatrix( );
}

		}; // video
	}; // services
}; // namespace powergine
