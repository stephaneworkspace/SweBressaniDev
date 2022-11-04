//import cwrapper
import SweSvg
import Foundation

var sweSvg = SweSvg(ephemPath: "")
sweSvg.set(natal: Date(), transit: Date(), lat: 16, lng: 26.6, tz: 2)
let svg = sweSvg.theme_astral()
print(svg)
let sign1 = try! sweSvg.asset_sign(i: 1)
let sign2 = try! sweSvg.asset_sign(i: 2)
//print(cwrapperfive())
