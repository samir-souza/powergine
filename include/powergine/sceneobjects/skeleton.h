// Copyright (c) 2004 Samir Araujo
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

#ifndef SKELETON_H
#define SKELETON_H

#include <string>
#include <powergine/sceneobjects/scenenode.h>

namespace powergine {
	namespace sceneobjects {

		/**
		 * A skeleton is a structure that allows the developer
		 * to deform a mesh by using an approach similar to a
		 * skeleton and the muscles/skin. The bones must be attached
		 * to the mesh and, transforming the bones, the mesh will
		 * be transformed too
		 * TODO: it must be implemented
		 */
		class Skeleton : public SceneNode {
		public:
			Skeleton( const std::string &rstrName );

			virtual ~Skeleton( );

		};

	}; // scenenode
}; // namespace powergine

#endif //SKELETON_H
