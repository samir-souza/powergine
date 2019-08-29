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

#ifndef VBRRT_H_
#define VBRRT_H_

#include <RRT.h>

#include <powergine/powergine.h>

#include <vector>

using namespace pg;


/**
 * This implementation uses Voronoi bias heuristics to grow the
 * tree. It will search for Voronoi areas to chose the next growing
 * point
 */
class VBRRT : public RRT {

public:

	VBRRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries );

	virtual ~VBRRT();

	// See RRT::buildNode
	virtual bool buildNode( );

	// Returns a list of a random free points in the map
	std::vector<Vector3D*> getRandomFreePoints( );

	// See RRT::
	virtual GraphVertex* findNearestVertex( std::vector<Vector3D*> points );

	// Returns a point that states at the middle of all given points
	Vector3D* middlePoint(std::vector<Vector3D*> points);

	// See RRT::getName
	virtual const char* getName( ) { return "Voronoi Bias RRT"; };

	// Connect the start to the end vertex building a path
	virtual bool connectGoal( );

	// Sort the given points by the nearest to the given vertex to the farthest
	std::vector<Vector3D*> nearestPoints(GraphVertex *vertex, std::vector<Vector3D*> points);

	// Update the random points list
	void setRandomPoints(std::vector<Vector3D*> randPoints){
		this->randPoints = randPoints;
	}

	// Return the random points list
	std::vector<Vector3D*> getRandomPoints(){
		return this->randPoints;
	}

protected:

	std::vector<Vector3D*> randPoints;

};

#endif /*VBRRT_H_*/
