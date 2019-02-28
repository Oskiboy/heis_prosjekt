cmake_minimum_required(VERSION 3.5.0)
project(HeisLab)

#---------------------
#   Initial setup
#---------------------
execute_process(COMMAND git submodule update --init)

add_compile_options(-std=c99 -Wall -pedantic)

#---------------------
#   Setting variables
#---------------------
# This step is primarily for Jenkins
if(DEFINED ENV{TEST_OUTPUT})
    set(test_output $ENV{TEST_OUTPUT})
else()
    set(test_output "${PROJECT_NAME}_test.bin")
endif()

if(DEFINED ENV{BUILD_OUTPUT})
    set(build_output "$ENV{BUILD_OUTPUT}")
else()
    set(build_output "${PROJECT_NAME}.bin")
endif()


#---------------------
#   Setting up sources and includes
#---------------------

#file(GLOB heislib_SRC "src/*.c")
#list(REMOVE_ITEM heislib_SRC "src/main.c")

include_directories(inc Unity/src)


#----------------------
#   Unity library
#----------------------
add_library(unity_lib Unity/src/unity.c)


#----------------------
#   Dummy executable
#----------------------
add_library(dummy_lib "src/test_lib.c")

add_executable(${test_output} "tests/dummy.c")


target_link_libraries(${test_output} dummy_lib unity_lib)
#add_library(heis_lib ${heislib_SRC})


add_executable(${build_output} src/main.c)
#target_link_libraries(${build_output} heis_lib)
