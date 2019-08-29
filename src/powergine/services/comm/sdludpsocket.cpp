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


#include <powergine/services/comm/sdludpsocket.h>
#include <iostream>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <SDL/SDL_net.h>

namespace powergine {
   namespace services {
      namespace comm {

unsigned int SDLUDPSocket::getPort( ) {
   return ( (IPaddress*)m_pIPAddress )->port;
}

std::string SDLUDPSocket::getIPAddress( ) {
   std::stringstream sstrIpAddress;
   sstrIpAddress << ( (IPaddress*)m_pIPAddress )->host;
   return sstrIpAddress.str( );
}

void SDLUDPSocket::close( ) {
   m_bConnected = false;
	SDLNet_UDP_Close((UDPsocket)m_pSocket);
}

void SDLUDPSocket::open( ) throw( IOException ) {
   m_pSocket = SDLNet_UDP_Open( ( !m_bConfiguredAsServer ) ? 0 : ((IPaddress*)m_pIPAddress)->port );
   if( !m_pSocket ) {
      std::stringstream sstrMessage;
      sstrMessage << "open: Cannot open socket - ";
      sstrMessage << SDLNet_GetError( );
      throw IOException( sstrMessage.str( ) );
   } // if
}

void SDLUDPSocket::accept( ) throw( IOException ) {
   // accept a connection coming in on server_UDPsock
   m_iChannel = SDLNet_UDP_Bind( (UDPsocket)m_pSocket, -1, ((IPaddress*)m_pIPAddress) );
   if( m_iChannel == -1 ) {
      std::stringstream sstrMessage;
      sstrMessage << "accept: Cannot put socket to accept - ";
      sstrMessage << SDLNet_GetError( );
      throw IOException( sstrMessage.str( ) );
   } // if
   m_bConnected = ( SDLNet_UDP_GetPeerAddress( (UDPsocket)m_pSocket, m_iChannel ) );
   // communicate over new_UDPsock
   // listeners will be alert
}

int SDLUDPSocket::receive( void *pData, int iMaxDataSize ) throw( IOException ) {
   if ( iMaxDataSize > 65535 ) {
      m_bConnected = false;
      std::stringstream sstrMessage;
      sstrMessage << "receive: Max data buffer size exceded! 65535";
      throw IOException( sstrMessage.str( ) );
   } // if


	int iSize = iMaxDataSize;

	if ( m_iPacketBytesReaded > 0 ) {
		int iLeftBytes = ((UDPpacket*)m_pPacket)->len - m_iPacketBytesReaded;
		if ( iLeftBytes <= iSize ) {
			iSize = iLeftBytes;
			m_iPacketBytesReaded = 0;
		} else {
			m_iPacketBytesReaded -= iSize;
		} // else
		std::memcpy( pData, ((UDPpacket*)m_pPacket)->data+m_iPacketBytesReaded, iSize );
	    return iSize;
	} // if

   int iResult = SDLNet_UDP_Recv( (UDPsocket)m_pSocket, ((UDPpacket*)m_pPacket) );

   if( iResult == -1 ) {
      m_bConnected = false;
      std::stringstream sstrMessage;
      sstrMessage << "receive: Cannot receive data from socket - ";
      sstrMessage << SDLNet_GetError( );
      throw IOException( sstrMessage.str( ) );
   } else if ( iResult == 0 ) {
   		return 0;
   } // else if

   if ( ((UDPpacket*)m_pPacket)->len > iMaxDataSize ) {
   		m_iPacketBytesReaded = iSize;
   } else {
   		iSize = ((UDPpacket*)m_pPacket)->len;
   } // else

   std::memcpy( pData, ((UDPpacket*)m_pPacket)->data, iSize );
   return iSize;
}

void SDLUDPSocket::send( void *pData, int iDataSize ) throw( IOException ) {
   // add one for the terminating NULL
   // TODO: check max size with iDataSize
   ((UDPpacket*)m_pPacket)->len = iDataSize;
   std::memcpy( ((UDPpacket*)m_pPacket)->data, pData, ((UDPpacket*)m_pPacket)->len );
   // setup destination host and port
   ((UDPpacket*)m_pPacket)->address.host = ((IPaddress*)m_pIPAddress)->host;
   ((UDPpacket*)m_pPacket)->address.port = ((IPaddress*)m_pIPAddress)->port;

   int iResult = SDLNet_UDP_Send( (UDPsocket)m_pSocket, m_iChannel, (UDPpacket*)m_pPacket );
   if( iResult < 0 ) {
      m_bConnected = false;
      std::stringstream sstrMessage;
      sstrMessage << "send: Cannot send data to socket - ";
      sstrMessage << SDLNet_GetError( );
      throw IOException( sstrMessage.str( ) );
   } // return
}

SDLUDPSocket::~SDLUDPSocket( ) {
   close( );
   SDLNet_FreePacket( (UDPpacket*)m_pPacket );
   SDLNet_UDP_Close( (UDPsocket)m_pSocket );
}

SDLUDPSocket::SDLUDPSocket( int iPort, const std::string &rstrIPAddress ) throw( InvalidParameterException, IOException )  :
   Socket( rstrIPAddress, iPort ),
   m_pPacket( SDLNet_AllocPacket( 65535 ) ),
   m_pIPAddress( new IPaddress( ) ),
   m_bConnected( false ),
   m_iChannel( -1 ),
   m_iPacketBytesReaded( 0 )
{
	if ( !m_pPacket ) {
        std::stringstream sstrMessage;
        sstrMessage << "SDLUDPSocket: Cannot Allocate Package Memory - ";
        sstrMessage << SDLNet_GetError( );
		throw IOException( sstrMessage.str( ) );
	} // if

   if( rstrIPAddress == "" ) {
      // prepare a server
      m_bConfiguredAsServer = true;
      if ( SDLNet_ResolveHost( ((IPaddress*)m_pIPAddress), NULL, iPort ) == -1 ) {
         std::stringstream sstrMessage;
         sstrMessage << "SDLUDPSocket: Cannot prepare a server socket - ";
         sstrMessage << SDLNet_GetError( );
         throw InvalidParameterException( sstrMessage.str( ) );
      } // if
   } else {
      // prepare a client
      m_bConfiguredAsServer = false;
      if ( iPort <= 0 || SDLNet_ResolveHost( ((IPaddress*)m_pIPAddress), rstrIPAddress.c_str(), iPort ) == -1 ) {
         std::stringstream sstrMessage;
         sstrMessage << "SDLUDPSocket: Cannot prepare client socket - ";
         sstrMessage << SDLNet_GetError( );
         throw InvalidParameterException( sstrMessage.str( ) );
      } // if
   } // else


}


bool SDLUDPSocket::isConnected( ) {
   return m_bConnected;
}

      }; // comm
   }; // services
}; //powergine
