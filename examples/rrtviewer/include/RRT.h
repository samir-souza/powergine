// Copyright (c) 2007 Samir Araujo <samir.araujo@gmail.com>
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

#ifndef RRT_H_
#define RRT_H_

#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/graph.h>
#include <powergine/primitives/graphvertex.h>
#include <powergine/tools/astarpathfinder.h>
#include <Map.h>
#include <vector>
#include <set>
#include <ctime>
#include <fstream>
#include <math.h>
#include <Obstacle.h>
#include <iostream>
#include <stdexcept>

using namespace powergine::tools;
using namespace powergine::primitives;

/**
 * This is a base class for building (RRT) Rapidly Random Trees
 * To better understand the algorithm take a look at:
 * http://msl.cs.uiuc.edu/rrt/
 */
class RRT {

	protected:
		int m_iStartTryNumber;
		int m_iTryNumber;
		int m_iBuildNodeTries;
		Graph *m_pGraph;
		Map *m_pMap;
		GraphVertex *m_pStartVertex;
		GraphVertex *m_pEndVertex;

	public:

		/**
		 * Comparator function used to determine which vertex
		 * is closer to a target vertex or a desired position
		 */
		class EdgeCostComparator {
		protected:
			Vector3D m_oSourceVertexPosition;
		public:

		    inline EdgeCostComparator( GraphVertex *pSourceVertex ) :
		    	m_oSourceVertexPosition( pSourceVertex->getPosition( ) ) { }

		    inline EdgeCostComparator( const Vector3D &rkPosition ) :
		    	m_oSourceVertexPosition( rkPosition ) { }

		    inline virtual ~EdgeCostComparator( ) { }

		    // Functor operator which compares two vertices
		  	bool operator( )( const GraphVertex* s1, const GraphVertex* s2) const {
		    	float fDistanceS1ToGoal = ( const_cast<GraphVertex*>( s1 )->getPosition( ) - m_oSourceVertexPosition ).magnitude( );
		    	float fDistanceS2ToGoal = ( const_cast<GraphVertex*>( s2 )->getPosition( ) - m_oSourceVertexPosition ).magnitude( );

		    	return ( fDistanceS1ToGoal < fDistanceS2ToGoal );
		  	} // operator
		};


		// Indicates how much a new node will grow in the chosen direction
		static const float GROW_DIST;
		// Maximum number of tries to grow a node. If it was exceeded, try to grow another node
		static const unsigned int MAX_CONNECT_GOAL_TRIES;

		RRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries );

		virtual ~RRT( );

		// Tries to build the whole tree at once
		virtual bool buildTree( );

		// Tries to build just one node
		virtual bool buildNode( );

		// Chooses a random position to grow the tree to
		virtual Vector3D* getRandomFreePoint( );

		// Find the nearest vertex to a given one
		virtual GraphVertex* findNearestVertex( GraphVertex *vertex );

		// Find the nearest vertex to a given position
		virtual GraphVertex* findNearestVertex( const Vector3D &rkPosition );

		// Tries to grow the tree from a source vertex to a given canditdate position
		virtual Vector3D* growVertex( Vector3D *pCandidatePoint, GraphVertex *pSourceVertex );

		// Checks if a source vertex can be connected to a canditate point
		virtual bool canConnect( Vector3D *pCandidatePoint, GraphVertex *pSourceVertex );

		// Checks if a source point can be connected to a canditate point
		virtual bool canConnect( Vector3D *pCandidatePoint, Vector3D *pSourcePoint );

		// Adds a new vertex positioned at the given point
		virtual GraphVertex* addVertex( Vector3D *pCandidatePoint );

		// Adds a new edge which connects the given two vertices
		virtual GraphEdge* addEdge( GraphVertex *pVertex1, GraphVertex *pVertex2 );

		// Print the tree
		virtual void print( );

		// Returns the algorithm name
		virtual const char* getName( ) { return "Rapidly-Exploring Random Tree"; };

		// Find a path between the start and end vertices given in the
		// class constructor
		virtual std::vector<GraphEdge*> findPath( );

		// Connects the start point to the end point
		virtual bool connectGoal( );

		// Returns the graph
		virtual inline Graph* getGraph( ) {
			return m_pGraph;
		};

		// Returns the map
		virtual inline Map* getMap( ) {
			return m_pMap;
		};

		// Returns the start vertex
		virtual inline GraphVertex *getStartVertex( ) {
			return m_pStartVertex;
		};

		// Returns the end vertex
		virtual inline GraphVertex *getEndVertex( ) {
			return m_pEndVertex;
		};

		// Gets the number of nodes added to the tree
		virtual inline int getNumberOfAcceptedNodes( ) {
			return ( m_iTryNumber == -1 ) ? m_pGraph->getVertices( ).size( ) - 2 : m_pGraph->getVertices( ).size( ) - 1;
		};

		// Gets the number of candidate nodes rejected due to collision problems
		virtual inline int getNumberOfRejectedNodes( ) {
			return m_iBuildNodeTries - getNumberOfAcceptedNodes( );
		};

		// Returns the number of tries required to build the tree
		virtual inline int getNumberOfTriesUsedToBuildTree( ) {
			return m_iBuildNodeTries;
		};
};

#endif /*RRT_H_*/
