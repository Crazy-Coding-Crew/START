cmake_minimum_required(VERSION 3.1)

project(Start_db)

set(CMAKE_CXX_COMPILER g++-4.9)
set(BUILD_SHARED_LIBS on)

#compiler flags
add_definitions(-std=c++1y -fPIC)

#file lists
file(GLOB SRC "src/*.cxx")
file(GLOB INC "include/*.h")
file(GLOB ODB "odb/*.*")

#include/lib directories lookup
include_directories($ENV{BOOST_INC_DIR} $ENV{ODB_INC_DIR} /usr/include/python2.7/ include/ odb/)
link_directories($ENV{BOOST_LIB_DIR} $ENV{ODB_LIB_DIR})

#odb cmd
add_custom_target(OUTPUT
        COMMAND mkdir -p odb
        COMMAND mkdir -p odb/schema
        COMMAND odb -o odb/ --std c++11 -d pgsql --generate-query --generate-schema --hxx-suffix .h --ixx-suffix .icc -Iinclude/ -I$ENV{ODB_INC_DIR} ${INC}
        DEPENDS include/Database.h include/Share.h include/Tick.h
        WORKING_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}"
        VERBATIM)

#shared lib
add_library(DB SHARED ${SRC} ${INC} ${ODB})
target_link_libraries(DB -lboost_program_options -lodb-pgsql -lodb)
set_target_properties(DB PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/lib/)
add_dependencies(DB OUTPUT)

#exe
add_executable(updateDB ${SRC} ${INC} ${ODB})
target_link_libraries(updateDB -lboost_program_options -lodb-pgsql -lodb)
set_target_properties(updateDB PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}/bin/)
add_dependencies(updateDB OUTPUT)
