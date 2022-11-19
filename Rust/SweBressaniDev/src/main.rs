//use crate::swe;
mod swe;
mod sweinterface;
use std::ffi::{c_double, CStr, CString};
use std::os::raw::{c_char, c_int};
use chrono::{Datelike, DateTime, NaiveDate, NaiveDateTime, NaiveTime, Timelike};
use chrono::format::ParseError;
/*
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
}*/

use actix_web::{web, App, HttpRequest, HttpServer, Responder};

async fn chart(req: HttpRequest) -> impl Responder {
    let date_natal = req.match_info().get("natal").unwrap_or("198401010000");
    let date_time_natal = NaiveDateTime::parse_from_str(date_natal, "%Y%m%d%H%M").unwrap(); // TODO
    let year = date_time_natal.year();
    let month = date_time_natal.month();
    let day = date_time_natal.day();
    let hour = date_time_natal.hour();
    let minute = date_time_natal.minute();
    let path = CString::new("").unwrap();
    let path_ptr = path.as_ptr();
    let res = unsafe {
        sweinterface::theme_astral_svg(year as c_int, month as c_int, day as c_int,
                                       hour as c_int, minute as c_int, 16 as c_double,
                                       26.6 as c_double, 2 as c_int, path_ptr,
                                       0 as c_int)
    };
    let res_cstr = unsafe { CStr::from_ptr(res) };
    let res_str = res_cstr.to_str().unwrap();
    format!("{}", res_str)
}

async fn greet(req: HttpRequest) -> impl Responder {
    let name = req.match_info().get("name").unwrap_or("World");
    unsafe { sweinterface::asset_sign(1) };
    format!("Hello {}!", &name)
}

#[actix_web::main]
async fn main() -> std::io::Result<()> {
    HttpServer::new(|| {
        App::new()
            .route("/", web::get().to(greet))
            .route("/{name}", web::get().to(greet))
            .route("/{natal}", web::get().to(chart))
    })
        .bind(("127.0.0.1", 8080))?
        .run()
        .await
}
