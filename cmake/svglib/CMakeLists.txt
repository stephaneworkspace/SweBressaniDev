cmake_minimum_required(VERSION 3.22)
project(Svg)
set(CMAKE_CXX_STANDARD 20)
set(SOURCES
        ../../Sources/svglib/circle.cpp
        ../../Sources/svglib/data.cpp
        ../../Sources/svglib/document.cpp
        ../../Sources/svglib/line.cpp
        ../../Sources/svglib/image.cpp
)

include_directories(BEFORE ../../Sources/svglib)
add_library(Svg STATIC ${SOURCES})