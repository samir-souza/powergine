// Copyright (c) 2007 Samir Araujo
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

#include <VBRRT.h>

VBRRT::VBRRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries ) :
	RRT( pMap, pStartVertex, pEndVertex, iNumberOfTries )
{
	m_pGraph->removeVertex( m_pStartVertex );
	m_pGraph->addVertex( new GraphVertex( *getRandomFreePoint( ) ) );
}

VBRRT::~VBRRT( ) {
}

bool VBRRT::buildNode( ) {
	if ( m_iTryNumber < 0 ) {
		return false;
	} else if ( m_iTryNumber == 0 ) {
		m_iTryNumber = -1;
		return connectGoal( );
	} // else

	m_iTryNumber--;
	m_iBuildNodeTries++;

	std::vector<Vector3D*> candidatePoints;
	Vector3D *pCandidatePoint;
	GraphVertex *pGrowingVertex;

	candidatePoints = getRandomFreePoints( );

	pGrowingVertex = findNearestVertex( candidatePoints );

	candidatePoints = nearestPoints( pGrowingVertex, candidatePoints );

	pCandidatePoint = middlePoint(candidatePoints);

	pCandidatePoint = growVertex( pCandidatePoint, pGrowingVertex );
	if ( !m_pMap->anyCollision( *pCandidatePoint ) &&
		 *pCandidatePoint != pGrowingVertex->getPosition( ) &&
		 canConnect( pCandidatePoint, pGrowingVertex ) ) {
   		addEdge( addVertex( pCandidatePoint ), pGrowingVertex);
   	} // if
   	return true;
}

std::vector<Vector3D*> VBRRT::getRandomFreePoints( ) {
	std::vector<Vector3D*> pontos;

	for (int i = 0; i < 20; ++i) {
   		pontos.push_back(getRandomFreePoint( ) );
	} // for
	return pontos;
}

GraphVertex* VBRRT::findNearestVertex( std::vector<Vector3D*> points ) {
	// find a vertex closer to the most points
	std::map<GraphVertex*, int> contador;
	GraphVertex *nearest = 0;
	GraphVertex *pResult = 0;

	int max = 0;
	unsigned int uiI;
	for( uiI = 0; uiI < points.size( ); uiI++ ) {
		nearest = RRT::findNearestVertex( *points[ uiI ] );
		contador[nearest]++;
		if ( contador[nearest] > max ) {
			max = contador[nearest];
			pResult = nearest;
		} // if
	} // for
	return pResult;
}

Vector3D* VBRRT::middlePoint(std::vector<Vector3D*> points){
	Vector3D *point = new Vector3D( );
	unsigned int uiI;
	for( uiI = 0; uiI < points.size( ); uiI++ ) {
		*point += *points[ uiI ];
	} // for
	*point /= points.size( );
	return point;
}

bool VBRRT::connectGoal( ) {
	RRT::connectGoal( );

	std::vector<GraphVertex*> vertices = m_pGraph->getVertices( );
	std::sort( vertices.begin( ), vertices.end( ), EdgeCostComparator( m_pStartVertex->getPosition( ) ) );
	bool bConnected = false;
	unsigned int uiI;
	for( uiI = 0; uiI < vertices.size( ) && uiI < MAX_CONNECT_GOAL_TRIES && !bConnected; uiI++ ) {
		if ( canConnect( &m_pStartVertex->getPosition( ), vertices[ uiI ] ) ) {
			addEdge( vertices[ uiI ], m_pStartVertex );
			m_pGraph->addVertex( m_pStartVertex );
			bConnected = true;
		} // if
	} // for
	return bConnected;
}

std::vector<Vector3D*> VBRRT::nearestPoints(GraphVertex *vertex, std::vector<Vector3D*> points){
	std::vector<Vector3D*> vecNearestPoints;
	unsigned int uiI;
	for( uiI = 0; uiI < points.size( ); uiI++ ){
		if ( vertex == RRT::findNearestVertex( *points[ uiI ] ) ) {
			vecNearestPoints.push_back( points[ uiI ] );
		} // if

	} // for
	return vecNearestPoints;
}

