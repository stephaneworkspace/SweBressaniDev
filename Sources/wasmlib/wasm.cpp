//
// Created by Stéphane on 09.11.22.
//

#include "include/wasm.h"

const char *theme_astral(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path, int color_mode) {
    return sweinterfacelib::theme_astral_svg(year, month, day, hour, min, lat, lng, gmt, ephem_path, color_mode);
}
