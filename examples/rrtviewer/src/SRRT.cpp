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

#include <SRRT.h>

const double SRRT::STEP_ANGLE = 20.0;
const int SRRT::MAX_NUM_TRIES = 1;
const int SRRT::MAX_RANDOM_FACTOR = 25;

SRRT::SRRT( Map *pMap, GraphVertex *pStartVertex, GraphVertex *pEndVertex, int iNumberOfTries ) :
	RRT( pMap, pStartVertex, pEndVertex, iNumberOfTries ),
	m_eState( int( 180.0f / STEP_ANGLE ) ),
	m_iCurrentTry( 0 ),
	m_iRandomFactor( 5 ) {
}

SRRT::~SRRT( ) {
}

bool SRRT::buildNode( ) {
	if ( ( m_pEndVertex->getPosition( ) - findNearestVertex( m_pEndVertex )->getPosition( ) ).magnitude( ) <= GROW_DIST ) {
		if ( m_iTryNumber != -1 ) {
			m_iTryNumber = 0;
		} // if
	} // if

	return RRT::buildNode( );
}

GraphVertex* SRRT::addVertex( Vector3D *pCandidatePoint ) {
	m_eState.setState( EState::START_STATE );
	m_iCurrentTry = 0;
	m_iRandomFactor = 5;
	return RRT::addVertex( pCandidatePoint );
}

Vector3D* SRRT::growVertex( Vector3D *pCandidatePoint, GraphVertex *pSourceVertex ) {
	m_iCurrentTry++;
	if ( m_iCurrentTry >= MAX_NUM_TRIES ) {
		m_eState.nextState( );
		m_iCurrentTry = 0;
		m_iRandomFactor = std::min( m_iRandomFactor + 5, MAX_RANDOM_FACTOR );
	} // if
	return RRT::growVertex( pCandidatePoint, pSourceVertex );
}

Vector3D* SRRT::getRandomFreePoint( const Vector3D &rkLine1, const Vector3D &rkLine2 ) {
	float fX1 = rkLine1.getX( );
	float fX2 = rkLine2.getX( );

	float fSinalX1 = ( fX1 < 0 ) ? -1.0f : 1.0f;
	float fSinalX2 = ( fX2 < 0 ) ? -1.0f : 1.0f;

	float fXStartLimit = 0;
	float fXRange = 0;
	if ( fSinalX1 != fSinalX2 ) {
		fXRange = fabs( fX1 ) + fabs( fX2 );
		fXStartLimit = std::min( fX1, fX2 );
	} else if ( fSinalX1 < 0 ) {
		fXRange = fabs( std::min( fX1, fX2 ) );
		fXStartLimit = -fXRange;
	} else {
		fXRange = fabs( std::max( fX1, fX2 ) );
	} // else
	if ( fXRange < 1 ) {
		fXRange = 1.0f;
	} // if

	float fX = rand( ) % (int)fXRange;
	fX += fXStartLimit;

	// m = (yB - yA) / (xB - xA)
	float fM1 = rkLine1.getY( ) / ( ( rkLine1.getX( ) != 0 ) ? rkLine1.getX( ) : 1.0f );
	float fM2 = rkLine2.getY( ) / ( ( rkLine2.getX( ) != 0 ) ? rkLine2.getX( ) : 1.0f );


	//y = m( x - xB ) + yB
	float fY1 = fM1 * ( fX - rkLine1.getX( ) ) + rkLine1.getY( );
	float fY2 = fM2 * ( fX - rkLine2.getX( ) ) + rkLine2.getY( );

	float fSinalYLine1 = ( rkLine1.getY( ) < 0 ) ? -1.0f : 1.0f;
	float fSinalYLine2 = ( rkLine2.getY( ) < 0 ) ? -1.0f : 1.0f;

	float fSinalY1 = ( fY1 < 0 ) ? -1.0 : 1.0;
	float fSinalY2 = ( fY2 < 0 ) ? -1.0 : 1.0;

	float fYRange = 0;
	float fYStartLimit;
	float fYEndLimit;
	if ( fSinalYLine1 == fSinalYLine2 ) {
		if ( fSinalYLine1 < 0 ) {
			if ( fSinalY1 == fSinalY2 ) {
				fYEndLimit = std::max( fY1, fY2 );
				fYStartLimit = std::min( fY1, fY2 );
			} else {
				fYEndLimit = std::min( fY1, fY2 );
				fYStartLimit = std::max( rkLine1.getY( ), rkLine2.getY( ) );
			} // else
			fYRange = fabs( fYEndLimit ) - fabs( fYStartLimit );
		} else {
			fYStartLimit = ( fSinalY1 == fSinalY2 ) ? std::min( fY1, fY2 ) : std::max( fY1, fY2 );
			fYRange = std::max( rkLine1.getY( ), rkLine2.getY( ) ) - fYStartLimit;
		} // else
	} else {
		fYRange = fabs( fY1 ) + fabs( fY2 );
		fYStartLimit = std::min( fY1, fY2 );
	} // else

	if ( fYRange < 1 ) {
		fYRange = 1.0f;
	} // if

	float fY = rand( ) % (int)fYRange;
	fY += fYStartLimit;

	return new Vector3D( fX, fY, 0 );

} // getRandomFreePoint

Vector3D* SRRT::getRandomFreePoint( ) {
	GraphVertex *pNearVertex = findNearestVertex( m_pEndVertex );

	m_oCurrentNearest = pNearVertex->getPosition( );
	Vector3D deltaVector = m_pEndVertex->getPosition( ) - pNearVertex->getPosition( );
	float fCurrentAngle = ( STEP_ANGLE * m_eState.getState( ) );
	float fPreviousAngle = fCurrentAngle - STEP_ANGLE;

	Vector3D oLine1 = Quaternion( fCurrentAngle, Vector3D( 0, 0, 1.0f ) ).rotateVector3D( deltaVector );
	Vector3D oLine2 = Quaternion( fPreviousAngle, Vector3D( 0, 0, 1.0f ) ).rotateVector3D( deltaVector );
	Vector3D oLine3 = Quaternion( -fPreviousAngle, Vector3D( 0, 0, 1.0f ) ).rotateVector3D( deltaVector );
	Vector3D oLine4 = Quaternion( -fCurrentAngle, Vector3D( 0, 0, 1.0f ) ).rotateVector3D( deltaVector );
	oLine1.normalize( );
	oLine2.normalize( );
	oLine3.normalize( );
	oLine4.normalize( );
	oLine1 *= GROW_DIST * m_iRandomFactor;
	oLine2 *= GROW_DIST * m_iRandomFactor;
	oLine3 *= GROW_DIST * m_iRandomFactor;
	oLine4 *= GROW_DIST * m_iRandomFactor;

	Vector3D *pRandomFreePoint = 0;

	if ( oLine2 == oLine3 ) {
		m_oLine1 = oLine1; m_oLine2 = oLine4;
		pRandomFreePoint = getRandomFreePoint( oLine1, oLine4 );
	} else if ( oLine1 == oLine4 ) {

		m_oLine1 = oLine2; m_oLine2 = oLine3;
		pRandomFreePoint = getRandomFreePoint( oLine2, oLine3 );
	} else if ( ( rand( ) % 2 ) == 0 ) {

		m_oLine1 = oLine1; m_oLine2 = oLine2;
		pRandomFreePoint = getRandomFreePoint( oLine1, oLine2 );
	} else {

		m_oLine1 = oLine3; m_oLine2 = oLine4;
		pRandomFreePoint = getRandomFreePoint( oLine3, oLine4 );

	} // else

	 m_oCurrentRandomFree = *pRandomFreePoint;
	*pRandomFreePoint += pNearVertex->getPosition( );
	return pRandomFreePoint;
}

void SRRT::print( ) {
    RenderPrimitive *pRenderMesh = new RenderPrimitive( RenderPrimitive::MODE_LINES, RenderPrimitive::POLYGON_LINE );

    pRenderMesh->setEdgeLinesSize( 2.0 );
    primitives::VertexDiffuseBuffer *pVertexHandler = new primitives::VertexDiffuseBuffer( 6 );
    primitives::LineBuffer *pPolygonHandler = new primitives::LineBuffer( 3 );

    primitives::VertexBuffer *pVertexBuffer =
       Core::get( )->getVideoManager( )->createVertexBuffer(
          pVertexHandler->getNumElements( ),
          primitives::VertexDiffuse::s_oFormat,
          pVertexHandler->getData( )
       );

	primitives::PolygonBuffer *pPolygonBuffer =
    	Core::get( )->getVideoManager( )->createPolygonBuffer(
           pPolygonHandler->getNumElements( ),
           primitives::Line::getNumVertices( ),
           pPolygonHandler->getData( )
        );

	pRenderMesh->setVertexBuffer( pVertexBuffer );
	pRenderMesh->setPolygonBuffer( pPolygonBuffer );

	primitives::VertexDiffuseBuffer::iterator *pVIterator = pVertexHandler->makeIterator( );
	primitives::LineBuffer::iterator *pPIterator = pPolygonHandler->makeIterator( );

	Vector3D oHigh( 0, 0, 3.0f );

	pVIterator->getCurrent( ).setAll( oHigh, Color( 1.0f, 1.0f, 0, 0 ) );
	pVIterator->goNext( );
	pVIterator->getCurrent( ).setAll( oHigh + m_oCurrentRandomFree, Color( 1.0f, 1.0f, 0, 0 ) );
	pVIterator->goNext( );

	pVIterator->getCurrent( ).setAll( oHigh , Color::BLUE );
	pVIterator->goNext( );
	pVIterator->getCurrent( ).setAll( oHigh  + m_oLine1, Color::BLUE );
	pVIterator->goNext( );

	pVIterator->getCurrent( ).setAll( oHigh, Color::BLUE );
	pVIterator->goNext( );
	pVIterator->getCurrent( ).setAll( oHigh  + m_oLine2, Color::BLUE );

	pPIterator->getCurrent( ).setAll( 0, 1 );
	pPIterator->goNext( );
	pPIterator->getCurrent( ).setAll( 2, 3 );
	pPIterator->goNext( );
	pPIterator->getCurrent( ).setAll( 4, 5 );

	Core::get( )->getVideoManager( )->render( *pRenderMesh );
} // render

