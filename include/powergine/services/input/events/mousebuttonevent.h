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

#ifndef MOUSEBUTTONEVENT_H
#define MOUSEBUTTONEVENT_H


namespace powergine {
	namespace services {
		namespace input {
			namespace events {

			/**
			 * It represents an event produced by a Mouse button action
			 */
			class MouseButtonEvent {

			public:

			   enum MOUSE_BUTTON_CODE {
				  MOUSE_BUTTON_NONE        = 0,
				  MOUSE_BUTTON_LEFT        = 1,
				  MOUSE_BUTTON_MIDDLE      = 2,
				  MOUSE_BUTTON_RIGHT       = 3,
				  MOUSE_BUTTON_WHEELUP     = 4,
				  MOUSE_BUTTON_WHEELDOWN   = 5
			   };

			   enum MOUSE_BUTTON_STATE {
				  MOUSE_BUTTON_RELEASED   = 0,
				  MOUSE_BUTTON_PRESSED    = 1
			   };

			   inline MouseButtonEvent( int iCode, int iState, int iX, int iY, bool bWheelButton = false ) :
				  m_iCode( iCode ), m_iState( iState ), m_iX( iX ), m_iY( iY ), m_bWheelButton( bWheelButton ) { }

			   // Returns the position of the mouse in X axis
			   inline int getX( ) const { return m_iX; }

			   // Returns the position of the mouse in Y axis
			   inline int getY( ) const { return m_iY; }

			   // Returns the mouse button code
			   inline int getCode( ) const { return m_iCode; }

			   // Returns the mouse button state
			   inline int getState( ) const { return m_iState; }

			   // Returns true if the button is the wheel button, false otherwise
			   inline bool isWheelButton( ) const { return m_bWheelButton; }

			private:
			   int m_iCode;
			   int m_iState;
			   int m_iX;
			   int m_iY;
			   bool m_bWheelButton;
			};

			}; // events
		}; // input
	}; // services
}; // powergine

#endif //MOUSEBUTTONEVENT_H
