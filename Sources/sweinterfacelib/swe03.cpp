//
// Created by Stéphane on 22.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

CalcUt Swe03::calc_ut(double tjd_ut, int ipl, int iflag) {
    double* xx_ptr = new double[6];
    char* serr_ptr = new char[255];
    int status;
    if (ipl == ASTRE_NOEUD_LUNAIRE || ipl == ASTRE_NOEUD_LUNAIRE_SUD) {
        status = swe_calc_ut(tjd_ut, ASTRE_NOEUD_LUNAIRE, iflag, xx_ptr, serr_ptr);
    } else {
        status = swe_calc_ut(tjd_ut, ipl, iflag, xx_ptr, serr_ptr);
    }
    if (ipl == ASTRE_NOEUD_LUNAIRE_SUD) {
        xx_ptr[0] += 180;
        if (xx_ptr[0] >= 360) {
            xx_ptr[0] -= 360;
        }
    }
    Swe17 swe17;
    SplitDeg splitdeg = swe17.split_deg(xx_ptr[0], 0);
    CalcUt res;
    res.longitude = xx_ptr[0];
    res.latitude = xx_ptr[1];
    res.distance_au = xx_ptr[2];
    res.speed_longitude = xx_ptr[3];
    res.speed_latitude = xx_ptr[4];
    res.speed_distance_au = xx_ptr[5];
    res.status = status;
    res.serr = serr_ptr;
    res.split = splitdeg;
    free(xx_ptr);
    free(serr_ptr);
    return res;
}

CalcUt Swe03::calc_ut_part_secondaire(double tjd_ut, int part, int iflag) {
    double* xx_ptr = new double[6];
    char* serr_ptr = new char[255];
    int ipl = ASTRE_SOLEIL;
    int status = swe_calc_ut(tjd_ut, ipl, iflag, xx_ptr, serr_ptr);
    double* xx_ptr_2 = new double[6];
    char* serr_ptr_2 = new char[255];
    ipl = ASTRE_LUNE;
    status = swe_calc_ut(tjd_ut, ipl, iflag, xx_ptr, serr_ptr);
    int longitude = xx_ptr[0] - xx_ptr[1];
    if (longitude >= 360) {
        longitude -= 360;
    }
    longitude = longitude + (30 * part);
    if (longitude >= 360) {
        longitude -= 360;
    }
    Swe17 swe17;
    SplitDeg splitdeg = swe17.split_deg(longitude, 0);
    CalcUt res;
    res.longitude = longitude;
    //res.latitude = xx_ptr[1];
    //res.distance_au = xx_ptr[2];
    //res.speed_longitude = xx_ptr[3];
    //res.speed_latitude = xx_ptr[4];
    //res.speed_distance_au = xx_ptr[5];
    //res.status = status;
    //res.serr = serr_ptr;
    res.split = splitdeg;
    free(xx_ptr);
    free(serr_ptr);
    free(xx_ptr_2);
    free(serr_ptr_2);
    return res;
}

void Swe03::display(CalcUt calcul_ut) {
    cout << "struct CalcUt {" << endl;
    cout << "longitude "              << calcul_ut.longitude << endl;
    cout << "latitude "               << calcul_ut.latitude << endl;
    cout << "distance_au "            << calcul_ut.distance_au << endl;
    cout << "speed_longgitude "       << calcul_ut.speed_longitude << endl;
    cout << "speed_latitude "         << calcul_ut.speed_latitude << endl;
    cout << "speed_distance_au "      << calcul_ut.speed_distance_au << endl;
    cout << "status "                 << calcul_ut.status << endl;
    cout << "serr "                   << calcul_ut.serr << endl;
    cout << "split struct SplitDeg {" << endl;
    cout << "   print "               << calcul_ut.split.print << endl;
    cout << "   deg "                 << calcul_ut.split.deg << endl;
    cout << "   min "                 << calcul_ut.split.min << endl;
    cout << "   sec "                 << calcul_ut.split.sec << endl;
    cout << "   cdegfr "              << calcul_ut.split.cdegfr << endl;
    cout << "   sign "                << calcul_ut.split.sign << endl;
    cout << "   result "              << calcul_ut.split.result << endl;
    cout << "   }"                    << endl;
    cout << "}"                       << endl;
}
