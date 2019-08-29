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


#include <powergine/primitives/ray.h>

namespace powergine {
	namespace primitives {
		
// Constructors/Destructors
// Methods
Ray::Ray ( const Vector3D &rkOrigin, const Vector3D &rkDirection ) {
  m_oOrigin = rkOrigin;
  m_oDirection = rkDirection;
} // Ray

Ray::Ray( ) {
  m_oOrigin = Vector3D::ORIGO;
  m_oDirection = Vector3D::ORIGO;
} // Ray

const Vector3D Ray::getOrigin( ) {
   return m_oOrigin;
} // getOrigin

const Vector3D Ray::getDirection( ) {
   return m_oDirection;
} // getOrigin
   
void Ray::setOrigin( const Vector3D &rkOrigin ) {
   m_oOrigin = rkOrigin;
} // getOrigin

void Ray::setDirection( const Vector3D &rkDirection ) {
   m_oDirection = rkDirection;
} // getOrigin
	
	}; // primitives
}; // namespace powergine
