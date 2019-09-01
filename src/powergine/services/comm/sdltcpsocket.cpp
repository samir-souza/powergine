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


#include <powergine/services/comm/sdltcpsocket.h>
#include <iostream>
#include <sstream>
#include <SDL/SDL_net.h>

namespace powergine {
   namespace services {
      namespace comm {

unsigned int SDLTCPSocket::getPort( ) {
   return ( (IPaddress*)m_pIPAddress )->port;
}

std::string SDLTCPSocket::getIPAddress( ) {
   std::stringstream sstrIpAddress;
   sstrIpAddress << ( (IPaddress*)m_pIPAddress )->host;
   return sstrIpAddress.str( );
}

void SDLTCPSocket::close( ) {
   SDLNet_TCP_Close( (TCPsocket)m_pSocket );
   m_bConnected = false;
}

void SDLTCPSocket::open( ) {
   m_pSocket = SDLNet_TCP_Open( (IPaddress*)m_pIPAddress );   
   if( !m_pSocket ) {
      std::stringstream sstrMessage;
      sstrMessage << "open: Cannot open socket - ";
      sstrMessage << SDLNet_GetError( );      
      throw IOException( sstrMessage.str( ) );
   } // if   
   m_bConnected = ( SDLNet_TCP_GetPeerAddress( (TCPsocket)m_pSocket ) );
}

void SDLTCPSocket::accept( ) {
   // accept a connection coming in on server_tcpsock      
   m_pClientSocket = SDLNet_TCP_Accept( (TCPsocket)m_pSocket );
   if( !m_pClientSocket ) {      
      std::stringstream sstrMessage;
      sstrMessage << "accept: Cannot put socket to accept - ";
      sstrMessage << SDLNet_GetError( );
      throw IOException( sstrMessage.str( ) );
   } // if
   m_bConnected = true;
   // communicate over new_tcpsock
   // listeners will be alert   
}

int SDLTCPSocket::receive( void *pData, int iMaxDataSize ) {
   
   //TCPsocket sock;      
   int iResult = SDLNet_TCP_Recv( (TCPsocket)m_pClientSocket, pData, iMaxDataSize );   
   if( !iResult ) {
      m_bConnected = false;
      std::stringstream sstrMessage;
      sstrMessage << "receive: Cannot receive data from socket - ";
      sstrMessage << SDLNet_GetError( );      
      throw IOException( sstrMessage.str( ) );
   } // if   
   return iResult;
   
}

void SDLTCPSocket::send( void *pData, int iDataSize ) {     
   // add one for the terminating NULL   
   int iResult = SDLNet_TCP_Send( (TCPsocket)m_pSocket, pData, iDataSize );
   
   if( iResult < iDataSize ) {
      m_bConnected = false;
      std::stringstream sstrMessage;
      sstrMessage << "send: Cannot send data to socket - ";
      sstrMessage << SDLNet_GetError( );      
      throw IOException( sstrMessage.str( ) );
   } // return
}

SDLTCPSocket::~SDLTCPSocket( ) {
   close( );
}
              
SDLTCPSocket::SDLTCPSocket( int iPort, const std::string &rstrIPAddress )  :
   Socket( rstrIPAddress, iPort ),
   m_pIPAddress( new IPaddress( ) ), 
   m_bConnected( false )
{
   if( rstrIPAddress == "" ) {
      // prepare a server
      if ( SDLNet_ResolveHost( (IPaddress*)m_pIPAddress, NULL, iPort ) == -1 ) {
         std::stringstream sstrMessage;
         sstrMessage << "SDLTCPSocket: Cannot prepare a server socket - ";
         sstrMessage << SDLNet_GetError( );
         throw InvalidParameterException( sstrMessage.str( ) );         
      } // if      
   } else {
      // prepare a client
      if ( SDLNet_ResolveHost( (IPaddress*)m_pIPAddress, rstrIPAddress.c_str(), iPort ) == -1 ) {
         std::stringstream sstrMessage;
         sstrMessage << "SDLTCPSocket: Cannot prepare client socket - ";
         sstrMessage << SDLNet_GetError( );
         throw InvalidParameterException( sstrMessage.str( ) );         
      } // if
   } // else
   

}


bool SDLTCPSocket::isConnected( ) {
   return m_bConnected;
}

      }; // comm
   }; // services
}; //powergine
