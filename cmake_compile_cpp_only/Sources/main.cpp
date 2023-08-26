//
// Created by Stéphane on 25.08.23.
//
#include "swelib.h"
#include "svglib.h"
#include "sweinterfacelib.h"
#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;
using namespace svglib;
using namespace sweinterfacelib;

int main() {
    // Version
    char *version = (char *) malloc(255);
    swelib::swe_version(version);
    std::string res = version;
    cout << "Swissephem: " << res << endl;
    free(version);
    // Maison TODO const MaisonOutput* ?
    const MaisonOutput* mo = theme_astral_maison_pos(1984, 4, 1, 0, 0, 16, 2, 2,"",0,"0");
    cout << mo[0].x << endl;
}
