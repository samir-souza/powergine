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


#include <powergine/utils/contact.h>
#include <powergine/sceneobjects/aabb.h>

namespace powergine {
	namespace utils {

Contact::Contact( sceneobjects::AABB* objectA, sceneobjects::AABB* objectB ) :
	objectA( objectA ), objectB( objectB ) {

}

void Contact::sort( ) {

}
const primitives::Vector3D Contact::getNormal( ) const {
   return m_oNormal;
}
void Contact::setNormal( const primitives::Vector3D &rkNormal ) {
  m_oNormal = rkNormal;
}
unsigned int Contact::getNumberPoints( ) const {
   return m_uiNumberPoints;
}
void Contact::setNumberPoints( unsigned int uiNumberPoints ) {
   m_uiNumberPoints = uiNumberPoints;
}

const primitives::Vector3D& Contact::operator[ ]( int iIndex ) {
   assert( iIndex >=0 && iIndex < m_uiNumberPoints );
   return m_oContactPoints[ iIndex ];
}

	}; // utils
}; // namespace powergine
