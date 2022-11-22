extern crate core;
use std::os::raw::{c_char, c_double, c_int};

#[cxx::bridge(namespace = "sweinterfacelib")]
mod ffi {
    unsafe extern "C++" {
        include!("../../../Sources/sweinterfacelib/include/sweinterfacelib.h");
        type Sign;
        pub fn read_svg(sign: u32) -> &'static str;
        pub fn read_svg_c(sign: u32) -> *const c_char;
        pub fn nom(sign: u32) -> &'static str;
    }
}

#[cxx::bridge(namespace = "svglib")]
mod ffisvg {
    struct SvgFill {
        fill: *const i8
    }

    struct SvgStroke {
        stroke: *const i8,
        stroke_width: f32
    }

    struct SvgProperties {
        fill: SvgFill,
        stroke: SvgStroke
    }

    struct Fill {
        fill: String
    }

    struct Stroke {
        stroke: String,
        stroke_width: f32
    }

    struct Circle {
        properties: SvgProperties
    }

    unsafe extern "C++" {
        include!("../../../Sources/svglib/include/svglib.h");
        type Circle;
        pub fn Circle(fill: Fill, stroke: Stroke) -> Circle;
        pub fn generate(x: f32, y: f32, r: f32) -> String;
    }
}

#[link(name = "sweinterfacelib", kind = "static")]
extern "C" {
    pub fn theme_astral_svg(year: c_int, month: c_int, day: c_int, hour: c_int, min: c_int, lat: c_double, lng: c_double, gmt: c_int, ephem_path: *const c_char, color_mode: c_int) -> *const c_char;
    pub fn asset_sign(sign: c_int) -> *const c_char;
}
