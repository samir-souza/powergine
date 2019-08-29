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


#include <powergine/utils/contactset.h>

namespace powergine {
	namespace utils {
	
// Constructors/Destructors
ContactSet::ContactSet( ) {
}

bool ContactSet::addContact( Contact *pContact ) {
   std::vector<Contact*>::iterator ppBegin = m_vpContacts.begin( );
   std::vector<Contact*>::iterator ppEnd = m_vpContacts.end( );

   while ( ppBegin != ppEnd ) {
            if ( *ppBegin == pContact ) {
                  return false; // item already exists in vector
            } // if
            ppBegin++;
   } // while
   m_vpContacts.push_back( pContact );
   return true;
}

bool ContactSet::removeContact( Contact *pContact ) {
   std::vector<Contact*>::iterator ppBegin = m_vpContacts.begin( );
   std::vector<Contact*>::iterator ppEnd = m_vpContacts.end( );

   while ( ppBegin != ppEnd ) {
            if ( *ppBegin == pContact ) {
                  m_vpContacts.erase( ppBegin );
                  return true;
            } // if
            ppBegin++;
   } // while	
   return false;  // item does not exists in vector
}

void ContactSet::clear( ) {
   m_vpContacts.clear( );
}

const std::vector<Contact*>& ContactSet::getContacts( ) {
   return m_vpContacts;
}
   
	}; // primitives
}; // namespace powergine
