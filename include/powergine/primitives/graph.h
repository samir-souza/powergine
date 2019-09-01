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

#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <powergine/primitives/graphvertex.h>
#include <powergine/primitives/graphedge.h>

namespace powergine {
   namespace primitives {

   /**
    * This is a basic Graph representation. It can be used
    * to build waypoints and other structures which requires
    * a graph as a datatype
    */
   class Graph {
	public:
		// Default constructor
		inline Graph( ) { };

		inline virtual ~Graph( ) { };

		// Add a new vertex to the graph
		void addVertex( GraphVertex *pVertex );
		GraphVertex* addVertex( const Vector3D& position );

		// Remove a vertex from the graph given its pointer
		void removeVertex( GraphVertex *pVertex );
		// Remove a vertex from the graph given its id
		void removeVertex( long lVertexId );

		// Add a new edge to the graph
		void addEdge( GraphEdge *pEdge );
		GraphEdge* addEdge( GraphVertex *pVertex1, GraphVertex *pVertex2 );
		GraphEdge* addEdge( const Vector3D &rkPosition1, const Vector3D &rkPosition2 );

		// Remove an edge from the graph given its pointer
		void removeEdge( GraphEdge *pEdge );
		// Remove an edge from the graph given its id
		void removeEdge( long lEdgeId );

		// Returns a description of the graph
		std::string toString( );

		// Check if a given vertex (pointer) belongs to the graph
		bool vertexBelongsToGraph( GraphVertex *pVertex );
		bool positionHasVertex( const Vector3D &rkPosition );
		// Check if a given edge (pointer) belongs to the graph
		bool edgeBelongsToGraph( GraphEdge *pEdge );
		bool verticesBelongToEdge( GraphVertex *pVertex1, GraphVertex *pVertex2 );

		// Returns the nearest vertex of the graph given a position
		GraphVertex *getVertexByPosition( const Vector3D &rkPosition );
		// Returns a vertex given its id
		GraphVertex *getVertex( long lVertexId );
		// Returns an edge given its id
		GraphEdge *getEdge( long lVertexId );
		GraphEdge *getEdge( GraphVertex *pVertex1, GraphVertex *pVertex2);

        GraphEdge* findNearestEdge( const Vector3D &rkPosition ) const;

		// Returns all edges of the graph
		inline std::vector<GraphEdge*> getEdges( ) {
			return m_vecEdges;
		};

		// Returns all vertices of the graph
		inline std::vector<GraphVertex*> getVertices( ) {
			return m_vecVertices;
		};


	private:
		std::vector<GraphEdge*> m_vecEdges;
		std::vector<GraphVertex*> m_vecVertices;

	};

	}; // primitives
}; // namespace powergine

#endif /*GRAPH_H_*/
