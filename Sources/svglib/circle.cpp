//
// Created by Stéphane on 04.10.22.
//
#include "include/svglib.h"

using namespace svglib;

Circle::Circle(const Fill& fill, const Stroke& stroke) {
    properties.fill.fill_cchar = fill.fill_str.c_str();
    properties.stroke.stroke_cchar = stroke.stroke_str.c_str();
    properties.stroke.stroke_width = stroke.stroke_width;
}

string Circle::generate(double x, double y, double r) {
    std::ostringstream oss;
    oss << "<circle cx=\"" << x
        << "\" cy=\"" << y
        << "\" fill=\"" << properties.fill.fill_cchar
        << "\" r=\"" << r
        << "\" stroke=\"" << properties.stroke.stroke_cchar
        << "\" stroke-width=\"" << static_cast<int>(properties.stroke.stroke_width) << "\"/>";
    return oss.str();
}