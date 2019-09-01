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


#ifndef SOCKETLISTENER_H
#define SOCKETLISTENER_H

#include <powergine/services/comm/sockettransferevent.h>
#include <powergine/services/comm/socketevent.h>

namespace powergine {
   namespace services {
      namespace comm {

        /**
         * Interface that must be implemented by a concrete class
         * that will handle the data exchanged between two sockets
         */
		class SocketListener {

		public:

		   inline virtual ~SocketListener( ) { }

		   // Event generated when a data packet is sent
		   virtual void  onSend ( SocketTransferEvent *pEvent ) = 0;

		   // Event generated when a data packet is received
		   virtual void  onReceive ( SocketTransferEvent *pEvent ) = 0;

		   // Event generated when a connection is opened
		   virtual void  onOpen ( SocketEvent *pEvent ) = 0;

		   // Event generated when a connection is closed
		   virtual void  onClose ( SocketEvent *pEvent ) = 0;

		   // Event generated when a connection is accepted by the other socket
		   virtual void  onAccept ( SocketEvent *pEvent ) = 0;

		};

      }; // comm
   }; // services
}; //powergine

#endif //SOCKETLISTENER_H

