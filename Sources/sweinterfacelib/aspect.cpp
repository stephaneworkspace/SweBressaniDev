//
// Created by Stéphane on 27.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

int* Aspect::angle(Aspects a) {
    int* res = new int[2];
    switch (a) {
        case Aspects::conjunction:
            res[0] = 0;
            res[1] = 10;
            break;
        case Aspects::opposition:
            res[0] = 180;
            res[1] = 8;
            break;
        case Aspects::trine:
            res[0] = 120;
            res[1] = 7;
            break;
        case Aspects::square:
            res[0] = 90;
            res[1] = 6;
            break;
        case Aspects::sextile:
            res[0] = 60;
            res[1] = 5;
            break;
        case Aspects::inconjunction:
            res[0] = 150;
            res[1] = 2;
            break;
        case Aspects::sequisquare:
            res[0] = 135;
            res[1] = 1;
            break;
        case Aspects::semisquare:
            res[0] = 45;
            res[1] = 1;
            break;
        case Aspects::semisextile:
            res[0] = 30;
            res[1] = 1;
            break;
    }
    return res;
}