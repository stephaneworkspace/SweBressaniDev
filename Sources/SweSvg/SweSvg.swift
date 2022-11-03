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
    public var year_transit: Int32
    public var month_transit: Int32
    public var day_transit: Int32
    public var hour_transit: Int32
    public var min_transit: Int32
    public var lat: Double
    public var lng: Double
    public var tz: Int32
    public var ephemPath: String
    public var utcTimeZone: cwrapper.SweTimeZone
    public var utcTimeZone_transit: cwrapper.SweTimeZone
    public var houses: [cwrapper.SweHouse]
    public var bodies_natal: [cwrapper.SweBodie]
    public var bodies_transit: [cwrapper.SweBodie]
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
        year_transit = 1984
        month_transit = 1
        day_transit = 1
        hour_transit = 0
        min_transit = 0
        lat = 0
        lng = 0
        tz = 0
        utcTimeZone = cwrapper.SweTimeZone()
        utcTimeZone_transit = cwrapper.SweTimeZone()
        houses = []
        bodies_natal = []
        bodies_transit = []
    }

    public func set(natal: Date, transit: Date, lat: Double, lng: Double, tz: Int32) {
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
        dateFormatter.dateFormat = "YYYY"
        year_transit = Int32(dateFormatter.string(from: transit)) ?? 1980
        dateFormatter.dateFormat = "MM"
        month_transit = Int32(dateFormatter.string(from: transit)) ?? 1
        dateFormatter.dateFormat = "dd"
        day_transit = Int32(dateFormatter.string(from: transit)) ?? 1
        dateFormatter.dateFormat = "hh"
        hour_transit = Int32(dateFormatter.string(from: transit)) ?? 0
        dateFormatter.dateFormat = "mm"
        min_transit = Int32(dateFormatter.string(from: transit)) ?? 0
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
        // Transit
        utcTimeZone_transit = cwrapper.SweTimeZone()
        utcTimeZone_transit.year = year_transit
        utcTimeZone_transit.month = month_transit
        utcTimeZone_transit.day = day_transit
        utcTimeZone_transit.hour = hour_transit
        utcTimeZone_transit.min = min_transit
        utcTimeZone_transit.sec = 0.0
        utcTimeZone_transit = cwrapper.swelib_utc_time_zone(utcTimeZone_transit, Double(self.tz))
        let utc_to_jd_transit = cwrapper.swelib_utc_to_jd(utcTimeZone_transit)

        // Houses
        houses = []
        for i in 0...12 {
            houses.append(cwrapper.swelib_house_ex(utc_to_jd, self.lat, self.lng, Int32(i + 1)))
        }

        // Bodies
        var b_arr: [Int] = []
        b_arr.append(Int(cwrapper.ASTRE_SOLEIL))
        b_arr.append(Int(cwrapper.ASTRE_LUNE))
        b_arr.append(Int(cwrapper.ASTRE_MERCURE))
        b_arr.append(Int(cwrapper.ASTRE_VENUS))
        b_arr.append(Int(cwrapper.ASTRE_MARS))
        b_arr.append(Int(cwrapper.ASTRE_JUPITER))
        b_arr.append(Int(cwrapper.ASTRE_SATURN))
        b_arr.append(Int(cwrapper.ASTRE_NEPTUNE))
        b_arr.append(Int(cwrapper.ASTRE_PLUTON))
        b_arr.append(Int(cwrapper.ASTRE_NOEUD_LUNAIRE))
        b_arr.append(Int(cwrapper.ASTRE_CHIRON))
        b_arr.append(Int(cwrapper.ASTRE_CERES))
        b_arr.append(Int(cwrapper.ASTRE_NOEUD_LUNAIRE_SUD))
        for b in b_arr {
            let calc_ut = cwrapper.swelib_calc_ut(utc_to_jd, Int32(b))
            let calc_ut_t = cwrapper.swelib_calc_ut(utc_to_jd_transit, Int32(b))
            bodies_natal.append(SweBodie.init(bodie: Int32(b), calc_ut: calc_ut))
            bodies_transit.append(SweBodie.init(bodie: Int32(b), calc_ut: calc_ut_t))
        }
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

    public func asset_house(i: Int) throws -> URL {
        let s: String = String(cString: UnsafePointer<CChar>(cwrapper.a_house(Int32(i))!))
        return try asset_svg_url(name: String(format: "asset_%d_house.svg", i), encoded: s)
    }

    public func asset_bodie(i: Int) throws -> URL {
        let s: String = String(cString: UnsafePointer<CChar>(cwrapper.a_bodie(Int32(i))!))
        return try asset_svg_url(name: String(format: "asset_%d_bodie.svg", i), encoded: s)
    }
}