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

#include <StarRRT.h>

const double StarRRT::VERY_BIG_NUMBER = 1.0e40;
const double StarRRT::OPTIMAL_FACTOR = -0.9;
const double StarRRT::ROBOT_SPEED = 0.4;

StarRRT::StarRRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries ) :
	RRT( pMap, pStartVertex, pEndVertex, iNumberOfTries ) {
}

StarRRT::~StarRRT() {
}

bool StarRRT::buildNode( ) {
	if ( m_iTryNumber < 0 ) {
		return false;
	} else if ( m_iTryNumber == 0 ) {
		m_iTryNumber = -1;
		return connectGoal( );
	} // else

	m_iTryNumber--;
	m_iBuildNodeTries++;

	Vector3D *pCandidatePoint;
	GraphVertex *pGrowingVertex;

	pCandidatePoint = getRandomFreePoint( );
	pGrowingVertex = findNearestVertex( *pCandidatePoint );
	pCandidatePoint = growVertex( pCandidatePoint, pGrowingVertex );
	if ( !m_pMap->anyCollision( *pCandidatePoint ) &&
		 *pCandidatePoint != pGrowingVertex->getPosition( ) &&
		 canConnect( pCandidatePoint, pGrowingVertex ) ) {
		 GraphVertex *pNewVertex = addVertex( pCandidatePoint );
   		addEdge( pNewVertex, pGrowingVertex);
   		m_mapVertices[ pNewVertex ] = m_mapVertices[ pGrowingVertex ] + 1;

   	} // if
   	return true;
}

GraphVertex* StarRRT::findNearestVertex( const Vector3D &rkPosition ) {
  	std::vector<GraphVertex*> vertices = getGraph( )->getVertices( );
  	GraphVertex *pBest = vertices[ rand( ) % vertices.size( ) ];
  	double dMinDistance = VERY_BIG_NUMBER;
  	unsigned int uiI;
  	for( uiI = 0; uiI <vertices.size( ); uiI++ ) {
  		double dCurrentDistance = ( vertices[ uiI ]->getPosition( ) - rkPosition ).magnitude( ) +
  			OPTIMAL_FACTOR * GROW_DIST * ROBOT_SPEED * m_mapVertices[ vertices[ uiI ] ];
    	if ( dCurrentDistance < dMinDistance ) {
      		dMinDistance = dCurrentDistance;
      		pBest = vertices[ uiI ];
    	} // if
  	} // for
  	return pBest;
}
