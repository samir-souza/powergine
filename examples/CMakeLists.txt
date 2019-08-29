cmake_minimum_required(VERSION 2.8)
project( RRTViewr )

SET(POWERGINE_INCLUDE_DIR /usr/local/include)
SET(POWERGINE_LIBS_DIR /usr/local/lib)

add_executable( rrtviewer 
    rrtviewer/src/VBRRT.cpp
    rrtviewer/src/PerformanceReport.cpp
    rrtviewer/src/main.cpp
    rrtviewer/src/RRT.cpp
    rrtviewer/src/Map.cpp
    rrtviewer/src/Obstacle.cpp
    rrtviewer/src/GoalBiasRRT.cpp
    rrtviewer/src/SRRT.cpp
    rrtviewer/src/RRTFactory.cpp
    rrtviewer/src/Renderer.cpp
    rrtviewer/src/StarRRT.cpp
)
find_library ( POWERGINE NAMES libpowergine.so PATHS ${POWERGINE_LIBS_DIR} )

target_include_directories(rrtviewer PRIVATE /usr/include/freetype2 ${POWERGINE_INCLUDE_DIR} ${PROJECT_SOURCE_DIR}/rrtviewer/include)
link_directories(${POWERGINE_LIBS_DIR})

find_library ( FTGL NAMES libftgl.so)
find_library ( FREETYPE NAMES libfreetype2.so)
find_package(SDL REQUIRED SDL>=1.2.0)
find_package(SDL_image REQUIRED SDL_image>=1.2.0)
find_package(SDL_net REQUIRED SDL_net>=1.2.0)

target_link_libraries( rrtviewer powergine ftgl freetype GL SDL SDL_image SDL_net)
