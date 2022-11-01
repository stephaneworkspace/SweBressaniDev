//
// Created by Stéphane on 22.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

H Swe14::house(double tjd_ut, double geo_lat, double geo_lng, char hsys, int house) {
    double* cusps_ptr = new double[37];
    double* ascmc_ptr = new double[10];
    int _ = swe_houses_ex(tjd_ut, 0, geo_lat, geo_lng, hsys, cusps_ptr, ascmc_ptr);
    int angle = ANGLES_NOTHING;
    if (house == 1) {
        angle = ANGLES_ASC;
    }
    if (house == 4) {
        angle = ANGLES_FC;
    }
    if (house == 7) {
        angle = ANGLES_DESC;
    }
    if (house == 10) {
        angle = ANGLES_MC;
    }
    H res = House::init(house, cusps_ptr[house], angle);
    free(cusps_ptr);
    free(ascmc_ptr);
    return res;
}

