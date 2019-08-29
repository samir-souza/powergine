
		Rapidly-exploring Random Trees (RRTs) visualizer
		------------------------------------------------
		
This application is a visualizer tool for observing the behavior of
five variations of the path-builder algorithm RRT. Besides the original
implementation of the RRT algorithm, four other variations were 
implemented. These variations have different heuristics to reach the same
goal. A variation called SRRT or Swimming RRT was proposed by me (Samir).

If you want more information about the RRTs, please take a look at:
http://msl.cs.uiuc.edu/rrt/

This application is also a demonstration of the use of library PowerGine,
a very simple 3D Engine written by me for studies and researching purposes.

You can found more information about this tool and the PowerGine in my website:
http://samir.araujo.googlepages.com/

Usage
-----

Just run the .exe. It will loads the images from the data/ directory and 
renders the scene. You can use the following commands to control the application:

The first four commands are only valid when the camera 1 is selected
a = Move the map to the left
d = Move the map to the right
w = Move the map up
s = Move the map down

z = Zoom in
x = Zoom out
q = Quit the application
r = Restore the initial state of the application

By default, the application starts with the original RRT algorithm selected
and ready to run. You can change the algorithm by using the following commands 
f = Previous algorithm
g = Next algorithm

The name of the current selected algorithm is shown on the top right corner 

You can see the tree growing step-by-step. Use the option bellow to activate
or deactivate the step-by-step mode
i = toggle step-by-step

m = Rebuilds the map and chooses another obstacles set
 
k = Saves the current map to a file
l = Loads the map from the file

There are two cameras that can be used to visualize the trees. A movable
camera (1) and a fixed camera at one corner of the map (2) 
1/2 = Change camera

Building
--------

This project was configured to be built with Eclipse(CDT)/Mingw. Mingw is a gcc 
port for Windows. Given that this application was originally programmed for Linux,
the most straightforward option to create a windows version of it was using
mingw, although a Visual Studio (C++) project can be easily created to compile
PowerGine and this tool.
MinGW - www.mingw.org
Eclipse - www.eclipse.org

This project also has dependencies with other libraries than PowerGine
SDL/SDL_image/SDL_net - www.libsdl.org
FTGL (Fonts for OpenGL) - ftgl.wiki.sourceforge.net
FreeType - www.freetype.org

```console
sudo apt-get install libftgl-dev
mkdir build && cd build
make -j3
ln -s ../rrtviewer/data/ .
./rrtviewer
```

--------------------------------------------------------  
Copyright (c) 2007 Samir Araujo <samir.araujo@gmail.com>
http://samir.araujo.googlepages.com/
