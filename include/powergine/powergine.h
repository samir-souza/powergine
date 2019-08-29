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

#ifndef POWERGINE_H_
#define POWERGINE_H_

// This file contains include instructions for all files
// of the engine. So you just need to include this one
// in your project

#include <powergine/primitives/color.h>
#include <powergine/primitives/line.h>
#include <powergine/primitives/material.h>
#include <powergine/primitives/matrix3x3.h>
#include <powergine/primitives/matrix4x4.h>
#include <powergine/primitives/renderprimitive.h>
#include <powergine/primitives/plane.h>
#include <powergine/primitives/quad.h>
#include <powergine/primitives/quaternion.h>
#include <powergine/primitives/ray.h>
#include <powergine/primitives/vertextexture.h>
#include <powergine/primitives/triangle.h>
#include <powergine/primitives/vector3d.h>
#include <powergine/primitives/vertex.h>
#include <powergine/primitives/vertexdiffusenormal.h>
#include <powergine/primitives/vertexnormal.h>
#include <powergine/primitives/vertexdiffuse.h>
#include <powergine/primitives/vertextexturediffusenormal.h>
#include <powergine/primitives/vertextexturediffuse.h>
#include <powergine/primitives/vertextexturenormal.h>
#include <powergine/primitives/texture.h>
#include <powergine/primitives/image.h>
#include <powergine/primitives/polygonbuffer.h>
#include <powergine/primitives/textcoords.h>
#include <powergine/primitives/vertexelement.h>
#include <powergine/primitives/vertexformat.h>
#include <powergine/primitives/vertexbuffer.h>
#include <powergine/primitives/graph.h>
#include <powergine/primitives/graphvertex.h>
#include <powergine/primitives/graphedge.h>
#include <powergine/core.h>
#include <powergine/sceneobjects/aabb.h>
#include <powergine/sceneobjects/baseentity.h>
#include <powergine/sceneobjects/boundingvolume.h>
#include <powergine/sceneobjects/bsptree.h>
#include <powergine/sceneobjects/camera.h>
#include <powergine/sceneobjects/frustum.h>
#include <powergine/sceneobjects/joint.h>
#include <powergine/sceneobjects/light.h>
#include <powergine/sceneobjects/massparticle.h>
#include <powergine/sceneobjects/mesh.h>
#include <powergine/sceneobjects/obb.h>
#include <powergine/sceneobjects/physicsnode.h>
#include <powergine/sceneobjects/renderentity.h>
#include <powergine/sceneobjects/rigidbody.h>
#include <powergine/sceneobjects/room.h>
#include <powergine/sceneobjects/sceneentity.h>
#include <powergine/sceneobjects/scenenode.h>
#include <powergine/sceneobjects/skeleton.h>
#include <powergine/sceneobjects/skydome.h>
#include <powergine/sceneobjects/srtnode.h>
#include <powergine/sceneobjects/bspnode.h>
#include <powergine/sceneobjects/spring.h>
#include <powergine/sceneobjects/bspvisdata.h>
#include <powergine/sceneobjects/bsplump.h>
#include <powergine/sceneobjects/chb.h>
#include <powergine/services/comm/communicationmanager.h>
#include <powergine/services/comm/ioexception.h>
#include <powergine/services/comm/netkeyboardclient.h>
#include <powergine/services/comm/netkeyboardserver.h>
#include <powergine/services/comm/socket.h>
#include <powergine/services/comm/socketevent.h>
#include <powergine/services/comm/socketlistener.h>
#include <powergine/services/comm/sockettransferevent.h>
#include <powergine/services/comm/sdltcpsocket.h>
#include <powergine/services/comm/sdludpsocket.h>
#include <powergine/services/comm/invalidparameterexception.h>
#include <powergine/services/comm/netkeyboardeventadapter.h>
#include <powergine/services/comm/sdlnetkeyboardeventadapter.h>
#include <powergine/services/input/events/joyevent.h>
#include <powergine/services/input/events/keyevent.h>
#include <powergine/services/input/events/mousebuttonevent.h>
#include <powergine/services/input/events/mousemotionevent.h>
#include <powergine/services/input/inputmanager.h>
#include <powergine/services/input/listeners/joylistener.h>
#include <powergine/services/input/listeners/keylistener.h>
#include <powergine/services/input/listeners/mousebuttonlistener.h>
#include <powergine/services/input/listeners/mousemotionlistener.h>
#include <powergine/services/input/sdl/sdlinputmanager.h>
#include <powergine/services/input/inputaction.h>

#include <powergine/services/video/opengl/oglvideomanager.h>
#include <powergine/services/video/opengl/oglvertexbuffer.h>
#include <powergine/services/video/opengl/ogltexture.h>
#include <powergine/services/video/opengl/sdlimage.h>
#include <powergine/services/video/videomanager.h>
#include <powergine/services/video/orthographicprojection.h>
#include <powergine/services/video/perspectiveprojection.h>
#include <powergine/services/video/projection.h>
#include <powergine/services/video/rendermode.h>
#include <powergine/services/video/renderwindow.h>
#include <powergine/services/video/videoproperties.h>
#include <powergine/services/video/viewport.h>
#include <powergine/utils/contact.h>
#include <powergine/utils/contactset.h>
#include <powergine/utils/entityvisitor.h>
#include <powergine/utils/mathhelper.h>
#include <powergine/utils/buffer.h>
#include <powergine/utils/collection.h>
#include <powergine/utils/bitset.h>
#include <powergine/utils/iterator.h>
#include <powergine/tools/q3bspheader.h>
#include <powergine/tools/objfile.h>
#include <powergine/tools/q3bspface.h>
#include <powergine/tools/q3bspvertex.h>
#include <powergine/tools/q3bsplump.h>
#include <powergine/tools/q3bsptexture.h>
#include <powergine/tools/q3bspfile.h>
#include <powergine/tools/q3bspnode.h>
#include <powergine/tools/q3bspleaf.h>
#include <powergine/tools/q3bsplightmap.h>
#include <powergine/tools/q3bspplane.h>
#include <powergine/tools/q3bspvisdata.h>
#include <powergine/tools/q3bspbrush.h>
#include <powergine/tools/q3bspbrushside.h>
#include <powergine/tools/objface.h>
#include <powergine/tools/objmtllib.h>
#include <powergine/tools/astarpathfinder.h>

// creating a short namespace alias for the whole project classes
namespace pg {
	using namespace powergine;
	using namespace powergine::primitives;
	using namespace powergine::sceneobjects;
	using namespace powergine::services;
	using namespace powergine::services::video;
	using namespace powergine::services::video::opengl;
	using namespace powergine::services::comm;
	using namespace powergine::services::input;
	using namespace powergine::services::input::events;
	using namespace powergine::services::input::listeners;
	using namespace powergine::services::input::sdl;
	using namespace powergine::utils;
	using namespace powergine::tools;
};

#endif /*POWERGINE_H_*/
