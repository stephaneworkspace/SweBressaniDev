extern crate core;
use std::os::raw::{c_char, c_double, c_int};

#[link(name = "sweinterfacelib", kind = "static")]
extern "C" {
    pub fn theme_astral_svg(year: c_int, month: c_int, day: c_int, hour: c_int, min: c_int, lat: c_double, lng: c_double, gmt: c_int, ephem_path: *const c_char, color_mode: c_int) -> *const c_char;
}
