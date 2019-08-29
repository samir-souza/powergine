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

#ifndef JOYLISTENER_H
#define JOYLISTENER_H

#include <powergine/services/input/events/joyevent.h>

namespace powergine {
   namespace services {
      namespace input {
         namespace listeners {

         /**
          * Interface that must be implemented by the Joystick
          * listener
          */
		class JoyListener {

		public:

		   inline JoyListener( ) { };

		   inline virtual ~JoyListener( ) { };

		   // Event called when X or Y were changed
		   virtual void axisMoved( events::JoyEvent *pEvent ) = 0;

		   // Event called when the ball scroll of the joystick moved
		   virtual void ballMoved( events::JoyEvent *pEvent ) = 0;

		   // Event called when the joystick hat moved
		   virtual void hatMoved( events::JoyEvent *pEvent ) = 0;

		   // Event called when a button is pressed
		   virtual void buttonPressed( events::JoyEvent *pEvent ) = 0;

		   // Event called when a button is released
		   virtual void buttonReleased( events::JoyEvent *pEvent ) = 0;

		};

         }; // listeners
      }; // input
   }; // services
}; // powergine

#endif //JOYLISTENER_H
