//
// Created by Stéphane on 01.10.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;
extern "C" {
    const char* theme_astral_svg(int year, int month, int day, int hour, int min, double lat, double lng, int gmt, const char* ephem_path, int color_mode) {
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
                svg_fill.fill = "transparent";
                svg_stroke.stroke = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
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
                    svg_stroke.stroke = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                    svg_stroke.stroke_width = 1;
                    Line svg_line(svg_stroke);
                    doc << svg_line.generate(lxy3[i].lx1, lxy3[i].ly1, lxy3[i].lx2, lxy3[i].ly2);
                    // Triangle small
                    svg_fill.fill = "black";
                    svg_stroke.stroke = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
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
                svg_fill.fill = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
                svg_stroke.stroke = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
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
        svg_stroke.stroke = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
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
        svg_stroke.stroke = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
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
        svg_stroke.stroke = color_mode == COLOR_MODE_LIGHT ? "black" : "white";
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
        const int MAX_ITEM = (MAX_ASTRES * 2) + 2;
        double* item_longitude = new double[MAX_ITEM];
        for (int i = 0; i < MAX_ASTRES; ++i) {
            item_longitude[i] = Swe03::calc_ut(utc_to_jd.julian_day_ut, astres[i], OPTION_FLAG_SPEED).longitude;
        }
        for (int i = 1; i < MAX_ASTRES; ++i) {
            //item_longitude[11 + i] = Swe03::calc_ut(utc_to_jd_t.julian_day_ut, astres[i], OptionFlag::speed).longitude;
        }
        item_longitude[(MAX_ASTRES * 2) + 1] = house[0].longitude;
        item_longitude[(MAX_ASTRES * 2) + 2] = house[9].longitude;

        /*
        CalcUt* c_ut = new CalcUt[2];
        const int MAX_PAIR = MAX_ITEM * (11 * 2);
        PairAspect* pair = new PairAspect[MAX_PAIR];
        int k = 0;
        svg_stroke.stroke_width = STROKE_FINE;
        for (int i = 0; i < MAX_ITEM; ++i) {
            for (int j = 0; j < (11 * 2); ++j) {
                bool swl = false;
                for (int l = 0; l < MAX_PAIR; ++l) {
                    if (pair[l].i == j && pair[l].j == i) {
                        swl = true;
                    }
                }
                if (i != j && !swl) {
                    double *c_ut_longitude = new double[2];
                    c_ut_longitude[0] = item_longitude[i];
                    c_ut_longitude[1] = item_longitude[j];
                    LineXYAspect lxya = DrawAspectLines::line(house[0], c_ut_longitude);
                    if (lxya.sw) {
                        switch (lxya.aspect) {
                            case Aspects::conjunction:
                                svg_stroke.stroke = "red";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::opposition:
                                svg_stroke.stroke = "red";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::trine:
                                svg_stroke.stroke = "red";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::square:
                                svg_stroke.stroke = "red";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::sextile:
                                svg_stroke.stroke = "blue";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::inconjunction:
                                svg_stroke.stroke = "green";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::sequisquare:
                                svg_stroke.stroke = "purple";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::semisquare:
                                svg_stroke.stroke = "purple";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                            case Aspects::semisextile:
                                svg_stroke.stroke = "green";
                                svg_line.set_stroke(svg_stroke);
                                doc << svg_line.generate(lxya.lx1, lxya.ly1, lxya.lx2, lxya.ly2);
                                break;
                        }
                        PairAspect p;
                        p.i = i;
                        p.j = j;
                        pair[k] = p;
                        k++;
                    }
                }
            }
        }*/

        static std::string encoded;
        if(!Base64::Encode(doc.generate(), &encoded)) {
            std::cout << "Failed to encode input string" << std::endl;
            //return false;
        } else {

        }
        free(astres);
        return encoded.c_str();
    }
    const char *asset_sign(int sign) {
        return sweinterfacelib::Sign::read_svg_c(sign);
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
}