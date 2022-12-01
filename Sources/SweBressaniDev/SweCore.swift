//
// Created by Stéphane on 05.11.22.
//

import Foundation
import SwiftUI
import TPPDF

let CIRCLE = 360.0
let CIRCLE_SIZE_TRANSIT: [(Double, Bool)] = [
    (42.0, true), // 0 CIRCLE ASPECT
    (59.0, true), // 1 CIRCLE TRANSIT
    (75.0, true), // 2 CIRCLE ZODIAC END
    (80.0, true), // 3 CIRCLE HOUSE
    (92.0, false), // 4 CIRCLE INVISIBLE -
    (92.0, false), // 5 CIRCLE INVISIBLE PLANET
    //    (0.0, false), // 5
    (0.0, false), // 6
    (82.0, false), // 7 between 2 and 3
    (85.0, false), // 8 correction planet between 2 and 3
    (49.0, false), // 9 Planet pos transit
    (57.5, false), // 10 - 7 transit
    (54.5, false), // 11 - 8 transit
    (84.5, false), // 12 part secondaire non activé
]
let PART_SECONDAIRE_CIRCLE = 360.0
let PART_SECONDAIRE_CIRCLE_SIZE_TRANSIT: [(Double, Bool)] = [
    (42.0, false), // 0 CIRCLE ASPECT
    (59.0, true), // 1 CIRCLE TRANSIT
    (75.0, true), // 2 CIRCLE ZODIAC END
    (80.0, true), // 3 CIRCLE HOUSE
    (96.0, false), // 4 CIRCLE INVISIBLE -
    (96.0, false), // 5 CIRCLE INVISIBLE PLANET
    //    (0.0, false), // 5
    (0.0, false), // 6
    (86.5, false), // 7 between 2 and 3
    (89.0, false), // 8 correction planet between 2 and 3
    (49.0, false), // 9 Planet pos transit
    (57.5, false), // 10 - 7 transit
    (54.5, false), // 11 - 8 transit
    (84.5, true), // 12 part secondaire
]
let LARGER_DRAW_LINE_RULES_SMALL = 0.1
let LARGER_DRAW_LINE_RULES_LARGE = 0.2
let ZODIAC_RATIO = 10.0
let ZODIAC_SIZE = 50.0
let BODIE_SIZE = 35.0
let ANGLE_SIZE = 50.0
let HOUSE_SIZE = 40.0
let HOUSE_RATIO = 5.0
let DEG_SIZE = 50.0
let MIN_SIZE = 50.0
public let RETROGRADE_DIV = 1.5
public let RETROGRADE_SIZE_DIV = 1.5
let ANGLE_RATIO_ASC = 10.0
let ANGLE_RATIO_FC = 7.0
let ANGLE_RATIO_DESC = 12.0
let ANGLE_RATIO_MC = 8.0
let ANGULAR_POINTER = -1.0
let DIV_TRAIT_POINTER = 1.5

public class SweCore {
    public enum Angles: Int32 {
        case Nothing = 0,
             Asc = 1,
             Fc = 2,
             Desc = 3,
             Mc = 4
    }
    public enum Calandar: Int32 {
        case Julian = 0, Gregorian = 1
    }
    public enum LargerDrawLine {
        case Large, Small
    }
    public enum Signs: Int {
        case Aries = 1,
             Taurus = 2,
             Gemini = 3,
             Cancer = 4,
             Leo = 5,
             Virgo = 6,
             Libra = 7,
             Scorpio = 8,
             Sagittarius = 9,
             Capricorn = 10,
             Aquarius = 11,
             Pisces = 12
    }
    public enum Bodies: Int {
        case Soleil = 0,
             Lune = 1,
             Mercure = 2,
             Venus = 3,
             Mars = 4,
             Jupiter = 5,
             Saturn = 6,
             Uranus = 7,
             Neptune = 8,
             Pluto = 9,
             NoeudLunaire = 11,
             Chiron = 15,
             Ceres = 17,
             NoeudLunaireSud = 24,
             PartSecondaire = 25 // Distance Lune-Soleil
    }
    public enum Aspects: Int {
        case Conjunction = 0,
             Opposition = 1,
             Trine = 2,
             Square = 3,
             Sextile = 4,
             Inconjunction = 5,
             Sequisquare = 6,
             Semisquare = 7,
             Semisextile = 8,
             Nothing = -1
    }
    public struct AstroCircle {
        public var center: Double
        public var radius: Double
    }
    public struct AstroLine {
        public var lX1: Double
        public var lY1: Double
        public var lX2: Double
        public var lY2: Double
    }
    public struct AstroHouseLine {
        public var lX1: Double
        public var lY1: Double
        public var lX2: Double
        public var lY2: Double
        public var lXY3: Bool
        public var lX3: Double
        public var lY3: Double
    }
    public struct AspectLine {
        public var aspect: SweCore.Aspects
        public var lX1: Double
        public var lY1: Double
        public var lX2: Double
        public var lY2: Double
    }
    public enum AspectType: Int {
        case Natal = 0, Transit = 1, NatalAndTransit = 2
    }
    public struct Offset {
        public var offX: Double
        public var offY: Double
    }
    public struct SplitDeg {
        public var print: String
        public var deg: Int32
        public var min: Int32
        public var sec: Int32
        public var cdegfr: Double
        public var sign: Signs
        public var result: Double
    }
    public struct HouseResult {
        public var cusps: [Double]
        public var ascmc: [Double]
        public var result: Int32
    }
    public struct Object {
        public var sign: Signs
        public var oSx: Double
        public var oSy: Double
        public var oPx: Double
        public var oPy: Double
    }
    public struct ObjectHouse {
        public var oSx: Double
        public var oSy: Double
        public var oPx: Double
        public var oPy: Double
    }
    public struct ObjectBodie {
        public var swRetrograde: Bool
        public var oSx: Double
        public var oSy: Double
        public var oPx: Double
        public var oPy: Double
    }
    public struct ObjectAngle {
        public var oSx: Double
        public var oSy: Double
        public var oPx: Double
        public var oPy: Double
    }
    public var size: Int // TODO sizeChart: (screenSize.width == 744 && screenSize.height == 1133) ? 630.0 : 390.0)
    public var colorMode: SweSvg.ColorMode
    public var swec: SweSvg
    public var bodiesForLoop: [SweCore.Bodies] = [
        SweCore.Bodies.Soleil,
        SweCore.Bodies.Lune,
        SweCore.Bodies.Mercure,
        SweCore.Bodies.Venus,
        SweCore.Bodies.Mars,
        SweCore.Bodies.Jupiter,
        SweCore.Bodies.Saturn,
        SweCore.Bodies.Uranus,
        SweCore.Bodies.Neptune,
        SweCore.Bodies.Pluto,
        SweCore.Bodies.NoeudLunaire,
        SweCore.Bodies.Chiron,
        SweCore.Bodies.Ceres,
        SweCore.Bodies.NoeudLunaireSud,
    ]
    public enum BodAng {
        case Bodie(SweCore.Bodies), Angle(SweCore.Angles)
    }

    public struct BodAngIdentifiable: Identifiable {
        public var id = UUID()
        public var bodAng: BodAng
        public var pos: Int
    }

    public struct BodAngAspectIdentifiable: Identifiable {
        public var id = UUID()
        public var bodAng1: BodAng
        public var pos1: Int
        public var swTransit1: Bool
        public var bodAng2: BodAng
        public var pos2: Int
        public var swTransit2: Bool
        public var aspect: SweCore.Aspects
    }

    public init(pathEphe: String, size: Int) {
        self.size = size
        colorMode = .Light
        swec = SweSvg(ephemPath: pathEphe)
    }

    public func set(natal: Date, transit: Date, lat: Double, lng: Double, tz: Int32, colorMode: SweSvg.ColorMode) {
        swec.set(natal: natal, transit: transit, lat: lat, lng: lng, tz: tz, colorMode: colorMode)
    }

    public func bodAng() -> [BodAngIdentifiable] {
        var res: [BodAngIdentifiable] = []
        var j = 0
        for (i, b) in bodiesForLoop.enumerated() {
            j = i
            res.append(BodAngIdentifiable.init(bodAng: BodAng.Bodie(b), pos: i))
        }
        j += 1
        res.append(BodAngIdentifiable.init(bodAng: BodAng.Angle(.Asc), pos: j))
        res.append(BodAngIdentifiable.init(bodAng: BodAng.Angle(.Mc), pos: j))
        return res
    }

    public func bodAngAspect(swTransit1: Bool, swTransit2: Bool) -> [BodAngAspectIdentifiable] {
        let resBodAng = bodAng()
        var res: [BodAngAspectIdentifiable] = []
        for ba in resBodAng {
            for ba2 in resBodAng {
                if ba.pos != ba2.pos {
                    var lon1 = 0.0
                    var lon2 = 0.0
                    switch ba.bodAng {
                    case .Bodie(let baB):
                        switch ba2.bodAng {
                        case .Bodie(let baB2):
                            if swTransit1 == false && swTransit2 == false {
                                for bod in swec.bodiesNatal {
                                    if bod.bodie == baB.rawValue {
                                        lon1 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                                for bod in swec.bodiesNatal {
                                    if bod.bodie == baB2.rawValue {
                                        lon2 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            } else if swTransit1 == false && swTransit2 == true {
                                for bod in swec.bodiesNatal {
                                    if bod.bodie == baB.rawValue {
                                        lon1 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                                for bod in swec.bodiesTransit {
                                    if bod.bodie == baB2.rawValue {
                                        lon2 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            } else if swTransit1 == true && swTransit2 == false {
                                for bod in swec.bodiesTransit {
                                    if bod.bodie == baB.rawValue {
                                        lon1 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                                for bod in swec.bodiesNatal {
                                    if bod.bodie == baB2.rawValue {
                                        lon2 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            } else if swTransit1 == true && swTransit2 == true {
                                for bod in swec.bodiesTransit {
                                    if bod.bodie == baB.rawValue {
                                        lon1 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                                for bod in swec.bodiesTransit {
                                    if bod.bodie == baB2.rawValue {
                                        lon2 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            }
                            break
                        case .Angle(let baA2):
                            if swTransit1 == false {
                                for bod in swec.bodiesNatal {
                                    if bod.bodie == baB.rawValue {
                                        lon1 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            } else if swTransit1 == true {
                                for bod in swec.bodiesTransit {
                                    if bod.bodie == baB.rawValue {
                                        lon1 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            }
                            lon2 = getAngleLongitude(angle: baA2)
                            break
                        }
                    case .Angle(let baA):
                        switch ba2.bodAng {
                        case .Bodie(let baB2):
                            lon1 = getAngleLongitude(angle: baA)
                            if swTransit2 == false {
                                for bod in swec.bodiesNatal {
                                    if bod.bodie == baB2.rawValue {
                                        lon2 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            } else if swTransit2 == true {
                                for bod in swec.bodiesTransit {
                                    if bod.bodie == baB2.rawValue {
                                        lon2 = bod.calc_ut.longitude
                                        break
                                    }
                                }
                            }
                            break
                        case .Angle(let baA2):
                            lon1 = getAngleLongitude(angle: baA)
                            lon2 = getAngleLongitude(angle: baA2)
                            break
                        }
                    }
                    var aspect = SweCore.Aspects.Nothing
                    let separation = getClosestDistance(angle1: lon1, angle2: lon2)
                    let absSeparation = abs(separation)
                    for aspectIdx in 0...SweCore.Aspects.Semisextile.rawValue {
                        let a = Aspects.init(rawValue: aspectIdx)!
                        if abs(absSeparation - Double(a.angle().0)) <= Double(a.angle().1) {
                            // .0 asp / .1 orb
                            aspect = a
                        }
                    }
                    res.append(BodAngAspectIdentifiable.init(
                            bodAng1: ba.bodAng,
                            pos1: ba.pos,
                            swTransit1: swTransit1,
                            bodAng2: ba2.bodAng,
                            pos2: ba2.pos,
                            swTransit2: swTransit2,
                            aspect: aspect))
                }
            }
        }
        return res
    }

    public func bodAngAspectPos(bodAngPos: Int, swTransit1: Bool, swTransit2: Bool, y: Int) -> (BodAngAspectIdentifiable, Bool) {
        let res: (BodAngAspectIdentifiable, Bool) = (BodAngAspectIdentifiable.init(bodAng1: BodAng.Bodie(.Soleil), pos1: 1, swTransit1: false, bodAng2: BodAng.Bodie(.Lune), pos2: 2, swTransit2: false, aspect: .Square), false)
        var i = 0;
        let bodAngAspect = bodAngAspect(swTransit1: swTransit1, swTransit2: swTransit2)
        for ba in bodAngAspect {
            if ba.pos1 == bodAngPos {
                if (y == i) {
                    return (ba, true)
                }
                i += 1
            }
        }
        return res
    }

    public func circles() -> [SweCore.AstroCircle] {
        var res: [SweCore.AstroCircle] = []
        let center = getRadiusTotal()
        for (idx, circleSize) in CIRCLE_SIZE_TRANSIT.enumerated() {
            if circleSize.1 {
                let radius = getRadiusCircle(occurs: idx).0
                res.append(SweCore.AstroCircle(center: center, radius: radius))
            }
        }
        return res
    }

    // N'est pas utilisé dans astronumerologie sur mon github stephaneworkspace
    public func partSecondaireCircles() -> [SweCore.AstroCircle] {
        var res: [SweCore.AstroCircle] = []
        let center = getRadiusTotal()
        for (idx, circleSize) in PART_SECONDAIRE_CIRCLE_SIZE_TRANSIT.enumerated() {
            if circleSize.1 {
                let radius = getRadiusCircle(occurs: idx).0
                res.append(SweCore.AstroCircle(center: center, radius: radius))
            }
        }
        return res
    }

    public func zodiacLines() -> [SweCore.AstroLine] {
        var res: [SweCore.AstroLine] = []
        for iIdx in 1...12 {
            // 0°
            let offPosAsc = 360.0 - swec.houses[0].longitude
            var pos = Double(iIdx) * 30.0 + offPosAsc
            pos = getFixedPos(pos_value: pos)
            let axy: [Offset] = getLineTrigo(
                    angular: pos,
                    radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                    radiusCircleEnd: getRadiusCircle(occurs: 1).0)
            res.append(SweCore.AstroLine(
                    lX1: axy[0].offX,
                    lY1: axy[0].offY,
                    lX2: axy[1].offX,
                    lY2: axy[1].offY)
            )
            // 1° to 29°
            var largerDrawLine: SweCore.LargerDrawLine = .Large
            for jIdx in 1...15 {
                if jIdx == 5 || jIdx == 10 || jIdx == 15 {
                    largerDrawLine = .Large
                } else {
                    largerDrawLine = .Small
                }
                pos = (Double(iIdx) * 30.0) + Double(jIdx) * 2.0 + offPosAsc
                pos = getFixedPos(pos_value: pos)
                let axy: [Offset] = getLineTrigo(
                        angular: pos,
                        radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                        radiusCircleEnd: getRadiusRulesInsideCircle(largerDrawLine: largerDrawLine))
                res.append(SweCore.AstroLine(
                        lX1: axy[0].offX,
                        lY1: axy[0].offY,
                        lX2: axy[1].offX,
                        lY2: axy[1].offY)
                )
            }
        }
        return res
    }

    public func zodiacSign(sign: Int) -> SweCore.Object {
        let zodiacSize = (((ZODIAC_SIZE * ZODIAC_RATIO) / 100.0) * Double(size)) / 100.0;
        let offPosAsc = CIRCLE - swec.houses[0].longitude
        let signEnum: SweCore.Signs = Signs.init(rawValue: sign) ?? SweCore.Signs.Aries
        let pos = (Double(signEnum.rawValue - 1) * 30.0) + 15.0 + offPosAsc
        let offset = getCenterItem(
                size: zodiacSize,
                offset: getPosTrigo(
                        angular: pos,
                        radiusCircle: getRadiusCircleZodiac()))
        let res = SweCore.Object(
                sign: signEnum,
                oSx: zodiacSize,
                oSy: zodiacSize,
                oPx: offset.offX,
                oPy: offset.offY)
        return res
    }

    public func house(number: Int) -> SweCore.ObjectHouse {
        let houseSize = (((HOUSE_SIZE * HOUSE_RATIO) / 100.0) * Double(size)) / 100.0
        let offPosAsc = CIRCLE - swec.houses[0].longitude
        var posNext: Double
        if number > 11 {
            posNext = swec.houses[0].longitude + offPosAsc
        } else {
            posNext = swec.houses[Int(number)].longitude + offPosAsc
        }
        let posNow = swec.houses[Int(number - 1)].longitude + offPosAsc
        var pos: Double
        if posNow > posNext {
            pos = posNow + ((posNext - posNow - CIRCLE) / 2.0)
        } else {
            pos = posNow + ((posNext - posNow) / 2.0)
        }
        pos = getFixedPos(pos_value: pos)
        let offset = getCenterItem(
                size: houseSize,
                offset: getPosTrigo(
                        angular: pos,
                        radiusCircle: getRadiusCircleHouse()))
        if number > 9 {
            return SweCore.ObjectHouse(
                    oSx: houseSize,
                    oSy: houseSize,
                    oPx: offset.offX,
                    oPy: offset.offY)
        } else {
            return SweCore.ObjectHouse(
                    oSx: houseSize / 1.5,
                    oSy: houseSize,
                    oPx: offset.offX,
                    oPy: offset.offY)
        }
    }

    // J'utilise l'objet ObjectHouse car c'est presque parail que les parts
    // dans le cas d'un cercle entre les astres natal et les maisons
    public func partSecondaire(number: Int) -> SweCore.ObjectHouse {
        //
        let partSize = (((HOUSE_SIZE * HOUSE_RATIO) / 100.0) * Double(size)) / 100.0
        let offPosAsc = CIRCLE - swec.partSecondaire[0].calc_ut.longitude
        var posNext: Double
        if number > 11 {
            posNext = swec.houses[0].longitude + offPosAsc
        } else {
            posNext = swec.houses[Int(number)].longitude + offPosAsc
        }
        let posNow = swec.houses[Int(number - 1)].longitude + offPosAsc
        var pos: Double
        if posNow > posNext {
            pos = posNow + ((posNext - posNow - CIRCLE) / 2.0)
        } else {
            pos = posNow + ((posNext - posNow) / 2.0)
        }
        pos = getFixedPos(pos_value: pos)
        let offset = getCenterItem(
                size: partSize,
                offset: getPosTrigo(
                        angular: pos,
                        radiusCircle: getRadiusCirclePartSecondaire()))
        if number > 9 {
            return SweCore.ObjectHouse(
                    oSx: partSize,
                    oSy: partSize,
                    oPx: offset.offX,
                    oPy: offset.offY)
        } else {
            return SweCore.ObjectHouse(
                    oSx: partSize / 1.5,
                    oSy: partSize,
                    oPx: offset.offX,
                    oPy: offset.offY)
        }
    }


    public func bodie(bodie: Bodies, swTransit: Bool) -> SweCore.ObjectBodie {
        let planetSize = (((BODIE_SIZE * ZODIAC_RATIO) / 100.0) * Double(size)) / 100.0;
        var swRetrograde = false
        if (!swTransit) {
            // natal
            for b in swec.bodiesNatal {
                if b.bodie == bodie.rawValue {
                    if abs(b.calc_ut.speed_longitude) < 0.0003 {
                        // Stationary
                    } else if b.calc_ut.speed_longitude > 0.0 {
                        // Direct
                    } else {
                        swRetrograde = true
                    }
                }
            }
        } else {
            // transit
            for b in swec.bodiesTransit {
                if b.bodie == bodie.rawValue {
                    if abs(b.calc_ut.speed_longitude) < 0.0003 {
                        // Stationary
                    } else if b.calc_ut.speed_longitude > 0.0 {
                        // Direct
                    } else {
                        swRetrograde = true
                    }
                }
            }
        }

        var pos = 0.0
        if (!swTransit) {
            // natal
            for b in swec.bodiesNatal {
                if b.bodie == bodie.rawValue {
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                }
            }
        } else {
            // transit
            for b in swec.bodiesTransit {
                if b.bodie == bodie.rawValue {
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                }
            }
        }
        let offset: SweCore.Offset
        if swTransit {
            offset = getCenterItem(
                    size: planetSize,
                    offset: getPosTrigo(
                            angular: pos,
                            radiusCircle: getRadiusCircle(occurs: 9).0))
        } else {
            offset = getCenterItem(
                    size: planetSize,
                    offset: getPosTrigo(
                            angular: pos,
                            radiusCircle: getRadiusCircle(occurs: 5).0))
        }
        let res = SweCore.ObjectBodie(
                swRetrograde: swRetrograde,
                oSx: planetSize,
                oSy: planetSize,
                oPx: offset.offX,
                oPy: offset.offY)
        return res
    }

    public func bodie_lines(bodie: SweCore.Bodies, swTransit: Bool) -> [SweCore.AstroLine] {
        var res: [SweCore.AstroLine] = []
        var pos = 0.0
        if (!swTransit) {
            // natal
            for b in swec.bodiesNatal {
                if (b.bodie == bodie.rawValue) {
                    var axy: [SweCore.Offset]
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                    axy =
                            getLineTrigo(
                                    angular: pos,
                                    radiusCircleBegin: getRadiusCircle(occurs: 3).0,
                                    radiusCircleEnd: getRadiusCircle(occurs: 7).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                    axy = getLineTrigo(
                            angular: pos,
                            radiusCircleBegin: getRadiusCircle(occurs: 7).0,
                            radiusCircleEnd: getRadiusCircle(occurs: 8).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                }
            }
        } else {
            // transit
            for b in swec.bodiesTransit {
                if (b.bodie == bodie.rawValue) {
                    var axy: [SweCore.Offset]
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                    axy =
                            getLineTrigo(
                                    angular: pos,
                                    radiusCircleBegin: getRadiusCircle(occurs: 1).0,
                                    radiusCircleEnd: getRadiusCircle(occurs: 10).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                    axy = getLineTrigo(
                            angular: pos,
                            radiusCircleBegin: getRadiusCircle(occurs: 10).0,
                            radiusCircleEnd: getRadiusCircle(occurs: 11).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                }
            }
        }
        return res
    }

    public func partSecondaireBodieLines(bodie: SweCore.Bodies, swTransit: Bool) -> [SweCore.AstroLine] {
        var res: [SweCore.AstroLine] = []
        var pos = 0.0
        if (!swTransit) {
            // natal
            for b in swec.bodiesNatal {
                if (b.bodie == bodie.rawValue) {
                    var axy: [SweCore.Offset]
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                    axy =
                            getLineTrigo(
                                    angular: pos,
                                    radiusCircleBegin: partSecondaireGetRadiusCircle(occurs: 2).0,
                                    radiusCircleEnd: partSecondaireGetRadiusCircle(occurs: 7).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                    axy = getLineTrigo(
                            angular: pos,
                            radiusCircleBegin: partSecondaireGetRadiusCircle(occurs: 7).0,
                            radiusCircleEnd: partSecondaireGetRadiusCircle(occurs: 8).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                }
            }
        } else {
            // transit
            for b in swec.bodiesTransit {
                if (b.bodie == bodie.rawValue) {
                    var axy: [SweCore.Offset]
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                    axy =
                            getLineTrigo(
                                    angular: pos,
                                    radiusCircleBegin: partSecondaireGetRadiusCircle(occurs: 1).0,
                                    radiusCircleEnd: partSecondaireGetRadiusCircle(occurs: 10).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                    axy = getLineTrigo(
                            angular: pos,
                            radiusCircleBegin: partSecondaireGetRadiusCircle(occurs: 10).0,
                            radiusCircleEnd: partSecondaireGetRadiusCircle(occurs: 11).0)
                    res.append(SweCore.AstroLine(
                            lX1: axy[0].offX,
                            lY1: axy[0].offY,
                            lX2: axy[1].offX,
                            lY2: axy[1].offY)
                    )
                }
            }
        }
        return res
    }

    public func angle(a: SweCore.Angles) -> SweCore.ObjectAngle {
        var angleRatio = ANGLE_RATIO_DESC
        if (a == .Asc) {
            angleRatio = ANGLE_RATIO_ASC
        } else if (a == .Mc) {
            angleRatio = ANGLE_RATIO_MC
        } else if (a == .Fc) {
            angleRatio = ANGLE_RATIO_FC
        }
        let angleSize = (((ANGLE_SIZE * angleRatio) / 100.0) * Double(size)) / 100.0

        let pos = getAngleLongitude(angle: a)
        let offAngle = getCenterItem(
                size: angleSize,
                offset: getPosTrigo(
                        angular: pos,
                        radiusCircle: getRadiusCircle(occurs: 5).0))
        let res = SweCore.ObjectAngle(
                oSx: angleSize,
                oSy: angleSize,
                oPx: offAngle.offX,
                oPy: offAngle.offY)
        return res
    }

    public func angleLines(angle: SweCore.Angles) -> [SweCore.AstroLine] {
        var res: [SweCore.AstroLine] = []
        var pos: Double = 0.0
        var axyLine: [SweCore.Offset] = []
        switch (angle) {
        case .Asc:
            pos = getAngleLongitude(angle: angle)
            axyLine = getLineTrigo(
                    angular: pos,
                    radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                    radiusCircleEnd: getRadiusCircle(occurs: 8).0)
            res.append(SweCore.AstroLine(
                    lX1: axyLine[0].offX,
                    lY1: axyLine[0].offY,
                    lX2: axyLine[1].offX,
                    lY2: axyLine[1].offY))
            break;
        case .Fc:
            pos = getAngleLongitude(angle: angle)
            axyLine = getLineTrigo(
                    angular: pos,
                    radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                    radiusCircleEnd: getRadiusCircle(occurs: 8).0)
            res.append(SweCore.AstroLine(
                    lX1: axyLine[0].offX,
                    lY1: axyLine[0].offY,
                    lX2: axyLine[1].offX,
                    lY2: axyLine[1].offY))
            break;
        case .Desc:
            pos = getAngleLongitude(angle: angle)
            axyLine = getLineTrigo(
                    angular: pos,
                    radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                    radiusCircleEnd: getRadiusCircle(occurs: 8).0)
            res.append(SweCore.AstroLine(
                    lX1: axyLine[0].offX,
                    lY1: axyLine[0].offY,
                    lX2: axyLine[1].offX,
                    lY2: axyLine[1].offY))
            break;
        case .Mc:
            pos = getAngleLongitude(angle: angle)
            axyLine = getLineTrigo(
                    angular: pos,
                    radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                    radiusCircleEnd: getRadiusCircle(occurs: 8).0)
            res.append(SweCore.AstroLine(
                    lX1: axyLine[0].offX,
                    lY1: axyLine[0].offY,
                    lX2: axyLine[1].offX,
                    lY2: axyLine[1].offY))
            break;
        default:
            break;
        }
        return res
    }

    public func houseLines() -> [SweCore.AstroHouseLine] {
        var res: [SweCore.AstroHouseLine] = []
        for iIdx in 0...11 {
            let offHouse = 360.0 - swec.houses[0].longitude
            let pos = getFixedPos(pos_value: offHouse + swec.houses[iIdx].longitude)
            var axyTriangle: [SweCore.Offset] = []
            let angularPointer = ANGULAR_POINTER
            if swec.houses[iIdx].angle == SweCore.Angles.Nothing.rawValue {
                axyTriangle = getTriangleTrigo(
                        angular: pos,
                        angularPointer: angularPointer,
                        radiusCircleBegin: getRadiusInsideCircleHouseForPointerBottom(),
                        radiusCircleEnd: getRadiusInsideCircleHouseForPointerTop())
                let axyLine: [SweCore.Offset] = getLineTrigo(
                        angular: pos,
                        radiusCircleBegin: getRadiusCircle(occurs: 3).0,
                        radiusCircleEnd: getRadiusCircle(occurs: 2).0)
                res.append(SweCore.AstroHouseLine(
                        lX1: axyLine[0].offX,
                        lY1: axyLine[0].offY,
                        lX2: axyLine[1].offX,
                        lY2: axyLine[1].offY,
                        lXY3: false,
                        lX3: 0.0,
                        lY3: 0.0)
                )
            } else {
                axyTriangle = getTriangleTrigo(
                        angular: pos,
                        angularPointer: angularPointer,
                        radiusCircleBegin: getRadiusCircle(occurs: 3).0,
                        radiusCircleEnd: getRadiusCircle(occurs: 2).0)
            }
            res.append(SweCore.AstroHouseLine(
                    lX1: axyTriangle[0].offX,
                    lY1: axyTriangle[0].offY,
                    lX2: axyTriangle[1].offX,
                    lY2: axyTriangle[1].offY,
                    lXY3: true,
                    lX3: axyTriangle[2].offX,
                    lY3: axyTriangle[2].offY)
            )
        }
        return res
    }

    public func partSecondaireLines() -> [SweCore.AstroHouseLine] {
        var res: [SweCore.AstroHouseLine] = []
        for iIdx in 0...11 {
            let offHouse = 30.0 * Double(iIdx)
            let pos = getFixedPos(pos_value: offHouse + swec.partSecondaire[0].calc_ut.longitude)
            var axyTriangle: [SweCore.Offset] = []
            let angularPointer = ANGULAR_POINTER
            axyTriangle = getTriangleTrigo(
                    angular: pos,
                    angularPointer: angularPointer,
                    radiusCircleBegin: getRadiusInsideCircleHouseForPointerBottom(),
                    radiusCircleEnd: getRadiusInsideCircleHouseForPointerTop())
            let axyLine: [SweCore.Offset] = getLineTrigo(
                    angular: pos,
                    radiusCircleBegin: getRadiusCircle(occurs: 8).0,
                    radiusCircleEnd: getRadiusCircle(occurs: 3).0)
            res.append(SweCore.AstroHouseLine(
                    lX1: axyLine[0].offX,
                    lY1: axyLine[0].offY,
                    lX2: axyLine[1].offX,
                    lY2: axyLine[1].offY,
                    lXY3: false,
                    lX3: 0.0,
                    lY3: 0.0)
            )
            res.append(SweCore.AstroHouseLine(
                    lX1: axyTriangle[0].offX,
                    lY1: axyTriangle[0].offY,
                    lX2: axyTriangle[1].offX,
                    lY2: axyTriangle[1].offY,
                    lXY3: false,
                    lX3: 0.0,
                    lY3: 0.0)
            )
        }
        return res
    }

    public func bodieSign(bodie: SweCore.Bodies, swTransit: Bool) -> Int {
        var res = 1
        if (!swTransit) {
            // Natal
            for b in swec.bodiesNatal {
                if b.bodie == bodie.rawValue {
                    for s in 1...12 {
                        var pos = Double(s - 1) * 30.0
                        if pos > 360 {
                            pos = 360 - pos
                        }
                        if b.calc_ut.longitude >= pos && b.calc_ut.longitude <= pos + 30 {
                            res = s
                            break
                        }
                    }
                }
            }
        } else {
            // Transit
            for b in swec.bodiesTransit {
                if b.bodie == bodie.rawValue {
                    for s in 1...12 {
                        var pos = Double(s - 1) * 30.0
                        if pos > 360 {
                            pos = 360 - pos
                        }
                        if b.calc_ut.longitude >= pos && b.calc_ut.longitude <= pos + 30 {
                            res = s
                            break
                        }
                    }
                }
            }
        }
        return res
    }

    public func bodieDegMinSec(bodie: SweCore.Bodies, swTransit: Bool) -> (Int32, Int32, Int32) {
        var deg: Int32 = 0
        var min: Int32 = 0
        var sec: Int32 = 0
        if (!swTransit) {
            // Natal
            for b in swec.bodiesNatal {
                if b.bodie == bodie.rawValue {
                    deg = b.calc_ut.split.deg
                    min = b.calc_ut.split.min
                    sec = b.calc_ut.split.sec
                }
            }
        } else {
            // Transit
            for b in swec.bodiesTransit {
                if b.bodie == bodie.rawValue {
                    deg = b.calc_ut.split.deg
                    min = b.calc_ut.split.min
                    sec = b.calc_ut.split.sec
                }
            }
        }
        return (deg, min, sec)
    }

    public func aspectLines(swBodies: [Bool], aspect: SweCore.Aspects, aspectType: SweCore.AspectType) -> [SweCore.AspectLine] {
        var res: [AspectLine] = []
        for (i, bodie) in bodiesForLoop.enumerated() {
            if swBodies[i] {
                var bodNatalLongitude = 0.0
                var bodTransitLongitude = 0.0
                for b in swec.bodiesNatal {
                    if b.bodie == bodie.rawValue {
                        bodNatalLongitude = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                    }
                }
                for b in swec.bodiesTransit {
                    if b.bodie == bodie.rawValue {
                        bodTransitLongitude = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                    }
                }
                switch aspectType {
                case .NatalAndTransit:
                    let separation = getClosestDistance(angle1: bodNatalLongitude, angle2: bodTransitLongitude)
                    let absSeparation = abs(separation)
                    let asp = aspect.angle().0
                    let orb = aspect.angle().1
                    if abs(absSeparation - Double(asp)) <= Double(orb) {
                        let pos1 = getPosTrigo(angular: bodNatalLongitude, radiusCircle: getRadiusCircle(occurs: 0).0)
                        let pos2 = getPosTrigo(angular: bodTransitLongitude, radiusCircle: getRadiusCircle(occurs: 0).0)
                        let line: AspectLine = AspectLine(
                                aspect: aspect,
                                lX1: pos1.offX,
                                lY1: pos1.offY,
                                lX2: pos2.offX,
                                lY2: pos2.offY)
                        res.append(line)
                        // angle
                        let angleArray: [SweCore.Angles] = [.Asc, .Mc]
                        for angle in angleArray {
                            let angleLongitude = getAngleLongitude(angle: angle)
                            let separation = getClosestDistance(
                                    angle1: bodTransitLongitude,
                                    angle2: angleLongitude)
                            let absSeparation = abs(separation)
                            let asp = aspect.angle().0
                            let orb = aspect.angle().1
                            if abs(absSeparation - Double(asp)) <= Double(orb) {
                                let pos1: Offset = getPosTrigo(
                                        angular: bodTransitLongitude,
                                        radiusCircle: getRadiusCircle(occurs: 0).0)
                                let pos2: Offset = getPosTrigo(
                                        angular: angleLongitude,
                                        radiusCircle: getRadiusCircle(occurs: 0).0)
                                let line: AspectLine = AspectLine(
                                        aspect: aspect,
                                        lX1: pos1.offX,
                                        lY1: pos1.offY,
                                        lX2: pos2.offX,
                                        lY2: pos2.offY)
                                res.append(line)
                            }
                        }
                    }
                    break
                case .Natal:
                    for (j, bodPair) in bodiesForLoop.enumerated() {
                        //if bodie.rawValue == SweCore.Bodies.Jupiter.rawValue && bodPair.rawValue == SweCore.Bodies.Saturn.rawValue {
                            // debug
                        //}
                        if swBodies[j] && bodPair != bodie {
                            var bod2NatalLongitude = 0.0
                            for b in swec.bodiesNatal {
                                if b.bodie == bodPair.rawValue {
                                    bod2NatalLongitude = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                                }
                            }
                            let separation = getClosestDistance(
                                    angle1: bodNatalLongitude,
                                    angle2: bod2NatalLongitude)
                            let absSeparation = abs(separation)
                            let asp = aspect.angle().0
                            let orb = aspect.angle().1
                            if abs(absSeparation - Double(asp)) <= Double(orb) {
                                let pos1: Offset = getPosTrigo(
                                        angular: bodNatalLongitude,
                                        radiusCircle: getRadiusCircle(occurs: 0).0)
                                let pos2: Offset = getPosTrigo(
                                        angular: bod2NatalLongitude,
                                        radiusCircle: getRadiusCircle(occurs: 0).0)
                                let line: AspectLine = AspectLine(
                                        aspect: aspect,
                                        lX1: pos1.offX,
                                        lY1: pos1.offY,
                                        lX2: pos2.offX,
                                        lY2: pos2.offY)
                                res.append(line)
                            }
                            // angle
                            let angleArray: [SweCore.Angles] = [.Asc, .Mc]
                            for angle in angleArray {
                                let angleLongitude = getAngleLongitude(angle: angle)
                                let separation = getClosestDistance(
                                        angle1: bodNatalLongitude,
                                        angle2: angleLongitude)
                                let absSeparation = abs(separation)
                                let asp = aspect.angle().0
                                let orb = aspect.angle().1
                                if abs(absSeparation - Double(asp)) <= Double(orb) {
                                    let pos1: Offset = getPosTrigo(
                                            angular: bodNatalLongitude,
                                            radiusCircle: getRadiusCircle(occurs: 0).0)
                                    let pos2: Offset = getPosTrigo(
                                            angular: angleLongitude,
                                            radiusCircle: getRadiusCircle(occurs: 0).0)
                                    let line: AspectLine = AspectLine(
                                            aspect: aspect,
                                            lX1: pos1.offX,
                                            lY1: pos1.offY,
                                            lX2: pos2.offX,
                                            lY2: pos2.offY)
                                    res.append(line)
                                }
                            }
                        }
                    }
                    break
                case .Transit:
                    for (j, bodPair) in bodiesForLoop.enumerated() {
                        if swBodies[j] && bodPair != bodie {
                            var bod2TransitLongitude = 0.0
                            for b in swec.bodiesTransit {
                                if b.bodie == bodPair.rawValue {
                                    bod2TransitLongitude = getBodieLongitude(bodie_longitude: b.calc_ut.longitude)
                                }
                            }
                            let separation = getClosestDistance(
                                    angle1: bodTransitLongitude,
                                    angle2: bod2TransitLongitude)
                            let absSeparation = abs(separation)
                            let asp = aspect.angle().0
                            let orb = aspect.angle().1
                            if abs(absSeparation - Double(asp)) <= Double(orb) {
                                let pos1: Offset = getPosTrigo(
                                        angular: bodTransitLongitude,
                                        radiusCircle: getRadiusCircle(occurs: 0).0)
                                let pos2: Offset = getPosTrigo(
                                        angular: bod2TransitLongitude,
                                        radiusCircle: getRadiusCircle(occurs: 0).0)
                                let line: AspectLine = AspectLine(
                                        aspect: aspect,
                                        lX1: pos1.offX,
                                        lY1: pos1.offY,
                                        lX2: pos2.offX,
                                        lY2: pos2.offY)
                                res.append(line)
                            }
                        }
                    }
                    break
                }
            }
        }
        return res
    }

    public static func bodieArrBoolForLoop() -> [Bool] {
        [
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            true,
            false,
            false,
            false,
        ]
    }

    private func getRadiusTotal() -> Double {
        Double(size) / 2.0
    }

    private func getRadiusCircle(occurs: Int) -> (Double, Bool) {
        let res = getRadiusTotal() * CIRCLE_SIZE_TRANSIT[occurs].0 / 100
        return (res, CIRCLE_SIZE_TRANSIT[occurs].1)
    }

    private func partSecondaireGetRadiusCircle(occurs: Int) -> (Double, Bool) {
        let res = getRadiusTotal() * PART_SECONDAIRE_CIRCLE_SIZE_TRANSIT[occurs].0 / 100
        return (res, PART_SECONDAIRE_CIRCLE_SIZE_TRANSIT[occurs].1)
    }

    private func getFixedPos(pos_value: Double) -> Double {
        var pos = pos_value
        var done = false
        while !done {
            if pos >= 360.0 {
                pos = pos - 360.0
            }
            if pos >= 360 {

            } else {
                done = true
            }
        }
        return pos
    }

    private func getLineTrigo(angular: Double, radiusCircleBegin: Double, radiusCircleEnd: Double) -> [SweCore.Offset] {
        var res: [SweCore.Offset] = []
        let dx1: Double = getCenter().offX
                + cos(angular / CIRCLE * 2.0 * Double.pi)
                * -1.0
                * radiusCircleBegin
        let dx2: Double = getCenter().offY
                + sin(angular / CIRCLE * 2.0 * Double.pi)
                * radiusCircleBegin
        let dy1: Double = getCenter().offX
                + cos(angular / CIRCLE * 2.0 * Double.pi)
                * -1.0
                * radiusCircleEnd
        let dy2: Double = getCenter().offY
                + sin(angular / CIRCLE * 2.0 * Double.pi)
                * radiusCircleEnd
        res.append(Offset(offX: dx1, offY: dx2))
        res.append(Offset(offX: dy1, offY: dy2))
        return res
    }

    private func getRadiusRulesInsideCircle(largerDrawLine: SweCore.LargerDrawLine) -> Double {
        var size = 0.0
        switch largerDrawLine {
        case .Small:
            size = 1.0 + LARGER_DRAW_LINE_RULES_SMALL
        case .Large:
            size = 1.0 + LARGER_DRAW_LINE_RULES_LARGE
        }
        return getRadiusTotal() * (((CIRCLE_SIZE_TRANSIT[2].0 - CIRCLE_SIZE_TRANSIT[1].0) / size)
                + CIRCLE_SIZE_TRANSIT[1].0) / 100.0
    }


    private func getCenter() -> SweCore.Offset {
        SweCore.Offset(offX: getRadiusTotal(), offY: getRadiusTotal())
    }

    private func getCenterItem(size: Double, offset: SweCore.Offset) -> SweCore.Offset {
        SweCore.Offset(
                offX: offset.offX - (size / 2.0),
                offY: offset.offY - (size / 2.0))
    }

    private func getPosTrigo(angular: Double, radiusCircle: Double) -> SweCore.Offset {
        let getCenter = getRadiusTotal()
        return SweCore.Offset(
                offX: getCenter + cos(angular / CIRCLE * 2.0 * Double.pi) * -1.0 * radiusCircle,
                offY: getCenter + sin(angular / CIRCLE * 2.0 * Double.pi) * radiusCircle)
    }

    private func getRadiusCircleZodiac() -> Double {
        let divTraitBig = 0.2
        return (getRadiusTotal() * (
                (
                        (CIRCLE_SIZE_TRANSIT[2].0 - CIRCLE_SIZE_TRANSIT[1].0) / (2.0 + divTraitBig)
                ) + CIRCLE_SIZE_TRANSIT[1].0))
                / 100.0
    }

    private func getRadiusInsideCircleHouseForPointerBottom() -> Double {
        let divTraitPointer = DIV_TRAIT_POINTER
        return (getRadiusTotal() * (((CIRCLE_SIZE_TRANSIT[3].0 - CIRCLE_SIZE_TRANSIT[2].0)
                / divTraitPointer)
                - CIRCLE_SIZE_TRANSIT[3].0)) / 100.0
    }

    private func getRadiusInsideCircleHouseForPointerTop() -> Double {
        (getRadiusTotal() * ((CIRCLE_SIZE_TRANSIT[3].0 - CIRCLE_SIZE_TRANSIT[2].0)
                - CIRCLE_SIZE_TRANSIT[3].0)) / 100.0
    }

    private func getTriangleTrigo(angular: Double, angularPointer: Double, radiusCircleBegin: Double, radiusCircleEnd: Double) -> [SweCore.Offset] {
        var res: [SweCore.Offset] = []
        let angular1 = getFixedPos(pos_value: angular - angularPointer)
        let angular2 = getFixedPos(pos_value: angular + angularPointer)
        let dx1: Double = getCenter().offX
                + cos(angular1 / CIRCLE * 2.0 * Double.pi)
                * -1.0
                * radiusCircleBegin
        let dy1: Double = getCenter().offY
                + sin(angular1 / CIRCLE * 2.0 * Double.pi)
                * radiusCircleBegin
        let dx2: Double = getCenter().offX
                + cos(angular2 / CIRCLE * 2.0 * Double.pi)
                * -1.0
                * radiusCircleBegin
        let dy2: Double = getCenter().offY
                + sin(angular2 / CIRCLE * 2.0 * Double.pi)
                * radiusCircleBegin
        let dx3: Double = getCenter().offX
                + cos(angular / CIRCLE * 2.0 * Double.pi)
                * -1.0
                * radiusCircleEnd
        let dy3: Double = getCenter().offY
                + sin(angular / CIRCLE * 2.0 * Double.pi)
                * radiusCircleEnd
        res.append(SweCore.Offset(offX: dx1, offY: dy1))
        res.append(SweCore.Offset(offX: dx2, offY: dy2))
        res.append(SweCore.Offset(offX: dx3, offY: dy3))
        return res
    }

    private func getRadiusCircleHouse() -> Double {
        (getRadiusTotal() * (((
                (CIRCLE_SIZE_TRANSIT[3].0 - CIRCLE_SIZE_TRANSIT[2].0) / 2.0))
                + CIRCLE_SIZE_TRANSIT[2].0))
                / 100.0
    }

    private func getRadiusCirclePartSecondaire() -> Double {
        (getRadiusTotal() * (((
                (PART_SECONDAIRE_CIRCLE_SIZE_TRANSIT[7].0 - PART_SECONDAIRE_CIRCLE_SIZE_TRANSIT[3].0)))
                + PART_SECONDAIRE_CIRCLE_SIZE_TRANSIT[2].0))
                / 100.0
    }

    private func getBodieLongitude(bodie_longitude: Double) -> Double {
        var pos = 0.0
        pos = CIRCLE - swec.houses[0].longitude + bodie_longitude
        pos = getFixedPos(pos_value: pos)
        return pos
    }

    private func getAngleLongitude(angle: SweCore.Angles) -> Double {
        var pos = 0.0
        for house in swec.houses {
            if house.angle == angle.rawValue {
                pos = CIRCLE - swec.houses[0].longitude + house.longitude
                break
            }
        }
        pos = getFixedPos(pos_value: pos)
        return pos
    }

    private func getClosestDistance(angle1: Double, angle2: Double) -> Double {
        getZnorm(angle: angle2 - angle1)
    }

    private func getZnorm(angle: Double) -> Double {
        let ang = Int(angle) % Int(CIRCLE)
        //let ang = Int(angle) % Int(CIRCLE)
        if Double(ang) <= (CIRCLE / 2.0) {
            return Double(ang)
        } else {
            return Double(ang) - CIRCLE
        }
    }
}

extension SweCore.Aspects {
    // Return property (angle, orbe)
    func angle() -> (Int32, Int32) {
        switch self {
        case .Conjunction:
            return (0, 10)
        case .Opposition:
            return (180, 8)
        case .Trine:
            return (120, 7)
        case .Square:
            return (90, 6)
        case .Sextile:
            return (60, 5)
        case .Inconjunction:
            return (150, 2)
        case .Sequisquare:
            return (135, 1)
        case .Semisquare:
            return (45, 1)
        case .Semisextile:
            return (30, 1)
        case .Nothing:
            return (0,0)
        }
    }

    // Return if maj

    func maj() -> Bool {
        switch self {
        case .Conjunction:
            return true
        case .Opposition:
            return true
        case .Trine:
            return true
        case .Square:
            return true
        case .Sextile:
            return true
        default:
            return false
        }
    }

    // Return text

    func text() -> String {
        switch self {
        case .Conjunction:
            return "Conjonction"
        case .Opposition:
            return "Opposition"
        case .Trine:
            return "Trigone"
        case .Square:
            return "Quadrature"
        case .Sextile:
            return "Sextile"
        case .Inconjunction:
            return "Quinconce"
        case .Sequisquare:
            return "Sesqui-carré"
        case .Semisquare:
            return "Demi-carré"
        case .Semisextile:
            return "Demi-sextile"
        default:
            return ""
        }
    }

    func color() -> SwiftUI.Color {
        switch self {
        case .Conjunction:
            return .red
        case .Opposition:
            return .red
        case .Trine:
            return .blue
        case .Square:
            return .red
        case .Sextile:
            return .blue
        case .Inconjunction:
            return .green
        case .Sequisquare:
            return .indigo
        case .Semisquare:
            return .indigo
        case .Semisextile:
            return .green
        case .Nothing:
            return .black
        }
    }

    func style() -> StrokeStyle {
        var stroke = StrokeStyle.init(lineWidth: 0.5)
        switch self {
        case .Sequisquare:
            stroke.dash = [7]
        case .Semisquare:
            stroke.dash = [7]
        case .Semisextile:
            stroke.dash = [7]
        default:
            return stroke
        }
        return stroke
    }
}

public class TextCore {
    public enum L {
        case F, E
    }

    public var langue : L

    public enum LEData: String {
        case F = "Données",
             E = "Datas"
    }

    public enum LELocalisation: String {
        case F = "Coordonnées",
             E = "Localisation"
    }

    public enum LEBirthDate: String {
        case F = "Date de naissance",
             E = "Birthdate"
    }

    public enum LEFirstName: String {
        case F = "Prénom",
             E = "First Name"
    }

    public enum LESecondName: String {
        case F = "2ème prénom",
             E = "Second Name"
    }

    public enum LEThirdName: String {
        case F = "3ème prénom",
             E = "Third Name"
    }

    public enum LELastName: String {
        case F = "Nom de famille",
             E = "Last Name"
    }

    public enum LELastNameAux: String {
        case F = "Nom de famille aux.",
             E = "Last Name Aux."
    }

    public enum LENumerologie: String {
        case F = "Numerologie",
             E = "Numerology"
    }

    public enum LEBorn: String {
        case F = "La naissance",
             E = "Born"
    }

    public enum LEAge: String {
        case F = "L'age",
             E = "Age"
    }

    public enum LELifePath: String {
        case F = "Le chemin de vie",
             E = "The life path"
    }

    public enum LENumber: String {
        case F = "Nombre",
             E = "Number"
    }

    public enum LECycleRealisation: String {
        case F = "Cycle de réalisation",
             E = "Realisation cycle"
    }

    public enum LECycleRealisation1JM: String {
        case F = "0 à 35 ans",
             E = "0 to 35 year"
    }

    public enum LECycleRealisation2JM: String {
        case F = "0 à 34 ans",
             E = "0 to 34 year"
    }

    public enum LECycleRealisation3JM: String {
        case F = "0 à 33 ans",
             E = "0 to 33 year"
    }

    public enum LECycleRealisation4JM: String {
        case F = "0 à 32 ans",
             E = "0 to 32 year"
    }

    public enum LECycleRealisation5JM: String {
        case F = "0 à 31 ans",
             E = "0 to 31 year"
    }

    public enum LECycleRealisation6JM: String {
        case F = "0 à 30 ans",
             E = "0 to 30 year"
    }

    public enum LECycleRealisation7JM: String {
        case F = "0 à 29 ans",
             E = "0 to 29 year"
    }

    public enum LECycleRealisation8JM: String {
        case F = "0 à 28 ans",
             E = "0 to 28 year"
    }

    public enum LECycleRealisation9JM: String {
        case F = "0 à 27 ans",
             E = "0 to 27 year"
    }

    public enum LECycleRealisation1JA: String {
        case F = "35 à 44 ans",
             E = "35 to 44 year"
    }

    public enum LECycleRealisation2JA: String {
        case F = "34 à 43 ans",
             E = "34 to 43 year"
    }

    public enum LECycleRealisation3JA: String {
        case F = "33 à 42 ans",
             E = "33 to 42 year"
    }

    public enum LECycleRealisation4JA: String {
        case F = "32 à 41 ans",
             E = "32 to 41 year"
    }

    public enum LECycleRealisation5JA: String {
        case F = "31 à 40 ans",
             E = "31 to 40 year"
    }

    public enum LECycleRealisation6JA: String {
        case F = "30 à 39 ans",
             E = "30 to 39 year"
    }

    public enum LECycleRealisation7JA: String {
        case F = "29 à 38 ans",
             E = "29 to 38 year"
    }

    public enum LECycleRealisation8JA: String {
        case F = "28 à 37 ans",
             E = "28 to 37 year"
    }

    public enum LECycleRealisation9JA: String {
        case F = "27 à 36 ans",
             E = "27 to 36 year"
    }

    public enum LECycleRealisation112: String {
        case F = "44 à 53 ans",
             E = "44 to 53 year"
    }

    public enum LECycleRealisation212: String {
        case F = "43 à 52 ans",
             E = "43 to 52 year"
    }

    public enum LECycleRealisation312: String {
        case F = "42 à 51 ans",
             E = "42 to 51 year"
    }

    public enum LECycleRealisation412: String {
        case F = "41 à 50 ans",
             E = "41 to 50 year"
    }

    public enum LECycleRealisation512: String {
        case F = "40 à 49 ans",
             E = "40 to 49 year"
    }

    public enum LECycleRealisation612: String {
        case F = "39 to 48 ans",
             E = "39 to 48 year"
    }

    public enum LECycleRealisation712: String {
        case F = "38 to 47 ans",
             E = "38 to 47 year"
    }

    public enum LECycleRealisation812: String {
        case F = "37 to 46 ans",
             E = "37 to 46 year"
    }

    public enum LECycleRealisation912: String {
        case F = "36 to 45 ans",
             E = "36 to 45 year"
    }

    public enum LECycleRealisation1MA: String {
        case F = "dès 53 ans",
             E = "> 53 year"
    }

    public enum LECycleRealisation2MA: String {
        case F = "dès 52 ans",
             E = "> 52 year"
    }

    public enum LECycleRealisation3MA: String {
        case F = "dès 51 ans",
             E = "> 51 year"
    }

    public enum LECycleRealisation4MA: String {
        case F = "dès 50 ans",
             E = "> 50 year"
    }

    public enum LECycleRealisation5MA: String {
        case F = "dès 49 ans",
             E = "> 49 year"
    }

    public enum LECycleRealisation6MA: String {
        case F = "dès 48 ans",
             E = "> 48 year"
    }

    public enum LECycleRealisation7MA: String {
        case F = "dès 47 ans",
             E = "> 47 year"
    }

    public enum LECycleRealisation8MA: String {
        case F = "dès 46 ans",
             E = "> 46 year"
    }

    public enum LECycleRealisation9MA: String {
        case F = "dès 45 ans",
             E = "> 45 year"
    }

    public enum ECycleRealisation {
        case JplusM, JplusA, UnplusDeux, MplusA
    }

    public enum LECycleUniversels: String {
        case F = "Cycle universels",
             E = "Universal Cycle"
    }

    public enum LEAgeDe: String {
        case F = "Age de/à",
             E = "Age to/bis"
    }

    public enum LECycleUniversel1: String {
        case F = "0 à 9 ans",
             E = "0 to 9 year"
    }

    public enum LECycleUniversel2: String {
        case F = "9 à 18 ans",
             E = "9 to 18 year"
    }

    public enum LECycleUniversel3: String {
        case F = "18 à 27 ans",
             E = "18 to 27 year"
    }

    public enum LECycleUniversel4: String {
        case F = "27 à 36 ans",
             E = "27 to 36 year"
    }

    public enum LECycleUniversel5: String {
        case F = "36 à 45 ans",
             E = "36 to 45 year"
    }

    public enum LECycleUniversel6: String {
        case F = "45 à 54 ans",
             E = "45 to 54 year"
    }

    public enum LECycleUniversel7: String {
        case F = "54 à 63 ans",
             E = "54 to 63 year"
    }

    public enum LECycleUniversel8: String {
        case F = "63 à 72 ans",
             E = "63 to 72 year"
    }

    public enum LECycleUniversel9: String {
        case F = "72 à 81 ans",
             E = "72 to 81 year"
    }

    public init(langue: L) {
        self.langue = langue
    }

    public func data() -> String {
        switch langue {
        case .F:
            return LEData.F.rawValue
        case .E:
            return LEData.E.rawValue
        }
    }

    public func localisation() -> String {
        switch langue {
        case .F:
            return LELocalisation.F.rawValue
        case .E:
            return LELocalisation.E.rawValue
        }
    }

    public func birthDate() -> String {
        switch langue {
        case .F:
            return LEBirthDate.F.rawValue
        case .E:
            return LEBirthDate.E.rawValue
        }
    }

    public func firstName() -> String {
        switch langue {
        case .F:
            return LEFirstName.F.rawValue
        case .E:
            return LEFirstName.E.rawValue
        }
    }

    public func secondName() -> String {
        switch langue {
        case .F:
            return LESecondName.F.rawValue
        case .E:
            return LESecondName.E.rawValue
        }
    }

    public func thirdName() -> String {
        switch langue {
        case .F:
            return LEThirdName.F.rawValue
        case .E:
            return LEThirdName.E.rawValue
        }
    }

    public func lastName() -> String {
        switch langue {
        case .F:
            return LELastName.F.rawValue
        case .E:
            return LELastName.E.rawValue
        }
    }

    public func lastNameAux() -> String {
        switch langue {
        case .F:
            return LELastNameAux.F.rawValue
        case .E:
            return LELastNameAux.E.rawValue
        }
    }

    public func latitude() -> String {
        switch langue {
        case .F:
            return "Latitude"
        case .E:
            return "Latitude"
        }
    }

    public func longitude() -> String {
        switch langue {
        case .F:
            return "Longitude"
        case .E:
            return "Longitude"
        }
    }

    public func numerologie() -> String {
        switch langue {
        case .F:
            return LENumerologie.F.rawValue
        case .E:
            return LENumerologie.E.rawValue
        }
    }

    public func born() -> String {
        switch langue {
        case .F:
            return LEBorn.F.rawValue
        case .E:
            return LEBorn.E.rawValue
        }
    }

    public func age() -> String {
        switch langue {
        case .F:
            return LEAge.F.rawValue
        case .E:
            return LEAge.E.rawValue
        }
    }

    public func lifePath() -> String {
        switch langue {
        case .F:
            return LELifePath.F.rawValue
        case .E:
            return LELifePath.E.rawValue
        }
    }

    public func cycle() -> String {
        switch langue {
        case .F:
            return "Cycle"
        case .E:
            return "Cycle"
        }
    }

    public func calcul() -> String {
        switch langue {
        case .F:
            return "Calcul"
        case .E:
            return "Calcul"
        }
    }

    public func nombre() -> String {
        switch langue {
        case .F:
            return LENumber.F.rawValue
        case .E:
            return LENumber.E.rawValue
        }
    }

    public func cycleRealisation() -> String {
        switch langue {
        case .F:
            return LECycleRealisation.F.rawValue
        case .E:
            return LECycleRealisation.E.rawValue
        }
    }

    public func cycleRealisation(iLivePath: Int, eCycle: ECycleRealisation) -> String {
        switch eCycle {
        case .JplusM:
            switch iLivePath {
            case 1:
                switch langue {
                case .F:
                    return LECycleRealisation1JM.F.rawValue
                case .E:
                    return LECycleRealisation1JM.E.rawValue
                }
            case 2:
                switch langue {
                case .F:
                    return LECycleRealisation2JM.F.rawValue
                case .E:
                    return LECycleRealisation2JM.E.rawValue
                }
            case 3:
                switch langue {
                case .F:
                    return LECycleRealisation3JM.F.rawValue
                case .E:
                    return LECycleRealisation3JM.E.rawValue
                }
            case 4:
                switch langue {
                case .F:
                    return LECycleRealisation4JM.F.rawValue
                case .E:
                    return LECycleRealisation4JM.E.rawValue
                }
            case 5:
                switch langue {
                case .F:
                    return LECycleRealisation5JM.F.rawValue
                case .E:
                    return LECycleRealisation5JM.E.rawValue
                }
            case 6:
                switch langue {
                case .F:
                    return LECycleRealisation6JM.F.rawValue
                case .E:
                    return LECycleRealisation6JM.E.rawValue
                }
            case 7:
                switch langue {
                case .F:
                    return LECycleRealisation7JM.F.rawValue
                case .E:
                    return LECycleRealisation7JM.E.rawValue
                }
            case 8:
                switch langue {
                case .F:
                    return LECycleRealisation8JM.F.rawValue
                case .E:
                    return LECycleRealisation8JM.E.rawValue
                }
            case 9:
                switch langue {
                case .F:
                    return LECycleRealisation9JM.F.rawValue
                case .E:
                    return LECycleRealisation9JM.E.rawValue
                }
            default:
                switch langue {
                case .F:
                    return LECycleRealisation1JM.F.rawValue
                case .E:
                    return LECycleRealisation1JM.E.rawValue
                }
            }
        case .JplusA:
            switch iLivePath {
            case 1:
                switch langue {
                case .F:
                    return LECycleRealisation1JA.F.rawValue
                case .E:
                    return LECycleRealisation1JA.E.rawValue
                }
            case 2:
                switch langue {
                case .F:
                    return LECycleRealisation2JA.F.rawValue
                case .E:
                    return LECycleRealisation2JA.E.rawValue
                }
            case 3:
                switch langue {
                case .F:
                    return LECycleRealisation3JA.F.rawValue
                case .E:
                    return LECycleRealisation3JA.E.rawValue
                }
            case 4:
                switch langue {
                case .F:
                    return LECycleRealisation4JA.F.rawValue
                case .E:
                    return LECycleRealisation4JA.E.rawValue
                }
            case 5:
                switch langue {
                case .F:
                    return LECycleRealisation5JA.F.rawValue
                case .E:
                    return LECycleRealisation5JA.E.rawValue
                }
            case 6:
                switch langue {
                case .F:
                    return LECycleRealisation6JA.F.rawValue
                case .E:
                    return LECycleRealisation6JA.E.rawValue
                }
            case 7:
                switch langue {
                case .F:
                    return LECycleRealisation7JA.F.rawValue
                case .E:
                    return LECycleRealisation7JA.E.rawValue
                }
            case 8:
                switch langue {
                case .F:
                    return LECycleRealisation8JA.F.rawValue
                case .E:
                    return LECycleRealisation8JA.E.rawValue
                }
            case 9:
                switch langue {
                case .F:
                    return LECycleRealisation9JA.F.rawValue
                case .E:
                    return LECycleRealisation9JA.E.rawValue
                }
            default:
                switch langue {
                case .F:
                    return LECycleRealisation1JA.F.rawValue
                case .E:
                    return LECycleRealisation1JA.E.rawValue
                }
            }
        case .UnplusDeux:
            switch iLivePath {
            case 1:
                switch langue {
                case .F:
                    return LECycleRealisation112.F.rawValue
                case .E:
                    return LECycleRealisation112.E.rawValue
                }
            case 2:
                switch langue {
                case .F:
                    return LECycleRealisation212.F.rawValue
                case .E:
                    return LECycleRealisation212.E.rawValue
                }
            case 3:
                switch langue {
                case .F:
                    return LECycleRealisation312.F.rawValue
                case .E:
                    return LECycleRealisation312.E.rawValue
                }
            case 4:
                switch langue {
                case .F:
                    return LECycleRealisation412.F.rawValue
                case .E:
                    return LECycleRealisation412.E.rawValue
                }
            case 5:
                switch langue {
                case .F:
                    return LECycleRealisation512.F.rawValue
                case .E:
                    return LECycleRealisation512.E.rawValue
                }
            case 6:
                switch langue {
                case .F:
                    return LECycleRealisation612.F.rawValue
                case .E:
                    return LECycleRealisation612.E.rawValue
                }
            case 7:
                switch langue {
                case .F:
                    return LECycleRealisation712.F.rawValue
                case .E:
                    return LECycleRealisation712.E.rawValue
                }
            case 8:
                switch langue {
                case .F:
                    return LECycleRealisation812.F.rawValue
                case .E:
                    return LECycleRealisation812.E.rawValue
                }
            case 9:
                switch langue {
                case .F:
                    return LECycleRealisation912.F.rawValue
                case .E:
                    return LECycleRealisation912.E.rawValue
                }
            default:
                switch langue {
                case .F:
                    return LECycleRealisation112.F.rawValue
                case .E:
                    return LECycleRealisation112.E.rawValue
                }
            }
        case .MplusA:
            switch iLivePath {
            case 1:
                switch langue {
                case .F:
                    return LECycleRealisation1MA.F.rawValue
                case .E:
                    return LECycleRealisation1MA.E.rawValue
                }
            case 2:
                switch langue {
                case .F:
                    return LECycleRealisation2MA.F.rawValue
                case .E:
                    return LECycleRealisation2MA.E.rawValue
                }
            case 3:
                switch langue {
                case .F:
                    return LECycleRealisation3MA.F.rawValue
                case .E:
                    return LECycleRealisation3MA.E.rawValue
                }
            case 4:
                switch langue {
                case .F:
                    return LECycleRealisation4MA.F.rawValue
                case .E:
                    return LECycleRealisation4MA.E.rawValue
                }
            case 5:
                switch langue {
                case .F:
                    return LECycleRealisation5MA.F.rawValue
                case .E:
                    return LECycleRealisation5MA.E.rawValue
                }
            case 6:
                switch langue {
                case .F:
                    return LECycleRealisation6MA.F.rawValue
                case .E:
                    return LECycleRealisation6MA.E.rawValue
                }
            case 7:
                switch langue {
                case .F:
                    return LECycleRealisation7MA.F.rawValue
                case .E:
                    return LECycleRealisation7MA.E.rawValue
                }
            case 8:
                switch langue {
                case .F:
                    return LECycleRealisation8MA.F.rawValue
                case .E:
                    return LECycleRealisation8MA.E.rawValue
                }
            case 9:
                switch langue {
                case .F:
                    return LECycleRealisation9MA.F.rawValue
                case .E:
                    return LECycleRealisation9MA.E.rawValue
                }
            default:
                switch langue {
                case .F:
                    return LECycleRealisation1MA.F.rawValue
                case .E:
                    return LECycleRealisation1MA.E.rawValue
                }
            }
        }
    }

    public func cycleUniversels() -> String {
        switch langue {
        case .F:
            return LECycleUniversels.F.rawValue
        case .E:
            return LECycleUniversels.E.rawValue
        }
    }

    public func ageDe() -> String {
        switch langue {
        case .F:
            return LEAgeDe.F.rawValue
        case .E:
            return LEAgeDe.E.rawValue
        }
    }

    public func cycleUniversel(iNombre: Int) -> String {
        switch iNombre {
        case 1:
            switch langue {
            case .F:
                return LECycleUniversel1.F.rawValue
            case .E:
                return LECycleUniversel1.E.rawValue
            }
        case 2:
            switch langue {
            case .F:
                return LECycleUniversel2.F.rawValue
            case .E:
                return LECycleUniversel2.E.rawValue
            }
        case 3:
            switch langue {
            case .F:
                return LECycleUniversel3.F.rawValue
            case .E:
                return LECycleUniversel3.E.rawValue
            }
        case 4:
            switch langue {
            case .F:
                return LECycleUniversel4.F.rawValue
            case .E:
                return LECycleUniversel4.E.rawValue
            }
        case 5:
            switch langue {
            case .F:
                return LECycleUniversel5.F.rawValue
            case .E:
                return LECycleUniversel5.E.rawValue
            }
        case 6:
            switch langue {
            case .F:
                return LECycleUniversel6.F.rawValue
            case .E:
                return LECycleUniversel6.E.rawValue
            }
        case 7:
            switch langue {
            case .F:
                return LECycleUniversel7.F.rawValue
            case .E:
                return LECycleUniversel7.E.rawValue
            }
        case 8:
            switch langue {
            case .F:
                return LECycleUniversel8.F.rawValue
            case .E:
                return LECycleUniversel8.E.rawValue
            }
        case 9:
            switch langue {
            case .F:
                return LECycleUniversel9.F.rawValue
            case .E:
                return LECycleUniversel9.E.rawValue
            }
        default:
            switch langue {
            case .F:
                return LECycleUniversel1.F.rawValue
            case .E:
                return LECycleUniversel1.E.rawValue
            }
        }
    }
}

public class NumerologieCore {
    public enum ECycle {
        case Formatif, Productif, Moisson
    }

    public static func lettre(lettre: String) -> (Int, Bool) {
        let l: String = lettre.uppercased()
        switch l {
        case "A":
            return (1, true)
        case "À":
            return (1, true)
        case "Á":
            return (1, true)
        case "Â":
            return (1, true)
        case "Ã":
            return (1, true)
        case "B":
            return (2, false)
        case "C":
            return (3, false)
        case "D":
            return (4, false)
        case "E":
            return (5, true)
        case "È":
            return (5, true)
        case "É":
            return (5, true)
        case "Ê":
            return (5, true)
        case "Ë":
            return (5, true)
        case "F":
            return (6, false)
        case "G":
            return (7, false)
        case "H":
            return (8, false)
        case "I":
            return (9, true)
        case "Í":
            return (9, true)
        case "Ì":
            return (9, true)
        case "Î":
            return (9, true)
        case "Ï":
            return (9, true)
        case "J":
            return (10, false)
        case "K":
            return (11, false)
        case "L":
            return (12, false)
        case "M":
            return (13, false)
        case "N":
            return (14, false)
        case "Ñ":
            return (14, false)
        case "O":
            return (15, true)
        case "Ó":
            return (15, true)
        case "Ò":
            return (15, true)
        case "Ô":
            return (15, true)
        case "Ö":
            return (15, true)
        case "Ø":
            return (15, true)
        case "Õ":
            return (15, true)
        case "P":
            return (16, false)
        case "Q":
            return (17, false)
        case "R":
            return (18, false)
        case "S":
            return (19, false)
        case "T":
            return (20, false)
        case "U":
            return (21, true)
        case "Ú":
            return (21, true)
        case "Ù":
            return (21, true)
        case "Û":
            return (21, true)
        case "Ü":
            return (21, true)
        case "V":
            return (22, false)
        case "W":
            return (23, false)
        case "X":
            return (24, false)
        case "Y":
            return (25, true)
        case "Ý":
            return (25, true)
        case "Z":
            return (26, false)
        default:
            return (0, false)
        }
    }

    public static func cm(nom: String) -> [[Int]] {
        var gauche: [(Int, Int)] = []
        var droite: [(Int, Int)] = []
        var total = 0;
        var _total_reduit = 0;
        for l in nom {
            let n: (Int, Bool) = NumerologieCore.lettre(lettre: String(l))
            if n.0 > 0 {
                let nombre_non_reduit = n.0
                let nombre_reduit = NumerologieCore.reduction(iNumber: nombre_non_reduit)
                if n.1 {
                    droite.append((nombre_non_reduit, nombre_reduit.last ?? nombre_non_reduit))
                } else {
                    gauche.append((nombre_non_reduit, nombre_reduit.last ?? nombre_non_reduit))
                }
            }
        }
        for d in droite {
            total += d.0
        }
        _total_reduit = NumerologieCore.reduction(iNumber: total).last ?? total
        total = 0
        for g in gauche {
            total += g.0
        }
        _total_reduit = NumerologieCore.reduction(iNumber: total).last ?? total
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
        let CASE_CM: [[Int]] = [[8, 1, 6], [3, 5, 7], [4, 9, 2]]
        var case_cm_final: [[Int]] = [[], [], []]
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
        return case_cm_final
    }

    public static func date(dBornDate: Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iYear = Int(dateFormatter.string(from: dBornDate)) ?? 1980
        dateFormatter.dateFormat = "MM"
        let iMonth = Int(dateFormatter.string(from: dBornDate)) ?? 1
        dateFormatter.dateFormat = "dd"
        let iDay = Int(dateFormatter.string(from: dBornDate)) ?? 1
        return String(iDay) + "." + String(iMonth) + "." + String(iYear)
    }

    public static func reduction(iNumber: Int) -> [Int] {
        var aiRes = [Int]()
        var iTemp: Int = iNumber
        var bDone: Bool = false
        while !bDone {
            aiRes.append(iTemp)
            if String(iTemp).count == 1 {
                bDone = true
            }
            var iTemp2: Int = 0
            for i in 0...String(iTemp).count - 1 {
                let sTemp: String = String(iTemp)
                let index = sTemp.index(sTemp.startIndex, offsetBy: i)
                let cTemp: Character = sTemp[index]
                iTemp2 = iTemp2 + cTemp.wholeNumberValue!
            }
            iTemp = iTemp2
        }
        return aiRes
    }

    public static func age(dBornDate: Date) -> Int {
        let now = Date()
        let calendar: NSCalendar! = NSCalendar(calendarIdentifier: .gregorian)
        let calcAge = calendar.components(.year, from: dBornDate, to: now, options: [])
        let age = calcAge.year!
        return age
    }

    public static func cheminDeVie(dBornDate: Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iYear = Int(dateFormatter.string(from: dBornDate)) ?? 1980
        dateFormatter.dateFormat = "MM"
        let iMonth = Int(dateFormatter.string(from: dBornDate)) ?? 1
        dateFormatter.dateFormat = "dd"
        let iDay = Int(dateFormatter.string(from: dBornDate)) ?? 1
        let iTemp = iDay + iMonth + iYear
        let aiTempReduction = reduction(iNumber: iTemp)
        var sTemp: String = ""
        for ai in aiTempReduction {
            if sTemp == "" {
                sTemp = String(ai)
            } else {
                sTemp = sTemp + " / " + String(ai)
            }
        }
        return sTemp
    }

    public static func cheminDeVieInt(dBornDate: Date) -> Int {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iYear = Int(dateFormatter.string(from: dBornDate)) ?? 1980
        dateFormatter.dateFormat = "MM"
        let iMonth = Int(dateFormatter.string(from: dBornDate)) ?? 1
        dateFormatter.dateFormat = "dd"
        let iDay = Int(dateFormatter.string(from: dBornDate)) ?? 1
        let iTemp = iDay + iMonth + iYear
        let aiTempReduction = reduction(iNumber: iTemp)
        return aiTempReduction.last!
    }

    public static func jPlusMInt(dBornDate: Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "MM"
        let iMonth = Int(dateFormatter.string(from: dBornDate)) ?? 1
        dateFormatter.dateFormat = "dd"
        let iDay = Int(dateFormatter.string(from: dBornDate)) ?? 1
        let iTemp = iDay + iMonth
        let aiTempReduction = reduction(iNumber: iTemp)
        var sTemp: String = ""
        for ai in aiTempReduction {
            if sTemp == "" {
                sTemp = String(ai)
            } else {
                sTemp = sTemp + " / " + String(ai)
            }
        }
        return sTemp
    }

    public static func jPlusAInt(dBornDate: Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iYear = Int(dateFormatter.string(from: dBornDate)) ?? 1980
        dateFormatter.dateFormat = "dd"
        let iDay = Int(dateFormatter.string(from: dBornDate)) ?? 1
        let iTemp = iDay + iYear
        let aiTempReduction = reduction(iNumber: iTemp)
        var sTemp: String = ""
        for ai in aiTempReduction {
            if sTemp == "" {
                sTemp = String(ai)
            } else {
                sTemp = sTemp + " / " + String(ai)
            }
        }
        return sTemp
    }

    public static func unPlusDeuxInt(dBornDate: Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iYear = Int(dateFormatter.string(from: dBornDate)) ?? 1980
        dateFormatter.dateFormat = "MM"
        let iMonth = Int(dateFormatter.string(from: dBornDate)) ?? 1
        dateFormatter.dateFormat = "dd"
        let iDay = Int(dateFormatter.string(from: dBornDate)) ?? 1
        dateFormatter.dateFormat = "hh"
        let iTemp = (iDay + iMonth) + (iDay + iYear)
        let aiTempReduction = reduction(iNumber: iTemp)
        var sTemp: String = ""
        for ai in aiTempReduction {
            if sTemp == "" {
                sTemp = String(ai)
            } else {
                sTemp = sTemp + " / " + String(ai)
            }
        }
        return sTemp
    }

    public static func mPlusAInt(dBornDate: Date) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iYear = Int(dateFormatter.string(from: dBornDate)) ?? 1980
        dateFormatter.dateFormat = "MM"
        let iMonth = Int(dateFormatter.string(from: dBornDate)) ?? 1
        let iTemp = iMonth + iYear
        let aiTempReduction = reduction(iNumber: iTemp)
        var sTemp: String = ""
        for ai in aiTempReduction {
            if sTemp == "" {
                sTemp = String(ai)
            } else {
                sTemp = sTemp + " / " + String(ai)
            }
        }
        return sTemp
    }

    public static func cycleAdjacents(dBornDate: Date, eCycle: NumerologieCore.ECycle) -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iYear = Int(dateFormatter.string(from: dBornDate)) ?? 1980
        dateFormatter.dateFormat = "MM"
        let iMonth = Int(dateFormatter.string(from: dBornDate)) ?? 1
        dateFormatter.dateFormat = "dd"
        let iDay = Int(dateFormatter.string(from: dBornDate)) ?? 1
        var iTemp = 0;
        switch eCycle {
        case .Formatif:
            iTemp = iMonth
            break
        case .Productif:
            iTemp = iDay
            break
        case .Moisson:
            iTemp = iYear
            break
        }
        let aiTempReduction = reduction(iNumber: iTemp)
        var sTemp: String = ""
        for ai in aiTempReduction {
            if sTemp == "" {
                sTemp = String(ai)
            } else {
                sTemp = sTemp + " / " + String(ai)
            }
        }
        return sTemp
    }

    public static func pdf(natal: Date, nom: String) throws -> Data {
        let text = TextCore(langue: .F)

        let document = PDFDocument(format: .a4)

        // Numérologie
        document.add(.contentCenter, text: text.numerologie())
        var table = PDFTable(rows: 3, columns: 2)
        var style = PDFTableStyle()
        style.rowHeaderCount = 0
        style.columnHeaderCount = 0
        table.style = style
        var lineStyle = PDFLineStyle(width: 1)
        var cellStyle = PDFTableCellStyle(
                borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
        table[1,0].style = cellStyle
        table[2,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,1].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
        table[1,1].style = cellStyle
        table[2,1].style = cellStyle
        table[0,0].alignment = .left
        table[1,0].alignment = .left
        table[2,0].alignment = .left
        table[0,1].alignment = .right
        table[1,1].alignment = .right
        table[2,1].alignment = .right
        table[0,0].content = try! PDFTableContent(content: text.born())
        table[0,1].content = try! PDFTableContent(content: String(NumerologieCore.date(dBornDate: natal)))
        table[1,0].content = try! PDFTableContent(content: text.age())
        table[1,1].content = try! PDFTableContent(content: String(NumerologieCore.age(dBornDate: natal)))
        table[2,0].content = try! PDFTableContent(content: text.lifePath())
        table[2,1].content = try! PDFTableContent(content: String(NumerologieCore.cheminDeVie(dBornDate: natal)))
        document.add(table: table)

// Cycle adjacents
        document.add(.contentCenter, text: "Cycle adjacents") // TODO
        table = PDFTable(rows: 4, columns: 3)
        style = PDFTableStyle()
        style.rowHeaderCount = 0
        style.columnHeaderCount = 0
        table.style = style
        lineStyle = PDFLineStyle(width: 1)
        cellStyle = PDFTableCellStyle(
                borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
        table[1,0].style = cellStyle
        table[2,0].style = cellStyle
        table[3,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,1].style = cellStyle
        table[0,2].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
        table[1,1].style = cellStyle
        table[2,1].style = cellStyle
        table[3,1].style = cellStyle
        table[1,2].style = cellStyle
        table[2,2].style = cellStyle
        table[3,2].style = cellStyle
        table[0,0].alignment = .left
        table[1,0].alignment = .left
        table[2,0].alignment = .left
        table[3,0].alignment = .left
        table[0,1].alignment = .center
        table[1,1].alignment = .center
        table[2,1].alignment = .center
        table[3,1].alignment = .center
        table[0,2].alignment = .right
        table[1,2].alignment = .right
        table[2,2].alignment = .right
        table[3,2].alignment = .right
        table[0,0].content = try! PDFTableContent(content: text.cycle())
        table[0,1].content = try! PDFTableContent(content: text.calcul())
        table[0,2].content = try! PDFTableContent(content: text.nombre())
        table[1,0].content = try! PDFTableContent(content: "Formatif") // TODO
        table[2,0].content = try! PDFTableContent(content: "Productif") // TODO
        table[3,0].content = try! PDFTableContent(content: "Moisson") // TODO
        table[1,1].content = try! PDFTableContent(content: "Mois") // TODO
        table[2,1].content = try! PDFTableContent(content: "Jour") // TODO
        table[3,1].content = try! PDFTableContent(content: "Année") // TODO
        table[1,2].content = try! PDFTableContent(content: NumerologieCore.cycleAdjacents(dBornDate: natal, eCycle: .Formatif))
        table[2,2].content = try! PDFTableContent(content: NumerologieCore.cycleAdjacents(dBornDate: natal, eCycle: .Productif))
        table[3,2].content = try! PDFTableContent(content: NumerologieCore.cycleAdjacents(dBornDate: natal, eCycle: .Moisson))
        document.add(table: table)

// Cycle de réalisation
        document.add(.contentCenter, text: text.cycleRealisation())
        table = PDFTable(rows: 5, columns: 3)
        style = PDFTableStyle()
        style.rowHeaderCount = 0
        style.columnHeaderCount = 0
        table.style = style
        lineStyle = PDFLineStyle(width: 1)
        cellStyle = PDFTableCellStyle(
                borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
        table[1,0].style = cellStyle
        table[2,0].style = cellStyle
        table[3,0].style = cellStyle
        table[4,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,1].style = cellStyle
        table[0,2].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
        table[1,1].style = cellStyle
        table[2,1].style = cellStyle
        table[3,1].style = cellStyle
        table[4,1].style = cellStyle
        table[1,2].style = cellStyle
        table[2,2].style = cellStyle
        table[3,2].style = cellStyle
        table[4,2].style = cellStyle
        table[0,0].alignment = .left
        table[1,0].alignment = .left
        table[2,0].alignment = .left
        table[3,0].alignment = .left
        table[4,0].alignment = .left
        table[0,1].alignment = .center
        table[1,1].alignment = .center
        table[2,1].alignment = .center
        table[3,1].alignment = .center
        table[4,1].alignment = .center
        table[0,2].alignment = .right
        table[1,2].alignment = .right
        table[2,2].alignment = .right
        table[3,2].alignment = .right
        table[4,2].alignment = .right
        table[0,0].content = try! PDFTableContent(content: "Age de à") // TODO
        table[0,1].content = try! PDFTableContent(content: text.calcul())
        table[0,2].content = try! PDFTableContent(content: text.nombre())
        table[1,0].content = try! PDFTableContent(content: text.cycleRealisation(
                iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .JplusM))
        table[2,0].content = try! PDFTableContent(content: text.cycleRealisation(
                iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .JplusA))
        table[3,0].content = try! PDFTableContent(content: text.cycleRealisation(
                iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .UnplusDeux))
        table[4,0].content = try! PDFTableContent(content: text.cycleRealisation(
                iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .MplusA))
        table[1,1].content = try! PDFTableContent(content: "J + M") // TODO
        table[2,1].content = try! PDFTableContent(content: "J + A") // TODO
        table[3,1].content = try! PDFTableContent(content: "1 + 2") // TODO
        table[4,1].content = try! PDFTableContent(content: "M + A") // TODO
        table[1,2].content = try! PDFTableContent(content: NumerologieCore.jPlusMInt(dBornDate: natal))
        table[2,2].content = try! PDFTableContent(content: NumerologieCore.jPlusAInt(dBornDate: natal))
        table[3,2].content = try! PDFTableContent(content: NumerologieCore.unPlusDeuxInt(dBornDate: natal))
        table[4,2].content = try! PDFTableContent(content: NumerologieCore.mPlusAInt(dBornDate: natal))
        document.add(table: table)

// Cycles universels
        document.add(.contentCenter, text: text.cycleUniversels())
        table = PDFTable(rows: 10, columns: 2)
        style = PDFTableStyle()
        style.rowHeaderCount = 0
        style.columnHeaderCount = 0
        table.style = style
        lineStyle = PDFLineStyle(width: 1)
        cellStyle = PDFTableCellStyle(
                borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
        table[1,0].style = cellStyle
        table[2,0].style = cellStyle
        table[3,0].style = cellStyle
        table[4,0].style = cellStyle
        table[5,0].style = cellStyle
        table[6,0].style = cellStyle
        table[7,0].style = cellStyle
        table[8,0].style = cellStyle
        table[9,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,1].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
        table[1,1].style = cellStyle
        table[2,1].style = cellStyle
        table[3,1].style = cellStyle
        table[4,1].style = cellStyle
        table[5,1].style = cellStyle
        table[6,1].style = cellStyle
        table[7,1].style = cellStyle
        table[8,1].style = cellStyle
        table[9,1].style = cellStyle
        table[0,0].alignment = .left
        table[1,0].alignment = .left
        table[2,0].alignment = .left
        table[3,0].alignment = .left
        table[4,0].alignment = .left
        table[5,0].alignment = .left
        table[6,0].alignment = .left
        table[7,0].alignment = .left
        table[8,0].alignment = .left
        table[9,0].alignment = .left
        table[0,1].alignment = .right
        table[1,1].alignment = .right
        table[2,1].alignment = .right
        table[3,1].alignment = .right
        table[4,1].alignment = .right
        table[5,1].alignment = .right
        table[6,1].alignment = .right
        table[7,1].alignment = .right
        table[8,1].alignment = .right
        table[9,1].alignment = .right
        table[0,0].content = try! PDFTableContent(content: text.ageDe())
        table[0,1].content = try! PDFTableContent(content: text.nombre())
        table[1,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 1))
        table[1,1].content = try! PDFTableContent(content: "1")
        table[2,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 2))
        table[2,1].content = try! PDFTableContent(content: "2")
        table[3,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 3))
        table[3,1].content = try! PDFTableContent(content: "3")
        table[4,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 4))
        table[4,1].content = try! PDFTableContent(content: "4")
        table[5,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 5))
        table[5,1].content = try! PDFTableContent(content: "5")
        table[6,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 6))
        table[6,1].content = try! PDFTableContent(content: "6")
        table[7,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 7))
        table[7,1].content = try! PDFTableContent(content: "7")
        table[8,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 8))
        table[8,1].content = try! PDFTableContent(content: "8")
        table[9,0].content = try! PDFTableContent(content: text.cycleUniversel(iNombre: 9))
        table[9,1].content = try! PDFTableContent(content: "9")
        document.add(table: table)

// CM
        let cm = NumerologieCore.cm(nom: nom)
        document.add(.contentCenter, text: "CM-PJ") // TODO
        table = PDFTable(rows: 3, columns: 3)
        style = PDFTableStyle()
        style.rowHeaderCount = 0
        style.columnHeaderCount = 0
        table.style = style
        lineStyle = PDFLineStyle(width: 1)
        cellStyle = PDFTableCellStyle(
                borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
        table[1,0].style = cellStyle
        table[2,0].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
        table[0,1].style = cellStyle
        table[0,2].style = cellStyle
        cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
        table[1,1].style = cellStyle
        table[1,2].style = cellStyle
        table[2,1].style = cellStyle
        table[2,2].style = cellStyle
        table[0,0].alignment = .center
        table[1,0].alignment = .center
        table[2,0].alignment = .center
        table[0,1].alignment = .center
        table[1,1].alignment = .center
        table[2,1].alignment = .center
        table[0,2].alignment = .center
        table[1,2].alignment = .center
        table[2,2].alignment = .center
        table[0,0].content = try! PDFTableContent(content: cm[0][0])
        table[0,1].content = try! PDFTableContent(content: cm[0][1])
        table[0,2].content = try! PDFTableContent(content: cm[0][2])
        table[1,0].content = try! PDFTableContent(content: cm[1][0])
        table[1,1].content = try! PDFTableContent(content: cm[1][1])
        table[1,2].content = try! PDFTableContent(content: cm[1][2])
        table[2,0].content = try! PDFTableContent(content: cm[2][0])
        table[2,1].content = try! PDFTableContent(content: cm[2][1])
        table[2,2].content = try! PDFTableContent(content: cm[2][2])
        document.add(table: table)

        let generator = PDFGenerator(document: document)
        //let url = try generator.generateURL(filename: "Example.pdf")
        let data = try generator.generateData()
        return data
    }
}
