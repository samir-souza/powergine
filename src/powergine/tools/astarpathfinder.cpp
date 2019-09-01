// Copyright (c) 2004 Samir Araujo
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


#include <powergine/tools/astarpathfinder.h>

namespace powergine {
	namespace tools {

// Class EdgeCostComparator
// It compares two Edges costs to help sorting
//
class EdgeCostComparator {
public:
  	bool operator( )( const primitives::GraphEdge* s1, const primitives::GraphEdge* s2) const {
    	return ( s1->getCost( ) < s2->getCost( ) );
  	} // operator
};

// Class HeuristicVertexCostComparator
// Euclidian Distance Heuristic Implementation 
class HeuristicVertexCostComparator {
public:
	inline HeuristicVertexCostComparator( primitives::GraphVertex *pEndVertex, std::map<const primitives::GraphVertex*,int> *pAccumulatedCost ) : 
		m_pEndVertex( pEndVertex ), m_pAccumulatedCost( pAccumulatedCost ) { } 
  	
  	inline bool operator( )( const primitives::GraphVertex* s1, const primitives::GraphVertex* s2) const {
    	float fDistanceS1ToGoal = ( const_cast<primitives::GraphVertex*>( s1 )->getPosition( ) ^ m_pEndVertex->getPosition( ) ).magnitude( );
    	float fDistanceS2ToGoal = ( const_cast<primitives::GraphVertex*>( s2 )->getPosition( ) ^ m_pEndVertex->getPosition( ) ).magnitude( );
    	
    	
    	return ( (*m_pAccumulatedCost)[ s1 ] + fDistanceS1ToGoal < (*m_pAccumulatedCost)[ s2 ] + fDistanceS2ToGoal );
  	} // operator
private:
  		primitives::GraphVertex *m_pEndVertex;
  		std::map<const primitives::GraphVertex*,int> *m_pAccumulatedCost;
};

// Simple constructor
AStarPathFinder::AStarPathFinder( primitives::Graph *pGraph ) : m_pGraph( pGraph ) {
} // AStarPathFinder

// Custom constructor
AStarPathFinder::AStarPathFinder( primitives::Graph *pGraph, primitives::GraphVertex *pStartVertex, primitives::GraphVertex *pEndVertex ) :	
	m_pStartVertex( pStartVertex ),
	m_pEndVertex( pEndVertex ),
	m_pGraph( pGraph )
 {
	updatePath( );
} //AStarPathFinder

void AStarPathFinder::setStartVertex( primitives::GraphVertex *pVertex ) {
	if ( m_pGraph->vertexBelongsToGraph( pVertex ) ) {
		this->m_pStartVertex = pVertex;
	} // if
} // setStartVertex

void AStarPathFinder::setStartVertex( long lVertexId ) {
	this->m_pStartVertex = m_pGraph->getVertex( lVertexId );
} // setStartVertex

void AStarPathFinder::setEndVertex( primitives::GraphVertex *pVertex ) {
	if ( m_pGraph->vertexBelongsToGraph( pVertex ) ) {
		this->m_pEndVertex = pVertex;
	} // if
} // setEndVertex

void AStarPathFinder::setEndVertex( long lVertexId ) {
	this->m_pEndVertex = m_pGraph->getVertex( lVertexId );
} // setEndVertex

	
void AStarPathFinder::updatePath( ) {
	if ( m_pStartVertex == 0 || m_pEndVertex == 0 ) {
		return;
	} // if

    this->m_vecEdgesPath.clear();
    this->m_vecVerticesPath.clear();
	
	std::map<const primitives::GraphVertex*, int> mapAccumulatedCost;
	std::map<const primitives::GraphVertex*, primitives::GraphEdge*> mapParents;
	
	std::vector<primitives::GraphVertex*> vecClosedVertex;
	std::vector<primitives::GraphVertex*> vecOpenVertex;
	
	vecOpenVertex.push_back( m_pStartVertex );
	mapAccumulatedCost[ m_pStartVertex ] = 0;

	bool goalReached = false;
	
	// main A Star loop
	while( vecOpenVertex.size( ) > 0 && !goalReached ) {

		std::sort( vecOpenVertex.begin( ), vecOpenVertex.end( ), HeuristicVertexCostComparator( m_pEndVertex, &mapAccumulatedCost ) );

		primitives::GraphVertex *pCurrentVertex = vecOpenVertex.front( );
	
		if ( pCurrentVertex == m_pEndVertex ) {
			goalReached = true;
			continue;
		} // if
			
		std::vector<primitives::GraphEdge*> vecAdjacentEdges = pCurrentVertex->getNonLoopEdges( );
		if ( vecAdjacentEdges.begin( ) != vecAdjacentEdges.end( ) ) {
			std::sort( vecAdjacentEdges.begin( ), vecAdjacentEdges.end( ), EdgeCostComparator( ) );
			std::vector<primitives::GraphEdge*>::iterator ppBegin = vecAdjacentEdges.begin( );
			
			for( ; ppBegin != vecAdjacentEdges.end( ) ; ppBegin++ ) {
				int newCost = mapAccumulatedCost[ pCurrentVertex ] + (*ppBegin)->getCost( );
			
				primitives::GraphVertex *pInspectedVertex = (*ppBegin)->getOtherVertex( pCurrentVertex );
				bool isVertexInClosedList = ( vecClosedVertex.end( ) != find ( vecClosedVertex.begin( ), vecClosedVertex.end( ), pInspectedVertex ) );
				bool isVertexInOpenList = ( vecOpenVertex.end( ) != find ( vecOpenVertex.begin( ), vecOpenVertex.end( ), pInspectedVertex ) );
				
				if ( ( isVertexInClosedList || isVertexInOpenList ) && mapAccumulatedCost[ pInspectedVertex ] <= newCost ) {
					continue;					
				} // if

				mapParents[ pInspectedVertex ] = (*ppBegin); 

				mapAccumulatedCost[ pInspectedVertex ] = newCost;

				if ( isVertexInClosedList ) {
					vecClosedVertex.erase( find ( vecClosedVertex.begin( ), vecClosedVertex.end( ), pInspectedVertex ) );
				} // if
				
				if ( !isVertexInOpenList ) {
					vecOpenVertex.push_back( pInspectedVertex );
				} // if

			} // for
		 
		} // if
		
		vecClosedVertex.push_back( pCurrentVertex );
		vecOpenVertex.erase( std::find( vecOpenVertex.begin( ), vecOpenVertex.end( ), pCurrentVertex ) );
	
	} // while
	
	primitives::GraphVertex* lastVertex = m_pEndVertex;
	
	while ( lastVertex != m_pStartVertex && mapParents[ lastVertex ] != 0 ) {
		primitives::GraphEdge* lastEdge = mapParents[ lastVertex ];
		m_vecEdgesPath.insert( m_vecEdgesPath.begin( ), lastEdge );
        m_vecVerticesPath.insert( m_vecVerticesPath.begin(), lastVertex );
		lastVertex = lastEdge->getOtherVertex( lastVertex );
	} // for
	
} // updatePath

std::string AStarPathFinder::toString( ) {
	std::stringstream ssString;
	
	std::vector<primitives::GraphEdge*>::iterator ppBegin = m_vecEdgesPath.begin( );
	
	if ( ppBegin !=  m_vecEdgesPath.end( ) ) {
		ssString << "Shortest path: " << std::endl;
	} else {
		ssString << "Does not exist shortest path!" << std::endl;
	} // else


	for( ; ppBegin != m_vecEdgesPath.end( ) ; ppBegin++ ) {
		ssString << (*ppBegin)->toString( );
	} // for
	
	return ssString.str( );
} // toString


	}; // tools
}; // namespace powergine
