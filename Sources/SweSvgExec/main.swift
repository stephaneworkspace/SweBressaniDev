//import cwrapper
import SweSvg

let sweSvg = SweSvg(ephemPath: "")
let s = sweSvg.theme_astral(year: 1984, month: 1, day: 4, hour: 0, min: 0, lat: 16.0, lng: 26.6, tz: 2)
print(s)
//let svg: String = String(cString: UnsafePointer<CChar>(theme_astral(1984, 1, 4, 0, 0, 16, 26, 2, "")))
//print(svg)
//print(cwrapperfive())
