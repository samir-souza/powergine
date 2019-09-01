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

#ifndef OBSTACLE_H_
#define OBSTACLE_H_

#include <powergine/primitives/vector3d.h>

using namespace powergine::primitives;

/**
 * This class represents an obstacle that can be positioned
 * inside a map
 */
class Obstacle{

	private:

		Vector3D upperLeftCorner;
		Vector3D lowerRightCorner;

	public:

		// default constructor
		Obstacle( Vector3D upperLeftCorner, Vector3D lowerRightCorner );

		// Checks if a given point lies inside the obstacle
		bool isCollision(Vector3D point);

		// Returns the obstacle height
		float getHeight();

		// Returns the obstacle width
		float getWidth();

		// Returns the upper left corner point
		const Vector3D& getUpperLeftCorner();

		// Returns the lower right corner point
		const Vector3D& getLowerRightCorner();
};

#endif /*OBSTACLE_H_*/
