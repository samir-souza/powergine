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


#include <powergine/primitives/graph.h>
#include <limits>

namespace powergine {
   namespace primitives {


void Graph::addVertex( GraphVertex *pVertex ) {
	if ( !vertexBelongsToGraph( pVertex ) ) { 
    	m_vecVertices.push_back( pVertex );
	} // if
}

GraphVertex* Graph::addVertex( const Vector3D & rkPosition ) {
    GraphVertex *pVertex = NULL;
    if ( !this->positionHasVertex( rkPosition ) ) {
        pVertex = new GraphVertex( rkPosition );
    	m_vecVertices.push_back( pVertex );
    } else {
        pVertex = this->getVertexByPosition( rkPosition ); 
    } // else
    return pVertex;
}

void Graph::removeVertex( GraphVertex *pVertex ) {
	removeVertex( pVertex->getId( ) );
}

void Graph::removeVertex( long lVertexId ) {
	std::vector< GraphVertex* >::iterator ppBegin = this->m_vecVertices.begin( );
	std::vector< GraphVertex* >::iterator ppEnd = this->m_vecVertices.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *ppBegin )->getId( ) == lVertexId ) {
      	m_vecVertices.erase( ppBegin );
      } // if            
      ++ppBegin;
    } // while 
}


void Graph::addEdge( GraphEdge *pEdge ) {
	if ( !edgeBelongsToGraph( pEdge ) ) { 
    	m_vecEdges.push_back( pEdge );
	} // if
}

GraphEdge* Graph::addEdge( GraphVertex *pVertex1, GraphVertex *pVertex2 ) {
    GraphEdge *pEdge = this->getEdge( pVertex1, pVertex2 );
    if ( pEdge == NULL ) {
        pEdge = new GraphEdge( pVertex1, pVertex2, (pVertex1->getPosition() - pVertex2->getPosition()).magnitude() );
        pVertex1->addEdge( pEdge );
        pVertex2->addEdge( pEdge );
        m_vecEdges.push_back( pEdge );
    } // if
    return pEdge;
}

GraphEdge* Graph::addEdge( const Vector3D &rkPosition1, const Vector3D &rkPosition2 ) {
    GraphVertex *pVertex1 = NULL, *pVertex2 = NULL;

    pVertex1 = this->addVertex( rkPosition1 );
    pVertex2 = this->addVertex( rkPosition2 );

    return this->addEdge( pVertex1, pVertex2 );
}

void Graph::removeEdge( GraphEdge *pEdge ) {
	removeEdge( pEdge->getId( ) );
}

void Graph::removeEdge( long lEdgeId ) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecEdges.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *ppBegin )->getId( ) == lEdgeId ) {
	(*ppBegin)->getVertex1()->removeEdge( lEdgeId );
	(*ppBegin)->getVertex2()->removeEdge( lEdgeId );
      	m_vecEdges.erase( ppBegin );
      } // if            
      ++ppBegin;
    } // while 
}

bool Graph::positionHasVertex( const Vector3D &rkPosition ) {

	std::vector< GraphVertex* >::iterator ppBegin = this->m_vecVertices.begin( );
	std::vector< GraphVertex* >::iterator ppEnd = this->m_vecVertices.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( rkPosition == (*ppBegin)->getPosition( ) ) {
      	return true;
      } // if            
      ++ppBegin;
    } // while 
    return false;
}

bool Graph::vertexBelongsToGraph( GraphVertex *pVertex ) {
    return this->positionHasVertex( pVertex->getPosition( ) );
}

bool Graph::edgeBelongsToGraph( GraphEdge *pEdge ) {
    return this->verticesBelongToEdge( pEdge->getVertex1( ), pEdge->getVertex2( ) );
}

bool Graph::verticesBelongToEdge( GraphVertex *pVertex1, GraphVertex *pVertex2 ) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecEdges.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *( *ppBegin )->getVertex1( ) == *pVertex1 &&
             *( *ppBegin )->getVertex2( ) == *pVertex2 ) ||
           ( *( *ppBegin )->getVertex1( ) == *pVertex2 &&
             *( *ppBegin )->getVertex2( ) == *pVertex1  ) ) {
      	return true;
      } // if            
      ++ppBegin;
    } // while 
    return false;
}

GraphVertex *Graph::getVertexByPosition( const Vector3D &rkPosition ) {
	std::vector< GraphVertex* >::iterator ppBegin = this->m_vecVertices.begin( );
	std::vector< GraphVertex* >::iterator ppEnd = this->m_vecVertices.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *ppBegin )->getPosition( ) == rkPosition ) {
      	return *ppBegin;
      } // if            
      ++ppBegin;
    } // while 
    return 0;
}

GraphVertex *Graph::getVertex( long lVertexId ) {
	std::vector< GraphVertex* >::iterator ppBegin = this->m_vecVertices.begin( );
	std::vector< GraphVertex* >::iterator ppEnd = this->m_vecVertices.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *ppBegin )->getId( ) == lVertexId ) {
      	return *ppBegin;
      } // if            
      ++ppBegin;
    } // while 
    return 0;
}

GraphEdge *Graph::getEdge( long lVertexId ) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecEdges.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *ppBegin )->getId( ) == lVertexId ) {
      	return ( *ppBegin );
      } // if            
      ++ppBegin;
    } // while 
    return 0;
}  
 
GraphEdge *Graph::getEdge( GraphVertex *pVertex1, GraphVertex *pVertex2) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecEdges.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *( *ppBegin )->getVertex1( ) == *pVertex1 &&
             *( *ppBegin )->getVertex2( ) == *pVertex2 ) ||
           ( *( *ppBegin )->getVertex1( ) == *pVertex2 &&
             *( *ppBegin )->getVertex2( ) == *pVertex1  ) ) {
      	return ( *ppBegin );
      } // if            
      ++ppBegin;
    } // while 
    return 0;
}
	
GraphEdge* Graph::findNearestEdge( const Vector3D &rkPosition ) const {
    std::vector< GraphEdge* >::const_iterator ppBegin = this->m_vecEdges.cbegin( );
    std::vector< GraphEdge* >::const_iterator ppEnd = this->m_vecEdges.cend( );
    float fMinDistance = std::numeric_limits<float>::infinity();
    GraphEdge *pEdge = NULL;
    while ( ppBegin != ppEnd ) {
        Vector3D kPointInEdge = (*ppBegin)->getNearestPointInEdge( rkPosition );
        float fDistance = (rkPosition - kPointInEdge ).magnitude( );
        if ( fDistance < fMinDistance ) {
            fMinDistance = fDistance;
            pEdge = *ppBegin;
        } // if
        ++ppBegin;
    } // while 
    return pEdge;
}

std::string Graph::toString( ) {
	std::stringstream ssString;
	
	ssString << "Number of Vertices: " << m_vecVertices.size( ) << std::endl;
	ssString << "Number of Edges: " << m_vecEdges.size( ) << std::endl;
	ssString << std::endl;
		
	std::vector< GraphVertex* >::iterator ppBeginV = this->m_vecVertices.begin( );
	std::vector< GraphVertex* >::iterator ppEndV = this->m_vecVertices.end( );
    
    while ( ppBeginV != ppEndV ) {            
	  ssString << ( *ppBeginV )->toString( ) << std::endl;
      ++ppBeginV;
    } // while

	std::vector< GraphEdge* >::iterator ppBeginE = this->m_vecEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEndE = this->m_vecEdges.end( );
    
    while ( ppBeginE != ppEndE ) {            
	  ssString << ( *ppBeginE )->toString( ) << std::endl;
      ++ppBeginE;
    } // while

    return ssString.str( );
}


	}; // primitives
}; // namespace powergine
