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

#ifndef RENDERIZADOR_H_
#define RENDERIZADOR_H_

#include <powergine/powergine.h>
#include <powergine/utils/powergineapp.h>
#include <RRTFactory.h>
#include <FTGL/ftgl.h>

using namespace pg;

/**
 * This application uses the PowerGine resources
 * to render a map full of obstacles. That map will be used as
 * a testbed for RRTs algorightms
 */
class Renderer : public PowerGineApp {
public:

	// Receives a RRT factory as argument
	Renderer( RRTFactory *pRRTFactory );

	virtual ~Renderer( );

	// Setup the application
	void setup( );

	// Start running the application
	void run( );

	// Render on screen information
	void renderOSD( );

	// Prepare the primitives which represents the environment
	RenderPrimitive* generateVertices( );
	RenderPrimitive* generateEdges( );
	RenderPrimitive* generateObstacles( std::vector<Obstacle*> obstacles, Material *pMaterial );

	// Key pressed event handler
	void pressed( events::KeyEvent* pEvent );

	// Key released event handler
    void released( events::KeyEvent *pEvent ) { };

private:
	RRTFactory *m_pRRTFactory;
	bool m_bRunning;
	std::vector<Camera*> m_vecCameras;
	Camera* m_pCamera;
	BSPTree *m_pRoom;
	RRT *m_pRRTree;
	BSPNode *m_pElement;
	SceneNode *m_pGraphNode;
	SceneNode *m_pMapNode;
  	InputAction *m_pForward;
    InputAction *m_pBackward;
    InputAction *m_pStrafeLeft;
    InputAction *m_pStrafeRight;
    InputAction *m_pZoomIn;
    InputAction *m_pZoomOut;
    InputAction *m_pBuildMap;
    InputAction *m_pSaveMap;
    InputAction *m_pLoadMap;
    int m_iCurrentCam;
	void mapSetup( );
	FTFont *m_pFont;
	bool m_bStepByStep;
	bool m_bUpdateTree;
	bool m_bLoading;
};

#endif /*RENDERIZADOR_H_*/
