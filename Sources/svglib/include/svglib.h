//
// Created by Stéphane on 21.10.22.
//
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace svglib {
    const string DELIMITER = ",";
    const char DELIMITER_CHAR = ',';
    struct SvgData {
        char data;
        int point_idx;
        int point_size;
    };
    struct SvgPoint {
        int point_idx;
        double point;
    };
    struct SvgFill {
        const char *fill_cchar;
    };
    struct SvgStroke {
        const char *stroke_cchar;
        double stroke_width;
    };
    struct SvgProperties {
        SvgFill fill;
        SvgStroke stroke;
    };
    struct Fill {
        string fill_str;
    };
    struct Stroke {
        string stroke_str;
        double stroke_width;
    };
    extern "C" {
        class Circle {
            private:
                SvgProperties properties;
            public:
                Circle(Fill fill, Stroke stroke);
                string generate(double x, double y, double r);
        };
        class Data {
        private:
            vector<SvgData> vec_data;
            vector<SvgPoint> vec_point;
            int idx_data;
            int idx_point;
            SvgProperties properties;
            static long get_size(string s);
            static double get_value(string s, int pos);
            SvgData set_data(char c, int point_size);
            SvgPoint set_point(string point_string, int pos);
            void set_command(char c, string s);
            string round(double var);
        public:
            Data(Fill fill, Stroke stroke);
            void move_to(double x, double y);
            void move_by(double x, double y);
            void line_to(double x, double y);
            void line_by(double x, double y);
            void close_to();
            void close_by();
            string generate();
        };
        class Document {
        private:
            double width;
            double height;
            string content;
        public:
            Document(double w, double h);
            Document &operator<<(string const &s) {
                content += s;
                return *this;
            }
            string generate();
        };
    }
    class Image {
    public:
        static string generate(double height, double width, double x, double y, const char *href);
    };
    class Line {
    private:
        SvgStroke stroke;
    public:
        Line(Stroke s);
        void set_stroke(Stroke s);
        string generate(double x1, double y1, double x2, double y2);
    };
}