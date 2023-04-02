//
// Created by Stéphane on 31.03.23.
//
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "swelib.h"
#include "sweinterfacelib.h"
#include <nlohmann/json.hpp>
using json = nlohmann::json;

using namespace std;
using namespace sweinterfacelib;

std::vector<std::string> tokenize(const std::string& s, char c) {
    auto end = s.cend();
    auto start = end;

    std::vector<std::string> v;
    for( auto it = s.cbegin(); it != end; ++it ) {
        if( *it != c ) {
            if( start == end )
                start = it;
            continue;
        }
        if( start != end ) {
            v.emplace_back(start, it);
            start = end;
        }
    }
    if( start != end )
        v.emplace_back(start, end);
    return v;
}

const string ENV[ 24 ] = {
        "COMSPEC", "DOCUMENT_ROOT", "GATEWAY_INTERFACE",
        "HTTP_ACCEPT", "HTTP_ACCEPT_ENCODING",
        "HTTP_ACCEPT_LANGUAGE", "HTTP_CONNECTION",
        "HTTP_HOST", "HTTP_USER_AGENT", "PATH",
        "QUERY_STRING", "REMOTE_ADDR", "REMOTE_PORT",
        "REQUEST_METHOD", "REQUEST_URI", "SCRIPT_FILENAME",
        "SCRIPT_NAME", "SERVER_ADDR", "SERVER_ADMIN",
        "SERVER_NAME","SERVER_PORT","SERVER_PROTOCOL",
        "SERVER_SIGNATURE","SERVER_SOFTWARE" };

int main () {
    bool sw_find = false;
    bool sw_chart = false;
    bool sw_json = false;
    bool sw_debug = false;
    int year = 1984;
    int month = 4;
    int day = 1;
    int hour = 0;
    int min = 0;
    float lat = 46.12;
    float lng = 6.09;
    int gmt = 2;
    int color = 0;
    vector<string> param = tokenize(getenv(ENV[10].c_str()), '&');
    for (int i = 0; i < param.size(); ++i) {
        vector<string> param_split = tokenize(param[i], '=');
        if (param_split[0] == "sw_chart" && param_split[1] == "true") {
            sw_chart = true;
            sw_find = true;
        }
        if (param_split[0] == "sw_json" && param_split[1] == "true") {
            sw_find = true;
            sw_json = true;
        }
        if (param_split[0] == "sw_debug" && param_split[1] == "true") {
            sw_find = true;
            sw_debug = true;
        }
        if (param_split[0] == "year") {
            year = stoi(param_split[1]);
        }
        if (param_split[0] == "month") {
            month = stoi(param_split[1]);
        }
        if (param_split[0] == "day") {
            day = stoi(param_split[1]);
        }
        if (param_split[0] == "hour") {
            hour = stoi(param_split[1]);
        }
        if (param_split[0] == "min") {
            min = stoi(param_split[1]);
        }
        if (param_split[0] == "lat") {
            lat = stof(param_split[1]);
        }
        if (param_split[0] == "lng") {
            lng = stof(param_split[1]);
        }
        if (param_split[0] == "gmt") {
            gmt = stoi(param_split[1]);
        }
        if (param_split[0] == "color") {
            color = stoi(param_split[1]);
        }
    }
    if (sw_find) {
        if (sw_chart) {
            const char *path = "./";
            string svg = sweinterfacelib::theme_astral_svg(year, month, day, hour, min, lat, lng, gmt, path, color);
            static std::string decode;
            if (!Base64::Decode(svg, &decode)) {
                std::cout << "Failed to decode" << std::endl;
            } else {
                cout << "Content-type:image/svg+xml\r\n\r\n";
                cout << decode << "\n";
            }
        } else if (sw_json) {
            Swe02::set_ephe_path("./");
            // TimeZone
            TimeZone time_zone;
            time_zone.year = year;
            time_zone.month = month;
            time_zone.day = day;
            time_zone.hour = hour;
            time_zone.min = min;
            time_zone.sec = 0;
            TimeZone utc_time_zone = TZ::utc_time_zone(time_zone, gmt);
            UtcToJd utc_to_jd = Swe08::utc_to_jd(utc_time_zone, CALANDAR_GREGORIAN);
            time_t t = time(0);
            tm* now = localtime(&t);
            TimeZone time_zone_t;
            time_zone_t.year = now->tm_year + 1900;
            time_zone_t.month = now->tm_mon + 1;
            time_zone_t.day = now->tm_mday;
            time_zone_t.hour = now->tm_hour;
            time_zone_t.min = now->tm_min;
            time_zone_t.sec = now->tm_sec;
            double gmt_t = gmt;
            TimeZone utc_time_zone_t = TZ::utc_time_zone(time_zone_t, gmt_t);
            UtcToJd utc_to_jd_t = Swe08::utc_to_jd(utc_time_zone_t, CALANDAR_GREGORIAN);

            H* house = new H[12];
            for (int i = 0; i < 12; ++i) {
                house[i] = Swe14::house(utc_to_jd.julian_day_ut, lat, lng, 'P', i + 1);
            }

            int* astres = new int[MAX_ASTRES];
            astres[SOLEIL] = ASTRE_SOLEIL;
            astres[LUNE] = ASTRE_LUNE;
            astres[MERCURE] = ASTRE_MERCURE;
            astres[VENUS] = ASTRE_VENUS;
            astres[MARS] = ASTRE_MARS;
            astres[JUPITER] = ASTRE_JUPITER;
            astres[SATURN] = ASTRE_SATURN;
            astres[URANUS] = ASTRE_URANUS;
            astres[NEPTUNE] = ASTRE_NEPTUNE;
            astres[PLUTON] = ASTRE_PLUTON;
            astres[NOEUD_LUNAIRE] = ASTRE_NOEUD_LUNAIRE;
            astres[CHIRON] = ASTRE_CHIRON;
            astres[CERES] = ASTRE_CERES;
            astres[NOEUD_LUNAIRE_SUD] = ASTRE_NOEUD_LUNAIRE_SUD;



            cout << "Content-type:application/json\r\n\r\n";
            // create an empty structure (null)

            json j;
            for (int i = 0; i < MAX_ASTRES; ++i) {
                string astre = Astre::name(i);
                if (astre != "") {
                    j["bodie"][astre]["asset"] = asset_bodie(i);
                }
            }
            j["pi"] = 3.141;
            j["happy"] = true;
            j["name"] = "Niels";
            j["nothing"] = nullptr;
            j["answer"]["everything"] = 42;
            j["list"] = { 1, 0, 2 };
            j["object"] = { {"currency", "USD"}, {"value", 42.99} };
            cout << j << "\n";
        } else if (sw_debug) {
            cout << "Content-type:text/html\r\n\r\n";
            cout << "<html>\n";
            cout << "<head>\n";
            cout << "<title>CGI Environment Variables</title>\n";
            cout << "</head>\n";
            cout << "<body>\n";
            cout << "<table border = \"0\" cellspacing = \"2\">";

            for ( int i = 0; i < 24; i++ ) {
                cout << "<tr><td>" << ENV[ i ] << "</td><td>";

                // attempt to retrieve value of environment variable
                char *value = getenv( ENV[ i ].c_str() );
                if ( value != 0 ) {
                    cout << value;
                } else {
                    cout << "Environment variable does not exist.";
                }
                cout << "</td></tr>\n";
            }
            cout << "</table>\n";
            cout << "</body>\n";
            cout << "</html>\n";
        }
    } else {
        cout << "Content-type:text/html\r\n\r\n";
        cout << "<html>\n";
        cout << "<head>\n";
        cout << "<title>CGI Environment Variables</title>\n";
        cout << "</head>\n";
        cout << "<body>bressani.dev</body></html>\n";
    }
    return 0;
}