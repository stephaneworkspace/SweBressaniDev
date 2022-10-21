//
// Created by Stéphane on 21.10.22.
//

#import "include/cwrapper.h"
#import "cpplib.h"
#include "sweinterfacelib.h"

int cwrapperfive() {
    return cpplib::five();
}

const char *theme_astral(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path) {
    return sweinterfacelib::theme_astral_svg(year, month, day, hour, min, lat, lng, gmt, ephem_path);
}
