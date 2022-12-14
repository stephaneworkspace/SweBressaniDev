//
// Created by Stéphane on 25.09.22.
//
#include "include/sweinterfacelib.h"

using namespace sweinterfacelib;

Size DrawHouseAngle::angle_size(int angle) {
    Size size;
    const double ANGLE_SIZE = 63;
    const double ANGLE_RATIO = 10;
    double width = 0;
    double height = 0;
    switch (angle) {
        case ANGLES_ASC:
            width = 44 * 6.8;
            height = 44 * 6.8 ;
            //width = 65 * 5.5;
            //height = 44 * 5.5;
            break;
        case ANGLES_FC:
            width = 37 * 5.8;
            height = 44 * 5.8;
            break;
        case ANGLES_DESC:
            width = 44 * 6.8 * 1.3;
            height = 44 * 6.8 * 1.3;
            //width = 87 * 5.5;
            //height = 44 * 5.5;
            break;
        case ANGLES_MC:
            width = 53 * 5.8;
            height = 44 * 5.8;
            break;
        default:
            width = ANGLE_SIZE * ANGLE_RATIO;
            height = ANGLE_SIZE * ANGLE_RATIO;
            break;
    }
    size.width = ((width / 100) * CHART_SIZE) / 100;
    size.height = ((height / 100) * CHART_SIZE) / 100;
    return size;
}

Offset DrawHouseAngle::angle(H* house, int angle) {
    double pos = Draw::get_angle_longitude(house, angle);
    Offset trigo = Draw::get_pos_trigo(pos, (Draw::get_radius_total() * 95) / 100);

    Offset res;
    Size as = DrawHouseAngle::angle_size(angle);
    res = Draw::get_center_item(as.width, as.height, trigo);
    return res;
}