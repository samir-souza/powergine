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

#ifndef BSPVISDATA_H
#define BSPVISDATA_H

#include <powergine/utils/bitset.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A BSP Visdata is part of the BSP (Binary Spatial Partition) tree toolkit
		 * It represents the visibility info about clusters which composes the
		 * environment. For instance, if a cluster is not visible, it will not
		 * be rendered
		 */
		class BSPVisData {

		public:

		   BSPVisData( unsigned int uiID, utils::BitSet *pClusters );

		   virtual ~BSPVisData( );

		   // Check if a given cluster is visible
		   bool isClusterVisible( unsigned int uiClusterID );

		   // Returns the visdata ID
		   unsigned int getID( );

		private:
		   unsigned int m_uiID;
		   utils::BitSet *m_pClusters;

		};

	}; // sceneobjects
}; // powergine

#endif //BSPVISDATA_H
