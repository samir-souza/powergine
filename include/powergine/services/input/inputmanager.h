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

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include <vector>
#include <map>
#include <string>
#include <powergine/services/input/inputaction.h>
#include <powergine/services/input/listeners/joylistener.h>
#include <powergine/services/input/listeners/mousebuttonlistener.h>
#include <powergine/services/input/listeners/mousemotionlistener.h>
#include <powergine/services/input/listeners/keylistener.h>
#include <powergine/services/input/events/joyevent.h>
#include <powergine/services/input/events/mousebuttonevent.h>
#include <powergine/services/input/events/mousemotionevent.h>
#include <powergine/services/input/events/keyevent.h>

namespace powergine {
   namespace services {
      namespace input {

		  /**
		   * This class is responsible for managing the input
		   * events (keyboard, mouse and joystick) and notify
		   * the respective listeners about the events
		   */
		class InputManager {

		public:

		   InputManager( );

		   virtual ~InputManager( );

		   enum MANAGER_TYPE {
			  MANAGER_SDL             = 0,
			  MANAGER_DIRECT_INPUT    = 1
		   };

		   enum INPUT_TYPE {
			  INPUT_SYSTEM         = 1,
			  INPUT_KBD            = 2,
			  INPUT_MOUSE_BUTTON   = 4,
			  INPUT_MOUSE_MOVE     = 8,
			  INPUT_JOY            = 16,
			  INPUT_ALL            = 31
		   };

		   // Register a new input action to handle a specific action
		   void addInputAction( InputAction *pInputAction );

		   // Removes a registered input action
		   void removeInputAction( InputAction *pInputAction );

		   // Removes all registered input actions
		   void removeAllInputActions( );

		   // Registers a new keyboard events listener
		   void addKeyListener( listeners::KeyListener *pListener );

		   // Registers a new mouse button events listener
		   void addMouseButtonListener( listeners::MouseButtonListener *pListener );

		   // Registers a new mouse motion events listener
		   void addMouseMotionListener( listeners::MouseMotionListener *pListener );

		   // Registers a new joystick events listener
		   void addJoyListener( listeners::JoyListener *pListener );

		   // Removes a registered keyboard events listener
		   void removeKeyListener( listeners::KeyListener *pListener );

		   // Removes a registered mouse button events listener
		   void removeMouseButtonListener( listeners::MouseButtonListener *pListener );

		   // Removes a registered mouse motion events listener
		   void removeMouseMotionListener( listeners::MouseMotionListener *pListener );

		   // Removes a registered joystick events listener
		   void removeJoyListener( listeners::JoyListener *pListener );

		   // Remove all registered listeners
		   void removeAllListeners( );

		   // Retrieve all keyboard listeners
		   std::vector<listeners::KeyListener*>& getKeyListeners( );

		   // Retrieve all mouse buttom listeners
		   std::vector<listeners::MouseButtonListener*>& getMouseButtonListeners( );

		   // Retrieve all mouse motion listeners
		   std::vector<listeners::MouseMotionListener*>& getMouseMotionListeners( );

		   // Retrieve all joystick listeners
		   std::vector<listeners::JoyListener*>& getJoyListeners( );

		   // Listeners events notification methods
		   void notifyKeyListeners( events::KeyEvent *pEvent );
		   void notifyMouseButtonListeners( events::MouseButtonEvent *pEvent );
		   void notifyMouseMotionListeners( events::MouseMotionEvent *pEvent );
		   void notifyJoyListeners( events::JoyEvent *pEvent );

		   // Process a specific input device and fire all listeners when necessary
		   virtual void processInput( INPUT_TYPE eType = INPUT_ALL ) = 0;

		   // Explicitly set the mouse position on screen
		   virtual void setMousePosition( int iX, int iY );

		   // Retrieves the current mouse position
		   virtual void getMousePosition( int &riX, int &riY ) = 0;

		private:

		   std::map< std::pair<int, InputAction::EVENT_TYPE>, InputAction*> m_mapInputActions;
		   std::vector<listeners::KeyListener*> m_vecKeyListeners;
		   std::vector<listeners::MouseButtonListener*> m_vecMouseButtonListeners;
		   std::vector<listeners::MouseMotionListener*> m_vecMouseMotionListeners;
		   std::vector<listeners::JoyListener*> m_vecJoyListeners;
		   bool m_bMouseRePositionEvent;
		};

      }; // input
   }; // services
}; //powergine


#endif //INPUTMANAGER_H

