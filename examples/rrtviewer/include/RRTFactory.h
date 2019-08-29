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

#ifndef RRTFACTORY_H_
#define RRTFACTORY_H_

#include <RRT.h>
#include <GoalBiasRRT.h>
#include <SRRT.h>
#include <StarRRT.h>
#include <VBRRT.h>

/**
 * This is a factory class, responsible for creating
 * instances of several types of RRTs
 */
class RRTFactory {
public:

	enum RRT_TYPE {
		TYPE_RRT 		= 0,
		TYPE_SRRT,
		TYPE_VBRRT,
		TYPE_GBRRT,
		TYPE_STARRRT,
		NUM_OF_TYPES // must be last
	};

	RRTFactory( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries );

	inline virtual ~RRTFactory( ){ };

	// Factory method which creates an instance of a given RRT variation
	RRT *createRRT( RRT_TYPE eType = TYPE_RRT );

	// Returns the current map
	inline Map *getMap( ) {
		return m_pMap;
	};

	// Returns the start vertex. The vertex which the RRTs will start growing
	inline GraphVertex *getStartVertex( ) {
		return m_pStartVertex;
	};

	// Returns the end vertex. The vertex which the RRTs will try to reach
	inline GraphVertex *getEndVertex( ) {
		return m_pEndVertex;
	};

	// Returns the number of tries used to grows the tree
	inline int getNumberOfTries( ) {
		return m_iNumberOfTries;
	};

	// The three methods bellow are used to automatically create
	// all the available types of RRT, in more the one step

	// Returns the current RRT type.
	inline RRT_TYPE currentType( ) {
		return (RRT_TYPE) m_iCurrentType;
	};

	// Returns the previous RRT type, following the enumeration
	RRT_TYPE previousType( );

	// Returns the next RRT type, following the enumeration
	RRT_TYPE nextType( );

private:
	Map *m_pMap;
	GraphVertex *m_pStartVertex;
	GraphVertex *m_pEndVertex;
	int m_iNumberOfTries;
	int m_iCurrentType;
};

#endif /*RRTFACTORY_H_*/
