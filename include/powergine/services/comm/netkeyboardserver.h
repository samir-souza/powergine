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


#ifndef NETKEYBOARDSERVER_H
#define NETKEYBOARDSERVER_H

#include <string>
#include <powergine/core.h>
#include <powergine/services/comm/socketlistener.h>
#include <powergine/services/comm/socket.h>
#include <powergine/services/input/events/keyevent.h>
#include <powergine/services/comm/netkeyboardeventadapter.h>
#include <powergine/services/comm/ioexception.h>

namespace powergine {
  namespace services {
     namespace comm {

		 /**
		  * This class implements the net keyboard Server. A mechanism
		  * to receive data from the Keyboard client and simulates a local
		  * keyboard from a remote machine
		  */
		class NetKeyboardServer : public SocketListener {
		public:

			//A server socket
		   NetKeyboardServer( Socket *pSocket, NetKeyboardEventAdapter *pEventAdapter );

		   inline virtual ~NetKeyboardServer( ) { }

		   // Starts the server
		   void startup( );

		   // Shutdowns the server
		   void shutdown( );


		   // Socket listener events
		   virtual void  onSend ( SocketTransferEvent *pEvent ) { };
		   virtual void  onReceive ( SocketTransferEvent *pEvent ) { };
		   virtual void  onOpen ( SocketEvent *pEvent ) { };
		   virtual void  onClose ( SocketEvent *pEvent ) { };
		   virtual void  onAccept ( SocketEvent *pEvent ) { };

		   // Translates the remote commands to simulate a local keyboard
		   virtual void  processEvent( input::events::KeyEvent *pKeyEvent ) = 0;

		private:
		   Socket *m_pServerSocket;
		   NetKeyboardEventAdapter *m_pEventAdapter;
		   bool m_bRunning;
		   bool m_bConnected;
		};

      }; // comm
   }; // services
}; //powergine

#endif //NETKEYBOARDSERVER_H
