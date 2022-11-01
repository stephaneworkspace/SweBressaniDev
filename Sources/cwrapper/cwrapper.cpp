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

void swelib_set_ephe_path(char* path) {
    swelib::swe_set_ephe_path(path);
    free(path);
}

SweTimeZone swelib_utc_time_zone(struct SweTimeZone time_zone, double timezone)  {
    sweinterfacelib::TimeZone utc_time_zone_t;
    utc_time_zone_t.year = time_zone.year;
    utc_time_zone_t.month = time_zone.month;
    utc_time_zone_t.day = time_zone.day;
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
    utc_time_zone_t.day = tz.day;
    utc_time_zone_t.min = tz.min;
    utc_time_zone_t.sec = tz.sec;
    sweinterfacelib::UtcToJd utc_to_jd_t = sweinterfacelib::Swe08::utc_to_jd(utc_time_zone_t, sweinterfacelib::Calandar::gregorian);
    SweUtcToJd utc_to_jd;
    utc_to_jd.julian_day_et = utc_to_jd_t.julian_day_et;
    utc_to_jd.julian_day_ut = utc_to_jd_t.julian_day_ut;
    utc_to_jd.err = utc_to_jd_t.err.c_str();
    utc_to_jd.result = utc_to_jd_t.result;
    return utc_to_jd;
}

int swelib_house_ex(double tjd_ut, int iflag, double geolat, double geolon, int hsys, double *cusps, double *ascms) {
    return swelib::swe_houses_ex(tjd_ut, iflag, geolat, geolon, hsys, cusps, ascms);
}


const char *a_sign(int sign) {
    return sweinterfacelib::asset_sign(sign);
}

