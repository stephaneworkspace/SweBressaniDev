//
// Created by Stéphane on 21.10.22.
//

#ifdef __cplusplus
extern "C" {
#endif
struct SweTimeZone {
    int year;
    int month;
    int day;
    int hour;
    int min;
    double sec;
};
struct SweUtcToJd {
    double julian_day_et;
    double julian_day_ut;
    const char* err;
    int result;
};

int cwrapperfive();
const char *theme_astral(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
const char *a_sign(int sign);
void swelib_set_ephe_path(char* path);
struct SweTimeZone swelib_utc_time_zone(struct SweTimeZone time_zone, double timezone);
struct SweUtcToJd swelib_utc_to_jd(struct SweTimeZone tz);
int swelib_house_ex(double tjd_ut, int iflag, double geolat, double geolon, int hsys, double *cusps, double *ascms);
#ifdef __cplusplus
}
#endif