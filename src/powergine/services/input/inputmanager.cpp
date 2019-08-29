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


#include <powergine/services/input/inputmanager.h>

namespace powergine {
   namespace services {
      namespace input {

InputManager::InputManager( ) {
   m_bMouseRePositionEvent = false;
} // InputManager


InputManager::~InputManager( ) {
   removeAllInputActions( );
   removeAllListeners( );
} // ~InputManager

void InputManager::addInputAction( InputAction *pInputAction ) {
   // ignore null actions
   if ( !pInputAction ) return;
   std::pair<int, InputAction::EVENT_TYPE> oKey( pInputAction->getCode( ), pInputAction->getEventType( ) );
   std::map< std::pair<int, InputAction::EVENT_TYPE>, InputAction*>::iterator ppFinder;
   ppFinder = m_mapInputActions.find( oKey );

   if ( ppFinder == m_mapInputActions.end( ) ) {
      m_mapInputActions[ oKey ] = pInputAction;
   } // if
} // addInputAction

void InputManager::removeInputAction( InputAction * pInputAction ) {
   // ignore null actions
   if ( !pInputAction ) return;
   std::pair<int, InputAction::EVENT_TYPE> oKey( pInputAction->getCode( ), pInputAction->getEventType( ) );
   std::map< std::pair<int, InputAction::EVENT_TYPE>, InputAction*>::iterator ppFinder;
   ppFinder = m_mapInputActions.find( oKey );

   if ( ppFinder != m_mapInputActions.end( ) ) {
      m_mapInputActions.erase( ppFinder );
   } // if
} // removeInputAction

void InputManager::removeAllInputActions( ) {
   std::map< std::pair<int, InputAction::EVENT_TYPE>, InputAction*>::iterator ppBegin;
   std::map< std::pair<int, InputAction::EVENT_TYPE>, InputAction*>::iterator ppEnd;
   ppBegin = m_mapInputActions.begin( );
   ppEnd = m_mapInputActions.end( );

   while( ppBegin != ppEnd ) {
      if ( ppBegin->second ) {
         delete ppBegin->second;
      } // if
      ++ppBegin;
   } // while
   m_mapInputActions.clear( );
} // removeAllInputActions


void InputManager::addKeyListener( listeners::KeyListener *pListener ) {
   // ignore null listeners
   if ( !pListener ) return;

   std::vector< listeners::KeyListener* >::iterator ppBegin = m_vecKeyListeners.begin( );
   std::vector< listeners::KeyListener* >::iterator ppEnd = m_vecKeyListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         return;
      } // if
      ppBegin++;
   } // while
   m_vecKeyListeners.push_back( pListener );
} // addKeyListener

void InputManager::addMouseButtonListener( listeners::MouseButtonListener* pListener ) {
   // ignore null listeners
   if ( !pListener ) return;

   std::vector< listeners::MouseButtonListener* >::iterator ppBegin = m_vecMouseButtonListeners.begin( );
   std::vector< listeners::MouseButtonListener* >::iterator ppEnd = m_vecMouseButtonListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         return;
      } // if
      ppBegin++;
   } // while
   m_vecMouseButtonListeners.push_back( pListener );

} // addMouseButtonListener

void InputManager::addMouseMotionListener( listeners::MouseMotionListener* pListener ) {
   // ignore null listeners
   if ( !pListener ) return;

   std::vector< listeners::MouseMotionListener* >::iterator ppBegin = m_vecMouseMotionListeners.begin( );
   std::vector< listeners::MouseMotionListener* >::iterator ppEnd = m_vecMouseMotionListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         return;
      } // if
      ppBegin++;
   } // while
   m_vecMouseMotionListeners.push_back( pListener );
} // addMotionButtonListener

void InputManager::addJoyListener( listeners::JoyListener* pListener ) {
   // ignore null listeners
   if ( !pListener ) return;

   std::vector<listeners::JoyListener*>::iterator ppBegin = m_vecJoyListeners.begin( );
   std::vector<listeners::JoyListener*>::iterator ppEnd = m_vecJoyListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         return;
      } // if
      ppBegin++;
   } // while
   m_vecJoyListeners.push_back( pListener );
} // addJoyListener

void InputManager::removeKeyListener( listeners::KeyListener* pListener ) {
   std::vector< listeners::KeyListener* >::iterator ppBegin = m_vecKeyListeners.begin( );
   std::vector< listeners::KeyListener* >::iterator ppEnd = m_vecKeyListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         m_vecKeyListeners.erase( ppBegin );
      } // if
      ppBegin++;
   } // while
} // removeKeyListener

void InputManager::removeMouseButtonListener( listeners::MouseButtonListener* pListener ) {
   std::vector< listeners::MouseButtonListener* >::iterator ppBegin = m_vecMouseButtonListeners.begin( );
   std::vector< listeners::MouseButtonListener* >::iterator ppEnd = m_vecMouseButtonListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         m_vecMouseButtonListeners.erase( ppBegin );
      } // if
      ppBegin++;
   } // while
} // removeMouseButtonListener

void InputManager::removeMouseMotionListener( listeners::MouseMotionListener* pListener ) {
   std::vector< listeners::MouseMotionListener* >::iterator ppBegin = m_vecMouseMotionListeners.begin( );
   std::vector< listeners::MouseMotionListener* >::iterator ppEnd = m_vecMouseMotionListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         m_vecMouseMotionListeners.erase( ppBegin );
      } // if
      ppBegin++;
   } // while
} // removeMouseMotionListener

void InputManager::removeJoyListener( listeners::JoyListener* pListener ) {
   std::vector< listeners::JoyListener* >::iterator ppBegin = m_vecJoyListeners.begin( );
   std::vector< listeners::JoyListener* >::iterator ppEnd = m_vecJoyListeners.end( );

   while ( ppBegin != ppEnd ) {
      if ( (*ppBegin) == pListener ) {
         m_vecJoyListeners.erase( ppBegin );
      } // if
      ppBegin++;
   } // while
} // removeMotionButtonListener

std::vector<listeners::KeyListener*>& InputManager::getKeyListeners( ) {
   return m_vecKeyListeners;
}

std::vector<listeners::MouseButtonListener*>& InputManager::getMouseButtonListeners( ) {
   return m_vecMouseButtonListeners;
}

std::vector<listeners::MouseMotionListener*>& InputManager::getMouseMotionListeners( ) {
   return m_vecMouseMotionListeners;
}

std::vector< listeners::JoyListener* >& InputManager::getJoyListeners( ) {
   return m_vecJoyListeners;
}

void InputManager::removeAllListeners( ) {
   // first free memory
   std::vector<listeners::KeyListener*>::iterator ppBegin1 = m_vecKeyListeners.begin( );
   std::vector<listeners::KeyListener*>::iterator ppEnd1 = m_vecKeyListeners.end( );
   while ( ppBegin1 != ppEnd1 ) {
      if ( (*ppBegin1) ) {
         delete (*ppBegin1);
      } // if
      ppBegin1++;
   } // while
   // then clear vector
   m_vecKeyListeners.clear( );

   // first free memory
   std::vector<listeners::MouseButtonListener*>::iterator ppBegin2 = m_vecMouseButtonListeners.begin( );
   std::vector<listeners::MouseButtonListener*>::iterator ppEnd2 = m_vecMouseButtonListeners.end( );
   while ( ppBegin2 != ppEnd2 ) {
      if ( (*ppBegin2) ) {
         delete (*ppBegin2);
      } // if
      ppBegin2++;
   } // while
   // then clear vector
   m_vecMouseButtonListeners.clear( );

   // first free memory
   std::vector<listeners::MouseMotionListener*>::iterator ppBegin3 = m_vecMouseMotionListeners.begin( );
   std::vector<listeners::MouseMotionListener*>::iterator ppEnd3 = m_vecMouseMotionListeners.end( );
   while ( ppBegin3 != ppEnd3 ) {
      if ( (*ppBegin3) ) {
         delete (*ppBegin3);
      } // if
      ppBegin3++;
   } // while
   // then clear vector
   m_vecMouseMotionListeners.clear( );

   // first free memory
   std::vector<listeners::JoyListener*>::iterator ppBegin4 = m_vecJoyListeners.begin( );
   std::vector<listeners::JoyListener*>::iterator ppEnd4 = m_vecJoyListeners.end( );
   while ( ppBegin4 != ppEnd4 ) {
      if ( (*ppBegin4) ) {
         delete (*ppBegin4);
      } // if
      ppBegin4++;
   } // while
   // then clear vector
   m_vecJoyListeners.clear( );

} // removeAllListeners

void InputManager::notifyKeyListeners( events::KeyEvent *pEvent ) {
   // prepare the keys for input actions
   std::pair<int, InputAction::EVENT_TYPE> oKeyPressed( pEvent->getCode( ), InputAction::EVENT_ON_KBD_KEY_PRESSED );
   std::pair<int, InputAction::EVENT_TYPE> oKeyReleased( pEvent->getCode( ), InputAction::EVENT_ON_KBD_KEY_RELEASED );

   // compare just one time for optimization
   if ( pEvent->getState( ) == events::KeyEvent::KEY_PRESSED ) {
      for ( unsigned int uiI = 0; uiI < m_vecKeyListeners.size( ); ++uiI ) {
         m_vecKeyListeners[ uiI ]->pressed( pEvent );
      } // for
      // dispatch the input actions
      if ( m_mapInputActions[ oKeyPressed ] ) {
         m_mapInputActions[ oKeyPressed ]->setActive( true );
      } // if
      if ( m_mapInputActions[ oKeyReleased ] ) {
         m_mapInputActions[ oKeyReleased ]->setActive( false );
      } // if
   } else {
      for ( unsigned int uiI = 0; uiI < m_vecKeyListeners.size( ); ++uiI ) {
         m_vecKeyListeners[ uiI ]->released( pEvent );
      } // for
      // dispatch the input actions
      if ( m_mapInputActions[ oKeyPressed ] ) {
         m_mapInputActions[ oKeyPressed ]->setActive( false );
      } // if
      if ( m_mapInputActions[ oKeyReleased ] ) {
         m_mapInputActions[ oKeyReleased ]->setActive( true );
      } // if
   } // else
} // notifyKeyListeners

void InputManager::notifyMouseButtonListeners( events::MouseButtonEvent *pEvent ) {
   // prepare the keys for input actions
   std::pair<int, InputAction::EVENT_TYPE> oKeyPressed( pEvent->getCode( ), InputAction::EVENT_ON_MOUSE_BUTTON_PRESSED );
   std::pair<int, InputAction::EVENT_TYPE> oKeyReleased( pEvent->getCode( ), InputAction::EVENT_ON_MOUSE_BUTTON_RELEASED );

   // compare just one time for optimization
   if ( pEvent->getState( ) == events::MouseButtonEvent::MOUSE_BUTTON_PRESSED ) {
      for ( unsigned int uiI = 0; uiI < m_vecMouseButtonListeners.size( ); ++uiI ) {
         m_vecMouseButtonListeners[ uiI ]->pressed( pEvent );
      } // for
      // dispatch the input actions
      if ( m_mapInputActions[ oKeyPressed ] ) {
         m_mapInputActions[ oKeyPressed ]->setActive( true );
      } // if
      if ( m_mapInputActions[ oKeyReleased ] ) {
         m_mapInputActions[ oKeyReleased ]->setActive( false );
      } // if
   } else {
      for ( unsigned int uiI = 0; uiI < m_vecMouseButtonListeners.size( ); ++uiI ) {
         m_vecMouseButtonListeners[ uiI ]->released( pEvent );
      } // for
      // dispatch the input actions
      if ( m_mapInputActions[ oKeyPressed ] ) {
         m_mapInputActions[ oKeyPressed ]->setActive( false );
      } // if
      if ( m_mapInputActions[ oKeyReleased ] ) {
         m_mapInputActions[ oKeyReleased ]->setActive( true );
      } // if
   } // else

} // notifyMouseButtonListeners

void InputManager::notifyMouseMotionListeners( events::MouseMotionEvent *pEvent ) {
   // compare just one time for optimization
   if ( pEvent->isButtonPressed( events::MouseButtonEvent::MOUSE_BUTTON_NONE ) ) {
      for ( unsigned int uiI = 0; uiI < m_vecMouseMotionListeners.size( ); ++uiI ) {
         m_vecMouseMotionListeners[ uiI ]->moved( pEvent );
      } // for
   } else {
      for ( unsigned int uiI = 0; uiI < m_vecMouseMotionListeners.size( ); ++uiI ) {
         m_vecMouseMotionListeners[ uiI ]->dragged( pEvent );
      } // for
   } // else
} // notifyMouseMotionListeners

void InputManager::notifyJoyListeners( events::JoyEvent *pEvent ) {
	// TODO: implement this method
} // notifyJoyListeners

void InputManager::setMousePosition( int iX, int iY ) {
   m_bMouseRePositionEvent = true;
}

      }; // input
   }; // services
}; //powergine

