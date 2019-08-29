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


#include <powergine/services/video/opengl/sdlimage.h>
#include <SDL/SDL_image.h>

namespace powergine {   
   namespace services {
      namespace video {
         namespace opengl {

SDLImage::SDLImage( const std::string &rkstrFileName ) :
   primitives::Image( rkstrFileName )
{
   m_pImage = IMG_Load( rkstrFileName.c_str( ) );

   if( !m_pImage ) {
      std::ostringstream sstrErrorMesg;
      sstrErrorMesg << "Cannot load image file: " << IMG_GetError( );
      throw( sstrErrorMesg.str( ) );    
   } // if
}

SDLImage::SDLImage( char *pcData, int iWidth, int iHeight, int iDepth ) :
   Image( std::string( "tmpImage" ) )
{   
   
   m_pImage = SDL_CreateRGBSurfaceFrom( pcData, iWidth,  iHeight, iDepth, 0,
                                        0xff0000, 0x00ff00, 0x0000ff, 0x000000 );
} // SDLImage

SDLImage::~SDLImage( ) {
   SDL_FreeSurface( m_pImage );   
}

int SDLImage::getWidth( ) const {
   return m_pImage->w;
}

int SDLImage::getHeight( ) const {
   return m_pImage->h;
}

unsigned short SDLImage::getBpp( ) const {
   return m_pImage->format->BitsPerPixel;
}

void* SDLImage::getData( ) {
   return m_pImage->pixels;
}
  
void SDLImage::setGamma( float fFactor ) {
   /*
   // used only in 8 bpp images
   //SDL_Color *pColor;
   for ( int iX = 0; iX < getWidth( ); iX++ ) {
      for ( int iY = 0; iY < getHeight( ); iY++ ) {         
         unsigned char szPixelColor[ 3 ];
         std::memset( &szPixelColor, 0, sizeof( unsigned char ) * 3 );
         
         SDL_GetRGB( 
            getPixel( iX, iY ), 
            m_pImage->format, 
            &szPixelColor[ 0 ],
            &szPixelColor[ 1 ],
            &szPixelColor[ 2 ] 
         );         

         
         float fRed   = *reinterpret_cast<float*>( &szPixelColor[ 0 ] );
         float fGreen = *reinterpret_cast<float*>( &szPixelColor[ 1 ] );
         float fBlue  = *reinterpret_cast<float*>( &szPixelColor[ 2 ] );
         
         float fScale = 1.0f, fTemp = 0.0f;
         
         // Multiply the factor by the RGB values, while keeping it to a 255 ratio
         fRed *= fFactor / 255.0f;		
         fGreen *= fFactor / 255.0f;
         fBlue *= fFactor / 255.0f;
         
         // Check if the the values went past the highest value
         if ( fRed > 1.0f && ( fTemp = ( 1.0f / fRed ) ) < fScale ) fScale = fTemp;
         if ( fGreen > 1.0f && ( fTemp = ( 1.0f / fGreen ) ) < fScale ) fScale = fTemp;
         if ( fBlue > 1.0f && ( fTemp = ( 1.0f / fBlue ) ) < fScale ) fScale = fTemp;
         
         // Get the scale for this pixel and multiply it by our pixel values
         fScale *= 255.0f;
         
         fRed *= fScale;
         fGreen *= fScale;
         fBlue *= fScale;
   
         std::memset( &szPixelColor, 0, sizeof( unsigned char ) * 3 );         
         szPixelColor[ 0 ] = *reinterpret_cast<unsigned char*>( &fRed );
         szPixelColor[ 1 ] = *reinterpret_cast<unsigned char*>( &fGreen );
         szPixelColor[ 2 ] = *reinterpret_cast<unsigned char*>( &fBlue );
         
         unsigned int uiPixel = SDL_MapRGB( m_pImage->format, 
                                          szPixelColor[ 0 ],
                                          szPixelColor[ 1 ],
                                          szPixelColor[ 2 ] );
         putPixel( iX, iY, uiPixel );


      } // for      
   } // for
*/
} // setGamma
 
unsigned int SDLImage::getPixel( unsigned int uiX, unsigned int uiY ) {

   unsigned char *pucPixel = 
      reinterpret_cast<unsigned char*>( getData( ) ) + 
         uiY * m_pImage->pitch + uiX * getBpp( );

    switch( getBpp( ) ) {
      case 1:
         return *pucPixel;
   
      case 2:
         return *reinterpret_cast<unsigned short*>( pucPixel );
   
      case 3:
         if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
               return pucPixel[0] << 16 | pucPixel[1] << 8 | pucPixel[2];
         else
               return pucPixel[0] | pucPixel[1] << 8 | pucPixel[2] << 16;
   
      case 4:
         return *reinterpret_cast<unsigned int*>( pucPixel );
   
      default:
         return 0;       // shouldn't happen, but avoids warnings
    } // switch
   
} // getPixel

void SDLImage::putPixel( unsigned int uiX, unsigned int uiY, unsigned int uiPixel ) {
   unsigned char *pucPixel = 
      reinterpret_cast<unsigned char*>( getData( ) ) + 
         uiY * m_pImage->pitch + uiX * getBpp( );
   SDL_LockSurface( m_pImage );
   switch( getBpp( ) ) {
      case 1:
         *pucPixel = uiPixel;
         break;
      
      case 2:
         *reinterpret_cast<unsigned short*>( pucPixel ) = uiPixel;
         break;
      
      case 3:
         if( SDL_BYTEORDER == SDL_BIG_ENDIAN ) {
               pucPixel[0] = (uiPixel >> 16) & 0xff;
               pucPixel[1] = (uiPixel >> 8) & 0xff;
               pucPixel[2] = uiPixel & 0xff;
         } else {
               pucPixel[0] = uiPixel & 0xff;
               pucPixel[1] = (uiPixel >> 8) & 0xff;
               pucPixel[2] = (uiPixel >> 16) & 0xff;
         } // else
         break;
      
      case 4:
         *reinterpret_cast<unsigned int*>( pucPixel ) = uiPixel;
         break;
   } // switch
   SDL_UnlockSurface( m_pImage );

} // putPixel


         }; // opengl
      }; // video
   }; // services
}; // namespace powergine



