// Copyright (c) 2007 Samir Araujo <samir.araujo@gmail.com>
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

#include <Renderer.h>
#include <GL/gl.h>

Renderer::Renderer( RRTFactory *pRRTFactory ) :
	PowerGineApp( ),
	m_pRRTFactory( pRRTFactory ),
	m_bRunning( true ),
	m_pCamera( 0 ),
	m_pRoom( new BSPTree( ) ),
	m_pRRTree( pRRTFactory->createRRT( ) ),
    m_pForward( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_w ) ),
    m_pBackward( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_s ) ),
    m_pStrafeLeft( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_a ) ),
    m_pStrafeRight( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_d ) ),
    m_pZoomIn( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_z ) ),
    m_pZoomOut( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_x ) ),
    m_pBuildMap( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_m ) ),
    m_pSaveMap( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_k ) ),
    m_pLoadMap( new InputAction( InputAction::EVENT_ON_KBD_KEY_PRESSED, events::KeyEvent::KBD_l ) ),
    m_iCurrentCam( 0 ),
#ifdef WIN32
    m_pFont( new FTGLBitmapFont( "C:\\WINDOWS\\Fonts\\arial.ttf" ) ),
#else
    m_pFont( new FTGLBitmapFont( "data/arial.ttf" ) ),
#endif
    m_bStepByStep( false ),
    m_bUpdateTree( true ),
    m_bLoading( false )
 {
 	m_pElement = new BSPNode( m_pRoom, BSPNode::LEAF );
 	m_pGraphNode = new SceneNode( "Grafo" );
 	m_pElement->addChildNode( m_pGraphNode );

 	m_pMapNode = new SceneNode( "Map" );
 	m_pElement->addChildNode( m_pMapNode );

  	m_pFont->Depth(20);

	int argc = 0;
 	char *argv[] = { };
    Core::get( )->initialize( argc, argv );
    setup( );
}

void Renderer::mapSetup( ) {

   	primitives::Material *pMaterialWall = new Material( "Stone Wall" );
   	pMaterialWall->setEmission( primitives::Color::BLACK );
   	pMaterialWall->setAmbient( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialWall->setDiffuse( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialWall->setSpecular( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialWall->setShininess( 0.6f );
   	pMaterialWall->addTexture( Core::get( )->getVideoManager( )->createTexture(
       	  "data/cubo.png", "data/cubo.png", primitives::Texture::FILTER_LINEAR, true
    ) );

   	primitives::Material *pMaterialFloor = new Material( "Floor" );
   	pMaterialFloor->setEmission( primitives::Color::GREEN );
   	pMaterialFloor->setAmbient( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialFloor->setDiffuse( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialFloor->setSpecular( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialFloor->setShininess( 0.1f );
   	pMaterialFloor->addTexture( Core::get( )->getVideoManager( )->createTexture(
       	  "data/floor.png", "data/floor.png", primitives::Texture::FILTER_TRILINEAR, true
    ) );


	Mesh *pMesh = (Mesh*)m_pMapNode->getRenderEntity( );
	if ( pMesh ) {
		pMesh->setRenderPrimitive( generateObstacles( m_pRRTree->getMap( )->getObstacles( ),pMaterialWall ) );
		pMesh->removeSubMesh( "Bottom Wall" );
		pMesh->removeSubMesh( "Floor" );
	} else {
		pMesh = new Mesh( std::string( "Obstacles" ), generateObstacles( m_pRRTree->getMap( )->getObstacles( ),pMaterialWall ) );
		m_pMapNode->setRenderEntity( pMesh );
	} // else

	std::vector<Obstacle*> vecElements;
	vecElements.push_back( new Obstacle( Vector3D( -2, m_pRRTree->getMap( )->getHeight( ), 0 ), Vector3D(0,0,0 ) ) );
	vecElements.push_back( new Obstacle( Vector3D( m_pRRTree->getMap( )->getWidth( ), m_pRRTree->getMap( )->getHeight( ), 0 ), Vector3D(m_pRRTree->getMap( )->getWidth( )+2,0,0 ) ) );
	vecElements.push_back( new Obstacle( Vector3D( -2, m_pRRTree->getMap( )->getHeight( )+2, 0 ), Vector3D(m_pRRTree->getMap( )->getWidth( )+2,m_pRRTree->getMap( )->getHeight( ),0 ) ) );
	vecElements.push_back( new Obstacle( Vector3D( -2, 0, 0 ), Vector3D(m_pRRTree->getMap( )->getWidth( )+2,-2,0 ) ) );

   	pMesh->addSubMesh( new Mesh( "Bottom Wall", generateObstacles( vecElements, pMaterialWall ) ) );

	vecElements.clear( );
   	vecElements.push_back( new Obstacle( Vector3D( -30.0f, m_pRRTree->getMap( )->getHeight( ) + 30.0f,-2.0f ), Vector3D( m_pRRTree->getMap( )->getWidth( ) + 30.0f, -30.0f, -2.0f ) ) );

   	pMesh->addSubMesh( new Mesh( "Floor", generateObstacles( vecElements, pMaterialFloor ) ) );

}

void Renderer::setup( ) {
	RenderMode *pRenderMode = new RenderMode( 800, 600, 24 );
	Core::get( )->createVideoManager( pRenderMode, VideoManager::MANAGER_OPENGL );
   	Core::get( )->getVideoManager( )->setMouseCursorVisibility( false );
   	Core::get( )->getInputManager( )->addKeyListener( this );

   	Core::get( )->getVideoManager( )->setPerspectiveProjection( 60.0f, 10.0f, 15000.0f );
//	Core::get( )->getVideoManager( )->getRenderWindow( )->getProperties( )->toggleProperty( VideoProperties::FULLSCREEN );
//   	Core::get( )->getVideoManager( )->refreshVideoMode( );


   Core::get( )->getInputManager( )->addInputAction( m_pForward );
   Core::get( )->getInputManager( )->addInputAction( m_pBackward );
   Core::get( )->getInputManager( )->addInputAction( m_pStrafeLeft );
   Core::get( )->getInputManager( )->addInputAction( m_pStrafeRight );
   Core::get( )->getInputManager( )->addInputAction( m_pZoomIn );
   Core::get( )->getInputManager( )->addInputAction( m_pZoomOut );
   Core::get( )->getInputManager( )->addInputAction( m_pBuildMap );
   Core::get( )->getInputManager( )->addInputAction( m_pSaveMap );
   Core::get( )->getInputManager( )->addInputAction( m_pLoadMap );

   m_pRoom->getRootNode( )->setLeftChild( m_pElement );

   Light *pLight = new Light( Light::AMBIENT );
   pLight->setAmbient( Color( 0.0, 0.0, 0.0, 1.0 ) );
   pLight->setDiffuse( Color( 1.0, 1.0, 1.0, 1.0 ) );
   pLight->setSpecular( Color( 1.0, 1.0, 1.0, 1.0 ) );
   Core::get( )->getVideoManager( )->addLight( pLight );

   	primitives::Material *pMaterialSky = new Material( "Sky Dome" );
   	pMaterialSky->setEmission( primitives::Color::GREEN );
   	pMaterialSky->setAmbient( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialSky->setDiffuse( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialSky->setSpecular( primitives::Color( 0.6f, 0.6f, 0.6f, 1.0 ) );
   	pMaterialSky->setShininess( 0.1f );
   	pMaterialSky->addTexture( Core::get( )->getVideoManager( )->createTexture(
       	  "data/sky.png", "data/sky.png", primitives::Texture::FILTER_TRILINEAR, true
    ) );

   SkyDome *pSkyDome = new SkyDome( pMaterialSky );
   SceneNode *pSkyNode = new SceneNode( "Floor" );
   pSkyNode->setRenderEntity( pSkyDome );
   m_pElement->addChildNode( pSkyNode );

   mapSetup( );

   Vector3D oMapCenter( m_pRRTree->getMap( )->getWidth() / 2, m_pRRTree->getMap( )->getHeight( ) / 2, 0 );

   m_pCamera = new Camera( "free cam" );
   m_pCamera->setRoom( m_pRoom );
   m_pCamera->doTranslation( Vector3D( m_pRRTree->getMap( )->getWidth() / 2, m_pRRTree->getMap( )->getHeight( ) / 2, 50.0f ) );
   m_pCamera->setActive( );
   m_vecCameras.push_back( m_pCamera );

   Camera *pCamera = new Camera( "right cam" );
   pCamera->setRoom( m_pRoom );
   pCamera->doTranslation( Vector3D( m_pRRTree->getMap( )->getWidth()+6, m_pRRTree->getMap( )->getHeight( )+6, 15.0f ) );
   pCamera->doRotation( Quaternion( -65.0f, Vector3D( 1.0f, 0, 0 ) ) );
   pCamera->doRotation( Quaternion( -135.0f, Vector3D( 0, 0, 1.0f ) ) );
   m_vecCameras.push_back( pCamera );

}

Renderer::~Renderer( ) {
  	delete m_pForward;
    delete m_pBackward;
    delete m_pStrafeLeft;
    delete m_pStrafeRight;
    delete m_pZoomIn;
    delete m_pZoomOut;
}

void Renderer::pressed( events::KeyEvent* pEvent ) {
	if( pEvent->getCode( ) == events::KeyEvent::KBD_q ) {
  		m_bRunning = false;
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_i && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		m_bStepByStep = !m_bStepByStep;
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_1 && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
   	  	m_iCurrentCam = ( m_iCurrentCam == 0 ) ? m_vecCameras.size( ) - 1 : m_iCurrentCam--;
   	  	m_vecCameras[ m_iCurrentCam ]->setActive( );
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_2 && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		m_iCurrentCam = ( ( m_iCurrentCam + 1 ) == (int)m_vecCameras.size( ) ) ? 0 : m_iCurrentCam++;
		m_vecCameras[ m_iCurrentCam ]->setActive( );
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_f && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		delete m_pRRTree;
   	  	m_pRRTree = m_pRRTFactory->createRRT( m_pRRTFactory->previousType( ) );
   	  	m_bLoading = true;
   	  	m_bUpdateTree = true;
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_g && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		delete m_pRRTree;
   	  	m_pRRTree = m_pRRTFactory->createRRT( m_pRRTFactory->nextType( ) );
   	  	m_bLoading = true;
   	  	m_bUpdateTree = true;
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_r && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		delete m_pRRTree;
   	  	m_pRRTree = m_pRRTFactory->createRRT( m_pRRTFactory->currentType( ) );
   	  	m_bLoading = true;
   	  	m_bUpdateTree = true;
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_m && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		m_pRRTree->getMap( )->randomMap( );
		mapSetup( );
		delete m_pRRTree;
   	  	m_pRRTree = m_pRRTFactory->createRRT( m_pRRTFactory->currentType( ) );
   	  	m_bLoading = true;
   	  	m_bUpdateTree = true;
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_k && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		m_pRRTree->getMap( )->writeMap( );
	} else if( pEvent->getCode( ) == events::KeyEvent::KBD_l && pEvent->getState( ) == KeyEvent::KEY_PRESSED ) {
		m_pRRTree->getMap( )->readMap( );
		mapSetup( );
		delete m_pRRTree;
   	  	m_pRRTree = m_pRRTFactory->createRRT( m_pRRTFactory->currentType( ) );
   	  	m_bLoading = true;
   	  	m_bUpdateTree = true;
	} // else if
};

void Renderer::renderOSD( ) {
	glDisable( GL_TEXTURE_2D);
	glMatrixMode( GL_PROJECTION );
	glLoadIdentity( );

	glOrtho( 0, 800, 600, 0, -1, 1 );
	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity( );
	glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );
	glRasterPos2i( 20, 50 );
	m_pFont->FaceSize( 14 );
	m_pFont->Render( "Commands:" );
	m_pFont->FaceSize( 12 );
	glRasterPos2i( 20, 65 );
	m_pFont->Render( "a = map left" );
	glRasterPos2i( 20, 75 );
	m_pFont->Render( "d = map right" );
	glRasterPos2i( 20, 85 );
	m_pFont->Render( "w = map up" );
	glRasterPos2i( 20, 95 );
	m_pFont->Render( "s = map down" );
	glRasterPos2i( 20, 105 );
	m_pFont->Render( "z = zoom in" );
	glRasterPos2i( 20, 115 );
	m_pFont->Render( "x = zoom out" );
	glRasterPos2i( 20, 125 );
	m_pFont->Render( "q = quit" );
	glRasterPos2i( 20, 135 );
	m_pFont->Render( "r = reset" );
	glRasterPos2i( 20, 145 );
	m_pFont->Render( "f = previous algorithm" );
	glRasterPos2i( 20, 155 );
	m_pFont->Render( "g = next algorithm" );
	glRasterPos2i( 20, 165 );
	m_pFont->Render( "i = toggle step-by-step" );
	glRasterPos2i( 20, 175 );
	m_pFont->Render( "m = rebuild map" );
	glRasterPos2i( 20, 185 );
	m_pFont->Render( "k = save map" );
	glRasterPos2i( 20, 195 );
	m_pFont->Render( "l = load map" );
	glRasterPos2i( 20, 205 );
	m_pFont->Render( "1/2 = change camera" );

	glRasterPos2i( 610, 50 );
	( m_bStepByStep ) ? m_pFont->Render( "Mode Step By Step" ) : m_pFont->Render( "Mode full tree" );

	glRasterPos2i( 610, 60 );
	m_pFont->Render( m_pRRTree->getName( ) );

	if ( m_bLoading ) {
		glRasterPos2i( 300, 310 );
		m_pFont->FaceSize( 30 );
		m_pFont->Render( "Building tree..." );

		glColor3f( 0, 0, 0 );
		glBegin( GL_QUADS );
			glVertex3f( 270, 280, 0 );
			glVertex3f( 270, 320, 0 );
			glVertex3f( 520, 320, 0 );
			glVertex3f( 520, 280, 0 );
		glEnd( );
		m_bLoading = false;
	} // if

   	Core::get( )->getVideoManager( )->setPerspectiveProjection( 60.0f, 10.0f, 15000.0f );

}

void Renderer::run( ) {
	Core::get( )->getVideoManager( )->openWindow( );
   	float fFator = 0.5;
   	clock_t oldTime = clock( );

	while ( m_bRunning ) {
    	Core::get( )->getVideoManager( )->clear( VideoManager::COLOR_BUFFER|VideoManager::DEPTH_BUFFER, Color::BLACK );
      	Core::get( )->getVideoManager( )->beginFrame( *Camera::getActive( )->getTransformation( ) );

		if ( m_bUpdateTree ) {
			Mesh *pRenderEdges = new Mesh( "edges", this->generateEdges( ) );
			Mesh *pRenderVertices = new Mesh( "vertices", this->generateVertices( ) );
			pRenderVertices->addSubMesh( pRenderEdges );
			m_pGraphNode->setRenderEntity( pRenderVertices );
			m_bUpdateTree = false;
		} // if

		Camera::getActive( )->render( );

		renderOSD( );

		Core::get( )->getVideoManager( )->endFrame( );
		Core::get( )->getVideoManager( )->flipBuffer( );
		//m_pRRTree->print( );

		if ( m_bStepByStep ) {
			if ( ( clock( ) - oldTime ) >= 500 ) {
	   	  		oldTime = clock( );
				m_bUpdateTree = m_pRRTree->buildNode( );
			} // if
		} else if ( m_pRRTree->buildTree( ) ) {
			m_bUpdateTree = true;
		} // else if

	   	if ( m_pCamera == Camera::getActive( ) ) {
		    if ( m_pForward->isActive( ) ) {
		       m_pCamera->doTranslation( Vector3D( 0.0f, -fFator, 0.0 ) );
		    } // if
		    if ( m_pBackward->isActive( ) ) {
		       m_pCamera->doTranslation( Vector3D( 0.0f, fFator, 0.0 ) );
		    } // if
		    if ( m_pStrafeLeft->isActive( ) ) {
		       m_pCamera->doTranslation( Vector3D( fFator, 0.0f, 0.0 ) );
		    } // if
		    if ( m_pStrafeRight->isActive( ) ) {
		       m_pCamera->doTranslation( Vector3D( -fFator, 0.0f, 0.0 ) );
		    } // if
		    if ( m_pZoomIn->isActive( ) ) {
		       m_pCamera->doTranslation( Vector3D( 0.0f, 0.0f, -fFator ) );
		    } // if
		    if ( m_pZoomOut->isActive( ) ) {
		       m_pCamera->doTranslation( Vector3D( 0.0f, 0.0f, fFator ) );
		    } // if
	   	} // if

		Core::get( )->getInputManager( )->processInput( );

	} // while

//   Core::get( )->getVideoManager( )->getRenderWindow( )->getProperties( )->toggleProperty( VideoProperties::FULLSCREEN );
//   Core::get( )->getVideoManager( )->refreshVideoMode( );


   Core::get( )->getVideoManager( )->closeWindow( );


} // renderizador


RenderPrimitive* Renderer::generateVertices(  ) {
	unsigned int uiNumPolygons = m_pRRTree->getGraph( )->getVertices( ).size( );
	if ( uiNumPolygons == 0 ) {
		return 0;
	} // if

    primitives::RenderPrimitive *pRenderMesh = new primitives::RenderPrimitive(
        primitives::RenderPrimitive::MODE_QUADS,
        primitives::RenderPrimitive::POLYGON_QUAD
    );

      primitives::VertexDiffuseBuffer *pVertexHandler = new primitives::VertexDiffuseBuffer( uiNumPolygons * 4 );
      primitives::QuadBuffer *pPolygonHandler = new primitives::QuadBuffer( uiNumPolygons );

      primitives::VertexBuffer *pVertexBuffer =
         Core::get( )->getVideoManager( )->createVertexBuffer(
            pVertexHandler->getNumElements( ),
            primitives::VertexDiffuse::s_oFormat,
            pVertexHandler->getData( )
         );

      primitives::PolygonBuffer *pPolygonBuffer =
         Core::get( )->getVideoManager( )->createPolygonBuffer(
            pPolygonHandler->getNumElements( ),
            primitives::Quad::getNumVertices( ),
            pPolygonHandler->getData( )
         );

   	  pRenderMesh->setVertexBuffer( pVertexBuffer );
   	  pRenderMesh->setPolygonBuffer( pPolygonBuffer );


      primitives::VertexDiffuseBuffer::iterator *pVIterator = pVertexHandler->makeIterator( );
      primitives::QuadBuffer::iterator *pPIterator = pPolygonHandler->makeIterator( );


      int iVertexCounter = 0;
      for ( unsigned int uiJ = 0 ; uiJ < uiNumPolygons; uiJ++ ) {

         pVIterator->getCurrent( ).setAll(
            (m_pRRTree->getGraph( )->getVertices( )[uiJ])->getPosition( ) + Vector3D( -0.08, -0.08, 0.0 ), Color::RED
         );
         pVIterator->goNext( );
         pVIterator->getCurrent( ).setAll(
            (m_pRRTree->getGraph( )->getVertices( )[uiJ])->getPosition( ) + Vector3D( -0.08, 0.08, 0.0 ), Color::RED
         );
         pVIterator->goNext( );
         pVIterator->getCurrent( ).setAll(
            (m_pRRTree->getGraph( )->getVertices( )[uiJ])->getPosition( ) + Vector3D( 0.08, 0.08, 0.0 ), Color::RED
         );
         pVIterator->goNext( );
         pVIterator->getCurrent( ).setAll(
            (m_pRRTree->getGraph( )->getVertices( )[uiJ])->getPosition( ) + Vector3D( 0.08, -0.08, 0.0 ), Color::RED
         );
         pVIterator->goNext( );

         pPIterator->getCurrent( ).setAll( iVertexCounter, iVertexCounter+1, iVertexCounter+2, iVertexCounter+3 );
         pPIterator->goNext( );
         iVertexCounter += 4;
      } // for

	return pRenderMesh;

} // generateVertices

RenderPrimitive* Renderer::generateEdges( ) {
	std::vector<GraphEdge*> edges = m_pRRTree->getGraph( )->getEdges( );
	unsigned int uiNumPolygons = edges.size( );
	if ( uiNumPolygons == 0 ) {
		return 0;
	} // if


    primitives::RenderPrimitive *pRenderMesh = new primitives::RenderPrimitive(
        primitives::RenderPrimitive::MODE_LINES,
        primitives::RenderPrimitive::POLYGON_LINE
    );

    pRenderMesh->setEdgeLinesSize( 2.0 );
      primitives::VertexDiffuseBuffer *pVertexHandler = new primitives::VertexDiffuseBuffer( uiNumPolygons * 2 );
      primitives::LineBuffer *pPolygonHandler = new primitives::LineBuffer( uiNumPolygons );

      primitives::VertexBuffer *pVertexBuffer =
         Core::get( )->getVideoManager( )->createVertexBuffer(
            pVertexHandler->getNumElements( ),
            primitives::VertexDiffuse::s_oFormat,
            pVertexHandler->getData( )
         );

      primitives::PolygonBuffer *pPolygonBuffer =
         Core::get( )->getVideoManager( )->createPolygonBuffer(
            pPolygonHandler->getNumElements( ),
            primitives::Line::getNumVertices( ),
            pPolygonHandler->getData( )
         );

   	  pRenderMesh->setVertexBuffer( pVertexBuffer );
   	  pRenderMesh->setPolygonBuffer( pPolygonBuffer );


      primitives::VertexDiffuseBuffer::iterator *pVIterator = pVertexHandler->makeIterator( );
      primitives::LineBuffer::iterator *pPIterator = pPolygonHandler->makeIterator( );



      std::vector<GraphEdge*> caminho = m_pRRTree->findPath( );

      int iVertexCounter = 0;
      for ( unsigned int uiJ = 0 ; uiJ < uiNumPolygons; uiJ++ ) {

         pVIterator->getCurrent( ).setAll(
            (edges[uiJ])->getVertex1( )->getPosition( ),
            ( std::find( caminho.begin( ), caminho.end( ), (edges[uiJ]) ) != caminho.end( ) ) ? Color::GREEN : Color::WHITE
         );
         pVIterator->goNext( );

         pVIterator->getCurrent( ).setAll(
            (edges[uiJ])->getVertex2( )->getPosition( ),
            ( std::find( caminho.begin( ), caminho.end( ), (edges[uiJ]) ) != caminho.end( ) ) ? Color::GREEN : Color::WHITE
         );
         pVIterator->goNext( );

         pPIterator->getCurrent( ).setAll( iVertexCounter, iVertexCounter+1 );
         pPIterator->goNext( );

         iVertexCounter += 2;
      } // for

	return pRenderMesh;

} // generateEdges

RenderPrimitive* Renderer::generateObstacles( std::vector<Obstacle*> obstacles, Material *pMaterial ) {

   primitives::RenderPrimitive *pRenderMesh = new primitives::RenderPrimitive(
     primitives::RenderPrimitive::MODE_QUADS,
     primitives::RenderPrimitive::POLYGON_QUAD
   );
   pRenderMesh->setMaterial( pMaterial );

   primitives::VertexTextureNormalBuffer *pVertexHandler = new primitives::VertexTextureNormalBuffer( obstacles.size( ) * 24 );
   primitives::QuadBuffer *pPolygonHandler = new primitives::QuadBuffer( obstacles.size( ) * 6 );

   primitives::VertexBuffer *pVertexBuffer =
      Core::get( )->getVideoManager( )->createVertexBuffer(
        pVertexHandler->getNumElements( ),
        primitives::VertexTextureNormal::s_oFormat,
        pVertexHandler->getData( )
     );

   primitives::PolygonBuffer *pPolygonBuffer =
     Core::get( )->getVideoManager( )->createPolygonBuffer(
        pPolygonHandler->getNumElements( ),
        primitives::Quad::getNumVertices( ),
        pPolygonHandler->getData( )
     );

   pRenderMesh->setVertexBuffer( pVertexBuffer );
   pRenderMesh->setPolygonBuffer( pPolygonBuffer );

   primitives::VertexTextureNormalBuffer::iterator *pVIterator = pVertexHandler->makeIterator( );
   primitives::QuadBuffer::iterator *pPIterator = pPolygonHandler->makeIterator( );

	Vector3D oHigh( 0, 0, 2 );
    Vector3D oFNormal( 0, 0, -1.0f );
    Vector3D oNNormal( 0, 0, 1.0f );
    Vector3D oLNormal( -1.0f, 0, 0 );
    Vector3D oRNormal( 1.0f, 0, 0 );
    Vector3D oTNormal( 0, 1.0f, 0 );
    Vector3D oBNormal( 0, -1.0f, 0 );

	float repeatV, repeatH;
	unsigned int uiI;
	int iNV = 0;
	for ( uiI = 0; uiI < obstacles.size( ); uiI++ ) {
	   Obstacle *o = obstacles[ uiI ];
	   Vector3D oWidth( o->getWidth( ), 0, 0 );
	   Vector3D oHeight( 0, o->getHeight( ), 0 );

	   repeatH = (float)o->getWidth( ) / 10.0f;
	   repeatV = (float)o->getHeight( ) / 10.0f;

	   Vector3D oP1F = o->getUpperLeftCorner( ) - oHeight;
	   Vector3D oP2F = o->getUpperLeftCorner( );
	   Vector3D oP3F = o->getUpperLeftCorner( ) + oWidth;
	   Vector3D oP4F = o->getUpperLeftCorner( ) + oWidth - oHeight;

	   Vector3D oP1N = oP1F + oHigh;
	   Vector3D oP2N = oP2F + oHigh;
	   Vector3D oP3N = oP3F + oHigh;
	   Vector3D oP4N = oP4F + oHigh;

	   Vector3D oP1L = oP1F;
	   Vector3D oP2L = oP2F;
	   Vector3D oP3L = oP2N;
	   Vector3D oP4L = oP1N;

	   Vector3D oP1R = oP4N;
	   Vector3D oP2R = oP3N;
	   Vector3D oP3R = oP3F;
	   Vector3D oP4R = oP4F;

	   Vector3D oP1T = oP2N;
	   Vector3D oP2T = oP2F;
	   Vector3D oP3T = oP3F;
	   Vector3D oP4T = oP3N;

	   Vector3D oP1B = oP1F;
	   Vector3D oP2B = oP1N;
	   Vector3D oP3B = oP4N;
	   Vector3D oP4B = oP4F;

	   // Far
	   pVIterator->getCurrent( ).setAll( oP1F, TextCoords( 0, 0 ), oFNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP2F, TextCoords( 0, repeatV ), oFNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP3F, TextCoords( repeatH, repeatV ), oFNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP4F, TextCoords( repeatH, 0 ), oFNormal ); pVIterator->goNext( );

	   // Near
	   pVIterator->getCurrent( ).setAll( oP1N, TextCoords( 0, 0 ), oNNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP2N, TextCoords( 0, repeatV ), oNNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP3N, TextCoords( repeatH, repeatV ), oNNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP4N, TextCoords( repeatH, 0 ), oNNormal ); pVIterator->goNext( );

		// Left
	   pVIterator->getCurrent( ).setAll( oP1L, TextCoords( 0, 0 ), oLNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP2L, TextCoords( 0, repeatV ), oLNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP3L, TextCoords( repeatH, repeatV ), oLNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP4L, TextCoords( repeatH, 0 ), oLNormal ); pVIterator->goNext( );

		// Right
	   pVIterator->getCurrent( ).setAll( oP1R, TextCoords( 0, 0 ), oRNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP2R, TextCoords( 0, repeatV ), oRNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP3R, TextCoords( repeatH, repeatV ), oRNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP4R, TextCoords( repeatH, 0 ), oRNormal ); pVIterator->goNext( );

		// Top
	   pVIterator->getCurrent( ).setAll( oP1T, TextCoords( 0, 0 ), oTNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP2T, TextCoords( 0, repeatV ), oTNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP3T, TextCoords( repeatH, repeatV ), oTNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP4T, TextCoords( repeatH, 0 ), oTNormal ); pVIterator->goNext( );

		// Bottom
	   pVIterator->getCurrent( ).setAll( oP1B, TextCoords( 0, 0 ), oBNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP2B, TextCoords( 0, repeatV ), oBNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP3B, TextCoords( repeatH, repeatV ), oBNormal ); pVIterator->goNext( );
	   pVIterator->getCurrent( ).setAll( oP4B, TextCoords( repeatH, 0 ), oBNormal ); pVIterator->goNext( );

	   pPIterator->getCurrent( ).setAll( iNV, iNV+1, iNV+2, iNV+3 );  pPIterator->goNext( );
	   pPIterator->getCurrent( ).setAll( iNV+4, iNV+5, iNV+6, iNV+7 );  pPIterator->goNext( );
	   pPIterator->getCurrent( ).setAll( iNV+8, iNV+9, iNV+10, iNV+11 );  pPIterator->goNext( );
	   pPIterator->getCurrent( ).setAll( iNV+12, iNV+13, iNV+14, iNV+15 );  pPIterator->goNext( );
	   pPIterator->getCurrent( ).setAll( iNV+16, iNV+17, iNV+18, iNV+19 );  pPIterator->goNext( );
	   pPIterator->getCurrent( ).setAll( iNV+20, iNV+21, iNV+22, iNV+23 );  pPIterator->goNext( );

		iNV += 24;
	} // for

	return pRenderMesh;
}
