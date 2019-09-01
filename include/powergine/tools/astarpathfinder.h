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

#ifndef ASTARPATHFINDER_H_
#define ASTARPATHFINDER_H_

#include <powergine/primitives/graph.h>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <sstream>
#include <iostream>

namespace powergine {
	namespace tools {

	/**
	 * A* Handler. It executes the A Star algorithm in a graph,
	 * using the Euclidian Distance Heuristic
	 */
	class AStarPathFinder {
	public:
		AStarPathFinder( primitives::Graph *pGraph );
		AStarPathFinder( primitives::Graph *pGraph, primitives::GraphVertex *pStartVertex, primitives::GraphVertex *pEndVertex );

		inline virtual ~AStarPathFinder( ) { };

		// Update the start vertex of the path into the graph the algorithm
		// must to find
		void setStartVertex( primitives::GraphVertex *pVertex );
		void setStartVertex( long lVertexId );

		// Update the end vertex of the path into the graph the algorithm
		// must to find
		void setEndVertex( primitives::GraphVertex *pVertex );
		void setEndVertex( long lVertexId );

		// run A* and make a Edge list to represent the path
		void updatePath( );

		// return the Edge list that represents the path
		inline std::vector<primitives::GraphEdge*> getPathEdges( ) {
			return m_vecEdgesPath;
		};

		// return the Vertex list that represents the path
		inline std::vector<primitives::GraphVertex*> getPathVertices( ) {
			return m_vecVerticesPath;
		};

		std::string toString( );

	private:
		std::vector<primitives::GraphEdge*> m_vecEdgesPath;
		std::vector<primitives::GraphVertex*> m_vecVerticesPath;
		primitives::GraphVertex *m_pStartVertex;
		primitives::GraphVertex *m_pEndVertex;
		primitives::Graph *m_pGraph;

	};

	}; // tools
}; // namespace powergine

#endif /*ASTARPATHFINDER_H_*/
