cmake_minimum_required(VERSION 3.21)
project(IZ2_Gallaann C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_CXX_FLAGS         "-Wall -Wno-unknown-pragmas -Wno-sign-compare -Woverloaded-virtual -Wwrite-strings -Wno-unused -Werror -Wpedantic")
set(CMAKE_CXX_FLAGS_DEBUG   "-O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")

set(CMAKE_C_FLAGS "--coverage") #--coverage

add_executable(IZ2_Gallaann main.c)

add_subdirectory(src)

option(gtest "" ON)
if(gtest)
    add_subdirectory(gtests)
endif(gtest)

target_link_libraries(IZ2_Gallaann LINK_PUBLIC storage two_points -lm)

option(parallel "On = parallel" OFF)
if(parallel)
    target_link_libraries(IZ2_Gallaann LINK_PUBLIC realisation_parallel)
else()
    target_link_libraries(IZ2_Gallaann LINK_PUBLIC realisation_consistent)
endif(parallel)

unset(parallel CACHE)
unset(gtest CACHE)
