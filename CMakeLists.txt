cmake_minimum_required(VERSION 3.5.0)
project(HeisLab)

execute_process(COMMAND git submodule update --init)

add_compile_options(-std=c99 -Wall -pedantic)

#file(GLOB heislib_SRC "src/*.c")
#list(REMOVE_ITEM heislib_SRC "src/main.c")

#include_directories(inc Unity/src)

#add_library(heis_lib ${heislib_SRC})


add_executable(${PROJECT_NAME}.bin src/main.c)
#target_link_libraries(${PROJECT_NAME}.bin heis_lib)
