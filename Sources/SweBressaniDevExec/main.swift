//import cwrapper
import Foundation
import SwiftUI
//#if canImport(UIKit)
//import UIKit
//#endif
import SweBressaniDev
import TPPDF

var sweSvg = SweSvg(ephemPath: "")
sweSvg.set(natal: Date(), transit: Date(), lat: 16, lng: 26.6, tz: 2, colorMode: .Light)
let svg = try! sweSvg.theme_astral()
print(svg)
let sign1 = try! sweSvg.asset_sign(i: 1)
let sign2 = try! sweSvg.asset_sign(i: 2)
//print(cwrapperfive())

let text = TextCore(langue: .F)

let document = PDFDocument(format: .a4)

// Numérologie
document.add(.contentCenter, text: text.numerologie())
let table = PDFTable(rows: 3, columns: 2)
let style = PDFTableStyle()
style.rowHeaderCount = 0
style.columnHeaderCount = 0
table.style = style
let lineStyle = PDFLineStyle(width: 1)
var cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
table[0,0].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
table[1,0].style = cellStyle
table[2,0].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
table[0,1].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
table[1,1].style = cellStyle
table[2,1].style = cellStyle
table[0,0].alignment = .left
table[1,0].alignment = .left
table[2,0].alignment = .left
table[0,0].content = try! PDFTableContent(content: text.born())
table[1,0].content = try! PDFTableContent(content: text.age())
table[2,0].content = try! PDFTableContent(content: text.lifePath())
document.add(table: table)

let generator = PDFGenerator(document: document)
let url = try generator.generateURL(filename: "Example.pdf")
print(url)