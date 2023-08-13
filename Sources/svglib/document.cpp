//
// Created by Stéphane on 04.10.22.
//

#include "include/svglib.h"

using namespace svglib;

Document::Document(double w, double h) : width(w), height(h), content("") {}

string Document::generate() {
    std::ostringstream oss;
    oss << "<svg viewBox=\"0 0 " << static_cast<int>(width) << " " << static_cast<int>(height)
        << "\" xmlns=\"http://www.w3.org/2000/svg\">" << content << "</svg>";
    return oss.str();
}
