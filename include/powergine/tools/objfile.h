// Copyright (c) 2004 Samir Araujo <samir.araujo@gmail.com>
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

#ifndef OBJFILE_H
#define OBJFILE_H


#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include <powergine/primitives/renderprimitive.h>
#include <powergine/primitives/vertexdiffusenormal.h>
#include <powergine/primitives/vertexnormal.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/triangle.h>
#include <powergine/primitives/textcoords.h>
#include <powergine/primitives/texture.h>
#include <powergine/sceneobjects/mesh.h>
#include <powergine/tools/objface.h>
#include <powergine/tools/objmtllib.h>

namespace powergine {
   namespace tools {

	/**
	 * This class is part of the OBJ Loader. It loads a 3D mesh from a .obj
	 * file.
	 * This is the main class which contains the mechanisms for loading a
	 * 3D mesh from a .obj file
	 */
	class OBJFile {

	public:

		// Default the constructor. Receives the .obj filename
	   OBJFile( const std::string &rkFileName, bool bDebug = false );

	   virtual ~OBJFile( );

	   // Returns the vertices list of the parsed .obj file
	   std::vector<primitives::Vector3D*>& getVertices( );

	   // Returns all the faces of the parsed object
	   std::map<std::string, std::vector<OBJFace*> >& getFaces( );

	   // Returns all the textures coords of the parsed object
	   std::vector<primitives::TextCoords*>& getTexturesCoords( );

	   // Returns all the normals of the vertices of the parsed object
	   std::vector<primitives::Vector3D*>& getNormals( );

	   // Returns the parsed mesh
	   sceneobjects::Mesh* getMesh( );

	private:
	   bool m_bDebug;
	   std::ifstream *m_pfleData;

	   sceneobjects::Mesh *m_pMesh;
	   std::vector<primitives::Vector3D*> m_vecVertices;
	   std::map<std::string, std::vector<OBJFace*> > m_mapFaces;
	   std::map<std::string, std::string> m_mapTextures;
	   std::vector<primitives::TextCoords*> m_vecTextCoords;
	   std::vector<primitives::Vector3D*> m_vecNormals;
	   OBJMtlLib *m_pMaterialLib;
	};

   }; // tools
}; // powergine

#endif //OBJFILE_H
