project(SweInterface)
set(CMAKE_CXX_STANDARD 20)
set(SOURCES
        ../../Sources/sweinterfacelib/angle.cpp
        ../../Sources/sweinterfacelib/aspect.cpp
        ../../Sources/sweinterfacelib/astre.cpp
        ../../Sources/sweinterfacelib/draw.cpp
        ../../Sources/sweinterfacelib/draw_aspect_line.cpp
        ../../Sources/sweinterfacelib/draw_bodie_astre.cpp
        ../../Sources/sweinterfacelib/draw_bodie_line.cpp
        ../../Sources/sweinterfacelib/draw_house_angle.cpp
        ../../Sources/sweinterfacelib/draw_house_line.cpp
        ../../Sources/sweinterfacelib/draw_house_number.cpp
        ../../Sources/sweinterfacelib/draw_zodiac_circle.cpp
        ../../Sources/sweinterfacelib/draw_zodiac_line.cpp
        ../../Sources/sweinterfacelib/draw_zodiac_sign.cpp
        ../../Sources/sweinterfacelib/swe02.cpp
        ../../Sources/sweinterfacelib/swe03.cpp
        ../../Sources/sweinterfacelib/swe08.cpp
        ../../Sources/sweinterfacelib/swe14.cpp
        ../../Sources/sweinterfacelib/swe17.cpp
        ../../Sources/sweinterfacelib/house.cpp
        ../../Sources/sweinterfacelib/sign.cpp
        ../../Sources/sweinterfacelib/timezone.cpp
        ../../Sources/sweinterfacelib/SweInterface.cpp)

include_directories( BEFORE ../../Sources/sweinterfacelib)
include_directories("../../Sources/swelib/include")
include_directories("../../Sources/svglib/include")
add_library(SweInterface STATIC ${SOURCES})