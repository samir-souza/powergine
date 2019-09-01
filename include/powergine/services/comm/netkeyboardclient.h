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


#ifndef NETKEYBOARDCLIENT_H
#define NETKEYBOARDCLIENT_H

#include <powergine/services/comm/socket.h>
#include <powergine/services/input/listeners/keylistener.h>
#include <powergine/services/input/events/keyevent.h>
#include <string>

namespace powergine {
   namespace services {
      namespace comm {

      /**
       * This class is a network util that can be used to control an
       * application remotely. It simulates a local keyboard. This client
       * must connect to a given server that will receive the commands
       * and executes it as if it was given by a local keyborad.
       */
		class NetKeyboardClient : public input::listeners::KeyListener {

		public:

			// Receives the client socket used to connect to the server
		   NetKeyboardClient ( Socket *pSocket );

		   virtual ~NetKeyboardClient ( );

		   // Implementation of the keyboard events
		   void  released ( input::events::KeyEvent *pEvent );
		   void  pressed ( input::events::KeyEvent *pEvent);

		   // Initialize the keyboard client client
		   void startup( );

		   // Shutdowns the service
		   void shutdown( );

		private:
		   Socket *m_pClientSocket;

		};

      }; // comm
   }; // services
}; //powergine

#endif //NETKEYBOARDCLIENT_H

