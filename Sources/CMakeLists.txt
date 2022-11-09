cmake_minimum_required(VERSION 3.22)
project(SweBressaniDev)

set(CMAKE_CXX_STANDARD 20)

add_subdirectory(svglib)
add_subdirectory(swelib)
add_subdirectory(sweinterfacelib)
add_subdirectory(wasmlib)

include_directories("../swelib/include")
include_directories("../svglib/include")
include_directories("../sweinterfacelib/include")
include_directories("../wasmlib/include")

#add_library(SweBressaniDev STATIC wasm/wasm.cpp wasm/include/wasm.h)

#target_link_libraries (SweBressaniDev Svg)
#target_link_libraries (SweBressaniDev swe)
#target_link_libraries (SweBressaniDev SweInterface)
#target_link_libraries (SweBressaniDev Wasm)

