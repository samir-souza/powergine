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


#include <powergine/services/video/videoproperties.h>

namespace powergine {
	namespace services {
		namespace video {


const VideoProperties DEFAULTPROPERTIES( VideoProperties::DOUBLEBUFFER |
                                                          VideoProperties::RESIZABLE |
                                                          VideoProperties::HARDWAREACCELERATED );

VideoProperties::VideoProperties( int iProperties ) {
   setProperties( iProperties );
}

void VideoProperties::reset( ) {
   m_iProperties = 0;
}

void VideoProperties::setProperties( int iProperties ) {
   m_iProperties = iProperties;
}

int VideoProperties::getProperties( ) const {
   return m_iProperties;
}

void VideoProperties::addProperty( PROPERTIES eProperty ) {
   m_iProperties |= eProperty;
}

void VideoProperties::removeProperty( PROPERTIES eProperty ) {
   if ( isSet( eProperty ) ) {
      m_iProperties ^= eProperty;
   } // if
}

void VideoProperties::toggleProperty( PROPERTIES eProperty ) {
   m_iProperties ^= eProperty;
}

bool VideoProperties::isSet( PROPERTIES eProperty ) {
   return ( ( m_iProperties & eProperty ) != 0 );
}

		}; // video
	}; // services
}; // namespace powergine
