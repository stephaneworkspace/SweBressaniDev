//import cwrapper
import Foundation
import SweBressaniDev
import TPPDF

var sweSvg = SweSvg(ephemPath: "")
sweSvg.set(natal: Date(), transit: Date(), lat: 16, lng: 26.6, tz: 2, colorMode: .Light)
let svg = try! sweSvg.theme_astral()
print(svg)
let sign1 = try! sweSvg.asset_sign(i: 1)
let sign2 = try! sweSvg.asset_sign(i: 2)
//print(cwrapperfive())


let document = PDFDocument(format: .a4)
document.add(.contentCenter, text: "Create PDF documents easily.")
let table = PDFTable(rows: 3, columns: 4)
table[0,0].content = try! PDFTableContent(content: "1")
document.add(table: table)

let generator = PDFGenerator(document: document)
let url = try generator.generateURL(filename: "Example.pdf")
print(url)