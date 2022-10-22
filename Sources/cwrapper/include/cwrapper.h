//
// Created by Stéphane on 21.10.22.
//

#ifdef __cplusplus
extern "C" {
#endif

int cwrapperfive();
const char *theme_astral(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
const char *a_sign(int sign);

#ifdef __cplusplus
}
#endif