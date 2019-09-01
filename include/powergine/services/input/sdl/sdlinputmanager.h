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

#ifndef SDLINPUTMANAGER_H
#define SDLINPUTMANAGER_H

#include <string>
#include <powergine/services/input/inputmanager.h>
#include <powergine/services/input/events/keyevent.h>
#include <powergine/services/input/events/mousebuttonevent.h>
#include <powergine/services/input/events/mousemotionevent.h>
#include <powergine/services/input/events/joyevent.h>

namespace powergine {
   namespace services {
      namespace input {
         namespace sdl {

         /**
          * SDL implementation of the input manager
          */
		class SDLInputManager : public InputManager {

		public:

		   inline SDLInputManager( ) : InputManager( ) { };

		   virtual ~SDLInputManager( ) { };

		   // initialize the manager
		   void initialize( );

		   // Process a given input envent
		   virtual void processInput( InputManager::INPUT_TYPE eType = InputManager::INPUT_ALL );

		   // Explicit set the mouse position on screen
		   virtual void setMousePosition( int iX, int iY );

		   // Get the current mouse position
		   virtual void getMousePosition( int &riX, int &riY );

		private:
		   int m_uiKbdCodeOffset;
		   int m_uiMouseButtonCodeOffset;
		   int m_uiMouseMotionCodeOffset;
		   int m_uiJoyCodeOffset;

		};
         }; // sdl
      }; // input
   }; // services
}; //powergine

#endif //SDLINPUTMANAGER_H

