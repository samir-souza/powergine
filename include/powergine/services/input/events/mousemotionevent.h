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

#ifndef MOUSEMOTIONEVENT_H
#define MOUSEMOTIONEVENT_H

#include <powergine/services/input/events/mousebuttonevent.h>


namespace powergine {
	namespace services {
		namespace input {
			namespace events {


			/**
			 * It represents an event produced by a Mouse motion action
			 */
			class MouseMotionEvent {

			public:

			   inline MouseMotionEvent( int iX, int iY, int iXRelative, int iYRelative, unsigned int uiButtonsState ) :
				  m_iX( iX ), m_iY( iY ),
				  m_iXRelative( iXRelative ), m_iYRelative( iYRelative ),
				  m_uiButtonsState( uiButtonsState ) { }

			   // Returns the position of the mouse in X axis
			   inline int getX( ) const { return m_iX; }

			   // Returns relative position of the mouse in X axis
			   inline int getXRelative( ) const { return m_iXRelative; }

			   // Returns the position of the mouse in Y axis
			   inline int getY( ) const { return m_iY; }

			   // Returns the relative position of the mouse in Y axis
			   inline int getYRelative( ) const { return m_iYRelative; }

			   // True if the given button is pressed, false otherwise
			   inline bool isButtonPressed( MouseButtonEvent::MOUSE_BUTTON_CODE eMouseButton ) {
				  if ( eMouseButton == MouseButtonEvent::MOUSE_BUTTON_NONE ) {
					 return ( m_uiButtonsState == 0 ) ? true : false;
				  } // if
				  return ( ( m_uiButtonsState & ( 1 << ( eMouseButton - 1 ) ) ) > 0 );
			   }

			private:
			   int m_iX;
			   int m_iY;
			   int m_iXRelative;
			   int m_iYRelative;
			   unsigned int m_uiButtonsState;
			};

			}; // events
		}; // input
	}; // services
}; // powergine

#endif //MOUSEMOTIONEVENT_H
