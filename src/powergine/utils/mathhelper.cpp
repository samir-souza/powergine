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


#include <powergine/utils/mathhelper.h>

namespace powergine {
   namespace utils {
    
const float MathHelper::PI = 3.1415926535897932384626433832795f;
const float MathHelper::PI_BY_180 = 0.0174532925199433f;
const float MathHelper::TWO_PI = 2.0f * PI;
const float MathHelper::HALF_PI = 0.5f * PI;
const float MathHelper::SQRT_3 = sqrt( 3.0f );
const float MathHelper::HALF_SQRT_3 = 0.5f * sqrt( 3.0f );

MathHelper* MathHelper::m_pSingleton = 0;

MathHelper::MathHelper( ) {
}

MathHelper* MathHelper::get( ) { 
   if ( m_pSingleton == 0 ) { 
      m_pSingleton = new MathHelper( );       
   } // if
   return m_pSingleton;
}

double MathHelper::degree2Radians( double dDegree ) const {  
   return dDegree * PI_BY_180;  
}

double MathHelper::degree2Radians( float fDegree ) const {  
   return degree2Radians( static_cast<double>( fDegree ) );  
}
      
   }; // utils   
}; // powergine   
