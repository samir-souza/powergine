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

#ifndef Q3BSPVISDATA_H
#define Q3BSPVISDATA_H

namespace powergine {
   namespace tools {

	/**
	 * This is part of the Quake 3 BSP loader tool
	 * It represents the visibility information pre-computed
	 * into the BSP for specific points in the map
	 */
	class Q3BSPVisData {

	public:
	   int iNumClusters;   // The number of clusters
	   int iBytesPerCluster;  // The amount of bytes (8 bits) in the cluster's bitset
	   char *pcBitSet;    // The array of bytes that holds the cluster bitsets

	};

   }; // tools
}; // powergine

#endif //Q3BSPVISDATA_H
