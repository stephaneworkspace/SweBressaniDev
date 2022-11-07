//
// Created by Stéphane on 04.10.22.
//

#include "include/svglib.h"

using namespace svglib;

Document::Document(double w, double h) {
    width = w;
    height = h;
    content = "";
}

string Document::generate() {
    string s = "<svg viewBox=\"0 0 " + to_string((int) width) + " " + to_string((int) height) + "\" xmlns=\"http://www.w3.org/2000/svg\">" + content + "</svg>";
    return s;
}
