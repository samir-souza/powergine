// Copyright (c) 2007 Samir Araujo
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

#ifndef SRRT_H_
#define SRRT_H_

#include <powergine/powergine.h>

using namespace pg;

#include <RRT.h>

/**
 * This is a variation of the RRT which uses a heuristics that
 * emulates the crawl movement of a swimmer. It is called
 * Swimming RRT. It was proposed by me (Samir). It uses two cones
 * to delimit the allowed area to grow the tree. The cones are
 * considered the arms of the swimmer. However, a complete crawling
 * will only happens if the algorithm fail to grow the tree
 */
class SRRT : public RRT {

public:

	/**
	 * This is a helper class which controls the crawling steps.
	 * A crawling is split in several states. The number of states
	 * is configured in the class constructor. At each step the
	 * cones will be rotated from the front to the sides. One cone
	 * points left and the other points right
	 */
	class EState {
		public:
		static const int START_STATE = 1;

		inline EState( int iMaxStates ) {
			m_iMaxStates = iMaxStates;
			m_iState = 1;
		};

		inline void nextState( ) {
			m_iState = ( m_iState % m_iMaxStates ) + 1;
		};

		inline int getState( ) {
			return m_iState;
		};

		inline void setState( int iState ) {
			m_iState = iState;
		};

		private:
		int m_iState;
		int m_iMaxStates;
	};

	// The angle used to rotate each cone at each step
	static const double STEP_ANGLE;
	// Number of tries per crawling step
	static const int MAX_NUM_TRIES;

	// Up limit for a random factor generation
	static const int MAX_RANDOM_FACTOR;

	SRRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries );

	virtual ~SRRT();

	// See RRT::buildNode
	virtual bool buildNode( );

	// See RRT::getRandomFreePoint
	virtual Vector3D* getRandomFreePoint( );

	// See RRT::getRandomFreePoint
	virtual Vector3D* getRandomFreePoint( const Vector3D &rkLine1, const Vector3D &rkLine2 );

	// See RRT::addVertex
	virtual GraphVertex* addVertex( Vector3D *pCandidatePoint );

	// See RRT::growVertex
	virtual Vector3D* growVertex( Vector3D *pCandidatePoint, GraphVertex *pSourceVertex );

	// See RRT::print
	virtual void print( );

	// See RRT::getName
	virtual const char* getName( ) { return "Swimming RRT"; };

protected:
	EState m_eState;
	int m_iCurrentTry;
	Vector3D m_oLine1;
	Vector3D m_oLine2;
	Vector3D m_oCurrentNearest;
	Vector3D m_oCurrentRandomFree;
	Vector3D *m_pSecondRandomPoint;
	int m_iRandomFactor;
};

#endif /*SRRT_H_*/
