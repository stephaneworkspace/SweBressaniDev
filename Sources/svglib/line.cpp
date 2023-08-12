//
// Created by Stéphane on 04.10.22.
//
#include "include/svglib.h"

using namespace svglib;

Line::Line(const Stroke& s) {
    configureStroke(s);
}

void Line::set_stroke(const Stroke& s) {
    configureStroke(s);
}

string Line::generate(double x1, double y1, double x2, double y2) {
    std::ostringstream oss;
    oss << "<line stroke=\"" << stroke.stroke_cchar
        << "\" stroke-width=\"" << stroke.stroke_width
        << "\" x1=\"" << x1
        << "\" x2=\"" << x2
        << "\" y1=\"" << y1
        << "\" y2=\"" << y2 << "\" />\n";
    return oss.str();
}

void Line::configureStroke(const Stroke& s) {
    stroke.stroke_cchar = s.stroke_str.c_str();
    stroke.stroke_width = s.stroke_width;
}