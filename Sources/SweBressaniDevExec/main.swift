//import cwrapper
import Foundation
import SwiftUI
//#if canImport(UIKit)
//import UIKit
//#endif
import SweBressaniDev

var sweSvg = SweSvg(ephemPath: "")
sweSvg.set(natal: Date(), transit: Date(), lat: 16, lng: 26.6, tz: 2, colorMode: .Light)
let svg = try! sweSvg.theme_astral()
print(svg)
let sign1 = try! sweSvg.asset_sign(i: 1)
let sign2 = try! sweSvg.asset_sign(i: 2)
//print(cwrapperfive())

//var swe = SweCore(pathEphe: "", size: 400)
//swe.set(natal: Date(), transit: Date(), lat: 16, lng: 26.6, tz: 2, colorMode: .Light)
//print(swe.bodieDegMinSec(bodie: .Soleil, swTransit: true))
/*
let nom = "Stéphane"
var gauche: [(Int, Int)] = []
var droite: [(Int, Int)] = []
var total = 0;
var total_reduit = 0;
for l in nom {
    let n: (Int, Bool) = NumerologieCore.lettre(lettre: String(l))
    if n.0 > 0 {
        let nombre_non_reduit = n.0
        let nombre_reduit = NumerologieCore.reduction(iNumber: nombre_non_reduit)
        if n.1 {
            droite.append((nombre_non_reduit, nombre_reduit.last ?? nombre_non_reduit))
            gauche.append((0,0))
        } else {
            droite.append((0,0))
            gauche.append((nombre_non_reduit, nombre_reduit.last ?? nombre_non_reduit))
        }
    } else {
        droite.append((0,0))
        gauche.append((0,0))
    }
}
print("droite")
print(droite)
for d in droite {
    total += d.0
}
total_reduit = NumerologieCore.reduction(iNumber: total).last ?? total
print((total, total_reduit))
total = 0
print("gauche")
print(gauche)
for g in gauche {
    total += g.0
}
total_reduit = NumerologieCore.reduction(iNumber: total).last ?? total
print((total, total_reduit))
var arr_cm: [Int] = []
for d in droite {
    var swTrouve = false
    for n in arr_cm {
        if d.1 == n {
            swTrouve = true
            break
        }
    }
    if !swTrouve {
        arr_cm.append(d.1)
    }
}
for g in gauche {
    var swTrouve = false
    for n in arr_cm {
        if g.1 == n {
            swTrouve = true
            break
        }
    }
    if !swTrouve {
        arr_cm.append(g.1)
    }
}
print(arr_cm)
let CASE_CM: [[Int]] = [[8,1,6],[3,5,7],[4,9,2]]
print("")
print(CASE_CM[0])
print(CASE_CM[1])
print(CASE_CM[2])
var case_cm_final: [[Int]] = [[],[],[]]
for (i, x) in CASE_CM.enumerated() {
    for y in x {
        var nombre = 0
        for z in arr_cm {
            if z == y {
                nombre = z
                break
            }
        }
        case_cm_final[i].append(nombre)
    }
}
print("")
print(case_cm_final[0])
print(case_cm_final[1])
print(case_cm_final[2])
*/