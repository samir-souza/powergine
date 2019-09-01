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

#ifndef MAP_H_
#define MAP_H_

#include <fstream>
#include <vector>
#include <iostream>
#include <Obstacle.h>
#include <powergine/primitives/vector3d.h>

using namespace powergine::primitives;

/**
 * This class represents a 2D map. It can contains obstacles
 * It will be used by the RRTs to grow trees
 */
class Map{

	private:

		int height;
		int width;
		Vector3D initialAgentPosition;
		Vector3D targetAgentPosition;
		std::vector<Obstacle*> obstacles;

	public:
		// Constructor. Map height, map width, initial agent position,
		// target agent position, randomize map
		Map(int h, int w, const Vector3D &rki, const Vector3D &rkg, bool randomMap);

		// Add a new obstacle to the map
		void addObstacle(Obstacle *obs);

		// Check if at a given point there are an obstacle (collision) or not
		bool anyCollision(const Vector3D &rkpoint);

		// Helper function that generates random obstacles
		void randomMap();

		// Defines the initial position and the targetAgentPosition positions
		// It is necessary to avoid creating obstacles on the same
		// place the agent will be and wants to reach
		void setInitialAgentPosition(const Vector3D &rki);
		void setTargetAgentPosition(const Vector3D &rkg);

		// Write a map to file
		void writeMap( );

		// Read a map from file
		void readMap();

		// Returns the map height
		int getHeight();
		// Returns the map width
		int getWidth();

		// Returns a list of obstacles
		std::vector<Obstacle*> getObstacles();

		// Returns a string representation of the map
		std::string toString( );
};

#endif /*MAP_H_*/
