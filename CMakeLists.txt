cmake_minimum_required(VERSION 2.6)
project(SDL OPENGL TEST)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
include_directories(${SDL2_INCLUDE_DIRS})

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_FLAGS "-g -Wall -std=c++11")

add_executable(main main.cpp)

set(PROGRAMS GameLoop GLHandler Model shader_loader ModelInstance Shader Camera GraphicsPipeline FramebufferBinder)
# set(CORELIBS )
set(CORELIBS ${OPENGL_LIBRARY} ${SDL2_LIBRARIES})

foreach(program ${PROGRAMS})
	add_executable(${program} ${program}.cpp)
	target_link_libraries(${program} ${CORELIBS})
endforeach(program)

