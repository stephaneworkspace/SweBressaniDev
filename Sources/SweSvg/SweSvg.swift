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

    public func theme_astral(year: Int32, month: Int32, day: Int32, hour: Int32, min: Int32, lat: Double, lng: Double, tz: Int32) -> String {
        let svg: String = String(cString: UnsafePointer<CChar>(cwrapper.theme_astral(year, month, day, hour, min, lat, lng, tz, ephemPath)))
        guard
                var documentsURL = (FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)).last,
                let convertedData = Data(base64Encoded: svg)
        else {
            print("error1")
            return "" // TODO
        }
        documentsURL.appendPathComponent("astrologie.svg")
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
}