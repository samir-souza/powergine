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

#ifndef MATHHELPER_H
#define MATHHELPER_H

#include <cmath>

namespace powergine {
   namespace utils {

   /**
    * Singleton class which contains several utilitaries, useful
    * for executing a lot of math calculations
    */
	class MathHelper {

	public:
	   // unique singleton instance
	   static MathHelper* get( );

	   // constants
	   static const float PI;
	   static const float PI_BY_180;
	   static const float TWO_PI;
	   static const float HALF_PI;
	   static const float SQRT_3;
	   static const float HALF_SQRT_3;

	   // find min of 2 elements
	   template < class Type > inline const Type& min( const Type &rkE1, const Type &rkE2 ) {
		  return( ( rkE1 < rkE2 ) ? rkE1 : rkE2 );
	   }
	   // find min of 3 elements
	   template < class Type > inline const Type& min( const Type &rkE1, const Type &rkE2, const Type &rkE3 ) {
		  return( ( rkE1 < rkE2 ) ? ( ( rkE1 < rkE3 ) ? rkE1 : rkE3 ) : ( ( rkE2 < rkE3 ) ? rkE2 : rkE3 ) );
	   }
	   // find max of 2 elements
	   template < class Type > inline const Type& max( const Type &rkE1, const Type &rkE2 ) {
		  return( ( rkE1 > rkE2 ) ? rkE1 : rkE2 );
	   }
	   // find max of 3 elements
	   template < class Type > inline const Type& max( const Type &rkE1, const Type &rkE2, const Type &rkE3 ) {
		  return( ( rkE1 > rkE2 ) ? ( ( rkE1 > rkE3 ) ? rkE1 : rkE3 ) : ( ( rkE2 > rkE3 ) ? rkE2 : rkE3 ) );
	   }


	   // convert double degree 2 radians
	   double degree2Radians( double dDegree ) const;

	   // convert float degree 2 radians
	   double degree2Radians( float fDegree ) const;

	protected:
	   MathHelper( );

	private:
	   static MathHelper *m_pSingleton;

	};

   }; // utils
}; // powergine

#endif // MATHHELPER_H
