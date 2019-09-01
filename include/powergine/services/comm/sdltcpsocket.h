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


#ifndef SDLTCPSOCKET_H
#define SDLTCPSOCKET_H

#include <powergine/services/comm/socket.h>
#include <string>


namespace powergine {
   namespace services {
      namespace comm {

		/**
		 * An SDL implementation of Socket for TCP Protocol
		 */
		class SDLTCPSocket : public Socket {

		public:
			// default constructor
			SDLTCPSocket ( int iPort, const std::string &rstrIPAddress = "" );

			virtual ~SDLTCPSocket( );

		   // Sends data via Socket
		   void send ( void *pData, int iDataSize );

		   // Receives data via Socket
		   int receive ( void *pData, int iMaxDataSize );

		   // Bind an ip address and a port from a server socket
		   void accept ();

		   // Open connection to a client or server socket
		   void open ();

		   // Closes an opened connection socket
		   void close ();

		   // Returns the socket IP Address
		   std::string getIPAddress ();

		   // Returns the socket Port identification
		   unsigned int getPort ();

		   // Returns true if the socket is connected
		   bool isConnected( );

		private:

		   // SDL TCP Socket Data Type
		   void *m_pSocket;
		   void *m_pClientSocket;
		   void *m_pIPAddress;

		   bool m_bConnected;
		};


      }; // comm
   }; // services
}; //powergine

#endif //SDLTCPSOCKET_H

