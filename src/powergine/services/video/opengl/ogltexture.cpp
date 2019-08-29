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


#include <powergine/services/video/opengl/ogltexture.h>
#include <SDL/SDL_opengl.h>
#include <GL/glu.h>

namespace powergine {   
   namespace services {
      namespace video {
         namespace opengl {
                 
OGLTexture::OGLTexture( primitives::Texture::FILTER eFilter, primitives::Image *pImage, bool bRepeat ) :
   Texture( eFilter, pImage, bRepeat ),
   m_uiID( 0 )
{         
   int iMaxTextureSize;
   glGetIntegerv( GL_MAX_TEXTURE_SIZE, &iMaxTextureSize );
   if ( m_pImage->getWidth( )%2 != 0 || m_pImage->getHeight( )%2 != 0 ) {
      std::ostringstream sstrErrorMesg;
      sstrErrorMesg << "Image dimensions must be power of two";
      sstrErrorMesg << " W[ " << m_pImage->getWidth( ) << " ]";
      sstrErrorMesg << " H[ " << m_pImage->getHeight( ) << " ]";
      throw( sstrErrorMesg.str( ) );
   } // if
   
   if ( m_pImage->getWidth( ) > 2+iMaxTextureSize || m_pImage->getHeight( ) > 2+iMaxTextureSize ) {
      std::ostringstream sstrErrorMesg;
      sstrErrorMesg << "Image dimensions must less than 2+MAX_TEXTURE_SIZE";
      sstrErrorMesg << " (" << m_pImage->getFileName( ) <<  ") " << 2+iMaxTextureSize;
      throw( sstrErrorMesg.str( ) ); 
   } // if   
      
   glGenTextures( 1, &m_uiID );   
   glBindTexture( GL_TEXTURE_2D, m_uiID );
   switch( m_eFilter ) {
      case Texture::FILTER_NEAREST: {
         
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST );
         glTexImage2D( GL_TEXTURE_2D, 0, 3, m_pImage->getWidth( ), m_pImage->getHeight( ),
               0, GL_RGB, GL_UNSIGNED_BYTE, m_pImage->getData( ) ); 
               
         break;
      } // case
      case Texture::FILTER_LINEAR: {
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
         glTexImage2D( GL_TEXTURE_2D, 0, 3, m_pImage->getWidth( ), m_pImage->getHeight( ),
                       0, GL_RGB, GL_UNSIGNED_BYTE, m_pImage->getData( ) );
               
         break;
      } // case
      case Texture::FILTER_BILINEAR: {
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST );
         gluBuild2DMipmaps( GL_TEXTURE_2D, 3, m_pImage->getWidth( ), m_pImage->getHeight( ),
               GL_RGB, GL_UNSIGNED_BYTE, m_pImage->getData( ) );               
         break;
      } // case
      case Texture::FILTER_TRILINEAR: {
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_LINEAR );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR );            
         gluBuild2DMipmaps( GL_TEXTURE_2D, 3, m_pImage->getWidth( ), m_pImage->getHeight( ),
               GL_RGB, GL_UNSIGNED_BYTE, m_pImage->getData( ) );  
                   
         break;
      } // case
      default:
      case Texture::FILTER_NO_FILTER: {
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST );
         glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST_MIPMAP_NEAREST );
         glTexImage2D( GL_TEXTURE_2D, 0, 3, m_pImage->getWidth( ), m_pImage->getHeight( ),
               0, GL_RGB, GL_UNSIGNED_BYTE, m_pImage->getData( ) );            
         break;
      } // case      
      
   } // switch 

} // OGLTexture
   
OGLTexture::~OGLTexture( ) {
   glDeleteTextures( 1, &m_uiID );
}

unsigned int OGLTexture::getID( ) const {
   return m_uiID;   
} // if

         }; // opengl
      }; // video
   }; // services
}; // namespace powergine


