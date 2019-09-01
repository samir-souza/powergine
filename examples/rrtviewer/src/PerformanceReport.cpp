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

#include <PerformanceReport.h>

PerformanceReport::PerformanceReport( int iNumberOfTests ) {
	m_iNumberOfTests = iNumberOfTests;

	Vector3D oStartPoint( 1, 1, 0 );
	Vector3D oEndPoint( 45, 25, 0 );

	m_pMap = new Map( 50, 50, oStartPoint, oEndPoint, false );

	GraphVertex *pStartVertex = new GraphVertex( oStartPoint );
	GraphVertex *pEndVertex = new GraphVertex( oEndPoint );

	m_pMap->readMap( );

	m_pRRTFactory = new RRTFactory( m_pMap, pStartVertex, pEndVertex, 500 );

}

PerformanceReport::~PerformanceReport( ) {
	delete m_pRRTFactory;
	delete m_pMap;
}

void PerformanceReport::runTests( ) {
	RRTFactory::RRT_TYPE eStartType = m_pRRTFactory->currentType( );
	RRTFactory::RRT_TYPE eCurrentType = eStartType;
	std::map<std::string, long > mapElapsedTotalTime;
	std::map<std::string, int > mapNumberOfAcceptedNodes;
	std::map<std::string, int > mapNumberOfRejectedNodes;
	std::map<std::string, int > mapNumberOfTriesToBuild;
	std::map<std::string, int > mapPathFound;
	std::map<std::string, std::vector<long> > mapElapsedPartialTime;
	clock_t totalExecutionTime = clock( );
	int iI;
	for ( iI = 0; iI < m_iNumberOfTests; iI++ ) {
		do {
			RRT *pCurrentRRT = m_pRRTFactory->createRRT( eCurrentType );
			eCurrentType = m_pRRTFactory->nextType( );
			clock_t elapsedTime = clock( );
			pCurrentRRT->buildTree( );
			elapsedTime = clock( ) - elapsedTime;
			mapElapsedTotalTime[ pCurrentRRT->getName( ) ] += elapsedTime;
			mapNumberOfAcceptedNodes[ pCurrentRRT->getName( ) ] += pCurrentRRT->getNumberOfAcceptedNodes( );
			mapNumberOfRejectedNodes[ pCurrentRRT->getName( ) ] += pCurrentRRT->getNumberOfRejectedNodes( );
			mapNumberOfTriesToBuild[ pCurrentRRT->getName( ) ] += pCurrentRRT->getNumberOfTriesUsedToBuildTree( );
			GraphEdge *pLastEdge = pCurrentRRT->findPath( ).back( );
			mapPathFound[ pCurrentRRT->getName( ) ] += ( pLastEdge && pLastEdge->getVertex2( ) == pCurrentRRT->getEndVertex( ) ) ? 1 : 0;
			mapElapsedPartialTime[ pCurrentRRT->getName( ) ].push_back( elapsedTime );
			delete pCurrentRRT;
		} while ( eCurrentType != eStartType );
	} // for
	totalExecutionTime = clock( ) - totalExecutionTime;
	std::cout << "STATUS REPORT" << std::endl;
	std::cout << std::endl;
	std::cout << "  Total number of algorithms: " << mapElapsedTotalTime.size( ) << std::endl;
	std::cout << "  Number of tests: " << m_iNumberOfTests << std::endl;
	std::cout << "  Total execution time: " << (double)totalExecutionTime / 1000.0 << "s " << std::endl;
	std::cout << std::endl;
	std::cout << "ALGORITHMS " << std::endl;
	std::cout << std::endl;
	std::map<std::string, long >::iterator it = mapElapsedTotalTime.begin( );
	while( it != mapElapsedTotalTime.end( ) ) {
		std::cout << "  Algorithm: " << it->first << std::endl;
		std::cout << "  Execution total time: " << (double)it->second / 1000.0 <<  "s " << std::endl;
		std::cout << "  Execution average time: " << (double)it->second / (double)m_iNumberOfTests / 1000.0 <<  "s " << std::endl;
		std::cout << "  Average Number of accepted nodes: " << mapNumberOfAcceptedNodes[ it->first ] /m_iNumberOfTests << std::endl;
		std::cout << "  Average Number of rejected nodes: " << mapNumberOfRejectedNodes[ it->first ] /m_iNumberOfTests<< std::endl;
		std::cout << "  Average Number of tries to build tree: " << mapNumberOfTriesToBuild[ it->first ] /m_iNumberOfTests<< std::endl;
		std::cout << "  Average Path found: " << mapPathFound[ it->first ] / m_iNumberOfTests << std::endl;
		std::cout << std::endl;
		it++;
	} // while

}
