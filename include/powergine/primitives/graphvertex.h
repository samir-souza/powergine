// Copyright (c) 2004 Samir Araujo <samir.araujo@gmail.com>
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

#ifndef GRAPHVERTEX_H_
#define GRAPHVERTEX_H_

#include <set>
#include <vector>
#include <powergine/primitives/vector3d.h>


namespace powergine {
   namespace primitives {

	class GraphEdge;

	/**
	 * Represents a graph Vertex. This class is part of the
	 * Graph toolset
	 */
	class GraphVertex {

	public:
		// Default constructor. It holds a vector position as argument
		inline GraphVertex( const Vector3D &rkPosition = Vector3D::ORIGO ) : m_oPosition( rkPosition ) {
			this->m_lId = s_lVertexIdCounter++;
		};

		inline virtual ~GraphVertex( ) { };

		// Getter of the Vertex id
		inline long getId( ) {
			return m_lId;
		};

		// Updates the vertex position
		inline void setPosition( const Vector3D &rkPosition ) {
			this->m_oPosition = rkPosition;
		};

		// Getter of the vertex position
		inline Vector3D &getPosition( ) {
			return this->m_oPosition;
		};

		// Return all edges connected to this vertex
		inline const std::vector<GraphEdge*> getEdges( ) const {
			return this->m_vecConnectedEdges;
		};

		// Returns the vertex degree. The number of edges
		// connected to this vertex
		inline int degree( ) {
			return (int)m_vecConnectedEdges.size( );
		};

		// Connects this vertex to a new edge
		void addEdge( GraphEdge *pEdge );

		// Disconnects this vertex from a given edge
		void removeEdge( GraphEdge *pEdge );

		// Disconnects this vertex from a given edge
		void removeEdge( long lEdgeId );

		// Returns a list which contains all the adjacent vertices to this one
		std::set<GraphVertex*> getAdjacentVertices( );

		// Returns a list which contains all edges that don't make a loop
		// on this vertex
		std::vector<GraphEdge*> getNonLoopEdges( );

		// Returns a string description of the vertex
		std::string toString( );

		// Equals operator to check if a vertex position is equals to another one
		inline bool operator==( GraphVertex &rkVertex ) {
			return ( getPosition( ) == rkVertex.getPosition( ) );
		};

	private:
		static long s_lVertexIdCounter;
		long m_lId;
		std::vector<GraphEdge*> m_vecConnectedEdges;
		Vector3D m_oPosition;
	};

	}; // primitives
}; // namespace powergine

#endif /*GRAPHVERTEX_H_*/
