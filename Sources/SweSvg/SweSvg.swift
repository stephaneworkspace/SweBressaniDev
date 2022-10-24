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

    private func ptrToString(ptr: UnsafePointer<CChar>) -> String {
        let s: String = String(cString: UnsafePointer<CChar>(ptr))
        return s
    }

    private func asset_svg(name: String, encoded: String) -> String {
        guard
                var documentsURL = (FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)).last,
                let convertedData = Data(base64Encoded: encoded)
        else {
            print("error1")
            return "" // TODO
        }
        documentsURL.appendPathComponent(name)
        do {
            try convertedData.write(to: documentsURL)
        } catch {
            print("error2")
            return "" // TODO
        }
        let svg_file = documentsURL.absoluteString
        print(documentsURL.absoluteString)
        return svg_file.replacingOccurrences(of: "file://", with: "")
    }

    public func theme_astral(year: Int32, month: Int32, day: Int32, hour: Int32, min: Int32, lat: Double, lng: Double, tz: Int32) -> String {
        let svg: String = ptrToString(ptr: cwrapper.theme_astral(year, month, day, hour, min, lat, lng, tz, ephemPath))
        return asset_svg(name: "asset_theme_astral.svg", encoded: svg)
    }

    public func asset_sign(i: Int32) -> String {
        let svg: String = ptrToString(ptr: cwrapper.a_sign(i))
        return asset_svg(name: String(format: "asset_%d_sign.svg"), encoded: svg)
    }
}