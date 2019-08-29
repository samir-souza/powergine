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


#include <powergine/services/comm/communicationmanager.h>

#include <algorithm>

namespace powergine {
   namespace services {
      namespace comm {
      
/**
 * Send data to All sockets
 */
void CommunicationManager::sendToAll (void *pData, int iDataSize) {
   std::vector<Socket*>::iterator ppBegin = m_vecSocketPool.begin( );
   std::vector<Socket*>::iterator ppEnd = m_vecSocketPool.end( );
   while( ppBegin != ppEnd ) {
      (*ppBegin)->send( pData, iDataSize );
   } // while
}
/**
 * Add a socket to the pool
 */
void CommunicationManager::addSocket (Socket *pSocket) {
   std::vector<Socket*>::iterator itResult = find( m_vecSocketPool.begin(), m_vecSocketPool.end(), pSocket );
   if ( itResult == m_vecSocketPool.end( ) ) {
      m_vecSocketPool.push_back( pSocket );
   } // if
}
/**
 * Remove a socket from the pool
 */
void CommunicationManager::removeSocket (Socket *pSocket) {
   std::vector<Socket*>::iterator itResult = find( m_vecSocketPool.begin(), m_vecSocketPool.end(), pSocket );
   if ( itResult != m_vecSocketPool.end( ) ) {
      m_vecSocketPool.erase( itResult );
   } // if
}


      }; // comm
   }; // services
}; //powergine
