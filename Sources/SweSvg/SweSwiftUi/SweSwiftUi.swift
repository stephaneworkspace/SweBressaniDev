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

    private var size: Int

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

    public func getSizeCGFLoat() -> CGFloat {
        CGFloat(size)
    }


    private func getRadiusTotal() -> Double {
        Double(size) / 2.0
    }

    private func getRadiusCircle(occurs: Int) -> (Double, Bool) {
        let res = getRadiusTotal() * CIRCLE_SIZE_TRANSIT[occurs].0 / 100
        return (res, CIRCLE_SIZE_TRANSIT[occurs].1)
    }
}