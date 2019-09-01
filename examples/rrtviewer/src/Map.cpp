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

#include <Map.h>
#include <time.h>

Map::Map(int h, int l, const Vector3D &rki, const Vector3D &rkg, bool r):
	height (h),
	width (l),
	initialAgentPosition (rki),
	targetAgentPosition (rkg) {
	if( r ) {
		randomMap();
	} // if
}//Map

void Map::addObstacle(Obstacle *obs){
	obstacles.push_back(obs);
}//addObstacle

bool Map::anyCollision(const Vector3D &rkpoint){
	if( rkpoint.getX( ) < 0.0f || rkpoint.getX( ) > width ||
		rkpoint.getY( ) < 0.0f || rkpoint.getY( ) > height ) { //out of the map
		return true;
	} // if
	unsigned int iI;
	for( iI = 0; iI < obstacles.size( ); iI++ ){
		if ( obstacles[ iI ]->isCollision( rkpoint ) ) {
			return true;
		} // if
	} // for
	return false;
}//isCollision

void Map::randomMap(){

	srand( time(0) );
	obstacles.clear( );

	int numberOfObstacles = rand( ) % 30 + 1;

	int i, x, y, obsHeight, obsLength;
	for (i = 0; i < numberOfObstacles; ++i) {
		x = rand() % getHeight() + 1;
		y = rand() % getWidth() + 1;
		obsHeight = rand() % 10 + 1;
		obsLength = rand() % 10 + 1;
		Vector3D aux1(x, y, 0);
		if(x + obsHeight > getHeight()){
			x = x + (getHeight() - x);
		}else{
			x = x + obsHeight;
		}
		if(y - obsLength < 0){
			y = 0;
		}else{
			y = y - obsLength;
		}
		Vector3D aux2(x, y, 0);
		Obstacle *aux = new Obstacle(aux1, aux2);
		if(!aux->isCollision(initialAgentPosition) && !aux->isCollision(targetAgentPosition)){

			addObstacle( aux );
		}
	}
}

std::string Map::toString(){
	std::stringstream output;

	int i, j;
	Vector3D aux(0, 0, 0);
	for (i = 0; i <= getHeight(); ++i) {
		for (j = 0; j <= getWidth(); ++j) {
			aux.setX(i);
			aux.setY(j);
			if(i == 0 || i == getHeight()){
				if (j == 0) {
					output << "|";
				} else {
					if (j != getWidth()){
						output << "-";
					} else {
						output << "|" << std::endl;
					} // else
				} // else
			} else {
				if (j == 0) {
					output << "|";

				} else if ( j == getWidth( ) ){
					output << "|" << std::endl;

				} else if( anyCollision( aux ) ){
					output << ".";

				} else {
					if ( initialAgentPosition.getX() == j && initialAgentPosition.getY() == i) {
						output << "i";

					} else if (targetAgentPosition.getX() == j && targetAgentPosition.getY() == i) {
						output << "g";

					} else {
						output << " ";

					} // else
				} // else
			} // else
		} // for
	} // for

	return output.str( );
}

void Map::writeMap(){
	std::ofstream mapFile( "map.dat", std::ofstream::binary );
	mapFile.write( reinterpret_cast<char*>( this ), sizeof( Map ) - sizeof( std::vector<Obstacle*> ) );
	mapFile << obstacles.size( );
	unsigned int uiI;
	for ( uiI = 0; uiI < obstacles.size( ); uiI++ ) {
		mapFile.write( reinterpret_cast<char*>( obstacles[ uiI ] ), sizeof( Obstacle ) );
	} // for
	mapFile.close( );
}

void Map::readMap(){
	std::ifstream mapFile( "map.dat", std::ifstream::binary );
	if ( !mapFile.good( ) ) {
		return;
	} // if
	mapFile.read( reinterpret_cast<char*>( this ), sizeof( Map ) - sizeof( std::vector<Obstacle*> ) );
	unsigned int uiI;
	unsigned int uiObstaclesNumber;
	mapFile >> uiObstaclesNumber;
	obstacles.clear( );
	char *pBuffer = 0;
	for ( uiI = 0; uiI < uiObstaclesNumber; uiI++ ) {
		 pBuffer = new char[ sizeof( Obstacle ) ];
		mapFile.read( pBuffer, sizeof( Obstacle ) );
		addObstacle( reinterpret_cast<Obstacle*>( pBuffer ) );
	} // for
	mapFile.close( );
}

void Map::setInitialAgentPosition(const Vector3D &rknewInit){
	initialAgentPosition = rknewInit;
}

void Map::setTargetAgentPosition(const Vector3D &rknewGoal){
	targetAgentPosition = rknewGoal;
}

int Map::getHeight(){
	return height;
}

int Map::getWidth(){
	return width;
}

std::vector<Obstacle*> Map::getObstacles(){
	return obstacles;
}
