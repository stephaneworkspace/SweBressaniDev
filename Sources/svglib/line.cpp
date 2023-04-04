//
// Created by Stéphane on 04.10.22.
//
#include "include/svglib.h"

using namespace svglib;

Line::Line(Stroke s) {
    stroke.stroke_cchar = s.stroke_str.c_str();
    stroke.stroke_width = s.stroke_width;
}

void Line::set_stroke(Stroke s) {
    stroke.stroke_cchar = s.stroke_str.c_str();
    stroke.stroke_width = s.stroke_width;
}

string Line::generate(double x1, double y1, double x2, double y2) {
    string stro;
    stro.assign(stroke.stroke_cchar);
    string s = "<line stroke=\""+ stro + "\" stroke-width=\"" + to_string((int) stroke.stroke_width) + "\" x1=\"" + to_string(x1) + "\" x2=\"" + to_string(x2) + "\" y1=\"" + to_string(y1) +"\" y2=\"" + to_string(y2) +"\" />\n";
    return s;
}