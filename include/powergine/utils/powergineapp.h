// Copyright (c) 2004 Samir Araujo <samir.araujo@gmail.com>
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

#ifndef POWERGINEAPP
#define POWERGINEAPP

#include <powergine/services/input/listeners/keylistener.h>
#include <powergine/services/input/listeners/joylistener.h>
#include <powergine/services/input/listeners/mousebuttonlistener.h>
#include <powergine/services/input/listeners/mousemotionlistener.h>

using namespace powergine::services::input;

namespace powergine {
	namespace utils {

	/**
	 * Helper class that can be used by the developer to
	 * create a new application which uses PowerGine
	 */
	class PowerGineApp : public listeners::KeyListener,
						 public listeners::MouseButtonListener,
						 public listeners::MouseMotionListener,
						 public listeners::JoyListener  {

	public:
		inline PowerGineApp( int argc = 0, char* argv[] = 0 ) { };

		virtual ~PowerGineApp( ) { };

		// Called during the initialization
		virtual void setup( ) = 0;

		// Called by the user. It starts the execution of the application
		virtual void run( ) = 0;

	   // keyboard events
	   virtual void released( events::KeyEvent *pEvent ) { };
	   virtual void pressed( events::KeyEvent *pEvent ) { };

	   // mouse button events
	   virtual void pressed( events::MouseButtonEvent *pEvent ) { };
	   virtual void released( events::MouseButtonEvent *pEvent ) { };

	   // mouse motion events
	   virtual void dragged( events::MouseMotionEvent *pEvent ) { };
	   virtual void moved( events::MouseMotionEvent *pEvent ) { };

	   // joystick events
	   virtual void axisMoved( events::JoyEvent *pEvent ) { };
	   virtual void ballMoved( events::JoyEvent *pEvent ) { };
	   virtual void hatMoved( events::JoyEvent *pEvent ) { };
	   virtual void buttonPressed( events::JoyEvent *pEvent ) { };
	   virtual void buttonReleased( events::JoyEvent *pEvent ) { };

	};

	}; // utils
}; //namespace powergine

#endif /*POWERGINEAPP*/
