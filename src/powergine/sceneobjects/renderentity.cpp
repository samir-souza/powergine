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


#include <powergine/sceneobjects/renderentity.h>

namespace powergine {
	namespace sceneobjects {
	
// Constructors/Destructors
// Methods
RenderEntity::RenderEntity( ) :
	BaseEntity( true )
{
	
} // RenderEntity

RenderEntity::~RenderEntity( ) {

}


bool RenderEntity::render( Frustum *pkFrustum ) {
  if ( !m_bActive ) {
      return false;
  } // if
  return true;
} // render

void RenderEntity::accept( const utils::EntityVisitor &rkVisitor ) {
   //rkVisitor.visitRenderEntity( this );
}

	}; // sceneobjects
}; // namespace powergine