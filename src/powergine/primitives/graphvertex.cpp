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


#include <powergine/primitives/graphvertex.h>
#include <powergine/primitives/graphedge.h>


namespace powergine {
   namespace primitives {
   	
long GraphVertex::s_lVertexIdCounter = 0;

void GraphVertex::addEdge( GraphEdge *pEdge ) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecConnectedEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecConnectedEdges.end( );
    
    while ( ppBegin != ppEnd ) {            
      if ( pEdge == *ppBegin ) {
      	return;         
      } // if           
      ++ppBegin;
    } // while 
    m_vecConnectedEdges.push_back( pEdge );
} // addEdge

void GraphVertex::removeEdge( GraphEdge *pEdge ) {
	removeEdge( pEdge->getId( ) );
   
} // removeEdge

void GraphVertex::removeEdge( long lEdgeId ) {
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecConnectedEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecConnectedEdges.end( );
    
    while ( ppBegin != ppEnd ) {            
      if ( ( *ppBegin )->getId( ) == lEdgeId ) {
      	m_vecConnectedEdges.erase( ppBegin );
      	( *ppBegin )->getOtherVertex( this )->removeEdge( lEdgeId );      
      } // if           
      ++ppBegin;
    } // while 
} // removeEdge
	
std::set<GraphVertex*> GraphVertex::getAdjacentVertices( ) {
	std::set<GraphVertex*> setAdjacentVertices;
	
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecConnectedEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecConnectedEdges.end( );
    while ( ppBegin != ppEnd ) {
    	if ( (*ppBegin)->getOtherVertex( this ) != this ) {
    		setAdjacentVertices.insert( (*ppBegin)->getOtherVertex( this ) );
    	} // if 
    	++ppBegin;            
    } // while	
    return setAdjacentVertices;
}

std::vector<GraphEdge*> GraphVertex::getNonLoopEdges( ) {
	std::vector<GraphEdge*> vecNonLoopEdges;
	
	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecConnectedEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecConnectedEdges.end( );
    while ( ppBegin != ppEnd ) {
    	if ( (*ppBegin)->getOtherVertex( this ) != this ) {
    		vecNonLoopEdges.push_back( *ppBegin );
    	} // if 
    	++ppBegin;            
    } // while	
    return vecNonLoopEdges;
	
}

std::string GraphVertex::toString( ) {
	std::stringstream ssString;
	ssString << "Vertex ID: " << m_lId << std::endl;

	std::vector< GraphEdge* >::iterator ppBegin = this->m_vecConnectedEdges.begin( );
	std::vector< GraphEdge* >::iterator ppEnd = this->m_vecConnectedEdges.end( );
    
    if ( ppBegin != ppEnd ) {
    	ssString << "Connected Edges" << std::endl;
    } // if
    while ( ppBegin != ppEnd ) {            
      ssString << "Edge ID: " << (*ppBegin)->getId( ) << std::endl;        
      ++ppBegin;
    } // while 
    return ssString.str( ); 
} // toString


	}; // primitives
}; // namespace powergine
