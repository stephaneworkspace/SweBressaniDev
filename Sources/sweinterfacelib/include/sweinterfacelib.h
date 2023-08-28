//
// Created by Stéphane on 21.10.22.
//
#pragma once
#include <iostream>
//#include <fstream>
#include <string>
#include <cstring>
#include <cmath>
#include "base64.h"
#include "svglib.h"
#include "swelib.h"

using namespace std;
using namespace svglib;
using namespace swelib;

namespace sweinterfacelib {
    // Signs
    const int SIGNS_BELIER = 1;
    const int SIGNS_TAUREAU = 2;
    const int SIGNS_GEMAUX = 3;
    const int SIGNS_CANCER = 4;
    const int SIGNS_LION = 5;
    const int SIGNS_VIERGE = 6;
    const int SIGNS_BALANCE = 7;
    const int SIGNS_SCORPION = 8;
    const int SIGNS_SAGITTAIRE = 9;
    const int SIGNS_CAPRICORNE = 10;
    const int SIGNS_VERSEAU = 11;
    const int SIGNS_POISSON = 12;
    // Swe17
    struct SplitDeg {
        string print;
        int deg;
        int min;
        int sec;
        double cdegfr;
        int sign;
        double result;
    };

    // Angles
    const int ANGLES_NOTHING = 0;
    const int ANGLES_ASC = 1;
    const int ANGLES_FC = 2;
    const int ANGLES_DESC = 3;
    const int ANGLES_MC = 4;

    // Aspects
    const int ASPECTS_CONJUNCTION = 0;
    const int ASPECTS_OPPOSITION = 1;
    const int ASPECTS_TRINE = 2;
    const int ASPECTS_SQUARE = 3;
    const int ASPECTS_SEXTILE = 4;
    const int ASPECTS_INCONJUNCTION = 5;
    const int ASPECTS_SEQUISQUARE = 6;
    const int ASPECTS_SEMISQUARE = 7;
    const int ASPECTS_SEMISEXTILE = 8;

    // Ordre dans le pointeur
    const int SOLEIL = 0;
    const int LUNE = 1;
    const int MERCURE = 2;
    const int VENUS = 3;
    const int MARS = 4;
    const int JUPITER = 5;
    const int SATURN = 6;
    const int URANUS = 7;
    const int NEPTUNE = 8;
    const int PLUTON = 9;
    const int NOEUD_LUNAIRE = 10;
    const int CHIRON = 11;
    const int CERES = 12;
    const int NOEUD_LUNAIRE_SUD = 13;

    // Lbraiaire Swe
    const int ASTRE_SOLEIL = 0;
    const int ASTRE_LUNE = 1;
    const int ASTRE_MERCURE = 2;
    const int ASTRE_VENUS = 3;
    const int ASTRE_MARS = 4;
    const int ASTRE_JUPITER = 5;
    const int ASTRE_SATURN = 6;
    const int ASTRE_URANUS = 7;
    const int ASTRE_NEPTUNE = 8;
    const int ASTRE_PLUTON = 9;
    const int ASTRE_NOEUD_LUNAIRE = 11;
    const int ASTRE_CHIRON = 15;
    const int ASTRE_CERES = 17;
    const int ASTRE_NOEUD_LUNAIRE_SUD = 24;

    //const int CALANDAR_JULIAN = 0;
    const int CALANDAR_GREGORIAN = 1;

    const double RETROGRADE_DIV = 1.5;

    struct CalcUt {
        double longitude;
        double latitude;
        double distance_au;
        double speed_longitude;
        double speed_latitude;
        double speed_distance_au;
        int status;
        string serr;
        SplitDeg split;
    };
    // Draw
    const int CHART_SIZE = 600;
    const double CHART_SIZE_MULTI = 1.6;
    const double CHART_SIZE_DIVID = 0.6;
    double const STROKE_FINE = 1;
    double const STROKE_BOLD = 2;
    struct Size {
        double width;
        double height;
    };
    struct Offset {
        double x;
        double y;
    };
    struct LineXY {
        double lx1;
        double ly1;
        double lx2;
        double ly2;
    };
    struct LineXY3 {
        double lx1;
        double ly1;
        double lx2;
        double ly2;
        double sw_lxy3;
        double lx3;
        double ly3;
    };
    struct LineXYAspect {
        double lx1;
        double ly1;
        double lx2;
        double ly2;
        bool sw;
        int aspect;
    };
    struct PairAspect {
        int i;
        int j;
    };
    // Draw zodiac circle
    enum CirclePositions {
        zero = 0,
        un = 1,
        deux = 2,
        trois = 3,
        quatre = 4,
        cinq = 5,
        six = 6,
        sept = 7,
        huit = 8,
    };
    struct CirclePosition {
        double pcent;
        double pcent_divider;
        bool sw;
    };
    struct CircleZod {
        double center;
        double radius;
        double radius_multiplier;
        double radius_divider;
        bool sw;
    };
    // Draw zodiac line
    enum larger_draw_line {
        small,
        large
    };
    // House
    struct H {
        int object_id;
        double longitude;
        SplitDeg split;
        int angle;
    };
    // Option flag
    const int OPTION_FLAG_SPEED = 256;
    /*
    enum OptionFlag {
        jpl_eph = 1,
        swiss_eph = 2,
        moshier = 4,
        heliocentric = 8,
        true_position = 16,
        j2000_equinox = 32,
        no_nutation = 64,
        speed3 = 128,
        speed = 256,
        no_gravitanional_deflection = 512,
        no_annual_aberration = 1024,
        astronomic_position = 1536,
        equatorial_position = 2048,
        x_y_z_cartesian_not_polar_coordinate = 4096,
        radians = 8192,
        barycentric_position = 16384,
        topocentric_position = 32768,
        sideral_position = 65536,
        i_CRS = 131072,
        dpsideps1980 = 262144,
        jpl_hor_approx = 524288
    };
     */
    // Swe07
    struct PhenoUt {
        double phase_angle;
        double phase_illuminated;
        double elongation_of_planet;
        double apparent_diameter_of_disc;
        double apparent_magnitude;
        int status;
        string serr;
    };
    // Swe08
    struct UtcToJd {
        double julian_day_et;
        double julian_day_ut;
        string err;
        int result;
    };
    // Timezone
    struct TimeZone {
        int year;
        int month;
        int day;
        int hour;
        int min;
        double sec;
    };
    struct PosAsset {
        double width;
        double height;
        double x;
        double y;
    };
    struct PosAstreAsset {
        const char* nom;
        bool retrograde;
        PosAsset astre;
        PosAsset astre_r;
        LineXY line;
    };
    const int COLOR_MODE_LIGHT = 0;
    const int COLOR_MODE_DARK = 1;
    const int MAX_ASTRES = 14;
    extern "C" {
        /*
         * Svg du thème complet
         */
        const char *theme_astral_svg(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path, int color_mode, const char *aspect_option);
        /*
         * Dessine les cercles sans les images, car j'aimerai séparer les symboles
         */
        const char *theme_astral_empty_svg(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path, int color_mode, const char* aspect_option);
        /*
         * Position des Maisons
         */
        const PosAsset* theme_astral_maison_pos(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
        /*
         * Position des Signs
         */
        const PosAsset* theme_astral_signe_pos(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
        /*
         * Astre position de l'image sans retrograde no lignes
         */
        const PosAstreAsset* theme_astral_astre_pos(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
        const char *asset_sign(int sign);
        const char *text_sign(int sign);
        const char *asset_house(int house, int color_mode);
        const char *asset_bodie(int bodie);
        const char *asset_bodie_r(int bodie);
        const char *text_bodie(int bodie);
        const char *asset_angle(int angle, int color_mode);
        const char *asset_aspect(int aspect);
        const char *text_aspect(int aspect);
        int type_aspect(int aspect);
        const char *grille_aspect_svg(int color_mode);
    class Angle {
        public:
            static string read_svg(int a, int color_mode);
            static const char* read_svg_c(int a, int color_mode);
        };
        class Aspect {
        public:
            static int *angle(int a);
            static string read_svg(int a);
            static const char* read_svg_c(int a);
            static const char* name(int a);
            static const char* name_fr(int a);
            static int type_aspect(int a);
        };
        class Astre {
        public:
            static string read_svg(int astre);
            static const char* read_svg_c(int astre);
            static string read_r_svg(int astre);
            static const char* read_r_svg_c(int astre);
            static const char* name(int a);
            static string *sign_name_and_svg(CalcUt calcul_ut);
        };
        class Draw {
        public:
            static double get_fixed_center(double pos_value);
            static double get_fixed_pos(double pos_value);
            static Offset get_center_item(double size, Offset offset);
            static Offset get_center_item(double width, double height, Offset offset);
            static Offset get_pos_trigo(double angular, double radius_circle);
            static double get_radius_total();
            static Offset *get_line_trigo(double angular, double radius_circle_begin, double radius_circle_end);
            static double get_astre_longitude(H house, CalcUt calcul_ut);
            static double get_item_longitude(H house, double longitude);
            static Offset *get_triangle_trigo(double angular,
                    double angular_pointer,
                    double radius_circle_begin,
                    double radius_circle_end);
            static double get_sign_longitude(H house_asc, CalcUt calcul_ut);
            static double get_angle_longitude(H *house, int angle);
            static double get_z_norm(double angle);
            static double get_closest_distance(double *angle);
        };
        class DrawAspectLines {
        public:
            static LineXYAspect line(H house_asc, double *item_longitude);
        };
        class DrawBodieAstre {
        private:
        public:
            static double astre_size();
            static double astre_r_size();
            static Offset bodie_astre(H house_asc, CalcUt calcul_ut, bool sw_transit);
        };
        class DrawBodieLines {
        public:
            LineXY line(H house_asc, CalcUt calcul_ut, bool sw_transit);
        };
        class DrawHouseAngle {
        public:
            static Size angle_size(int angle);
            static Offset angle(H *house, int angle);
        };
        class DrawHouseLines {
        public:
            LineXY3 *lines(H *house);
            LineXY3 *triangles_small(H *house);
            LineXY angle_lines(H *house, int angle);
        };
        class DrawHouseNumber {
        public:
            static Size number_size(int house_number);
            static Offset number(int house_number, H *house);
        };
        class DrawCircle {
        private:
            CirclePosition get_radius_circle(CirclePositions circle_position);
        public:
            CircleZod circle(CirclePositions circle_position);
        };
        class DrawZodiacLines {
        private:
            double get_radius_rules_inside_circle(larger_draw_line ldl);
        public:
            LineXY *line(H house_asc);
        };
        class DrawZodiacSign {
        public:
            static double zodiac_size();
            static Offset zodiac_sign(int sign, H house_asc);
        };
        class House {
        public:
            static string read_svg(int house, int color_mode);
            static const char* read_svg_c(int house, int color_mode);
            static H init(int object_id, double longitude, int angle);
        };
        class Sign {
        public:
            static string read_svg(int sign);
            static const char *read_svg_c(int sign);
            static string nom(int sign);
        };
        class Swe02 {
        public:
            static void set_ephe_path(string path);
            void close();
            string version();
            string get_library_path();
        };
        class Swe03 {
        public:
            static CalcUt calc_ut(double tjd_ut, int ipl, int iflag);
            static CalcUt calc_ut_part_secondaire(double tjd_ut, int part, int iflag);
            static void display(CalcUt calcul_ut);
        };
        class Swe07 {
        public:
            PhenoUt calc_ut(double tjd_ut, int ipl, int iflag);
        };
        class Swe08 {
        public:
            static UtcToJd utc_to_jd(TimeZone tz, int calandar);
        };
        class Swe14 {
        public:
            static H house(double tjd_ut, double geo_lat, double geo_lng, char hsys, int house);
        };
        class Swe17 {
        public:
            static SplitDeg split_deg(double ddeg, int roundflag);
        };
        class TZ {
        public:
            static TimeZone utc_time_zone(TimeZone time_zone, double timezone);
        };
    }
}
