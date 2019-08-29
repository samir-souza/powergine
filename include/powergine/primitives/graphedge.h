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

#ifndef GRAPHEDGE_H_
#define GRAPHEDGE_H_

#include <sstream>

namespace powergine {
   namespace primitives {

	class GraphVertex;

	/**
	 * Represents a graph edge. This class is part of the
	 * Graph toolset
	 */
	class GraphEdge {
	public:
		// Default constructor. It must receive both vertices which this edge links
		GraphEdge( GraphVertex *pVertex1, GraphVertex *pVertex2, float fCost = 0 );

		inline virtual ~GraphEdge( ) { };

		// Getter of the first vertex
		inline GraphVertex* getVertex1( ) const {
			return this->m_pVertex1;
		};

		// Getter of the second vertex
		inline GraphVertex* getVertex2( ) const {
			return this->m_pVertex2;
		};

		// Getter of the edge id
		inline long getId( ) {
			return this->m_lId;
		};

		// Getter of the edge cost. The cost is informed
		// during the Edge creation
		inline float getCost( ) const {
			return this->m_fCost;
		};

		// Checks if a given edge intersects this one
		bool intersection( GraphEdge *pEdge );

		// Given a vertex, returns the other vertex connected by this edge
		GraphVertex* getOtherVertex( GraphVertex* pVertex );

		// Returns a string description of the edge
		std::string toString( ) const;

	private:
		static long s_lEdgeIdCounter;
		GraphVertex *m_pVertex1;
		GraphVertex *m_pVertex2;
		float m_fCost;
		long m_lId;

	};

	}; // primitives
}; // namespace powergine

#endif /*GRAPHEDGE_H_*/
