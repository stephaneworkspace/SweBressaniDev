//
// Created by Stéphane on 04.10.22.
//
#include "include/svglib.h"

using namespace svglib;

string Image::generate(double height, double width, double x, double y, const char* href) {
    string h;
    h.assign(href);
    static string output;
    /*if (!Base64::Decode(h, &output)) {
        std::cout << "Failed to decode input string" << std::endl;
        string s = "<image height=\""+ to_string((int) height) + "\" href=\"" + h + "\" width=\"" + to_string((int) width) + "\" x=\"" + to_string((int) x) + "\" y=\"" + to_string((int) y) + "\"/>";
        return s;
    }*/
    //string s = "<g><svg viewBox=\"0 0 " + to_string((int) width) + " " + to_string((int) height) + "\" height=\"" + to_string(height) + "\" width=\"" + to_string(width) + "\" x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\"></svg></g>";
    string s = "<image height=\"" + to_string(height) + "\" href=\"" + h + "\" width=\"" + to_string(width) + "\" x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\"/>\n";
    //s += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(width) + "\" height=\"" + to_string(height) + "\"/>";
    //s += "<rect x=\"" + to_string(x) + "\" y=\"" + to_string(y) + "\" width=\"" + to_string(1) + "\" height=\""+ to_string(1) + "\"/>";
    return s;
}
