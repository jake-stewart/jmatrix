
cmake_minimum_required(VERSION 3.10)

project(jmatrix)

# header files
include_directories(include)

# source files
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
SET(CMAKE_CXX_STANDARD 11)

add_executable(jmatrix ${SOURCES})


