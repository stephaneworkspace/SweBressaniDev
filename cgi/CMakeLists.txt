project(SweInterfaceCgi)
set(CMAKE_CXX_STANDARD 20)
include_directories( BEFORE . )
include_directories("../Sources/swelib/include")
include_directories("../Sources/svglib/include")
include_directories("../Sources/sweinterfacelib/include")




add_executable(SweInterfaceCgi
        main.cpp
        ../Sources/swelib/include/swelib.h
        ../Sources/swelib/swecl.c
        ../Sources/swelib/swedate.c
        ../Sources/swelib/swehel.c
        ../Sources/swelib/swehouse.c
        ../Sources/swelib/swejpl.c
        ../Sources/swelib/swemmoon.c
        ../Sources/swelib/swemplan.c
        ../Sources/swelib/swepcalc.c
        ../Sources/swelib/sweph.c
        ../Sources/swelib/swephlib.c

        ../Sources/svglib/circle.cpp
        ../Sources/svglib/data.cpp
        ../Sources/svglib/document.cpp
        ../Sources/svglib/line.cpp
        ../Sources/svglib/image.cpp

       ../Sources/sweinterfacelib/angle.cpp
       ../Sources/sweinterfacelib/aspect.cpp
       ../Sources/sweinterfacelib/astre.cpp
       ../Sources/sweinterfacelib/draw.cpp
       ../Sources/sweinterfacelib/draw_aspect_line.cpp
       ../Sources/sweinterfacelib/draw_bodie_astre.cpp
       ../Sources/sweinterfacelib/draw_bodie_line.cpp
       ../Sources/sweinterfacelib/draw_house_angle.cpp
       ../Sources/sweinterfacelib/draw_house_line.cpp
       ../Sources/sweinterfacelib/draw_house_number.cpp
       ../Sources/sweinterfacelib/draw_zodiac_circle.cpp
       ../Sources/sweinterfacelib/draw_zodiac_line.cpp
       ../Sources/sweinterfacelib/draw_zodiac_sign.cpp
       ../Sources/sweinterfacelib/swe02.cpp
       ../Sources/sweinterfacelib/swe03.cpp
       ../Sources/sweinterfacelib/swe08.cpp
       ../Sources/sweinterfacelib/swe14.cpp
       ../Sources/sweinterfacelib/swe17.cpp
       ../Sources/sweinterfacelib/house.cpp
       ../Sources/sweinterfacelib/sign.cpp
       ../Sources/sweinterfacelib/timezone.cpp
       ../Sources/sweinterfacelib/SweInterface.cpp)

include_directories(BEFORE ../Sources/swelib)
include_directories(BEFORE ../Sources/svglib)
include_directories( BEFORE ../Sources/sweinterfacelib)
include_directories( BEFORE . )