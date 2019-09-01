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

#ifndef CONTACTSET_H
#define CONTACTSET_H

#include <vector>
#include <powergine/utils/contact.h>

namespace powergine {
	namespace utils {

	/**
	 * A contact set stores all the contact points computed by the
	 * physics manager to detect the collision between two objects
	 */
	class ContactSet {

	public:
	   ContactSet( );

	   virtual ~ContactSet( ) { };

	   // Add a new contact point to this set
	   bool addContact( Contact *pContact );

	   // Remove a contact point from this set
	   bool removeContact( Contact *pContact );

	   // Remove all contact points from this set
	   void clear( );

	   // Returns all the registered contact points
	   const std::vector<Contact*>& getContacts( );

	private:
	   std::vector<Contact*> m_vpContacts;
	};

	}; // primitives
}; // namespace powergine

#endif //CONTACTSET_H
