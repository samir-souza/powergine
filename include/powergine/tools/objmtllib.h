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

#ifndef OBJMTLLIB_H
#define OBJMTLLIB_H


#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <map>

#include <powergine/primitives/material.h>
#include <powergine/primitives/color.h>

namespace powergine {
   namespace tools {


   /**
    * This class is part of the OBJ Loader. It loads a 3D mesh from a .obj
	* file.
	* This class parses a material file used to compose a .obj file
	*
    */
	class OBJMtlLib {

	public:
		// Default constructor. It receives the material filename
	   OBJMtlLib( const std::string &rkFileName, bool bDebug = false );

	   virtual ~OBJMtlLib( );

	   // Returns the parsed material
	   primitives::Material* getMaterial( const std::string &rkstrName );

	private:
	   bool m_bDebug;
	   std::ifstream *m_pfleData;

	   std::map<std::string, primitives::Material*> m_mapMaterials;
	};

   }; // tools
}; // powergine

#endif //OBJMTLLIB_H
