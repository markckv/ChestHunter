cmake_minimum_required(VERSION 3.8)
project(ChestHunter)

set(CMAKE_CXX_STANDARD 17)

include(FindPkgConfig)
pkg_search_module(SDL2 REQUIRED sdl2)
find_package(OpenGL REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS})
pkg_search_module(SDL2 REQUIRED sdl2)
pkg_search_module(SDL2_net REQUIRED SDL2_net)
pkg_search_module(SDL2_image REQUIRED SDL2_image)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
set(SOURCE_FILES main.cpp SRC/Net.cpp SRC/Net.h SRC/MapGenerator.cpp SRC/MapGenerator.h SRC/GameObject.h SRC/Graphics.cpp SRC/Graphics.h SRC/RunGame.cpp SRC/RunGame.h SRC/fakeSDL.h)
add_executable(ChestHunter ${SOURCE_FILES})
target_link_libraries(ChestHunter ${SDL2_image_LIBRARIES} ${SDL2_net_LIBRARIES}  ${SDL2_LIBRARIES} ${OPENGL_LIBRARIES} )