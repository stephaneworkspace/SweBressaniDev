//
// Created by Stéphane on 27.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

int* Aspect::angle(int a) {
    int* res = new int[2];
    switch (a) {
        case ASPECTS_CONJUNCTION:
            res[0] = 0;
            res[1] = 10;
            break;
        case ASPECTS_OPPOSITION:
            res[0] = 180;
            res[1] = 8;
            break;
        case ASPECTS_TRINE:
            res[0] = 120;
            res[1] = 7;
            break;
        case ASPECTS_SQUARE:
            res[0] = 90;
            res[1] = 6;
            break;
        case ASPECTS_SEXTILE:
            res[0] = 60;
            res[1] = 5;
            break;
        case ASPECTS_INCONJUNCTION:
            res[0] = 150;
            res[1] = 2;
            break;
        case ASPECTS_SEQUISQUARE:
            res[0] = 135;
            res[1] = 1;
            break;
        case ASPECTS_SEMISQUARE:
            res[0] = 45;
            res[1] = 1;
            break;
        case ASPECTS_SEMISEXTILE:
            res[0] = 30;
            res[1] = 1;
            break;
    }
    return res;
}