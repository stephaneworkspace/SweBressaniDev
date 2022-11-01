//
// Created by Stéphane on 22.10.22.
//

import Foundation
import SwiftUI

public class SweSwiftUi {
    public struct Circle {
        var center: Double
        var radius: Double
    }

    public struct Line {
        var lX1: Double
        var lY1: Double
        var lX2: Double
        var lY2: Double
    }

    public struct Offset {
        var offX: Double
        var offY: Double
    }

    public var size: Int

    public init() {
        size = 400
    }

    public func drawCircle(circles: [Circle]) -> Path {
        var path = Path()
        for circle in circles.reversed() {
            path.move(to: CGPoint(x: circle.center + circle.radius, y: circle.center))
            path.addArc(
                    center: CGPoint(
                            x: circle.center,
                            y: circle.center),
                    radius: circle.radius,
                    startAngle: .zero,
                    endAngle: .degrees(360.0),
                    clockwise: false)
            path.closeSubpath()
        }
        return path
    }

    public func drawLine(lines: [Line]) -> Path {
        var path = Path()
        for line in lines {
            path.move(to: CGPoint(x: line.lX1, y: line.lY1))
            path.addLine(to: CGPoint(x: line.lX2, y: line.lY2))
            path.closeSubpath()
        }
        return path
    }

    public func circles() -> [Circle] {
        var res: [Circle] = []
        let center = getRadiusTotal()
        for (idx, circleSize) in CIRCLE_SIZE_TRANSIT.enumerated() {
            if circleSize.1 {
                let radius = getRadiusCircle(occurs: idx).0
                res.append(Circle(center: center, radius: radius))
            }
        }
        return res
    }

    func zodiac_lines() -> [Line] {
        var res: [Line] = []
        for iIdx in 1...12 {
            // 0°
            let offPosAsc = 360.0 // - swe.houses[0].longitude
            var pos = Double(iIdx) * 30.0 + offPosAsc
            pos = getFixedPos(pos_value: pos)
            let axy: [Offset] = getLineTrigo(
                    angular: pos,
                    radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                    radiusCircleEnd: getRadiusCircle(occurs: 1).0)
            res.append(Line(
                    lX1: axy[0].offX,
                    lY1: axy[0].offY,
                    lX2: axy[1].offX,
                    lY2: axy[1].offY)
            )
            // 1° to 29°
            var largerDrawLine: LargerDrawLine = .large
            for jIdx in 1...15 {
                if jIdx == 5 || jIdx == 10 || jIdx == 15 {
                    largerDrawLine = .large
                } else {
                    largerDrawLine = .small
                }
                pos = (Double(iIdx) * 30.0) + Double(jIdx) * 2.0 + offPosAsc
                pos = getFixedPos(pos_value: pos)
                let axy: [Offset] = getLineTrigo(
                        angular: pos,
                        radiusCircleBegin: getRadiusCircle(occurs: 2).0,
                        radiusCircleEnd: getRadiusRulesInsideCircle(largerDrawLine: largerDrawLine))
                res.append(Line(
                        lX1: axy[0].offX,
                        lY1: axy[0].offY,
                        lX2: axy[1].offX,
                        lY2: axy[1].offY)
                )
            }
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

    private func getLineTrigo(angular: Double, radiusCircleBegin: Double, radiusCircleEnd: Double) -> [Offset] {
        var res: [Offset] = []
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

    func getRadiusRulesInsideCircle(largerDrawLine: LargerDrawLine) -> Double {
        var size = 0.0
        switch largerDrawLine {
        case .small:
            size = 1.0 + LARGER_DRAW_LINE_RULES_SMALL
        case .large:
            size = 1.0 + LARGER_DRAW_LINE_RULES_LARGE
        }
        return getRadiusTotal() * (((CIRCLE_SIZE_TRANSIT[2].0 - CIRCLE_SIZE_TRANSIT[1].0) / size)
                + CIRCLE_SIZE_TRANSIT[1].0) / 100.0
    }

    private func getCenter() -> Offset {
        Offset(offX: getRadiusTotal(), offY: getRadiusTotal())
    }
}