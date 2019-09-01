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



#include <powergine/services/video/renderwindow.h>

namespace powergine {
	namespace services {
		namespace video {


RenderWindow::RenderWindow( RenderMode *pRenderMode, const VideoProperties &rkProperties ) :
   m_pCurrentRenderMode( pRenderMode ),
   m_oProperties( rkProperties )
{
}

RenderWindow::~RenderWindow( ) {
   delete m_pCurrentRenderMode;
}


const RenderMode *RenderWindow::getCurrentRenderMode( ) const {
   return m_pCurrentRenderMode;
}

bool RenderWindow::setCurrentRenderMode( RenderMode *pRenderMode ) {
   std::vector<RenderMode*>::iterator ppBegin = m_vRenderModes.begin( );
   std::vector<RenderMode*>::iterator ppEnd = m_vRenderModes.end( );

   while( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pRenderMode ) {
         m_pCurrentRenderMode = pRenderMode;
         return true;
      } // if
      ppBegin++;
   } // while
   return false;
}

bool RenderWindow::addRenderMode( RenderMode *pRenderMode ) {
   std::vector<RenderMode*>::iterator ppBegin = m_vRenderModes.begin( );
   std::vector<RenderMode*>::iterator ppEnd = m_vRenderModes.end( );

   while( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pRenderMode ) {
         return false;
      } // if
      ppBegin++;
   } // while
   m_vRenderModes.push_back( pRenderMode );
   return true;
}

bool RenderWindow::removeRenderMode( RenderMode *pRenderMode ) {
   std::vector<RenderMode*>::iterator ppBegin = m_vRenderModes.begin( );
   std::vector<RenderMode*>::iterator ppEnd = m_vRenderModes.end( );

   while( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pRenderMode ) {
         m_vRenderModes.erase( ppBegin );
         return true;
      } // if
      ppBegin++;
   } // while
   return false;
}

std::vector<RenderMode*>& RenderWindow::getRenderModes( ) {
   return m_vRenderModes;
}

VideoProperties* RenderWindow::getProperties( ) const {
   return const_cast<VideoProperties*>( &m_oProperties );
} // getProperties

		}; // video
	}; // services
}; // namespace powergine
