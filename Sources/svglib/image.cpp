//
// Created by Stéphane on 04.10.22.
//
#include "include/svglib.h"

using namespace svglib;

string Image::generate(double height, double width, double x, double y, const char* href) {
    std::ostringstream oss;
    oss << "<image height=\"" << height
        << "\" href=\"" << href
        << "\" width=\"" << width
        << "\" x=\"" << x
        << "\" y=\"" << y << "\"/>\n";
    return oss.str();
}
