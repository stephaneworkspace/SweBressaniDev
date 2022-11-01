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

void set_ephe_path(char* path) {
    swelib::swe_set_ephe_path(path);
    free(path);
}

void swe_utc_time_zone(int iyear, int imonth, int iday, int ihour, int imin, double dsec, double d_timezone, int* iyear_out, int* imonth_out, int* iday_out, int* ihour_out, int* imin_out, double* dsec_out) {
    swelib::swe_utc_time_zone(iyear, imonth, iday, ihour, imin, dsec, d_timezone, iyear_out, imonth_out, iday_out, ihour_out, imin_out, dsec_out);
}

const char *a_sign(int sign) {
    return sweinterfacelib::asset_sign(sign);
}
