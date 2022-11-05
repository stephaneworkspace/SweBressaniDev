//
// Created by Stéphane on 21.10.22.
//

#import "include/cwrapper.h"
#import "cpplib.h"
#include "sweinterfacelib.h"

int cwrapperfive() {
    return cpplib::five();
}

const char *theme_astral(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path, int color_mode) {
    return sweinterfacelib::theme_astral_svg(year, month, day, hour, min, lat, lng, gmt, ephem_path, color_mode);
}

const char *a_sign(int sign) {
    return sweinterfacelib::asset_sign(sign);
}

const char *a_house(int house) {
    return sweinterfacelib::asset_house(house);
}

const char *a_bodie(int bodie) {
    return sweinterfacelib::asset_bodie(bodie);
}

const char *a_bodie_r(int bodie) {
    return sweinterfacelib::asset_bodie_r(bodie);
}

const char *a_angle(int angle, int color_mode) {
    return sweinterfacelib::asset_angle(angle, color_mode);
}


void swelib_set_ephe_path(char* path) {
    swelib::swe_set_ephe_path(path);
}

SweTimeZone swelib_utc_time_zone(struct SweTimeZone time_zone, double timezone)  {
    sweinterfacelib::TimeZone utc_time_zone_t;
    utc_time_zone_t.year = time_zone.year;
    utc_time_zone_t.month = time_zone.month;
    utc_time_zone_t.day = time_zone.day;
    utc_time_zone_t.hour = time_zone.hour;
    utc_time_zone_t.min = time_zone.min;
    utc_time_zone_t.sec = time_zone.sec;
    sweinterfacelib::TimeZone res = sweinterfacelib::TZ::utc_time_zone(utc_time_zone_t, timezone);
    SweTimeZone tz;
    tz.year = res.year;
    tz.month = res.month;
    tz.day = res.day;
    tz.hour = res.hour;
    tz.min = res.min;
    tz.sec = res.sec;
    return tz;
}

void swelib_utc_time_zone(int year, int month, int day, int hour, int min, double sec, double d_timezone, int* p_year_out, int* p_month_out, int* p_day_out, int* p_hour_out, int* p_min_out, double* p_sec_out) {
    swelib::swe_utc_time_zone(year, month, day, hour, min, sec, d_timezone, p_year_out, p_month_out, p_day_out, p_hour_out, p_min_out, p_sec_out);
}

SweUtcToJd swelib_utc_to_jd(SweTimeZone tz) {
    sweinterfacelib::TimeZone utc_time_zone_t;
    utc_time_zone_t.year = tz.year;
    utc_time_zone_t.month = tz.month;
    utc_time_zone_t.hour = tz.hour;
    utc_time_zone_t.day = tz.day;
    utc_time_zone_t.min = tz.min;
    utc_time_zone_t.sec = tz.sec;
    sweinterfacelib::UtcToJd utc_to_jd_t = sweinterfacelib::Swe08::utc_to_jd(utc_time_zone_t, sweinterfacelib::CALANDAR_GREGORIAN);
    SweUtcToJd utc_to_jd;
    utc_to_jd.julian_day_et = utc_to_jd_t.julian_day_et;
    utc_to_jd.julian_day_ut = utc_to_jd_t.julian_day_ut;
    utc_to_jd.err = utc_to_jd_t.err.c_str();
    utc_to_jd.result = utc_to_jd_t.result;
    return utc_to_jd;
}

SweHouse swelib_house_ex(SweUtcToJd utc_to_jd, double lat, double lng, int house) {
    sweinterfacelib::H house_h = sweinterfacelib::Swe14::house(utc_to_jd.julian_day_ut, lat, lng, 'P', house);
    SweHouse h;
    h.object_id = house_h.object_id;
    h.longitude = house_h.longitude;
    h.split.deg = house_h.split.deg;
    h.split.print = house_h.split.print.c_str();
    h.split.deg = house_h.split.deg;
    h.split.min = house_h.split.min;
    h.split.sec = house_h.split.sec;
    h.split.cdegfr = house_h.split.cdegfr;
    h.split.sign = house_h.split.sign;
    h.split.result = house_h.split.result;
    h.angle = house_h.angle;
    return h;
}

SweCalcUt swelib_calc_ut(SweUtcToJd utc_to_jd, int ipl) {
    sweinterfacelib::CalcUt calcul_ut = sweinterfacelib::Swe03::calc_ut(utc_to_jd.julian_day_ut, ipl, sweinterfacelib::OPTION_FLAG_SPEED);
    SweCalcUt c_ut;
    c_ut.longitude = calcul_ut.longitude;
    c_ut.latitude = calcul_ut.latitude;
    c_ut.distance_au = calcul_ut.distance_au;
    c_ut.speed_longitude = calcul_ut.speed_longitude;
    c_ut.speed_latitude = calcul_ut.speed_latitude;
    c_ut.speed_distance_au = calcul_ut.speed_distance_au;
    c_ut.status = calcul_ut.status;
    c_ut.serr = calcul_ut.serr.c_str();
    c_ut.split.print = calcul_ut.split.print.c_str();
    c_ut.split.deg = calcul_ut.split.deg;
    c_ut.split.min = calcul_ut.split.min;
    c_ut.split.sec = calcul_ut.split.sec;
    c_ut.split.cdegfr = calcul_ut.split.cdegfr;
    c_ut.split.sign = calcul_ut.split.sign;
    c_ut.split.result = calcul_ut.split.result;
    return c_ut;
}