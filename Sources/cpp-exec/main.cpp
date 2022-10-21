//
// Created by Stéphane on 21.10.22.
//

#include <iostream>
#include "cpplib.h"
//#include "swelib.h"
//#include "svglib.h"
#include "sweinterfacelib.h"

using namespace std;
using namespace svglib;

int main() {
    std::cout << cpplib::five() << std::endl;
    /*
    char *version = (char *) malloc(255);
    swelib::swe_version(version);
    std::string res = version;
    std::cout << res << std::endl;
    //free(version);

    // Document
    Document doc = Document(50, 50);
    // Data
    Fill fill;
    fill.fill = "none";
    Stroke stroke;
    stroke.stroke = "black";
    stroke.stroke_width = 3;
    Data data = Data(fill, stroke);
    data.move_to(10.0, 10.0);
    data.line_by(0.50, 50.0);
    data.line_by(50, 0);
    data.line_by(0, -50);
    data.close_by();
    doc << data.generate();
    // Circle
    Circle circle = Circle(fill, stroke);
    doc << circle.generate(10, 20, 30);
    // Circle
    Line line = Line(stroke);
    doc << line.generate(10, 20, 30, 40);
    // Image
    doc << Image::generate(10, 20, 30, 40, "data:image/svg+xml;base64,");
    // Document
    cout << doc.generate() << endl;

    cout << sweinterfacelib::theme_astral_svg(1984, 1, 4, 0, 0, 16, 26, 2, version) << endl;
    free(version);*/
    return 0;
}