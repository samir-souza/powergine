// Copyright (c) 2004 Samir Araujo <samir.araujo.com>
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

namespace powergine {
   namespace primitives {


void Graph::addVertex( GraphVertex *pVertex ) {
	if ( !vertexBelongsToGraph( pVertex ) ) { 
    	m_vecVertices.push_back( pVertex );
	} // if
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

void Graph::removeEdge( GraphEdge *pEdge ) {
	removeEdge( pEdge->getId( ) );
}

void Graph::removeEdge( long lEdgeId ) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecEdges.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( ( *ppBegin )->getId( ) == lEdgeId ) {
      	m_vecEdges.erase( ppBegin );
      } // if            
      ++ppBegin;
    } // while 
}

bool Graph::vertexBelongsToGraph( GraphVertex *pVertex ) {
	std::vector< GraphVertex* >::iterator ppBegin = this->m_vecVertices.begin( );
	std::vector< GraphVertex* >::iterator ppEnd = this->m_vecVertices.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( *pVertex == **ppBegin ) {
      	return true;
      } // if            
      ++ppBegin;
    } // while 
    return false;
}

bool Graph::edgeBelongsToGraph( GraphEdge *pEdge ) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecEdges.end( );
    
    while ( ppBegin != ppEnd ) {
      if ( *ppBegin == pEdge ) {
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
