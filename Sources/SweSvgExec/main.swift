//import cwrapper
import SweSvg
import Foundation

var sweSvg = SweSvg(ephemPath: "")
sweSvg.set(natal: Date(), lat: 16, lng: 26.6, tz: 2)
let svg = sweSvg.theme_astral()
let sign = try! sweSvg.asset_sign(i: 1)
//print(cwrapperfive())
