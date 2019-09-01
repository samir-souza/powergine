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

#ifndef SRTNODE_H
#define SRTNODE_H

#include <powergine/sceneobjects/renderentity.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/quaternion.h>

namespace powergine {
	namespace sceneobjects {


		/**
		 * This is a special node type used to compose SRTrees
		 */
		class SRTNode : public RenderEntity {

		public:

		   SRTNode( );

		   virtual ~SRTNode( );

		   // Returns the node's scaling factor
		   float getScaling( ) const;

		   // Returns the node's translation
		   const primitives::Vector3D& getTranslation( ) const;

		   // Returns the node's rotation
		   const primitives::Quaternion& getRotation( ) const;

		   // Updates the node's scaling
		   void setScaling( float fScaling );

		   // Updates the node's translation
		   void setTranslation( const primitives::Vector3D &rkTranslation );

		   // Updates the node's rotation
		   void setRotation( const primitives::Quaternion &rkRotation );

		   // Applies a scaling factor to this node
		   void doScaling( float fScaling );

		   // Applies a translation to this node
		   void doTranslation( const primitives::Vector3D &rkTranslation );

		   // Applies a rotation to this node
		   void doRotation( const primitives::Quaternion &rkRotation );

		   // RTTI method which accepts a Visitor design pattern
		   virtual void accept( const utils::EntityVisitor &rkVisitor );

		private:
		   float m_fScaling;
		   primitives::Quaternion m_oRotation;
		   primitives::Vector3D m_oTranslation;

		};

	}; // sceneobjects
}; // namespace powergine

#endif //SRTNODE_H
