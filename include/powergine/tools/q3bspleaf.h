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

#ifndef Q3BSPLEAF_H
#define Q3BSPLEAF_H

namespace powergine {
   namespace tools {

	/**
	 * This is part of the Quake 3 BSP loader tool
	 * It represents a tree leaf
	 */
	class Q3BSPLeaf {

	public:
		int iCluster;				// The visibility cluster
		int iArea;					// The area portal
		struct {
		  int x,y,z;    // The bounding box min position.
		} oBBMinPos;

		struct {
		  int x,y,z;    // The bounding box max position.
		} oBBMaxPos;


		int iLeafFaceStartIndex;				// The first index into the face array
		int iNumLeafFaces;			// The number of faces for this leaf
		int iLeafBrushStartIndex;				// The first index for into the brushes
		int iNumLeafBrushes;		// The number of brushes for this leaf

	};

   }; // tools
}; // powergine

#endif //Q3BSPLEAF_H
