//
// Created by Stéphane on 21.10.22.
//

import Foundation
import cwrapper

public struct SweSvg {
    public private(set) var text = "Hello, World!"
    private var ephemPath: String
    public init(ephemPath: String) {
        self.ephemPath = ephemPath
    }

    public func theme_astral(year: Int32, month: Int32, day: Int32, hour: Int32, min: Int32, lng: Double, lat: Double, tz: Int32) -> String {
        let svg: String = String(cString: UnsafePointer<CChar>(cwrapper.theme_astral(year, month, day, hour, min, lng, lat, tz, ephemPath)))
        return svg
    }
}