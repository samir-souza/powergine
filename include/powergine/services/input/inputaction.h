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

#ifndef INPUTACTION_H
#define INPUTACTION_H

#include <string>

namespace powergine {
   namespace services {
      namespace input {


		  /**
		   * An input action is an event handler, responsible for
		   * mapping a specific input event to a internal type.
		   * It classifies the event and when it occurs, the input
		   * manager is capable of recognizing the interested listener
		   * to send a notification
		   */
		class InputAction {

		public:

		   enum EVENT_TYPE {
			  EVENT_ON_KBD_KEY_PRESSED         = 0,
			  EVENT_ON_KBD_KEY_RELEASED        = 1,

			  EVENT_ON_MOUSE_BUTTON_PRESSED    = 2,
			  EVENT_ON_MOUSE_BUTTON_RELEASED   = 4,
			  /*
			  EVENT_ON_MOUSE_LEFT              = 8,
			  EVENT_ON_MOUSE_RIGHT             = 16,
			  EVENT_ON_MOUSE_UP                = 32,
			  EVENT_ON_MOUSE_DOWN              = 64,
			  EVENT_ON_MOUSE_MOVE              = EVENT_ON_MOUSE_LEFT|EVENT_ON_MOUSE_RIGHT|EVENT_ON_MOUSE_UP|EVENT_ON_MOUSE_DOWN,
			  */
			  EVENT_ON_JOY_BUTTON_PRESSED      = 128,
			  EVENT_ON_JOY_BUTTON_RELEASED     = 256,

			  EVENT_ON_JOY_AXIS_LEFT           = 512,
			  EVENT_ON_JOY_AXIS_RIGHT          = 1024,
			  EVENT_ON_JOY_AXIS_UP             = 2048,
			  EVENT_ON_JOY_AXIS_DOWN           = 4096,
			  EVENT_ON_JOY_AXIS_MOVE           = EVENT_ON_JOY_AXIS_LEFT|EVENT_ON_JOY_AXIS_RIGHT|EVENT_ON_JOY_AXIS_UP|EVENT_ON_JOY_AXIS_DOWN,
		   };

		   // It receives the event type and the code. The code
		   // can be, for instance, the key code
		   inline InputAction( EVENT_TYPE eEventType, int iCode ) :
			  m_eEventType( eEventType ), m_bActive( false ), m_iCode( iCode ) { };

			// Checks if the action is active or not
		   inline bool isActive( ) const { return m_bActive; }

		   // Update the action activation
		   inline void setActive( bool bActive ) { m_bActive = bActive; }

		   // Toggles the action activation
		   inline void toggle( ) { m_bActive = !m_bActive; }

		   // Checks if this action is of the same type of the given
		   // event type
		   inline bool isEventActive( EVENT_TYPE eEventType ) const {
			  return ( ( eEventType & m_eEventType ) == eEventType );
		   }

		   // Gets the action code
		   inline int getCode( ) const { return m_iCode; }

		   // Gets the action type
		   inline EVENT_TYPE getEventType( ) const { return m_eEventType; }

		private:
		   EVENT_TYPE m_eEventType;
		   bool m_bActive;
		   int m_iCode;
		};

      }; // input
   }; // services
}; //powergine


#endif //INPUTACTION_H

