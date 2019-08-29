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


#ifndef INVALIDPARAMETEREXCEPTION_H
#define INVALIDPARAMETEREXCEPTION_H
#include <string>

namespace powergine {
   namespace services {
      namespace comm {

      /**
       * Exception class. Used to notify that an invalid argument was
       * passed to a given method
       */
		class InvalidParameterException {
		public:
		   inline InvalidParameterException( ) : m_strMessage( "Invalid Parameter" ) { }

		   inline InvalidParameterException( const std::string &rstrMessage ) : m_strMessage( rstrMessage ) { }

		   inline virtual ~InvalidParameterException( ) { }

		   inline std::string toString( ) const { return m_strMessage; }

		private:
		   std::string m_strMessage;
		};

      }; // comm
   }; // services
}; //powergine

#endif //INVALIDPARAMETEREXCEPTION_H

