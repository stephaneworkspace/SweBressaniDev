cmake_minimum_required(VERSION 3.22)
project(Svg)
set(CMAKE_CXX_STANDARD 20)
set(SOURCES
    circle.cpp
    data.cpp
    document.cpp
    line.cpp
    image.cpp
)

include_directories(BEFORE .)
add_library(Svg STATIC ${SOURCES})