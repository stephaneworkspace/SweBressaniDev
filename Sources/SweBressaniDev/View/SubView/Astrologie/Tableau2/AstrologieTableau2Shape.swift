//
// Created by Stéphane on 11.11.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct DrawAspectArray: Shape {
    var size: Double
    //var transitType: Swe.TransitType TODO

    public init(size: Double) {
        self.size = size
    }

    public func path(in rect: CGRect) -> Path {
        var path = Path()
        let cas = Double(size) / 16
        let MAX = 15 // TODO const global
        let max = 15
        //if transitType == .NatalTransit {
        //    max -= 2
        //}
        path.move(to: CGPoint(x: 0, y: cas))
        path.addLine(to: CGPoint(x: 0, y: Double(max + 1) * cas))
        for iDx in 1...max {
            let idx = Double(iDx)
            path.move(to: CGPoint(x: idx * cas, y: idx * cas))
            if iDx == MAX {
                path.addLine(to: CGPoint(x: idx * cas, y: idx * cas))
            } else {
                path.addLine(to: CGPoint(x: idx * cas, y: (idx + 1) * cas))
            }
            if iDx == MAX {
                path.move(to: CGPoint(x: (idx - 1) * cas, y: idx * cas))
            } else {
                path.move(to: CGPoint(x: idx * cas, y: idx * cas))
            }
            path.addLine(to: CGPoint(x: 0, y: idx * cas))
            if iDx == MAX {
                path.move(to: CGPoint(x: (idx - 1) * cas, y: (idx + 1) * cas))
            } else {
                path.move(to: CGPoint(x: idx * cas, y: (idx + 1) * cas))
            }
            path.addLine(to: CGPoint(x: 0, y: (idx + 1) * cas))
            path.move(to: CGPoint(x: idx * cas, y: (idx + 1) * cas))
            path.addLine(to: CGPoint(x: idx * cas, y: Double(max + 1) * cas))
        }
        return path
    }
}
