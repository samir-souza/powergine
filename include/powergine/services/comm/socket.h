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


#ifndef SOCKET_H
#define SOCKET_H

#include <powergine/services/comm/ioexception.h>
#include <powergine/services/comm/invalidparameterexception.h>
#include <string>
#include <vector>

namespace powergine {
   namespace services {
      namespace comm {

		class SocketListener;

		/**
		 * An abstract class for socket implementation
		 */
		class Socket {

		public:
		   // Default constructor
		   inline Socket ( const std::string &rstrIPAddress, unsigned int uiPort ) throw( InvalidParameterException ) { }

		   inline virtual ~Socket( ) { }

		   // Sends data via Socket
		   virtual void send ( void *pData, int iDataSize ) throw( IOException ) = 0;

		   // Receives data via Socket
		   virtual int receive ( void *pData, int iMaxDataSize ) throw( IOException ) = 0;

		   // Bind an ip address and a port from a server socket
		   virtual void accept () throw( IOException ) = 0;

		   // Open connection to a client or server socket
		   virtual void open () throw( IOException ) = 0;

		   // Closes an opened connection socket
		   virtual void close () = 0;

		   // Returns the socket IP Address
		   virtual std::string getIPAddress () = 0;

		   // Returns the socket Port identification
		   virtual unsigned int getPort () = 0;

		   // Returns true if the socket is connected
		   virtual bool isConnected( ) = 0;

		   // Add a socket listener to this socket
		   void  addListener ( SocketListener *pListener );

		   // Remove a socket listener from this socket
		   void  removeListener ( SocketListener *pListener );

		private:
		   std::vector<SocketListener*> m_vecListeners;

		};

      }; // comm
   }; // services
}; //powergine

#endif //SOCKET_H

