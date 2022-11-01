//
// Created by Stéphane on 21.10.22.
//

#ifdef __cplusplus
extern "C" {
#endif

int cwrapperfive();
const char *theme_astral(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
const char *a_sign(int sign);
void set_ephe_path(char* path);
void swe_utc_time_zone(int iyear, int imonth, int iday, int ihour, int imin, double dsec, double d_timezone, int *iyear_out, int *imonth_out, int *iday_out, int *ihour_out, int *imin_out, double *dsec_out);
#ifdef __cplusplus
}
#endif