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


#include <powergine/primitives/graphedge.h>
#include <powergine/primitives/graphvertex.h>
#include <limits>

namespace powergine {
   namespace primitives {

long GraphEdge::s_lEdgeIdCounter = 0;

GraphEdge::GraphEdge( GraphVertex *pVertex1, GraphVertex *pVertex2, float fCost ) : 
	m_pVertex1( pVertex1 ), m_pVertex2( pVertex2 ), m_fCost( fCost ) { 	
	this->m_lId = s_lEdgeIdCounter++;
};

GraphVertex* GraphEdge::getOtherVertex( GraphVertex* pVertex ) {
	return ( pVertex == getVertex1() ) ? getVertex2( ) : getVertex1( );
} // getOtherVertex

bool GraphEdge::intersection( GraphEdge *pEdge ) {
	float fX1Edge1 = pEdge->getVertex1( )->getPosition( ).getX( ); // x1
	float fY1Edge1 = pEdge->getVertex1( )->getPosition( ).getY( ); // y1
	float fX2Edge1 = pEdge->getVertex2( )->getPosition( ).getX( ); // x2
	float fY2Edge1 = pEdge->getVertex2( )->getPosition( ).getY( ); // y2

	float fX1Edge2 = this->getVertex1( )->getPosition( ).getX( ); // x3
	float fY1Edge2 = this->getVertex1( )->getPosition( ).getY( ); // y3
	float fX2Edge2 = this->getVertex2( )->getPosition( ).getX( ); // x4
	float fY2Edge2 = this->getVertex2( )->getPosition( ).getY( ); // y4

	float fA1 = fY2Edge1 - fY1Edge1; // a1:= y2-y1;
	float fB1 = fX1Edge1 - fX2Edge1; // b1:= x1-x2;
	
	float fA2 = fY2Edge2 - fY1Edge2; // a2:= y4-y3;
	float fB2 = fX1Edge2 - fX2Edge2; // b2:= x3-x4;

	
	float fDenom = fA1 * fB2 - fA2 * fB1;

	if ( fDenom == 0 ) {
		return false;
	} // if
	
	float fC1 = fX2Edge1*fY1Edge1 - fX1Edge1*fY2Edge1; //  c1:= x2*y1 - x1*y2;  { a1*x + b1*y + c1 = 0 is line 1 }
	float fC2 = fX2Edge2*fY1Edge2 - fX1Edge2*fY2Edge2; //  c2:= x4*y3 - x3*y4;  { a2*x + b2*y + c2 = 0 is line 2 }

	float fCommonX = (fB2*fC1 - fB1*fC2)/fDenom;
    float fCommonY = (fA1*fC2 - fA2*fC1)/fDenom;

	
	if ( ( fCommonX == fX1Edge1 && fCommonY == fY1Edge1 ) || ( fCommonX == fX2Edge1 && fCommonY == fY2Edge1 ) ) {
		return false;	
	} // if
	return true;

	
	// intersection point
	//  x:=(b1*c2 - b2*c1)/denom; 
	// y:=(a2*c1 - a1*c2)/denom;

} // intersection

Vector3D GraphEdge::getNearestPointInEdge( const Vector3D &rkPoint ) const {
    Vector3D kPos1 = this->getVertex1( )->getPosition( );
    Vector3D kPos2 = this->getVertex2( )->getPosition( );
    float fEdgeLength = (kPos1 - kPos2).magnitude();
    if ( fEdgeLength == 0 ) {
        return kPos1;
    } else {
        float fT = ((rkPoint - kPos1) * (kPos1 - kPos2)) / fEdgeLength;
        fT = std::max(0.0f, std::min( 1.0f, fT ) );
        return ((kPos2 - kPos1) * fT) + kPos1; 
    } // else 
}

std::string GraphEdge::toString( ) const {
	std::stringstream ssString;
	ssString << "Edge ID: " << m_lId << " Cost: " << m_fCost << std::endl;
	ssString << "Vertex 1 ID: " << getVertex1( )->getId( ) << std::endl;
	ssString << "Vertex 2 ID: " << getVertex2( )->getId( ) << std::endl;
	return ssString.str( );
} // toString

	}; // primitives
}; // namespace powergine

