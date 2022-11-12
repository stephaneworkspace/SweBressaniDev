//use crate::swe;
mod swe;
use std::ffi::{CStr, CString};
use std::os::raw::c_char;

fn main() {
    println!("Hello, world!");
    // Get the version
    let mut version = [0; 255];
    let v = unsafe {
        let p = version.as_mut_ptr();
        swe::swe_version(p);
        CStr::from_ptr(p)
    };
    println!("{:?}", CString::from(v).to_str().unwrap().to_string());
}
