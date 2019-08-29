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

#include <iostream>
#include <list>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <cmath>
#include <Map.h>
#include <Renderer.h>
#include <RRTFactory.h>
#include <PerformanceReport.h>

int main(int argc, char* argv[] ) {
	if ( argc > 2 && *argv[1] == 'T' ) {
		PerformanceReport *pReport = new PerformanceReport( std::atoi( argv[2] ) );
		pReport->runTests( );
		return 0;
	} // if

	Vector3D start(1,1,0);
	Vector3D end(45,25,0);

	Map *pMap = new Map( 50, 50, start, end, false );

	//pMap->addObstacle( new Obstacle( Vector3D( 10, 40, 0 ), Vector3D( 30, 0, 0 ) ) );
	//pMap->addObstacle( new Obstacle( Vector3D( 10, 50, 0 ), Vector3D( 30, 41, 0 ) ) );
	//pMap->readMap( );

	pMap->addObstacle( new Obstacle( Vector3D( 20, 50, 0 ), Vector3D( 22, 25, 0 ) ) );
	pMap->addObstacle( new Obstacle( Vector3D( 20, 21, 0 ), Vector3D( 22, 0, 0 ) ) );

	pMap->addObstacle( new Obstacle( Vector3D( 23, 45, 0 ), Vector3D( 25, 5, 0 ) ) );

	GraphVertex *pStartVertex = new GraphVertex( start );
	GraphVertex *pEndVertex = new GraphVertex( end );

	try {
		Renderer render( new RRTFactory( pMap, pStartVertex, pEndVertex, 1500 ) );

		render.run( );
	} catch( std::string &ex ) {
		std::cerr << ex << std::endl;
	} // catch

	return 0;
}
