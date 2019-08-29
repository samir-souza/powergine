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


#include <SDL/SDL.h>
#include <powergine/services/input/sdl/sdlinputmanager.h>
 
 namespace powergine {
   namespace services {
      namespace input {
         namespace sdl {

SDL_Event m_oEvent;

void SDLInputManager::initialize( ) {
   m_uiKbdCodeOffset = -3;
   m_uiMouseButtonCodeOffset = -5;
   m_uiMouseMotionCodeOffset = -4;
   m_uiJoyCodeOffset = -7;
} // initialize

void SDLInputManager::processInput( InputManager::INPUT_TYPE eType ) {   
   while( SDL_PollEvent( &m_oEvent ) ) {
      switch( m_oEvent.type ) {

         case SDL_KEYDOWN: {
            int iCode = m_oEvent.key.keysym.sym;
            int iState = m_oEvent.key.state;
            InputManager::notifyKeyListeners( 
               new events::KeyEvent( iCode, iState )
            );
         } break;
         case SDL_KEYUP: {
            int iCode = m_oEvent.key.keysym.sym;
            int iState = m_oEvent.key.state;
            InputManager::notifyKeyListeners( 
               new events::KeyEvent( iCode, iState )
            );
         } break;
      
         case SDL_MOUSEBUTTONDOWN: {            
            int iCode = m_oEvent.button.button + m_uiMouseButtonCodeOffset;            
            int iState = events::MouseButtonEvent::MOUSE_BUTTON_PRESSED;            
            InputManager::notifyMouseButtonListeners( 
               new events::MouseButtonEvent( 
                  iCode, iState,
                  m_oEvent.button.x, m_oEvent.button.y,
                  ( m_oEvent.button.button == SDL_BUTTON_WHEELDOWN )
               )
            );
         } break;
         case SDL_MOUSEBUTTONUP: {            
            int iCode = m_oEvent.button.button + m_uiMouseButtonCodeOffset;
            int iState = events::MouseButtonEvent::MOUSE_BUTTON_RELEASED;
            InputManager::notifyMouseButtonListeners( 
               new events::MouseButtonEvent( 
                  iCode, iState,
                  m_oEvent.button.x, m_oEvent.button.y,
                  ( m_oEvent.button.button == SDL_BUTTON_WHEELUP )
               )
            );
         } break;
               
         case SDL_MOUSEMOTION: {            
            unsigned int uiButtonsState = 0 | m_oEvent.motion.state;            
            InputManager::notifyMouseMotionListeners( 
               new events::MouseMotionEvent( 
                  m_oEvent.motion.x, m_oEvent.motion.y,
                  m_oEvent.motion.xrel, m_oEvent.motion.yrel,
                  uiButtonsState
               )
            );
            

         } break;
         
         case SDL_JOYAXISMOTION: {
         } break;
         
         case SDL_JOYBUTTONDOWN: {
         } break;
         case SDL_JOYBUTTONUP: {
         } break;
      
      } // switch      
   } // while

} // processInput

void SDLInputManager::setMousePosition( int iX, int iY ) {
   InputManager::setMousePosition( iX, iY );
   SDL_WarpMouse( iX, iY );
} // setMousePosition

void SDLInputManager::getMousePosition( int &riX, int &riY ) {
   SDL_GetMouseState( &riX, &riY );   
} // setMousePosition
                  
         }; // sdl
       }; // input
   }; // services
}; //powergine
