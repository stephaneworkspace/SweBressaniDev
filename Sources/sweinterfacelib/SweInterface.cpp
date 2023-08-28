//
// Created by Stéphane on 01.10.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;
extern "C" {
    const char* theme_astral_svg(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char* ephem_path, int color_mode, const char* aspect_option) {
        // Charger le path des ephem, depuis swift il est a préciser, sinon ça utilise de ce répertoire
        string ephem_path_string;
        if (strcmp(ephem_path, "") == 0) {
            //ephem_path_string = filesystem::current_path().parent_path().parent_path();
            ephem_path_string += "/ephem";
        } else {
            ephem_path_string = ephem_path;
        }
        Swe02::set_ephe_path(ephem_path_string);

        // TimeZone
        TimeZone time_zone;
        time_zone.year = year;
        time_zone.month = month;
        time_zone.day = day;
        time_zone.hour = hour;
        time_zone.min = min;
        time_zone.sec = 0;
        TimeZone utc_time_zone = TZ::utc_time_zone(time_zone, gmt);
        UtcToJd utc_to_jd = Swe08::utc_to_jd(utc_time_zone, CALANDAR_GREGORIAN);
        time_t t = time(0);
        tm* now = localtime(&t);
        TimeZone time_zone_t;
        time_zone_t.year = now->tm_year + 1900;
        time_zone_t.month = now->tm_mon + 1;
        time_zone_t.day = now->tm_mday;
        time_zone_t.hour = now->tm_hour;
        time_zone_t.min = now->tm_min;
        time_zone_t.sec = now->tm_sec;
        double gmt_t = gmt;
        TimeZone utc_time_zone_t = TZ::utc_time_zone(time_zone_t, gmt_t);
        UtcToJd utc_to_jd_t = Swe08::utc_to_jd(utc_time_zone_t, CALANDAR_GREGORIAN);

        H* house = new H[12];
        for (int i = 0; i < 12; ++i) {
            house[i] = Swe14::house(utc_to_jd.julian_day_ut, lat, lng, 'P', i + 1);
        }

        int* astres = new int[MAX_ASTRES];
        astres[SOLEIL] = ASTRE_SOLEIL;
        astres[LUNE] = ASTRE_LUNE;
        astres[MERCURE] = ASTRE_MERCURE;
        astres[VENUS] = ASTRE_VENUS;
        astres[MARS] = ASTRE_MARS;
        astres[JUPITER] = ASTRE_JUPITER;
        astres[SATURN] = ASTRE_SATURN;
        astres[URANUS] = ASTRE_URANUS;
        astres[NEPTUNE] = ASTRE_NEPTUNE;
        astres[PLUTON] = ASTRE_PLUTON;
        astres[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
        astres[CHIRON] = ASTRE_CHIRON;
        astres[CERES] = ASTRE_CERES;
        astres[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;

        Document doc(CHART_SIZE, CHART_SIZE);
        Fill svg_fill;
        Stroke svg_stroke;

        // Draw circles natal
        DrawCircle dz;
        for (int i = 0; i <= 8; ++i) {
            CircleZod cz = dz.circle(static_cast<CirclePositions>(i));
            if (cz.sw) {
                svg_fill.fill_str = "transparent";
                svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                svg_stroke.stroke_width = 1;
                Circle svg_circle(svg_fill, svg_stroke);
                doc << svg_circle.generate(CHART_SIZE / 2, CHART_SIZE / 2, cz.radius * 0.8);
            }
        }

        // Draw house lines
        DrawHouseLines dhl;
        LineXY3* lxy3 = dhl.lines(house);
        LineXY3 *lxy3_ts = dhl.triangles_small(house);
        for (int i = 0; i < 12; ++i) {
            if (!lxy3[i].sw_lxy3) {
                //double stroke; TOTO enlever ?
                if (i == 3 || i == 6 || i == 9) {
                } else {
                    // Line
                    svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                    svg_stroke.stroke_width = 1;
                    Line svg_line(svg_stroke);
                    doc << svg_line.generate(lxy3[i].lx1, lxy3[i].ly1, lxy3[i].lx2, lxy3[i].ly2);
                    // Triangle small
                    svg_fill.fill_str = "black";
                    svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                    svg_stroke.stroke_width = 1;
                    Data svg_data(svg_fill, svg_stroke);
                    svg_data.move_to(lxy3_ts[i].lx3, lxy3_ts[i].ly3);
                    svg_data.line_to(lxy3_ts[i].lx2, lxy3_ts[i].ly2);
                    svg_data.line_to(lxy3_ts[i].lx1, lxy3_ts[i].ly1);
                    svg_data.close_to();
                    doc << svg_data.generate();
                }
            } else {
                // Triangle big (in lines() function)
                svg_fill.fill_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                svg_stroke.stroke_width = 1;
                Data svg_data(svg_fill, svg_stroke);
                svg_data.move_to(lxy3[i].lx3, lxy3[i].ly3);
                svg_data.line_to(lxy3[i].lx2, lxy3[i].ly2);
                svg_data.line_to(lxy3[i].lx1, lxy3[i].ly1);
                svg_data.close_to();
                doc << svg_data.generate();
            }
        }

        // Angle line
        svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
        svg_stroke.stroke_width = STROKE_BOLD;
        Line svg_line(svg_stroke);
        LineXY lxy;

        for (int i = ANGLES_ASC; i < ANGLES_MC + 1; ++i) {
            lxy = dhl.angle_lines(house, i);
            doc << svg_line.generate(lxy.lx1, lxy.ly1, lxy.lx2, lxy.ly2);
        }

        // Draw house number image
        Size house_size;
        for (int i = 1; i < 13; ++i) {
            Offset offset;
            house_size = DrawHouseNumber::number_size(i);
            offset = DrawHouseNumber::number(i, house);
            doc << Image::generate(house_size.width, house_size.height, offset.x, offset.y, House::read_svg(i, color_mode).c_str());
            //doc << Image::generate(7, 7, offset.x, offset.y, House::read_svg(i).c_str());
        }

        // Draw house angle image
        Size angle_size;
        Angle house_angle;
        Offset offset;
        // Asc
        for (int angle = ANGLES_ASC; angle < ANGLES_MC + 1; ++angle) {
            offset = DrawHouseAngle::angle(house, angle);
            angle_size = DrawHouseAngle::angle_size(angle);
            doc << Image::generate(angle_size.width, angle_size.height, offset.x, offset.y, Angle::read_svg(angle, color_mode).c_str());
        }

        // Draw zodiac lines
        svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
        svg_stroke.stroke_width = 1;
        svg_line.set_stroke(svg_stroke);
        DrawZodiacLines dzl;
        LineXY* lz = dzl.line(house[0]);
        for (int i = 0; i < (16 * 12); ++i) {
            doc << svg_line.generate(lz[i].lx1, lz[i].ly1, lz[i].lx2, lz[i].ly2);
        }

        // Draw zodiac image
        Sign sign;
        double zodiac_size;
        for (int i = 1; i < 13; ++i) {
            Offset offset;
            zodiac_size = DrawZodiacSign::zodiac_size();
            offset = DrawZodiacSign::zodiac_sign(i, house[0]);
            doc << Image::generate(zodiac_size, zodiac_size, offset.x, offset.y, Sign::read_svg(i).c_str());
        }

        // Draw astre image + line
        double astre_size = DrawBodieAstre::astre_size();
        double astre_r_size = DrawBodieAstre::astre_r_size();
        svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
        svg_stroke.stroke_width = 1;
        svg_line.set_stroke(svg_stroke);
        DrawBodieLines dbl;
        // LineXY lxy;
        for (int i = 0; i < MAX_ASTRES; ++i) {
            Offset offset;
            // Natal
            CalcUt calcul_ut = Swe03::calc_ut(utc_to_jd.julian_day_ut, astres[i], OPTION_FLAG_SPEED);
            bool sw_retrograde = false;
            if (abs(calcul_ut.speed_longitude) < 0.0003) {
                // Stationary
            } else if (calcul_ut.speed_longitude > 0.0) {
                // Direct
            } else {
                sw_retrograde = true;
            }
            offset = DrawBodieAstre::bodie_astre(house[0], calcul_ut, false);
            lxy = dbl.line(house[0], calcul_ut, false);
            doc << Image::generate(astre_size, astre_size, offset.x, offset.y, Astre::read_svg(astres[i]).c_str());
            if (sw_retrograde) {
                doc << Image::generate(astre_r_size, astre_r_size, offset.x + astre_size / RETROGRADE_DIV, offset.y + astre_size / RETROGRADE_DIV, Astre::read_r_svg(astres[i]).c_str());
            }
            doc << svg_line.generate(lxy.lx1, lxy.ly1, lxy.lx2, lxy.ly2);
            // Transit
            CalcUt calcul_ut_t = Swe03::calc_ut(utc_to_jd_t.julian_day_ut, astres[i], OPTION_FLAG_SPEED);
            sw_retrograde = false;
            if (abs(calcul_ut_t.speed_longitude) < 0.0003) {
                // Stationary
            } else if (calcul_ut_t.speed_longitude > 0.0) {
                // Direct
            } else {
                sw_retrograde = true;
            }
            offset = DrawBodieAstre::bodie_astre(house[0], calcul_ut_t, true);
            lxy = dbl.line(house[0], calcul_ut_t, true);
            doc << Image::generate(astre_size, astre_size, offset.x, offset.y, Astre::read_svg(astres[i]).c_str());
            if (sw_retrograde) {
                doc << Image::generate(astre_r_size, astre_r_size, offset.x + astre_size / RETROGRADE_DIV, offset.y + astre_size / RETROGRADE_DIV, Astre::read_r_svg(astres[i]).c_str());
            }
            doc << svg_line.generate(lxy.lx1, lxy.ly1, lxy.lx2, lxy.ly2);
        }

        // Aspect
        const int MAX_ITEM = NOEUD_LUNAIRE_SUD + 2;
        double* item_longitude = new double[MAX_ITEM];
        for (int i = 0; i <= MAX_ASTRES; ++i) {
            item_longitude[i] = Swe03::calc_ut(utc_to_jd.julian_day_ut, astres[i], OPTION_FLAG_SPEED).longitude;
        }
        item_longitude[NOEUD_LUNAIRE_SUD + 1] = house[0].longitude;
        item_longitude[NOEUD_LUNAIRE_SUD + 2] = house[9].longitude;

        int* astres_aspect = new int[MAX_ASTRES + 2];
        astres_aspect[SOLEIL] = ASTRE_SOLEIL;
        astres_aspect[LUNE] = ASTRE_LUNE;
        astres_aspect[MERCURE] = ASTRE_MERCURE;
        astres_aspect[VENUS] = ASTRE_VENUS;
        astres_aspect[MARS] = ASTRE_MARS;
        astres_aspect[JUPITER] = ASTRE_JUPITER;
        astres_aspect[SATURN] = ASTRE_SATURN;
        astres_aspect[URANUS] = ASTRE_URANUS;
        astres_aspect[NEPTUNE] = ASTRE_NEPTUNE;
        astres_aspect[PLUTON] = ASTRE_PLUTON;
        astres_aspect[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
        astres_aspect[CHIRON] = ASTRE_CHIRON;
        astres_aspect[CERES] = ASTRE_CERES;
        astres_aspect[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;
        astres_aspect[NOEUD_LUNAIRE_SUD + 1] = 98;
        astres_aspect[NOEUD_LUNAIRE_SUD + 2] = 99;

        // aspect_option
        string s;
        s = s.assign(aspect_option);
        auto end = s.cend();
        auto start = end;
        vector<string> v_aspect_option;
        for( auto it = s.cbegin(); it != end; ++it ) {
            if( *it != ',' ) {
                if( start == end )
                    start = it;
                continue;
            }
            if( start != end ) {
                v_aspect_option.emplace_back(start, it);
                start = end;
            }
        }
        if( start != end )
            v_aspect_option.emplace_back(start, end);
        //

        svg_stroke.stroke_width = STROKE_FINE;
        for (int i = 0; i < NOEUD_LUNAIRE_SUD + 2; ++i) { // noeud lunaire sud
            bool sw_aspect_i = false;
            for (auto& l : v_aspect_option) {
                if (stoi(l) == astres_aspect[i]) {
                    sw_aspect_i = true;
                    break;
                }
            }
            for (int j = 0; j < NOEUD_LUNAIRE_SUD + 2; ++j) {
                bool sw_aspect_j = false;
                for (auto& l : v_aspect_option) {
                    if (stoi(l) == astres_aspect[j]) {
                        sw_aspect_j = true;
                        break;
                    }
                }
                if (sw_aspect_i && sw_aspect_j) {
                    if (i != j) {
                        double *c_ut_longitude = new double[2];
                        c_ut_longitude[0] = item_longitude[i];
                        c_ut_longitude[1] = item_longitude[j];
                        LineXYAspect lxya = DrawAspectLines::line(house[0], c_ut_longitude);
                        if (lxya.sw) {
                            switch (lxya.aspect) {
                                case ASPECTS_CONJUNCTION:
                                    svg_stroke.stroke_str = "red";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_OPPOSITION:
                                    svg_stroke.stroke_str = "red";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_TRINE:
                                    svg_stroke.stroke_str = "blue";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_SQUARE:
                                    svg_stroke.stroke_str = "red";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_SEXTILE:
                                    svg_stroke.stroke_str = "blue";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_INCONJUNCTION:
                                    svg_stroke.stroke_str = "green";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_SEQUISQUARE:
                                    svg_stroke.stroke_str = "purple";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_SEMISQUARE:
                                    svg_stroke.stroke_str = "purple";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                                case ASPECTS_SEMISEXTILE:
                                    svg_stroke.stroke_str = "green";
                                    svg_line.set_stroke(svg_stroke);
                                    doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                    break;
                            }
                        }
                        free(c_ut_longitude);
                    }
                }
            }
        }

        static std::string encoded;
        if(!Base64::Encode(doc.generate(), &encoded)) {
            std::cout << "Failed to encode input string" << std::endl;
            //return false;
        } else {

        }
        free(astres);
        free(astres_aspect);
        free(item_longitude);
        return encoded.c_str();
    }
    const char *theme_astral_empty_svg(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path, int color_mode, const char *aspect_option) {
        // Charger le path des ephem, depuis swift il est a préciser, sinon ça utilise de ce répertoire
        string ephem_path_string;
        if (strcmp(ephem_path, "") == 0) {
            //ephem_path_string = filesystem::current_path().parent_path().parent_path();
            ephem_path_string += "/ephem";
        } else {
            ephem_path_string = ephem_path;
        }
        Swe02::set_ephe_path(ephem_path_string);

        // TimeZone
        TimeZone time_zone;
        time_zone.year = year;
        time_zone.month = month;
        time_zone.day = day;
        time_zone.hour = hour;
        time_zone.min = min;
        time_zone.sec = 0;
        TimeZone utc_time_zone = TZ::utc_time_zone(time_zone, gmt);
        UtcToJd utc_to_jd = Swe08::utc_to_jd(utc_time_zone, CALANDAR_GREGORIAN);
        time_t t = time(0);
        tm *now = localtime(&t);
        TimeZone time_zone_t;
        time_zone_t.year = now->tm_year + 1900;
        time_zone_t.month = now->tm_mon + 1;
        time_zone_t.day = now->tm_mday;
        time_zone_t.hour = now->tm_hour;
        time_zone_t.min = now->tm_min;
        time_zone_t.sec = now->tm_sec;
        double gmt_t = gmt;
        TimeZone utc_time_zone_t = TZ::utc_time_zone(time_zone_t, gmt_t);
        UtcToJd utc_to_jd_t = Swe08::utc_to_jd(utc_time_zone_t, CALANDAR_GREGORIAN);

        H *house = new H[12];
        for (int i = 0; i < 12; ++i) {
            house[i] = Swe14::house(utc_to_jd.julian_day_ut, lat, lng, 'P', i + 1);
        }

        int *astres = new int[MAX_ASTRES];
        astres[SOLEIL] = ASTRE_SOLEIL;
        astres[LUNE] = ASTRE_LUNE;
        astres[MERCURE] = ASTRE_MERCURE;
        astres[VENUS] = ASTRE_VENUS;
        astres[MARS] = ASTRE_MARS;
        astres[JUPITER] = ASTRE_JUPITER;
        astres[SATURN] = ASTRE_SATURN;
        astres[URANUS] = ASTRE_URANUS;
        astres[NEPTUNE] = ASTRE_NEPTUNE;
        astres[PLUTON] = ASTRE_PLUTON;
        astres[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
        astres[CHIRON] = ASTRE_CHIRON;
        astres[CERES] = ASTRE_CERES;
        astres[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;

        Document doc(CHART_SIZE, CHART_SIZE);
        Fill svg_fill;
        Stroke svg_stroke;

        // Draw circles natal
        DrawCircle dz;
        for (int i = 0; i <= 8; ++i) {
            CircleZod cz = dz.circle(static_cast<CirclePositions>(i));
            if (cz.sw) {
                svg_fill.fill_str = "transparent";
                svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                svg_stroke.stroke_width = 1;
                Circle svg_circle(svg_fill, svg_stroke);
                doc << svg_circle.generate(CHART_SIZE / 2, CHART_SIZE / 2, cz.radius * 0.8);
            }
        }

        // Draw house lines
        DrawHouseLines dhl;
        LineXY3 *lxy3 = dhl.lines(house);
        LineXY3 *lxy3_ts = dhl.triangles_small(house);
        for (int i = 0; i < 12; ++i) {
            if (!lxy3[i].sw_lxy3) {
                //double stroke; TOTO enlever ?
                if (i == 3 || i == 6 || i == 9) {
                } else {
                    // Line
                    svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                    svg_stroke.stroke_width = 1;
                    Line svg_line(svg_stroke);
                    doc << svg_line.generate(lxy3[i].lx1, lxy3[i].ly1, lxy3[i].lx2, lxy3[i].ly2);
                    // Triangle small
                    svg_fill.fill_str = "black";
                    svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                    svg_stroke.stroke_width = 1;
                    Data svg_data(svg_fill, svg_stroke);
                    svg_data.move_to(lxy3_ts[i].lx3, lxy3_ts[i].ly3);
                    svg_data.line_to(lxy3_ts[i].lx2, lxy3_ts[i].ly2);
                    svg_data.line_to(lxy3_ts[i].lx1, lxy3_ts[i].ly1);
                    svg_data.close_to();
                    doc << svg_data.generate();
                }
            } else {
                // Triangle big (in lines() function)
                svg_fill.fill_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                svg_stroke.stroke_width = 1;
                Data svg_data(svg_fill, svg_stroke);
                svg_data.move_to(lxy3[i].lx3, lxy3[i].ly3);
                svg_data.line_to(lxy3[i].lx2, lxy3[i].ly2);
                svg_data.line_to(lxy3[i].lx1, lxy3[i].ly1);
                svg_data.close_to();
                doc << svg_data.generate();
            }
        }

        // Angle line
        svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
        svg_stroke.stroke_width = STROKE_BOLD;
        Line svg_line(svg_stroke);
        LineXY lxy;

        for (int i = ANGLES_ASC; i < ANGLES_MC + 1; ++i) {
            lxy = dhl.angle_lines(house, i);
            doc << svg_line.generate(lxy.lx1, lxy.ly1, lxy.lx2, lxy.ly2);
        }

        // Draw house angle image
        Size angle_size;
        Angle house_angle;
        Offset offset;
        // Asc
        for (int angle = ANGLES_ASC; angle < ANGLES_MC + 1; ++angle) {
            offset = DrawHouseAngle::angle(house, angle);
            angle_size = DrawHouseAngle::angle_size(angle);
            doc << Image::generate(
                    angle_size.width,
                    angle_size.height,
                    offset.x,
                    offset.y,
                    Angle::read_svg(angle, color_mode).c_str());
        }

        // Draw zodiac lines
        svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
        svg_stroke.stroke_width = 1;
        svg_line.set_stroke(svg_stroke);
        DrawZodiacLines dzl;
        LineXY *lz = dzl.line(house[0]);
        for (int i = 0; i < (16 * 12); ++i) {
            doc << svg_line.generate(lz[i].lx1, lz[i].ly1, lz[i].lx2, lz[i].ly2);
        }

        static std::string encoded;
        if (!Base64::Encode(doc.generate(), &encoded)) {
            std::cout << "Failed to encode input string" << std::endl;
            //return false;
        } else {

        }
        free(astres);
        return encoded.c_str();
    }
    const PosAsset *theme_astral_maison_pos(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path) {
        // Charger le path des ephem, depuis swift il est a préciser, sinon ça utilise de ce répertoire
        string ephem_path_string;
        if (strcmp(ephem_path, "") == 0) {
            //ephem_path_string = filesystem::current_path().parent_path().parent_path();
            ephem_path_string += "/ephem";
        } else {
            ephem_path_string = ephem_path;
        }
        Swe02::set_ephe_path(ephem_path_string);

        // TimeZone
        TimeZone time_zone;
        time_zone.year = year;
        time_zone.month = month;
        time_zone.day = day;
        time_zone.hour = hour;
        time_zone.min = min;
        time_zone.sec = 0;
        TimeZone utc_time_zone = TZ::utc_time_zone(time_zone, gmt);
        UtcToJd utc_to_jd = Swe08::utc_to_jd(utc_time_zone, CALANDAR_GREGORIAN);
        time_t t = time(0);
        tm *now = localtime(&t);
        TimeZone time_zone_t;
        time_zone_t.year = now->tm_year + 1900;
        time_zone_t.month = now->tm_mon + 1;
        time_zone_t.day = now->tm_mday;
        time_zone_t.hour = now->tm_hour;
        time_zone_t.min = now->tm_min;
        time_zone_t.sec = now->tm_sec;
        double gmt_t = gmt;
        TimeZone utc_time_zone_t = TZ::utc_time_zone(time_zone_t, gmt_t);
        UtcToJd utc_to_jd_t = Swe08::utc_to_jd(utc_time_zone_t, CALANDAR_GREGORIAN);

        H *house = new H[12];
        for (int i = 0; i < 12; ++i) {
            house[i] = Swe14::house(utc_to_jd.julian_day_ut, lat, lng, 'P', i + 1);
        }

        int *astres = new int[MAX_ASTRES];
        astres[SOLEIL] = ASTRE_SOLEIL;
        astres[LUNE] = ASTRE_LUNE;
        astres[MERCURE] = ASTRE_MERCURE;
        astres[VENUS] = ASTRE_VENUS;
        astres[MARS] = ASTRE_MARS;
        astres[JUPITER] = ASTRE_JUPITER;
        astres[SATURN] = ASTRE_SATURN;
        astres[URANUS] = ASTRE_URANUS;
        astres[NEPTUNE] = ASTRE_NEPTUNE;
        astres[PLUTON] = ASTRE_PLUTON;
        astres[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
        astres[CHIRON] = ASTRE_CHIRON;
        astres[CERES] = ASTRE_CERES;
        astres[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;

        Document doc(CHART_SIZE, CHART_SIZE);
        Fill svg_fill;
        Stroke svg_stroke;

        PosAsset *pos_asset = new PosAsset[13];

        // Draw house number image
        Size house_size;
        for (int i = 1; i < 13; ++i) {
            Offset offset;
            house_size = DrawHouseNumber::number_size(i);
            offset = DrawHouseNumber::number(i, house);
            pos_asset[i].width = house_size.width;
            pos_asset[i].height = house_size.height;
            pos_asset[i].x = offset.x;
            pos_asset[i].y = offset.y;
        }

        free(astres);
        return pos_asset;
    }
    const PosAsset* theme_astral_signe_pos(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path) {
        // Charger le path des ephem, depuis swift il est a préciser, sinon ça utilise de ce répertoire
        string ephem_path_string;
        if (strcmp(ephem_path, "") == 0) {
            //ephem_path_string = filesystem::current_path().parent_path().parent_path();
            ephem_path_string += "/ephem";
        } else {
            ephem_path_string = ephem_path;
        }
        Swe02::set_ephe_path(ephem_path_string);

        // TimeZone
        TimeZone time_zone;
        time_zone.year = year;
        time_zone.month = month;
        time_zone.day = day;
        time_zone.hour = hour;
        time_zone.min = min;
        time_zone.sec = 0;
        TimeZone utc_time_zone = TZ::utc_time_zone(time_zone, gmt);
        UtcToJd utc_to_jd = Swe08::utc_to_jd(utc_time_zone, CALANDAR_GREGORIAN);
        time_t t = time(0);
        tm *now = localtime(&t);
        TimeZone time_zone_t;
        time_zone_t.year = now->tm_year + 1900;
        time_zone_t.month = now->tm_mon + 1;
        time_zone_t.day = now->tm_mday;
        time_zone_t.hour = now->tm_hour;
        time_zone_t.min = now->tm_min;
        time_zone_t.sec = now->tm_sec;
        double gmt_t = gmt;
        TimeZone utc_time_zone_t = TZ::utc_time_zone(time_zone_t, gmt_t);
        UtcToJd utc_to_jd_t = Swe08::utc_to_jd(utc_time_zone_t, CALANDAR_GREGORIAN);

        H *house = new H[12];
        for (int i = 0; i < 12; ++i) {
            house[i] = Swe14::house(utc_to_jd.julian_day_ut, lat, lng, 'P', i + 1);
        }

        int *astres = new int[MAX_ASTRES];
        astres[SOLEIL] = ASTRE_SOLEIL;
        astres[LUNE] = ASTRE_LUNE;
        astres[MERCURE] = ASTRE_MERCURE;
        astres[VENUS] = ASTRE_VENUS;
        astres[MARS] = ASTRE_MARS;
        astres[JUPITER] = ASTRE_JUPITER;
        astres[SATURN] = ASTRE_SATURN;
        astres[URANUS] = ASTRE_URANUS;
        astres[NEPTUNE] = ASTRE_NEPTUNE;
        astres[PLUTON] = ASTRE_PLUTON;
        astres[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
        astres[CHIRON] = ASTRE_CHIRON;
        astres[CERES] = ASTRE_CERES;
        astres[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;

        Document doc(CHART_SIZE, CHART_SIZE);
        Fill svg_fill;
        Stroke svg_stroke;

        PosAsset *pos_asset = new PosAsset[13];
        double zodiac_size;
        for (int i = 1; i < 13; ++i) {
            Offset offset;
            zodiac_size = DrawZodiacSign::zodiac_size();
            offset = DrawZodiacSign::zodiac_sign(i, house[0]);
            pos_asset[i].width = zodiac_size;
            pos_asset[i].height = zodiac_size;
            pos_asset[i].x = offset.x;
            pos_asset[i].y = offset.y;
        }

        free(astres);
        return pos_asset;
    }
    const PosAstreAsset* theme_astral_astre_pos(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char *ephem_path, const char *aspect_option) {
        // Charger le path des ephem, depuis swift il est a préciser, sinon ça utilise de ce répertoire
        string ephem_path_string;
        if (strcmp(ephem_path, "") == 0) {
            //ephem_path_string = filesystem::current_path().parent_path().parent_path();
            ephem_path_string += "/ephem";
        } else {
            ephem_path_string = ephem_path;
        }
        Swe02::set_ephe_path(ephem_path_string);

        // TimeZone
        TimeZone time_zone;
        time_zone.year = year;
        time_zone.month = month;
        time_zone.day = day;
        time_zone.hour = hour;
        time_zone.min = min;
        time_zone.sec = 0;
        TimeZone utc_time_zone = TZ::utc_time_zone(time_zone, gmt);
        UtcToJd utc_to_jd = Swe08::utc_to_jd(utc_time_zone, CALANDAR_GREGORIAN);
        time_t t = time(0);
        tm *now = localtime(&t);
        TimeZone time_zone_t;
        time_zone_t.year = now->tm_year + 1900;
        time_zone_t.month = now->tm_mon + 1;
        time_zone_t.day = now->tm_mday;
        time_zone_t.hour = now->tm_hour;
        time_zone_t.min = now->tm_min;
        time_zone_t.sec = now->tm_sec;
        double gmt_t = gmt;
        TimeZone utc_time_zone_t = TZ::utc_time_zone(time_zone_t, gmt_t);
        UtcToJd utc_to_jd_t = Swe08::utc_to_jd(utc_time_zone_t, CALANDAR_GREGORIAN);

        H *house = new H[12];
        for (int i = 0; i < 12; ++i) {
            house[i] = Swe14::house(utc_to_jd.julian_day_ut, lat, lng, 'P', i + 1);
        }

        // aspect_option
        string s;
        s = s.assign(aspect_option);
        auto end = s.cend();
        auto start = end;
        vector<string> v_aspect_option;
        for (auto it = s.cbegin(); it != end; ++it) {
            if (*it != ',') {
                if (start == end)
                    start = it;
                continue;
            }
            if (start != end) {
                v_aspect_option.emplace_back(start, it);
                start = end;
            }
        }
        if (start != end)
            v_aspect_option.emplace_back(start, end);
        //



        int *astres = new int[MAX_ASTRES];
        astres[SOLEIL] = ASTRE_SOLEIL;
        astres[LUNE] = ASTRE_LUNE;
        astres[MERCURE] = ASTRE_MERCURE;
        astres[VENUS] = ASTRE_VENUS;
        astres[MARS] = ASTRE_MARS;
        astres[JUPITER] = ASTRE_JUPITER;
        astres[SATURN] = ASTRE_SATURN;
        astres[URANUS] = ASTRE_URANUS;
        astres[NEPTUNE] = ASTRE_NEPTUNE;
        astres[PLUTON] = ASTRE_PLUTON;
        astres[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
        astres[CHIRON] = ASTRE_CHIRON;
        astres[CERES] = ASTRE_CERES;
        astres[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;

        int* astres_aspect = new int[MAX_ASTRES + 2];
        astres_aspect[SOLEIL] = ASTRE_SOLEIL;
        astres_aspect[LUNE] = ASTRE_LUNE;
        astres_aspect[MERCURE] = ASTRE_MERCURE;
        astres_aspect[VENUS] = ASTRE_VENUS;
        astres_aspect[MARS] = ASTRE_MARS;
        astres_aspect[JUPITER] = ASTRE_JUPITER;
        astres_aspect[SATURN] = ASTRE_SATURN;
        astres_aspect[URANUS] = ASTRE_URANUS;
        astres_aspect[NEPTUNE] = ASTRE_NEPTUNE;
        astres_aspect[PLUTON] = ASTRE_PLUTON;
        astres_aspect[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
        astres_aspect[CHIRON] = ASTRE_CHIRON;
        astres_aspect[CERES] = ASTRE_CERES;
        astres_aspect[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;
        astres_aspect[NOEUD_LUNAIRE_SUD + 1] = 98;
        astres_aspect[NOEUD_LUNAIRE_SUD + 2] = 99;

        Document doc(CHART_SIZE, CHART_SIZE);
        Fill svg_fill;
        Stroke svg_stroke;

        PosAstreAsset* paa = new PosAstreAsset[MAX_ASTRES];

        // Draw astre image + line
        double astre_size = DrawBodieAstre::astre_size();
        double astre_r_size = DrawBodieAstre::astre_r_size();
        //svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
        //svg_stroke.stroke_width = 1;
        //svg_line.set_stroke(svg_stroke);
        DrawBodieLines dbl;
        LineXY lxy;
        for (int i = 0; i < MAX_ASTRES; ++i) {
            Offset offset;
            // Natal
            CalcUt calcul_ut = Swe03::calc_ut(utc_to_jd.julian_day_ut, astres[i], OPTION_FLAG_SPEED);
            bool sw_retrograde = false;
            if (abs(calcul_ut.speed_longitude) < 0.0003) {
                // Stationary
            } else if (calcul_ut.speed_longitude > 0.0) {
                // Direct
            } else {
                sw_retrograde = true;
            }
            offset = DrawBodieAstre::bodie_astre(house[0], calcul_ut, false);
            lxy = dbl.line(house[0], calcul_ut, false);
            bool sw_aspect_i = false;
            for (auto& l : v_aspect_option) {
                if (stoi(l) == astres_aspect[i]) {
                    sw_aspect_i = true;
                    break;
                }
            }
            if (sw_aspect_i) {
                paa[i].nom = text_bodie(i);
            } else {
                paa[i].nom = "NULL";
            }

            paa[i].retrograde = sw_retrograde;
            paa[i].astre.width = astre_size;
            paa[i].astre.height = astre_size;
            paa[i].astre.x = offset.x;
            paa[i].astre.y = offset.y;
            if (sw_retrograde) {
                paa[i].astre_r.width = astre_r_size;
                paa[i].astre_r.height = astre_r_size;
                paa[i].astre_r.x = offset.x;
                paa[i].astre_r.y = offset.y;
            } else {
                paa[i].astre_r.width = 0;
                paa[i].astre_r.height = 0;
                paa[i].astre_r.x = 0;
                paa[i].astre_r.y = 0;
            }
            //doc << svg_line.generate(lxy.lx1, lxy.ly1, lxy.lx2, lxy.ly2);
            paa[i].line.lx1 = lxy.lx1;
            paa[i].line.ly1 = lxy.ly1;
            paa[i].line.lx2 = lxy.lx2;
            paa[i].line.ly2 = lxy.ly2;

            /*// Transit
            CalcUt calcul_ut_t = Swe03::calc_ut(utc_to_jd_t.julian_day_ut, astres[i], OPTION_FLAG_SPEED);
            sw_retrograde = false;
            if (abs(calcul_ut_t.speed_longitude) < 0.0003) {
                // Stationary
            } else if (calcul_ut_t.speed_longitude > 0.0) {
                // Direct
            } else {
                sw_retrograde = true;
            }
            offset = DrawBodieAstre::bodie_astre(house[0], calcul_ut_t, true);
            lxy = dbl.line(house[0], calcul_ut_t, true);
            doc << Image::generate(astre_size, astre_size, offset.x, offset.y, Astre::read_svg(astres[i]).c_str());
            if (sw_retrograde) {
                doc
                        << Image::generate(astre_r_size, astre_r_size, offset.x + astre_size / RETROGRADE_DIV, offset.y + astre_size / RETROGRADE_DIV, Astre::read_r_svg(astres[i]).c_str());
            }
            doc << svg_line.generate(lxy.lx1, lxy.ly1, lxy.lx2, lxy.ly2);
             */
        }

        free(astres);
        return paa;
    }
    const char *asset_sign(int sign) {
        return sweinterfacelib::Sign::read_svg_c(sign);
    }
    const char *text_sign(int sign) {
        string n = sweinterfacelib::Sign::nom(sign);
        const char* nn = n.c_str();
        return nn;
    }
    const char *asset_house(int house, int color_mode) {
        return sweinterfacelib::House::read_svg_c(house, color_mode);
    }
    const char *asset_bodie(int bodie) {
        return sweinterfacelib::Astre::read_svg_c(bodie);
    }
    const char *asset_bodie_r(int bodie) {
        return sweinterfacelib::Astre::read_r_svg_c(bodie);
    }
    const char *asset_angle(int angle, int color_mode) {
        return sweinterfacelib::Angle::read_svg_c(angle, color_mode);
    }
    const char *text_bodie(int bodie) {
        return sweinterfacelib::Astre::name(bodie);
    }
    const char *asset_aspect(int aspect) {
        return sweinterfacelib::Aspect::read_svg_c(aspect);
    }
    const char *text_aspect(int aspect) {
        return sweinterfacelib::Aspect::name_fr(aspect);
    }
    int type_aspect(int aspect) {
        return sweinterfacelib::Aspect::type_aspect(aspect);
    }
    const char *grille_aspect_svg(int color_mode) {
        const int GRILLE_SIZE = 25; // px
        const int GRILLE_LINES = 16;
        const int GRILLE_COLS = 15;
        const int GRILLE_LINES_SIZE = GRILLE_LINES * GRILLE_SIZE;
        const int GRILLE_COLS_SIZE = GRILLE_COLS * GRILLE_SIZE;

        Document doc(GRILLE_COLS_SIZE + 1, GRILLE_LINES_SIZE + 1);
        Stroke svg_stroke;
        svg_stroke.stroke_str = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
        svg_stroke.stroke_width = 1;
        Line svg_line(svg_stroke);
        // Bordures Horizontales

        // Ligne 1
        // vide
        // Ligne 2 à 15
        for (int i = 1; i < GRILLE_LINES - 1; i++) {
            int calc = i * GRILLE_SIZE;
            doc << svg_line.generate(0 + 1, calc, calc ,calc); // 0 + 1 pour commencer à 1
        }
        // Ligne 16
        int calc1 = (GRILLE_LINES - 1) * GRILLE_SIZE;
        int calc2 = (GRILLE_LINES - 2) * GRILLE_SIZE;
        doc << svg_line.generate(0, calc1, calc2 ,calc1);
        // Ligne 17
        calc1 = (GRILLE_LINES) * GRILLE_SIZE;
        calc2 = (GRILLE_LINES - 2) * GRILLE_SIZE;
        doc << svg_line.generate(0, calc1, calc2 ,calc1);

        // Bordures Verticales
        // Col 1 à 15
        for (int i = 0; i < GRILLE_COLS; i++) {
            calc1 = i * GRILLE_SIZE;
            calc2 = (i + 1) * GRILLE_SIZE;
            calc2 = i == 0 ? calc2 : calc2 - GRILLE_SIZE;
            doc << svg_line.generate(i == 0 ? 1 : calc1, calc2, i == 0 ? 1 : calc1, GRILLE_LINES_SIZE); // i == 0 ? 1 -> pour commencer à 1
        }

        static std::string encoded;
        if(!Base64::Encode(doc.generate(), &encoded)) {
            std::cout << "Failed to encode input string" << std::endl;
            //return false;
        } else {

        }
        return encoded.c_str();
    }
}
