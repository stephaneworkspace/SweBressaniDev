//
// Created by Stéphane on 04.10.22.
//
#include "include/svglib.h"

using namespace svglib;

Line::Line(Stroke s) {
    stroke.stroke = s.stroke.c_str();
    stroke.stroke_width = s.stroke_width;
}

void Line::set_stroke(Stroke s) {
    stroke.stroke = s.stroke.c_str();
    stroke.stroke_width = s.stroke_width;
}

string Line::generate(float x1, float y1, float x2, float y2) {
    string stro;
    stro.assign(stroke.stroke);
    string s = "<line stroke=\""+ stro + "\" stroke-width=\"" + to_string((int) stroke.stroke_width) + "\" x1=\"" + to_string(x1) + "\" x2=\"" + to_string(x2) + "\" y1=\"" + to_string(y1) +"\" y2=\"" + to_string(y2) +"\"/>";
    return s;
}