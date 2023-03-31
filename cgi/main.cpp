//
// Created by Stéphane on 31.03.23.
//
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <sstream>
#include "swelib.h"
#include "sweinterfacelib.h"

using namespace std;

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

    vector<string> s = tokenize(getenv(ENV[10].c_str()), '&');
    for (int i = 0; i < s.size(); ++i) {
        vector<string> sp = tokenize(s[i], '=');
        cout << "<tr><td>" << sp[0] << "</td><td>" << sp[1] << "</td></tr>\n";
    }

    char *path = (char *) malloc(255);
    //free(path);

    cout << sweinterfacelib::theme_astral_svg(1984, 1, 4, 0, 0, 16, 26, 2, path, 0) << endl;

    cout << "</table>\n";
    cout << "</body>\n";
    cout << "</html>\n";

    return 0;
}