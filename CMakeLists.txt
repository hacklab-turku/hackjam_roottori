cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_COMPILER g++)
project(game_project)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
find_package(SFML 2 COMPONENTS graphics audio window system)
include_directories(${SFML_INCLUDE_DIR})

add_definitions(-std=c++0x -g)

FILE(GLOB sources source/*)
add_executable(game_project ${sources})
target_link_libraries(game_project ${SFML_LIBRARIES})
