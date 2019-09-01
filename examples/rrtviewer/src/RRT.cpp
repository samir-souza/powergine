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

#include <RRT.h>

const float RRT::GROW_DIST = 1.0;
const unsigned int RRT::MAX_CONNECT_GOAL_TRIES = 10;

RRT::RRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries ) :
	m_iStartTryNumber( iNumberOfTries ),
	m_iTryNumber( iNumberOfTries ),
	m_iBuildNodeTries( 0 ),
    m_pGraph( new Graph( ) ),
	m_pMap( pMap ),
	m_pStartVertex( pStartVertex ),
	m_pEndVertex( pEndVertex )
{
	if ( m_pMap->anyCollision( m_pStartVertex->getPosition( ) ) ||
		 m_pMap->anyCollision( m_pEndVertex->getPosition( ) ) ) {
		 	throw std::invalid_argument( "Invalid start and/or end points!" );
	} // if
	m_pGraph->addVertex( m_pStartVertex );
	srand( time(0) );
}

RRT::~RRT( ) {
	std::vector<GraphEdge*> edges;
	std::vector<GraphVertex*> vertices;

	unsigned int uiI;

	edges = m_pStartVertex->getEdges( );
	for( uiI = 0; uiI < edges.size( ); uiI++ ) {
		m_pStartVertex->removeEdge( edges[ uiI ] );
	} // for
	edges = m_pEndVertex->getEdges( );
	for( uiI = 0; uiI < edges.size( ); uiI++ ) {
		m_pEndVertex->removeEdge( edges[ uiI ] );
	} // for

	edges = getGraph( )->getEdges( );
	for( uiI = 0; uiI < edges.size( ); uiI++ ) {
		delete edges[ uiI ];
	} // for

	vertices = getGraph( )->getVertices( );
	for( uiI = 0; uiI < vertices.size( ); uiI++ ) {
		if ( vertices[ uiI ] != m_pStartVertex && vertices[ uiI ] != m_pEndVertex ) {
			delete vertices[ uiI ];
		} // for
	} // for
}

bool RRT::buildNode( ) {
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
   		addEdge( addVertex( pCandidatePoint ), pGrowingVertex);
   		return true;
   	} // if
   	return false;
}

bool RRT::buildTree( ) {
	bool bResult = false;
	while ( m_iTryNumber >= 0 ) {
		buildNode( );
		bResult = true;
	} // while
	return bResult;
} // buildTree

bool RRT::connectGoal( ) {

	std::vector<GraphVertex*> vertices = m_pGraph->getVertices( );
	std::sort( vertices.begin( ), vertices.end( ), EdgeCostComparator( m_pEndVertex->getPosition( ) ) );
	bool bConnected = false;
	unsigned int uiI;
	for( uiI = 0; uiI < vertices.size( ) && uiI < MAX_CONNECT_GOAL_TRIES && !bConnected; uiI++ ) {
		if ( canConnect( &m_pEndVertex->getPosition( ), vertices[ uiI ] ) ) {
			addEdge( vertices[ uiI ], m_pEndVertex );
			m_pGraph->addVertex( m_pEndVertex );
			bConnected = true;
		} // if
	} // for
	return bConnected;
}

GraphVertex* RRT::addVertex( Vector3D *pCandidatePoint ){
	GraphVertex *pNewVertex = new GraphVertex( *pCandidatePoint );
	m_pGraph->addVertex( pNewVertex );
	return pNewVertex;
}

GraphEdge* RRT::addEdge(GraphVertex *pVertex1, GraphVertex *pVertex2 ){

	GraphEdge *pNewEdge = new GraphEdge( pVertex1, pVertex2, ( pVertex1->getPosition() - pVertex2->getPosition( ) ).magnitude( ) );
	pVertex1->addEdge( pNewEdge );
	pVertex2->addEdge( pNewEdge );
	m_pGraph->addEdge( pNewEdge );
	return pNewEdge;
}

Vector3D* RRT::getRandomFreePoint( ){
	double dX, dY;
	dX = rand( ) % (int)m_pMap->getWidth( );
   	dY = rand( ) % (int)m_pMap->getHeight( );
   return new Vector3D( dX, dY, 0 );
}

GraphVertex* RRT::findNearestVertex( GraphVertex *pVertex ){
	return findNearestVertex( pVertex->getPosition( ) );
}

GraphVertex* RRT::findNearestVertex( const Vector3D &rkPosition ) {
	std::vector<GraphVertex*> vertices = m_pGraph->getVertices( );
	std::sort( vertices.begin( ), vertices.end( ), EdgeCostComparator( rkPosition ) );
	return vertices.front( );
}

Vector3D* RRT::growVertex( Vector3D *pCandidatePoint, GraphVertex *pSourceVertex ){
	Vector3D *resposta = new Vector3D( *pCandidatePoint - pSourceVertex->getPosition( ) );
	resposta->normalize( );
	*resposta *= GROW_DIST;
	*resposta += pSourceVertex->getPosition( );
	return resposta;
}

bool RRT::canConnect( Vector3D *pCandidatePoint, Vector3D *pSourcePoint ) {
    Vector3D unitPoint = *pCandidatePoint - *pSourcePoint;
    float fDistance = unitPoint.magnitude( );
    unitPoint.normalize( );

   	Vector3D currentPoint = *pSourcePoint;

	unsigned int iI;
	for ( iI = 0; iI <= fDistance; ++iI ) {
		if( m_pMap->anyCollision( currentPoint ) ){
			return false;
		} else {
			currentPoint += unitPoint;
		} // else
	} // for
    return true;
}

bool RRT::canConnect( Vector3D *pCandidatePoint, GraphVertex *pSourceVertex ){
	return canConnect( pCandidatePoint, new Vector3D( pSourceVertex->getPosition( ) ) );
} // canConnect

void RRT::print( ) {
	std::cout << m_pGraph->toString( );
}

std::vector<GraphEdge*> RRT::findPath( ) {
	return ( new AStarPathFinder( m_pGraph, m_pStartVertex, m_pEndVertex ) )->getPathEdges( );
}
