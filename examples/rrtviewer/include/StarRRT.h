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

#ifndef STARRRT_H_
#define STARRRT_H_

#include <RRT.h>

#include <powergine/powergine.h>

#include <vector>

using namespace pg;

/**
 * This implementation
 */
class StarRRT : public RRT {

public:
	static const double OPTIMAL_FACTOR;
	static const double ROBOT_SPEED;
	static const double VERY_BIG_NUMBER;

	StarRRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries );

	virtual ~StarRRT();

	// See RRT::buildNode
	virtual bool buildNode( );

	// See RRT::findNearestVertex
	virtual GraphVertex* findNearestVertex( const Vector3D &rkPosition );

	// See RRT::getName
	virtual const char* getName( ) { return "Star RRT"; };



private:
	std::map<GraphVertex*, int> m_mapVertices;
};

#endif /*STARRRT_H_*/
