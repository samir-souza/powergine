cmake_minimum_required(VERSION 2.8)
project( PowerGine )

SET(OPENCV_LIBS_DIR /usr/local/lib)

add_library(powergine SHARED
    src/powergine/utils/contactset.cpp
    src/powergine/utils/bitset.cpp
    src/powergine/utils/mathhelper.cpp
    src/powergine/utils/entityvisitor.cpp
    src/powergine/utils/contact.cpp
    src/powergine/core.cpp
    src/powergine/tools/objmtllib.cpp
    src/powergine/tools/q3bspfile.cpp
    src/powergine/tools/objfile.cpp
    src/powergine/tools/astarpathfinder.cpp
    src/powergine/sceneobjects/aabb.cpp
    src/powergine/sceneobjects/sceneentity.cpp
    src/powergine/sceneobjects/bspvisdata.cpp
    src/powergine/sceneobjects/light.cpp
    src/powergine/sceneobjects/skeleton.cpp
    src/powergine/sceneobjects/skydome.cpp
    src/powergine/sceneobjects/rigidbody.cpp
    src/powergine/sceneobjects/scenenode.cpp
    src/powergine/sceneobjects/obb.cpp
    src/powergine/sceneobjects/mesh.cpp
    src/powergine/sceneobjects/room.cpp
    src/powergine/sceneobjects/bsplump.cpp
    src/powergine/sceneobjects/baseentity.cpp
    src/powergine/sceneobjects/joint.cpp
    src/powergine/sceneobjects/camera.cpp
    src/powergine/sceneobjects/spring.cpp
    src/powergine/sceneobjects/srtnode.cpp
    src/powergine/sceneobjects/physicsnode.cpp
    src/powergine/sceneobjects/bsptree.cpp
    src/powergine/sceneobjects/frustum.cpp
    src/powergine/sceneobjects/chb.cpp
    src/powergine/sceneobjects/renderentity.cpp
    src/powergine/sceneobjects/bspnode.cpp
    src/powergine/sceneobjects/massparticle.cpp
    src/powergine/services/input/inputmanager.cpp
    src/powergine/services/input/sdl/sdlinputmanager.cpp
    src/powergine/services/comm/sdltcpsocket.cpp
    src/powergine/services/comm/netkeyboardserver.cpp
    src/powergine/services/comm/socket.cpp
    src/powergine/services/comm/sdludpsocket.cpp
    src/powergine/services/comm/netkeyboardclient.cpp
    src/powergine/services/comm/sdlnetkeyboardeventadapter.cpp
    src/powergine/services/comm/communicationmanager.cpp
    src/powergine/services/video/orthographicprojection.cpp
    src/powergine/services/video/perspectiveprojection.cpp
    src/powergine/services/video/projection.cpp
    src/powergine/services/video/renderwindow.cpp
    src/powergine/services/video/viewport.cpp
    src/powergine/services/video/rendermode.cpp
    src/powergine/services/video/videomanager.cpp
    src/powergine/services/video/opengl/oglvideomanager.cpp
    src/powergine/services/video/opengl/ogltexture.cpp
    src/powergine/services/video/opengl/sdlimage.cpp
    src/powergine/services/video/opengl/oglvertexbuffer.cpp
    src/powergine/services/video/videoproperties.cpp
    src/powergine/services/physics/physicsmanager.cpp
    src/powergine/primitives/vector3d.cpp
    src/powergine/primitives/matrix3x3.cpp
    src/powergine/primitives/quaternion.cpp
    src/powergine/primitives/vertex.cpp
    src/powergine/primitives/vertextexturediffusenormal.cpp
    src/powergine/primitives/vertextexture.cpp
    src/powergine/primitives/plane.cpp
    src/powergine/primitives/renderprimitive.cpp
    src/powergine/primitives/vertexdiffusenormal.cpp
    src/powergine/primitives/ray.cpp
    src/powergine/primitives/material.cpp
    src/powergine/primitives/line.cpp
    src/powergine/primitives/vertexelement.cpp
    src/powergine/primitives/quad.cpp
    src/powergine/primitives/vertextexturediffuse.cpp
    src/powergine/primitives/vertextexturenormal.cpp
    src/powergine/primitives/graph.cpp
    src/powergine/primitives/graphedge.cpp
    src/powergine/primitives/vertexnormal.cpp
    src/powergine/primitives/texture.cpp
    src/powergine/primitives/matrix4x4.cpp
    src/powergine/primitives/vertexbuffer.cpp
    src/powergine/primitives/polygonbuffer.cpp
    src/powergine/primitives/graphvertex.cpp
    src/powergine/primitives/color.cpp
    src/powergine/primitives/vertexdiffuse.cpp
    src/powergine/primitives/triangle.cpp
)

find_package(SDL REQUIRED sdl)
find_package(SDL_image REQUIRED SDL_image>=1.2.0)
find_package(SDL_net REQUIRED SDL_net>=1.2.0)

target_include_directories(powergine PRIVATE ${PROJECT_SOURCE_DIR}/include)

install(TARGETS powergine DESTINATION /usr/local/lib)
install(DIRECTORY include/ DESTINATION include)
