cmake_minimum_required(VERSION 3.1)

project(Start_db)

set(CMAKE_CXX_COMPILER g++-4.9)
set(BUILD_SHARED_LIBS on)

set( CMAKE_LIBRARY_PATH /soft/odb/2.4.0/lib)
add_definitions(-std=c++1y -fPIC)

file(GLOB SRC "src/*.cxx")
file(GLOB INC "include/*.h")

include_directories(include $ENV{BOOST_INC_DIR} $ENV{ODB_INC_DIR} /usr/include/python2.7/ include/ odb/)

add_library(Start_db SHARED ${INC} ${SRC})

add_custom_target(OUTPUT
        COMMAND mkdir -p odb
        COMMAND mkdir -p odb/schema
        COMMAND odb -o odb/ --std c++11 -d pgsql --generate-query --generate-schema --hxx-suffix .h --ixx-suffix .icc -Iinclude/ -I/soft/odb/2.4.0/include/ include/Database.h include/Share.h include/Tick.h
        DEPENDS include/Database.h include/Share.h include/Tick.h
        WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
        VERBATIM)

target_link_libraries(Start_db -L/soft/odb/2.4.0/lib -lodb-pgsql -lodb)

add_dependencies(${PROJECT_NAME} OUTPUT)