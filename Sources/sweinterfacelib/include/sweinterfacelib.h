//
// Created by Stéphane on 21.10.22.
//
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "base64.h"
#include "svglib.h"
#include "swelib.h"

using namespace std;
using namespace svglib;
using namespace swelib;

namespace sweinterfacelib {
    // Signs
    enum Signs {
        belier = 1,
        taureau = 2,
        gemaux = 3,
        cancer = 4,
        lion = 5,
        vierge = 6,
        balance = 7,
        scorpion = 8,
        sagittaire = 9,
        capricorne = 10,
        verseau = 11,
        poisson = 12,
    };
    // Swe17
    struct SplitDeg {
        string print;
        int deg;
        int min;
        int sec;
        double cdegfr;
        Signs sign;
        double result;
    };
    enum Angles {
        nothing = 0,
        asc = 1,
        fc = 2,
        desc = 3,
        mc = 4
    };
    enum Aspects {
        conjunction = 0,
        opposition = 1,
        trine = 2,
        square = 3,
        sextile = 4,
        inconjunction = 5,
        sequisquare = 6,
        semisquare = 7,
        semisextile = 8
    };
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
    // les nombres de cet enum sont pour la libraiaire Swe
    enum Astres {
        soleil = 0,
        lune = 1,
        mercure = 2,
        venus = 3,
        mars = 4,
        jupiter = 5,
        saturn = 6,
        uranus = 7,
        neptune = 8,
        pluto = 9,
        noeud_lunaire = 11,
        chiron = 15,
        ceres = 17,
        noeud_lunaire_sud = 24,
    };
    enum Calandar {
        julian = 0,
        gregorian = 1
    };
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
    double const STROKE_FINE = 0.5;
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
        Aspects aspect;
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
        Angles angle;
    };
    // Option flag
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
    extern "C" {
        const char *theme_astral_svg(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path);
        class Angle {
        public:
            static string read_svg(Angles a);
        };
        class Aspect {
        public:
            static int *angle(Aspects a);
        };
        class Astre {
        public:
            static string read_svg(Astres astre);

            static string nom(Astres a);

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

            static double get_angle_longitude(H *house, Angles angle);

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

            static Offset bodie_astre(H house_asc, CalcUt calcul_ut, bool sw_transit);
        };
        class DrawBodieLines {
        public:
            LineXY line(H house_asc, CalcUt calcul_ut, bool sw_transit);
        };
        class DrawHouseAngle {
        public:
            static Size angle_size(Angles angle);

            static Offset angle(H *house, Angles angle);
        };
        class DrawHouseLines {
        public:
            LineXY3 *lines(H *house);

            LineXY angle_lines(H *house, Angles angle);
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

            static Offset zodiac_sign(Signs sign, H house_asc);
        };
        class House {
        public:
            static string read_svg(int house);

            static H init(int object_id, double longitude, Angles angle);
        };
        class Sign {
        public:
            static string read_svg(Signs sign);

            static string nom(Signs sign);
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
            static CalcUt calc_ut(double tjd_ut, Astres ipl, OptionFlag iflag);

            static void display(CalcUt calcul_ut);
        };
        class Swe07 {
        public:
            PhenoUt calc_ut(double tjd_ut, Astres ipl, OptionFlag iflag);
        };
        class Swe08 {
        public:
            static UtcToJd utc_to_jd(TimeZone tz, Calandar calandar);
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