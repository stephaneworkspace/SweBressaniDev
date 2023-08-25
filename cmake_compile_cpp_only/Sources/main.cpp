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

int main() {
    char *version = (char *) malloc(255);
    swelib::swe_version(version);
    std::string res = version;
    cout << res << endl;
    free(version);
}
