cmake_minimum_required(VERSION 3.10)

project(jmatrix)
set(CURSES_NEED_NCURSES TRUE)

# header files
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

# source files
file(GLOB SOURCES "src/*.cpp")

set(CMAKE_CXX_FLAGS_RELEASE "-O3")
set(CMAKE_CXX_STANDARD 20)

add_executable(jmatrix ${SOURCES})
target_link_libraries(jmatrix ${CURSES_LIBRARIES})
