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

#[link(name = "sweinterfacelib", kind = "static")]
extern "C" {
    pub fn theme_astral_svg(year: c_int, month: c_int, day: c_int, hour: c_int, min: c_int, lat: c_double, lng: c_double, gmt: c_int, ephem_path: *const c_char, color_mode: c_int) -> *const c_char;
    pub fn asset_sign(sign: c_int) -> *const c_char;
}
