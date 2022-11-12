extern crate cc;
use std::env;
use std::path::Path;

fn main() {
    //cc::Build::new().file("src/multiply.c").compile("multiply");
    let dir = env::var("CARGO_MANIFEST_DIR").unwrap();
    cc::Build::new()
        .file(Path::new(&dir).join("../../Sources/swelib/swecl.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swedate.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swehel.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swehouse.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swejpl.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swemmoon.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swemplan.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swepcalc.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/sweph.c"))
        .file(Path::new(&dir).join("../../Sources/swelib/swephlib.c"))
        .compile("swelib");
    cc::Build::new()
        .cpp(true)
        //.flag("-g")
        .file(Path::new(&dir).join("../../Sources/svglib/circle.cpp"))
        .file(Path::new(&dir).join("../../Sources/svglib/data.cpp"))
        .file(Path::new(&dir).join("../../Sources/svglib/document.cpp"))
        .file(Path::new(&dir).join("../../Sources/svglib/image.cpp"))
        .file(Path::new(&dir).join("../../Sources/svglib/line.cpp"))
        .compile("svglib");
    cc::Build::new()
        .cpp(true)
        //.flag("-g")
        .include(Path::new(&dir).join("../../Sources/swelib/include"))
        .include(Path::new(&dir).join("../../Sources/svglib/include"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/angle.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/aspect.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/astre.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_aspect_line.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_bodie_astre.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_bodie_line.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_house_angle.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_house_line.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_house_number.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_zodiac_circle.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_zodiac_line.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/draw_zodiac_sign.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/swe02.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/swe03.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/swe08.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/swe14.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/swe17.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/house.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/timezone.cpp"))
        .file(Path::new(&dir).join("../../Sources/sweinterfacelib/SweInterface.cpp"))
        .compile("sweinterfacelib");
}