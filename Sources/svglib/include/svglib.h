//
// Created by Stéphane on 21.10.22.
//
#include <fstream>
#include <iostream>
#include <vector>

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
        float point;
    };
    struct SvgFill {
        const char *fill;
    };
    struct SvgStroke {
        const char *stroke;
        float stroke_width;
    };
    struct SvgProperties {
        SvgFill fill;
        SvgStroke stroke;
    };
    struct Fill {
        string fill;
    };
    struct Stroke {
        string stroke;
        float stroke_width;
    };
    extern "C" {
        class Circle {
            private:
                SvgProperties properties;
            public:
                Circle(Fill fill, Stroke stroke);
                string generate(float x, float y, float r);
        };
        class Data {
        private:
            vector<SvgData> vec_data;
            vector<SvgPoint> vec_point;
            int idx_data;
            int idx_point;
            SvgProperties properties;
            static long get_size(string s);
            static float get_value(string s, int pos);
            SvgData set_data(char c, int point_size);
            SvgPoint set_point(string point_string, int pos);
            void set_command(char c, string s);
            string round(float var);
        public:
            Data(Fill fill, Stroke stroke);
            void move_to(float x, float y);
            void move_by(float x, float y);
            void line_to(float x, float y);
            void line_by(float x, float y);
            void close_to();
            void close_by();
            string generate();
        };
        class Document {
        private:
            float width;
            float height;
            string content;
        public:
            Document(float w, float h);
            Document &operator<<(string const &s) {
                content += s;
                return *this;
            }
            string generate();
        };
    }
    class Image {
    public:
        static string generate(float height, float width, float x, float y, const char *href);
    };
    class Line {
    private:
        SvgStroke stroke;
    public:
        Line(Stroke s);
        void set_stroke(Stroke s);
        string generate(float x1, float y1, float x2, float y2);
    };
}