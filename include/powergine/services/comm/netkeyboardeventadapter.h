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


#ifndef NETKEYBOARDEVENTADAPTER_H
#define NETKEYBOARDEVENTADAPTER_H

#include <powergine/services/input/events/keyevent.h>

namespace powergine {
   namespace services {
      namespace comm {

      /**
       * This interface must be implemented by an adapter service
       * used to translate network commands to keyboard events
       */
		class NetKeyboardEventAdapter {

		public:
		   inline NetKeyboardEventAdapter( ) { }

		   virtual inline ~NetKeyboardEventAdapter( ) { }

		   virtual void processEvent( input::events::KeyEvent *pEvent ) = 0;
		};

      }; // comm
   }; // services
}; //powergine

#endif //NETKEYBOARDEVENTADAPTER_H
