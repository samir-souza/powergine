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


#ifndef SOCKETEREVENT_H
#define SOCKETEREVENT_H

namespace powergine {
   namespace services {
      namespace comm {

		class Socket;

		/**
		 * An event created by a socket operation
		 */
		class SocketEvent {

		public:
		   inline SocketEvent( Socket *pSocket ) : m_pSocket( pSocket ) { };

		   inline virtual ~SocketEvent( ) { };

		   // Update a general purpose user data pointer
		   inline void setUserData( void* pUserData ) {
			   this->m_pUserData = pUserData;
		   }

		   // Retrieves the pointer for the user data structure
		   inline void* getUserData( ) {
			   return this->m_pUserData;
		   }

		private:
		   Socket *m_pSocket;
		   void *m_pUserData;
		};


      }; // comm
   }; // services
}; //powergine


#endif //SOCKETEREVENT_H

