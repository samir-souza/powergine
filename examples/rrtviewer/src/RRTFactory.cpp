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

#include <RRTFactory.h>

RRTFactory::RRTFactory( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries ) :
	m_pMap( pMap ),
	m_pStartVertex( pStartVertex ),
	m_pEndVertex( pEndVertex ),
	m_iNumberOfTries( iNumberOfTries ),
	m_iCurrentType( 0 ) {

}

RRT *RRTFactory::createRRT( RRT_TYPE eType ) {
	m_iCurrentType = eType;
	switch( eType ) {
		case TYPE_SRRT:
			return new SRRT( m_pMap, m_pStartVertex, m_pEndVertex, m_iNumberOfTries );
		case TYPE_VBRRT:
			return new VBRRT( m_pMap, m_pStartVertex, m_pEndVertex, m_iNumberOfTries );
		case TYPE_GBRRT:
			return new GoalBiasRRT( m_pMap, m_pStartVertex, m_pEndVertex, m_iNumberOfTries );
		case TYPE_STARRRT:
			return new StarRRT( m_pMap, m_pStartVertex, m_pEndVertex, m_iNumberOfTries );
		case TYPE_RRT: default:
			return new RRT( m_pMap, m_pStartVertex, m_pEndVertex, m_iNumberOfTries );
	};
}

RRTFactory::RRT_TYPE RRTFactory::previousType( ) {
	return (RRT_TYPE)( ( m_iCurrentType - 1 < 0 ) ? NUM_OF_TYPES - 1 : m_iCurrentType - 1 );
}

RRTFactory::RRT_TYPE RRTFactory::nextType( ) {
	return (RRT_TYPE)( ( m_iCurrentType + 1 >= (int)NUM_OF_TYPES ) ? 0 : m_iCurrentType + 1 );
}
