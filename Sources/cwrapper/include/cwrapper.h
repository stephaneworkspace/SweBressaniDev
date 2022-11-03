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

struct SweSplitDeg {
    const char *print;
    int deg;
    int min;
    int sec;
    double cdegfr;
    int sign;
    double result;
};

struct SweHouse {
    int object_id;
    double longitude;
    struct SweSplitDeg split;
    int angle;
};

struct SweCalcUt {
    double longitude;
    double latitude;
    double distanceAu;
    double speedLongitude;
    double speedLatitude;
    double speedDistanceAu;
    int status;
    const char* serr;
    struct SweSplitDeg split;
};

struct SwePhenoUt {
    double phaseAngle;
    double phaseIlluminated;
    double elongationOfPlanet;
    double apparentDimaeterOfDisc;
    double apparentMagnitude;
    int status;
    const char* serr;
};

struct SweBodie {
    int bodie;
    struct SweCalcUt calculUt;
    struct SwePhenoUt phnoUt;
};

int cwrapperfive();
const char *theme_astral(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
const char *a_sign(int sign);
const char *a_house(int house);
const char *a_bodie(int bodie);
void swelib_set_ephe_path(char* path);
struct SweTimeZone swelib_utc_time_zone(struct SweTimeZone time_zone, double timezone);
struct SweUtcToJd swelib_utc_to_jd(struct SweTimeZone tz);
struct SweHouse swelib_house_ex(struct SweUtcToJd utc_to_jd, double lat, double lng, int house);
#ifdef __cplusplus
}
#endif