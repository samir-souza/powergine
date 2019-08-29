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

#ifndef VIDEOMANAGER_H
#define VIDEOMANAGER_H

#include <string>
#include <queue>
#include <powergine/primitives/renderprimitive.h>
#include <powergine/primitives/matrix4x4.h>
#include <powergine/primitives/triangle.h>
#include <powergine/primitives/vertex.h>
#include <powergine/services/video/projection.h>
#include <powergine/services/video/perspectiveprojection.h>
#include <powergine/services/video/orthographicprojection.h>
#include <powergine/services/video/viewport.h>
#include <powergine/services/video/renderwindow.h>
#include <powergine/services/video/rendermode.h>
#include <powergine/sceneobjects/light.h>


namespace powergine {
	namespace services {
		namespace video {

		/**
		 * This class is responsible for managing all the operations
		 * involving rendering and video configuration
		 */
		class VideoManager {

		public:
		   enum BUFFER {
			  COLOR_BUFFER    = 1, // Color buffer (framebuffer, pixelbuffer)
			  DEPTH_BUFFER    = 2, // Depth z buffer
			  STENCIL_BUFFER  = 4  // Stencil Buffer
		   };

		   enum MANAGER_TYPE {
			  MANAGER_OPENGL,
			  MANAGER_DIRECT3D,
			  MANAGER_SOFTWARE
		   };

		   VideoManager( services::video::RenderMode *pRenderMode );

		   virtual ~VideoManager( );

		   // Hide or show the mouse arrow on screen
		   virtual void setMouseCursorVisibility( bool bVisibility );

		   // Check if the mouse arrow is hidden or not
		   bool isMouseCursorVisible( );

		   // Update the Projection Matrix using to transform the scene graph objects
		   virtual void setProjectionMatrix( const primitives::Matrix4x4 &rkMatrix ) = 0;

		   // Update the Perspective projection info
		   void setPerspectiveProjection( const services::video::PerspectiveProjection &rkPerspectiveProjection );

		   // Update the Perspective projection info
		   void setPerspectiveProjection( float fFOV, float fZNear, float fZFar );

		   // Updates the Orthographic projection
		   void setOrthoGraphicProjection( const services::video::OrthographicProjection &rkOrthographicProjection );

		   // Updates the Orthographic projection
		   void setOrthoGraphicProjection( float fLeft, float fRight, float fTop, float fBottom, float fZNear, float fZFar );

		   // Toggles the projection type between Perspective and Projection
		   void toggleProjection( );

		   // Activates the Perspective projection
		   void activePerspectiveProjection( );

		   // Activates the orthographic projection
		   void activeOrthographicProjection( );

		   // Retrieve the current viewport
		   services::video::ViewPort* getViewPort( ) const;

		   // Update the current viewport
		   void setViewPort( const services::video::ViewPort &rkViewPort);

		   // Returns the current view matrix
		   primitives::Matrix4x4* getViewMatrix( ) const;

		   // Returns the projection Matrix
		   const primitives::Matrix4x4& getProjectionMatrix( );

		   // Returns the current render window
		   services::video::RenderWindow* getRenderWindow( );

		   // Returns the distance of the near and far planes from the origin
		   float getZNear( );
		   float getZFar( );

		   // Returns the FOV angle used to configure the Frustum
		   float getFOV( );

		   // Returns the width and height of the screen
		   int getWidth( );
		   int getHeight( );

		   // Returns the number of bits per pixels of the rendering screen
		   int getBPP( );

		   // Initialize the service
		   virtual void initialize( ) = 0;

		   // Open a new window
		   virtual bool openWindow( ) = 0;
		   virtual bool openWindow( const services::video::RenderWindow &rkRenderWindow ) = 0;

		   // Close the current window
		   virtual void closeWindow( ) = 0;

		   // Starts rendering a frame. It traverses the graph scene and render all
		   // objects of the scene in a given frame
		   virtual void beginFrame( const primitives::Matrix4x4 &rkProjectionMatrix ) = 0;

		   // Finishes rendering a frame
		   virtual void endFrame( ) = 0;

		   // Change the buffer that will be rendered. Doublebuffer option
		   virtual void flipBuffer( ) = 0;

		   // Render a given primitive
		   virtual void render( const primitives::RenderPrimitive &rkRenderPrimitive) = 0;

		   // Clear the screen
		   virtual void clear( unsigned int uiBufferBits, const primitives::Color &rkColor, float fDepthValue = 1.0f, unsigned int uiStencilValue = 0 ) = 0;

		   // Add a light to the environment
		   virtual void addLight( sceneobjects::Light *pLight) = 0;

		   // Multiplies the current active matrix (Modelview, Projection or Orthographic)
		   // by another one
		   virtual void multMatrix( const primitives::Matrix4x4 &rkMatrix ) = 0;

		   // Reset the current active matrix (Modelview, Projection or Orthographic)
		   // and loads the values of the given one
		   virtual void loadMatrix( const primitives::Matrix4x4 &rkMatrix ) = 0;

		   // Refresh the windows with a new video mode configuration
		   virtual void refreshVideoMode( ) = 0;

		   // Creates a new vertex buffer
		   virtual primitives::VertexBuffer* createVertexBuffer( int iNumVertices, const primitives::VertexFormat &rkFormat, unsigned char *pucData = 0 ) = 0;

		   // Creates a new polygon buffer
		   virtual primitives::PolygonBuffer* createPolygonBuffer( int iNumPolygons, int iNumPolygonVertices, unsigned char *pucData = 0 ) = 0;

		   // Creates a new texture
		   virtual primitives::Texture* createTexture( const std::string &rkstrTextureName, primitives::Image *pImage, primitives::Texture::FILTER eFilter, bool bRepeat = false ) = 0;
		   virtual primitives::Texture* createTexture( const std::string &rkstrTextureName, const std::string &rkstrFileName, primitives::Texture::FILTER eFilter, bool bRepeat = false ) = 0;

		   // Returns an already registered texture
		   virtual primitives::Texture* getTexture( const std::string &rkstrTextureName ) = 0;

		   // Constant which defines a default render mode
		   static services::video::RenderMode *DEFAULT_RENDER_MODE;

		protected:

		   primitives::Matrix4x4 m_oCurrentViewMatrix;
		   services::video::Projection *m_pProjection;
		   services::video::PerspectiveProjection m_oPerspectiveProjection;
		   services::video::OrthographicProjection m_oOrthographicProjection;
		   services::video::ViewPort m_oViewPort;
		   services::video::RenderWindow m_oRenderWindow;
		   bool m_bMouseVisible;
		   unsigned int  m_uiMaxQueueElements;
		   primitives::RenderPrimitive** m_ppRenderQueue;
		   unsigned int  m_uiNumQueueElements;
		}; // RenderManager

		}; // video
	}; // services
}; // namespace powergine

#endif //RENDERMANAGER_H
