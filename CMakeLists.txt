cmake_minimum_required(VERSION 2.8)
project( PowerGine )
if (APPLE)
set(CMAKE_MACOSX_RPATH 1)
endif()

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.cpp)
add_library(powergine SHARED ${SRC_FILES})

find_package(SDL REQUIRED sdl)
find_package(SDL_image REQUIRED SDL_image>=1.2.0)
find_package(SDL_net REQUIRED SDL_net>=1.2.0)
find_package(OpenGL REQUIRED)

if (APPLE)
    include_directories( ${OPENGL_INCLUDE_DIR}/Headers)
else()
    include_directories( ${OPENGL_INCLUDE_DIR}/GL)
endif()

include_directories(${SDL_INCLUDE_DIR})

target_link_libraries(powergine ${OPENGL_LIBRARY})
target_link_libraries(powergine ${SDL_LIBRARY} ${SDL_NET_LIBRARY} ${SDL_IMAGE_LIBRARY})
target_include_directories(powergine PRIVATE ${PROJECT_SOURCE_DIR}/include)

install(TARGETS powergine DESTINATION /usr/local/lib)
install(DIRECTORY include/ DESTINATION include)
