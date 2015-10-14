cmake_minimum_required(VERSION 3.1)

project(Start.core)

set(CMAKE_CXX_COMPILER g++-4.9)
set(BUILD_SHARED_LIBS on)

add_definitions(-std=c++1y -fPIC)

file(GLOB SRC "src/*.cxx")
file(GLOB INC "include/*.h")

include_directories(include $ENV{BOOST_INC_DIR} $ENV{ODB_INC_DIR} /usr/include/python2.7/ ../DB/include/)

add_library(Start_core SHARED ${INC} ${SRC})