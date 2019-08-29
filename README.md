
## PowerGine - A simple 3D Game Engine
---------

PowerGine is an implementation of a (purely object oriented)
3D Game engine. It was programmed in C++ and was developed for
research and development purposes. PowerGine is not a
complete Game Engine. However, if you like the project and want 
to use it or parts of it in your own project, please add a 
reference to PowerGine.

PowerGine has a lot of functionalities and can be considered
a good reference material. There are several open source engines
that can be used if you wish to create a complete game.
For instance Ogre3D (www.ogre3d.org).

You can find more information about this project on:
http://samir.araujo.googlepages.com/

Functionalities
---------------

- A powerful math library
- Complete scene-graph support
- Generic rendering interface, that can be used to implement several renderers
  - An OpenGL renderer is available
- Centralized access to all resources
- External mesh files loader for Wavefront .obj files
- Quake 3 BSP map file loader
- Graph support that can be used to build paths, waypoints and path-planning
- A simple implementation of the classical A* algorithm, compatible with the
  Graph library of the engine
- Network communications support
- Virtual keyboard: You can control an application remotely with this tool
- Support for keyboard, mouse and joystick
- Basic infrastructure for collision detection and physics

Building
--------

This project has dependencies with other libraries:
SDL/SDL_image/SDL_net - www.libsdl.org

```console
$ mkdir build && cd build
$ cmake .. && make -j4
```

Done! Just link the shared library in your project.

--------------------------------------------------------
Copyright (c) 2004 Samir Araujo <samir.araujo (at) gmail.com>
http://samir.araujo.googlepages.com/
