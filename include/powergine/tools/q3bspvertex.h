// Copyright (c) 2004 Samir Araujo <samir.araujo@gmail.com>
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

#ifndef Q3BSPVERTEX_H
#define Q3BSPVERTEX_H

#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/textcoords.h>

namespace powergine {
   namespace tools {

	/**
	 * This is part of the Quake 3 BSP loader tool
	 * The objects are composed by vertices. This class
	 * also holds information about texture coords, lightmap,
	 * normal and diffuse color
	 */
	class Q3BSPVertex {

	public:
		primitives::Vector3D oPosition;  // (x, y, z) position.
		primitives::TextCoords oTextureCoord;  // (u, v) texture coordinate
		primitives::TextCoords oLightmapCoord; // (u, v) lightmap coordinate
		primitives::Vector3D oNormal;  // (x, y, z) normal vector
		unsigned int color;
	};

   }; // tools
}; // powergine

#endif //Q3BSPVERTEX_H
