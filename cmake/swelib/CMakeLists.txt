cmake_minimum_required(VERSION 2.8)
project(cswisseph)
message(STATUS "-- Configuring cswisseph...")
set(SOURCES
        ../../Sources/swelib/swecl.c
        ../../Sources/swelib/swedate.c
        ../../Sources/swelib/swehel.c
        ../../Sources/swelib/swehouse.c
        ../../Sources/swelib/swejpl.c
        ../../Sources/swelib/swemmoon.c
        ../../Sources/swelib/swemplan.c
    #swemptab.c
        ../../Sources/swelib/swepcalc.c
        ../../Sources/swelib/sweph.c
        ../../Sources/swelib/swephlib.c
)
include_directories(BEFORE ../../Sources/swelib)
add_library(swe STATIC ${SOURCES})