//
// Created by Stéphane on 21.10.22.
//

import Foundation
import cwrapper
// TODO protocol

public class SweSvg {
    public private(set) var text = "Hello, World!"
    public var year: Int32
    public var month: Int32
    public var day: Int32
    public var hour: Int32
    public var min: Int32
    public var lat: Double
    public var lng: Double
    public var tz: Int32
    public var ephemPath: String
    public var utcTimeZone: cwrapper.SweTimeZone
    public var houses: [cwrapper.SweHouse]
    public init(ephemPath: String) {
        self.ephemPath = ephemPath
        let pathPtr = UnsafeMutablePointer<Int8>(mutating: (self.ephemPath as NSString).utf8String)
        cwrapper.swelib_set_ephe_path(pathPtr)
        //free(pathPtr) TODO comprendre
        year = 1984
        month = 1
        day = 1
        hour = 0
        min = 0
        lat = 0
        lng = 0
        tz = 0
        utcTimeZone = cwrapper.SweTimeZone()
        houses = []
    }

    public func set(natal: Date, lat: Double, lng: Double, tz: Int32) {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        year = Int32(dateFormatter.string(from: natal)) ?? 1980
        dateFormatter.dateFormat = "MM"
        month = Int32(dateFormatter.string(from: natal)) ?? 1
        dateFormatter.dateFormat = "dd"
        day = Int32(dateFormatter.string(from: natal)) ?? 1
        dateFormatter.dateFormat = "hh"
        hour = Int32(dateFormatter.string(from: natal)) ?? 0
        dateFormatter.dateFormat = "mm"
        min = Int32(dateFormatter.string(from: natal)) ?? 0
        self.lat = lat
        self.lng = lng
        self.tz = tz

        // Compute julian day
        utcTimeZone = cwrapper.SweTimeZone()
        utcTimeZone.year = year
        utcTimeZone.month = month
        utcTimeZone.day = day
        utcTimeZone.hour = hour
        utcTimeZone.min = min
        utcTimeZone.sec = 0.0
        utcTimeZone = cwrapper.swelib_utc_time_zone(utcTimeZone, Double(self.tz))
        let utc_to_jd = cwrapper.swelib_utc_to_jd(utcTimeZone)
        // Transit TODO

        // Houses
        houses = []
        for i in 0...12 {
            houses.append(cwrapper.swelib_house_ex(utc_to_jd, self.lat, self.lng, Int32(i)))
        }
        print(houses[0].longitude)
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
        return svg_file.replacingOccurrences(of: "file://", with: "")
    }

    enum URLError: Error { // TODO
        case error1
        case error2
    }

    private func asset_svg_url(name: String, encoded: String) throws -> URL {
        let e = encoded.replacingOccurrences(of:  "data:image/svg+xml;base64,", with: "")
        guard
                var documentsURL = (FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)).last,
                let convertedData = Data(base64Encoded: e)
        else {
            print("Svg pas valide")
            throw  URLError.error1
        }
        documentsURL.appendPathComponent(name)
        do {
            try convertedData.write(to: documentsURL)
        } catch {
            print("error2")
            throw  URLError.error2
        }
        return documentsURL.absoluteURL
    }

    public func theme_astral() -> String {
        // TODO
        let svg: String = ptrToString(ptr: cwrapper.theme_astral(year, month, day, hour, min, lat, lng, tz, ephemPath))
        return asset_svg(name: "asset_theme_astral.svg", encoded: svg)
    }

    public func asset_sign(i: Int) throws -> URL {
        let s: String = String(cString: UnsafePointer<CChar>(cwrapper.a_sign(Int32(i))!))
        return try asset_svg_url(name: String(format: "asset_%d_sign.svg", i), encoded: s)
    }
}