project(Wasm)
set(CMAKE_CXX_STANDARD 20)
set(SOURCES
    wasm.cpp
)

include_directories( BEFORE . )
include_directories("../swelib/include")
include_directories("../svglib/include")
include_directories("../sweinterfacelib/include")
add_library(Wasm STATIC ${SOURCES})