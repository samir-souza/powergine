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


#include <powergine/services/comm/sdlnetkeyboardeventadapter.h>
#include <SDL/SDL.h>

namespace powergine {
   namespace services {
      namespace comm {


void SDLNetKeyboardEventAdapter::processEvent( input::events::KeyEvent *pKeyEvent ) {
   SDL_Event oEvent;
   oEvent.type = ( pKeyEvent->getState( ) == input::events::KeyEvent::KEY_PRESSED ) ? SDL_KEYDOWN : SDL_KEYUP ;
   oEvent.key.keysym.sym = (SDLKey)pKeyEvent->getCode( );
   oEvent.key.state = pKeyEvent->getState( );
   SDL_PushEvent( &oEvent );      
} // processEvet

      }; // comm
   }; // services
}; //powergine

