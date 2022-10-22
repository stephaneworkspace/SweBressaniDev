//import cwrapper
import SweSvg
import Foundation

let sweSvg = SweSvg(ephemPath: "")
let svg = sweSvg.theme_astral(year: 1984, month: 1, day: 4, hour: 0, min: 0, lat: 16.0, lng: 26.6, tz: 2)
print("Fichier svg")
drawSvg(svg: svg)

func drawSvg(svg: String) {
    guard
            var documentsURL = (FileManager.default.urls(for: .documentDirectory, in: .userDomainMask)).last,
            let convertedData = Data(base64Encoded: svg)
    else {
        print("error1")
        return
    }
    documentsURL.appendPathComponent("astrologie.svg")
    do {
        try convertedData.write(to: documentsURL)
    } catch {
        print("error2")
        return
    }
    print(documentsURL.absoluteString)
}



//print(s)
//let svg: String = String(cString: UnsafePointer<CChar>(theme_astral(1984, 1, 4, 0, 0, 16, 26, 2, "")))
//print(svg)
//print(cwrapperfive())
