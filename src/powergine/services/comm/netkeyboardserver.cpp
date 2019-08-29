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



#include <powergine/services/comm/netkeyboardserver.h>
#include <SDL/SDL.h>

namespace powergine {
  namespace services {
     namespace comm {

NetKeyboardServer::NetKeyboardServer( Socket *pSocket, NetKeyboardEventAdapter *pEventAdapter ) :
   m_pServerSocket( pSocket ),
   m_pEventAdapter( pEventAdapter ),
   m_bRunning( false ),
   m_bConnected( false )
{
   m_pServerSocket->addListener( this );
}

void NetKeyboardServer::startup( ) throw( IOException ) {
   try {
      m_bRunning = true;
      m_pServerSocket->open( );
      onOpen( new SocketEvent( m_pServerSocket ) );

      while( m_bRunning ) {

         try {
            // try to accept a connection
            m_pServerSocket->accept( );
            onAccept( new SocketEvent( m_pServerSocket ) );

            SocketTransferEvent *pEvent = new SocketTransferEvent( );
            pEvent->m_iDataSize = sizeof( input::events::KeyEvent );
            pEvent->m_pData = static_cast<void*>( new char[ pEvent->m_iDataSize ] );

            while( m_pServerSocket->isConnected( ) ) {
               try {
                  m_pServerSocket->receive( pEvent->m_pData, pEvent->m_iDataSize );
                  onReceive( pEvent );
               } catch( IOException &ex ) {
                  // no data in recv buffer
               } // catch
            } // while

         } catch( IOException &ex ) {
            // cannot accept a connection
            Core::get( )->sleep( 100 );
            continue;
         } // catch

      } // while
      shutdown( );
   } catch( IOException &ex ) {
      throw ex;
   } // catch
}

void NetKeyboardServer::shutdown( ) {
   m_bRunning = false;
   m_pServerSocket->close( );
}

      }; // comm
   }; // services
}; //powergine
