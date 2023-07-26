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

var case_cm2: [[Int]] = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
for d in droite {
    switch d.1 {
    case 1:
        case_cm2[0][0] =  case_cm2[0][0] + 1
        break
    case 2:
        case_cm2[0][1] =  case_cm2[0][1] + 1
        break
    case 3:
        case_cm2[0][2] =  case_cm2[0][2] + 1
        break
    case 4:
        case_cm2[1][0] =  case_cm2[1][0] + 1
        break
    case 5:
        case_cm2[1][1] =  case_cm2[1][1] + 1
        break
    case 6:
        case_cm2[1][2] =  case_cm2[1][2] + 1
        break
    case 7:
        case_cm2[2][0] =  case_cm2[2][0] + 1
        break
    case 8:
        case_cm2[2][1] =  case_cm2[2][1] + 1
        break
    case 9:
        case_cm2[2][2] =  case_cm2[2][2] + 1
        break
    default:
        break
    }
}
for g in gauche {
    switch g.1 {
    case 1:
        case_cm2[0][0] =  case_cm2[0][0] + 1
        break
    case 2:
        case_cm2[0][1] =  case_cm2[0][1] + 1
        break
    case 3:
        case_cm2[0][2] =  case_cm2[0][2] + 1
        break
    case 4:
        case_cm2[1][0] =  case_cm2[1][0] + 1
        break
    case 5:
        case_cm2[1][1] =  case_cm2[1][1] + 1
        break
    case 6:
        case_cm2[1][2] =  case_cm2[1][2] + 1
        break
    case 7:
        case_cm2[2][0] =  case_cm2[2][0] + 1
        break
    case 8:
        case_cm2[2][1] =  case_cm2[2][1] + 1
        break
    case 9:
        case_cm2[2][2] =  case_cm2[2][2] + 1
        break
    default:
        break
    }
}
print("")
print(case_cm2[0])
print(case_cm2[1])
print(case_cm2[2])

// Juillet 2023
// Exportation pour backend astrologie en ruby
import SweBressaniDev
let _svg = SweSvg(ephemPath: "")
/*
// 0
var i = 0;
var path = try! _svg.asset_bodie(i: i)
var text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "soleil = Da01Astre.create(nom: \"Soleil\", svg: \"%@\", id_swe: 0, id_sweinterfacelib: 0, sw_traditionnelle: true)", text ?? ""))
// 1
i = 1
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "lune = Da01Astre.create(nom: \"Lune\", svg: \"%@\", id_swe: 1, id_sweinterfacelib: 1, sw_traditionnelle: true)", text ?? ""))
// 2
i = 2
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "mercure = Da01Astre.create(nom: \"Mercure\", svg: \"%@\", id_swe: 2, id_sweinterfacelib: 2, sw_traditionnelle: true)", text ?? ""))
// 3
i = 3
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "venus = Da01Astre.create(nom: \"Venus\", svg: \"%@\", id_swe: 3, id_sweinterfacelib: 3, sw_traditionnelle: true)", text ?? ""))
// 4
i = 4
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "mars = Da01Astre.create(nom: \"Mars\", svg: \"%@\", id_swe: 4, id_sweinterfacelib: 4, sw_traditionnelle: true)", text ?? ""))
// 5
i = 5
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "jupiter = Da01Astre.create(nom: \"Jupiter\", svg: \"%@\", id_swe: 5, id_sweinterfacelib: 5, sw_traditionnelle: true)", text ?? ""))
// 6
i = 6
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "saturne = Da01Astre.create(nom: \"Saturne\", svg: \"%@\", id_swe: 6, id_sweinterfacelib: 6, sw_traditionnelle: true)", text ?? ""))
// 7
i = 7
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "uranus = Da01Astre.create(nom: \"Uranus\", svg: \"%@\", id_swe: 7, id_sweinterfacelib: 7, sw_traditionnelle: true)", text ?? ""))
// 8
i = 8
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "neptune = Da01Astre.create(nom: \"Neptune\", svg: \"%@\", id_swe: 8, id_sweinterfacelib: 8, sw_traditionnelle: true)", text ?? ""))
// 9
i = 9
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "pluton = Da01Astre.create(nom: \"Pluton\", svg: \"%@\", id_swe: 9, id_sweinterfacelib: 9, sw_traditionnelle: true)", text ?? ""))
// 11
i = 11
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "noeud_lunaire = Da01Astre.create(nom: \"Noeud Lunaire\", svg: \"%@\", id_swe: 11, id_sweinterfacelib: 10, sw_traditionnelle: false)", text ?? ""))
// 15
i = 15
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "chiron = Da01Astre.create(nom: \"Chiron\", svg: \"%@\", id_swe: 15, id_sweinterfacelib: 11, sw_traditionnelle: false)", text ?? ""))
// 17
i = 17
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "ceres = Da01Astre.create(nom: \"Ceres\", svg: \"%@\", id_swe: 17, id_sweinterfacelib: 12, sw_traditionnelle: false)", text ?? ""))
// 24
i = 24
path = try! _svg.asset_bodie(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "noeud_lunaire_sud = Da01Astre.create(nom: \"Noeud Lunaire Sud\", svg: \"%@\", id_swe: 24, id_sweinterfacelib: 13, sw_traditionnelle: false)", text ?? ""))
*/
/*
// 0
var i = 0
var path = try! _svg.asset_aspect(i: i)
var text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "conjonction = Da02Aspect.create(nom: \"Conjonction\", angle: 0, orbe_admis: 10, svg: \"%@\", id_swe: %d, sw_majeur: true)", text ?? "", i))
// 1
i = 1
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "opposition = Da02Aspect.create(nom: \"Opposition\", angle: 180, orbe_admis: 8, svg: \"%@\", id_swe: %d, sw_majeur: true)", text ?? "", i))
// 2
i = 2
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "trigone = Da02Aspect.create(nom: \"Trigone\", angle: 30, orbe_admis: 7, svg: \"%@\", id_swe: %d, sw_majeur: true)", text ?? "", i))
// 3
i = 3
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "carre = Da02Aspect.create(nom: \"Carré\", angle: 40, orbe_admis: 6, svg: \"%@\", id_swe: %d, sw_majeur: true)", text ?? "", i))
// 4
i = 4
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "sextile = Da02Aspect.create(nom: \"Sextile\", angle: 60, orbe_admis: 5, svg: \"%@\", id_swe: %d, sw_majeur: true)", text ?? "", i))
// 5
i = 5
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "quinconce = Da02Aspect.create(nom: \"Quinconce\", angle: 150, orbe_admis: 2, svg: \"%@\", id_swe: %d, sw_majeur: false)", text ?? "", i))
// 6
i = 6
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "sexqui_carre = Da02Aspect.create(nom: \"Sexqui-Carré\", angle: 135, orbe_admis: 1, svg: \"%@\", id_swe: %d, sw_majeur: false)", text ?? "", i))
// 7
i = 7
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "demi_carre = Da02Aspect.create(nom: \"Demi-Carré\", angle: 45, orbe_admis: 1, svg: \"%@\", id_swe: %d, sw_majeur: false)", text ?? "", i))
// 8
i = 8
path = try! _svg.asset_aspect(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "demi_sextile = Da02Aspect.create(nom: \"Demi-Sextile\", angle: 30, orbe_admis: 1, svg: \"%@\", id_swe: %d, sw_majeur: false)", text ?? "", i))
*/
 /*
// Signes
var i = 1
var path = try! _svg.asset_sign(i: i)
var text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "belier = Da03Signe.create(nom: \"Belier\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 2
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "taureau = Da03Signe.create(nom: \"Taureau\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 3
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "gemaux = Da03Signe.create(nom: \"Gemaux\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 4
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "cancer = Da03Signe.create(nom: \"Cancer\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 5
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "lion = Da03Signe.create(nom: \"Lion\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 6
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "vierge = Da03Signe.create(nom: \"Vierge\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 7
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "balance = Da03Signe.create(nom: \"Balance\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 8
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "scorpion = Da03Signe.create(nom: \"Scorpion\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 9
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "scorpion = Da03Signe.create(nom: \"Sagittaire\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 10
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "capricorne = Da03Signe.create(nom: \"Capricorne\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 11
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "verseau = Da03Signe.create(nom: \"Verseau\", svg: \"%@\", id_swe: %d)", text ?? "", i))
i = 12
path = try! _svg.asset_sign(i: i)
text = try? String(contentsOf: path).data(using: .utf8)?.base64EncodedString()
print(String(format: "poisson = Da03Signe.create(nom: \"Poisson\", svg: \"%@\", id_swe: %d)", text ?? "", i))
 */