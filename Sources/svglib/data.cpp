//
// Created by Stéphane on 03.10.22.
//
#include "include/svglib.h"

using namespace svglib;

long Data::get_size(const string& s) {
    return std::count(s.begin(), s.end(), DELIMITER_CHAR) + 1;
}

double Data::get_value(const string& s, int pos) {
    string c = DELIMITER;
    string res = "";
    auto start = 0U;
    auto end = s.find(c);
    int i = 0;
    while (end != string::npos)
    {
        if (pos == i) {
            res = s.substr(start, end - start);
            float res_int = stof(res);
            return res_int;
        }
        i++;
        start = end + c.length();
        end = s.find(c, start);
    }
    if (pos == i) {
        res = s.substr(start, end);
        float res_int = stof(res);
        return res_int;
    }
    return 0;
}

SvgData Data::set_data(char c, int point_size) {
    SvgData data;
    data.point_idx = idx_data;
    data.point_size = point_size;
    data.data = c;
    return data;
}

SvgPoint Data::set_point(const string& point_string, int pos) {
    SvgPoint point;
    point.point_idx = idx_data;
    point.point = Data::get_value(point_string, pos);
    return point;
}

void Data::set_command(char c, const string& s) {
    long size = Data::get_size(s);
    vec_data.push_back(Data::set_data(c, size));
    for (int k = 0; k < size; ++k) {
        vec_point.push_back(Data::set_point(s, k));
    }
    idx_data++;
    idx_point += size;
}

string Data::round(double var){
    return to_string(var);
}

Data::Data(const Fill& fill, const Stroke& stroke) {
    idx_data = 0;
    idx_point = 0;
    properties.fill.fill_cchar = fill.fill_str.c_str();
    properties.stroke.stroke_cchar = stroke.stroke_str.c_str();
    properties.stroke.stroke_width = stroke.stroke_width;
}

void Data::move_to(double x, double y) {
    char c = 'M';
    Data::set_command(c, to_string(x) + "," + to_string(y));
}

void Data::move_by(double x, double y) {
    char c = 'm';
    Data::set_command(c, to_string(x) + "," + to_string(y));
}

void Data::line_to(double x, double y) {
    char c = 'L';
    Data::set_command(c, to_string(x) + "," + to_string(y));
}

void Data::line_by(double x, double y) {
    char c = 'l';
    Data::set_command(c, to_string(x) + "," + to_string(y));
}

void Data::close_to() {
    char c = 'Z';
    vec_data.push_back(Data::set_data(c, 0));
    idx_data++;
}

void Data::close_by() {
    char c = 'z';
    vec_data.push_back(Data::set_data(c, 0));
    idx_data++;
}

string Data::generate() {
    std::ostringstream oss;
    std::ostringstream osst;

    for (int i = 0; i < idx_data; ++i) {
        osst << vec_data[i].data;
        int k = 0;
        for (int j = 0; j < idx_point; ++j) {
            if (vec_point[j].point_idx == vec_data[i].point_idx) {
                osst << (k++ ? "," : "") << vec_point[j].point;
            }
        }
        if (i < idx_data - 1) oss << " ";
    }

    oss << "<path d=\"" << osst.str()
        << "\" fill=\"" << properties.fill.fill_cchar
        << "\" stroke=\"" << properties.stroke.stroke_cchar
        << "\" stroke-width=\"" << properties.stroke.stroke_width << "\"/>";

    return oss.str();
}