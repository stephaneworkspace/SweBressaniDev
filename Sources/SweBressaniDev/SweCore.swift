//
// Created by Stéphane on 05.11.22.
//

import Foundation
import SwiftUI

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
             NoeudLunaireSud = 24
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

    public init(pathEphe: String) {
        size = 400
        colorMode = .Light
        swec = SweSvg(ephemPath: pathEphe)
    }

    public func set(natal: Date, transit: Date, lat: Double, lng: Double, tz: Int32, bodies: [SweCore.Bodies], colorMode: SweSvg.ColorMode) {
        swec.set(natal: natal, transit: transit, lat: lat, lng: lng, tz: tz, colorMode: colorMode)
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

    public func zodiac_lines() -> [SweCore.AstroLine] {
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

    public func zodiac_sign(sign: Int) -> SweCore.Object {
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
        var houseSize = (((HOUSE_SIZE * HOUSE_RATIO) / 100.0) * Double(size)) / 100.0
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

    public func bodie(bodie: Bodies, swTransit: Bool) -> SweCore.ObjectBodie {
        var planetRatio: Double
        if swTransit {
            planetRatio = 6.0 // TODO const
        } else {
            planetRatio = 12.0 // TODO const
        }
        let planetSize = (((BODIE_SIZE * ZODIAC_RATIO) / 100.0) * Double(size)) / 100.0;
        let degRatio = 6.0 // TODO const
        let degSize = (((DEG_SIZE * degRatio) / 100.0) * Double(size))
        let minRatio = 6.0 // TODO const
        let minSize = (((MIN_SIZE * degRatio) / 100.0) * Double(size))
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
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude, swTransit: swTransit)
                }
            }
        } else {
            // transit
            for b in swec.bodiesTransit {
                if b.bodie == bodie.rawValue {
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude, swTransit: swTransit)
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
        // TODO deg min line 1336 sw_draw.rs
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
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude, swTransit: swTransit)
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
                    pos = getBodieLongitude(bodie_longitude: b.calc_ut.longitude, swTransit: swTransit)
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

    public func angle_lines(angle: SweCore.Angles) -> [SweCore.AstroLine] {
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

    public func house_lines() -> [SweCore.AstroHouseLine] {
        var res: [SweCore.AstroHouseLine] = []
        for iIdx in 0...11 {
            let offHouse = 360.0 - swec.houses[0].longitude
            let pos = getFixedPos(pos_value: offHouse + swec.houses[iIdx].longitude)
            var axyTriangle: [SweCore.Offset] = []
            let angularPointer = -1.0 // TODO CONST
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

    private func getRadiusTotal() -> Double {
        Double(size) / 2.0
    }

    private func getRadiusCircle(occurs: Int) -> (Double, Bool) {
        let res = getRadiusTotal() * CIRCLE_SIZE_TRANSIT[occurs].0 / 100
        return (res, CIRCLE_SIZE_TRANSIT[occurs].1)
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

    func getRadiusRulesInsideCircle(largerDrawLine: SweCore.LargerDrawLine) -> Double {
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
        let divTraitPointer = 1.5 // TODO CONST
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

    private func getBodieLongitude(bodie_longitude: Double, swTransit: Bool) -> Double {
        var pos = 0.0
        if swTransit {
            pos = CIRCLE - swec.houses[0].longitude + bodie_longitude
        } else {
            pos = CIRCLE - swec.houses[0].longitude + bodie_longitude
        }
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
}