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

#ifndef JOYEVENT_H
#define JOYEVENT_H

namespace powergine {
	namespace services {
		namespace input {
			namespace events {

			/**
			 * It represents an event produced by a joystick action
			 */
			class JoyEvent {

			public:
			   enum STATE {
				  NONE,
				  AXIS_MOVE,
				  BALL_MOVE,
				  HAT_MOVE,
				  BUTTON_DOWN,
				  BUTTON_UP
			   };

			   enum CODE {
				  BUTTON_01,
				  BUTTON_02,
				  BUTTON_03,
				  BUTTON_04,
				  BUTTON_05,
				  BUTTON_06,
				  BUTTON_07,
				  BUTTON_08,
				  BUTTON_09,
				  BUTTON_10,
				  BUTTON_11,
				  BUTTON_12,
				  BUTTON_13,
				  BUTTON_14,
				  BUTTON_15,
				  BUTTON_16
			   };

			   JoyEvent( JoyEvent::STATE eState, JoyEvent::STATE eButtonState, JoyEvent::CODE eButtonCode, unsigned short usAxisID, int iAxisValue );

			   // Returns the event state
			   STATE getState( ) const;

			   // Returns the button state
			   STATE getButtonState( ) const;

			   // Returns the affected axis
			   unsigned short getAxis( ) const;

			   // Returns the current value of the axis
			   int getAxisValue( ) const;

			private:
			   STATE m_eState;
			   STATE m_eButtonState;
			   CODE m_eButtonCode;
			   unsigned short m_usAxisID;
			   int m_iAxisValue;

			};

			}; // events
		}; // input
	}; // services
}; // powergine

#endif //JOYEVENT_H
