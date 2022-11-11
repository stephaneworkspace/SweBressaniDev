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
let natal = Date()

let document = PDFDocument(format: .a4)

// Numérologie
document.add(.contentCenter, text: text.numerologie())
var table = PDFTable(rows: 3, columns: 2)
var style = PDFTableStyle()
style.rowHeaderCount = 0
style.columnHeaderCount = 0
table.style = style
var lineStyle = PDFLineStyle(width: 1)
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
table[0,1].alignment = .right
table[1,1].alignment = .right
table[2,1].alignment = .right
table[0,0].content = try! PDFTableContent(content: text.born())
table[0,1].content = try! PDFTableContent(content: String(NumerologieCore.date(dBornDate: natal)))
table[1,0].content = try! PDFTableContent(content: text.age())
table[1,1].content = try! PDFTableContent(content: String(NumerologieCore.age(dBornDate: natal)))
table[2,0].content = try! PDFTableContent(content: text.lifePath())
table[2,1].content = try! PDFTableContent(content: String(NumerologieCore.cheminDeVie(dBornDate: natal)))
document.add(table: table)

// Cycle adjacents
document.add(.contentCenter, text: "Cycle adjacents") // TODO
table = PDFTable(rows: 4, columns: 3)
style = PDFTableStyle()
style.rowHeaderCount = 0
style.columnHeaderCount = 0
table.style = style
lineStyle = PDFLineStyle(width: 1)
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
table[0,0].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
table[1,0].style = cellStyle
table[2,0].style = cellStyle
table[3,0].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
table[0,1].style = cellStyle
table[0,2].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
table[1,1].style = cellStyle
table[2,1].style = cellStyle
table[3,1].style = cellStyle
table[1,2].style = cellStyle
table[2,2].style = cellStyle
table[3,2].style = cellStyle
table[0,0].alignment = .left
table[1,0].alignment = .left
table[2,0].alignment = .left
table[3,0].alignment = .left
table[0,1].alignment = .center
table[1,1].alignment = .center
table[2,1].alignment = .center
table[3,1].alignment = .center
table[0,2].alignment = .right
table[1,2].alignment = .right
table[2,2].alignment = .right
table[3,2].alignment = .right
table[0,0].content = try! PDFTableContent(content: text.cycle())
table[0,1].content = try! PDFTableContent(content: text.calcul())
table[0,2].content = try! PDFTableContent(content: text.nombre())
table[1,0].content = try! PDFTableContent(content: "Formatif") // TODO
table[2,0].content = try! PDFTableContent(content: "Productif") // TODO
table[3,0].content = try! PDFTableContent(content: "Moisson") // TODO
table[1,1].content = try! PDFTableContent(content: "Mois") // TODO
table[2,1].content = try! PDFTableContent(content: "Jour") // TODO
table[3,1].content = try! PDFTableContent(content: "Année") // TODO
table[1,2].content = try! PDFTableContent(content: NumerologieCore.cycleAdjacents(dBornDate: natal, eCycle: .Formatif))
table[2,2].content = try! PDFTableContent(content: NumerologieCore.cycleAdjacents(dBornDate: natal, eCycle: .Productif))
table[3,2].content = try! PDFTableContent(content: NumerologieCore.cycleAdjacents(dBornDate: natal, eCycle: .Moisson))
document.add(table: table)

// Cycle de réalisation
document.add(.contentCenter, text: text.cycleRealisation())
table = PDFTable(rows: 5, columns: 3)
style = PDFTableStyle()
style.rowHeaderCount = 0
style.columnHeaderCount = 0
table.style = style
lineStyle = PDFLineStyle(width: 1)
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, top: lineStyle, right: lineStyle, bottom: lineStyle))
table[0,0].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(left: lineStyle, right: lineStyle, bottom: lineStyle))
table[1,0].style = cellStyle
table[2,0].style = cellStyle
table[3,0].style = cellStyle
table[4,0].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(top: lineStyle, right: lineStyle, bottom: lineStyle))
table[0,1].style = cellStyle
table[0,2].style = cellStyle
cellStyle = PDFTableCellStyle(borders: PDFTableCellBorders(right: lineStyle, bottom: lineStyle))
table[1,1].style = cellStyle
table[2,1].style = cellStyle
table[3,1].style = cellStyle
table[4,1].style = cellStyle
table[1,2].style = cellStyle
table[2,2].style = cellStyle
table[3,2].style = cellStyle
table[4,2].style = cellStyle
table[0,0].alignment = .left
table[1,0].alignment = .left
table[2,0].alignment = .left
table[3,0].alignment = .left
table[4,0].alignment = .left
table[0,1].alignment = .center
table[1,1].alignment = .center
table[2,1].alignment = .center
table[3,1].alignment = .center
table[4,1].alignment = .center
table[0,2].alignment = .right
table[1,2].alignment = .right
table[2,2].alignment = .right
table[3,2].alignment = .right
table[4,2].alignment = .right
table[0,0].content = try! PDFTableContent(content: "Age de à") // TODO
table[0,1].content = try! PDFTableContent(content: text.calcul())
table[0,2].content = try! PDFTableContent(content: text.nombre())
table[1,0].content = try! PDFTableContent(content: text.cycleRealisation(
        iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .JplusM))
table[2,0].content = try! PDFTableContent(content: text.cycleRealisation(
        iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .JplusA))
table[3,0].content = try! PDFTableContent(content: text.cycleRealisation(
        iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .UnplusDeux))
table[4,0].content = try! PDFTableContent(content: text.cycleRealisation(
        iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: natal), eCycle: .MplusA))
table[1,1].content = try! PDFTableContent(content: "J + M") // TODO
table[2,1].content = try! PDFTableContent(content: "J + A") // TODO
table[3,1].content = try! PDFTableContent(content: "1 + 2") // TODO
table[4,1].content = try! PDFTableContent(content: "M + A") // TODO
table[1,2].content = try! PDFTableContent(content: NumerologieCore.jPlusMInt(dBornDate: natal))
table[2,2].content = try! PDFTableContent(content: NumerologieCore.jPlusAInt(dBornDate: natal))
table[3,2].content = try! PDFTableContent(content: NumerologieCore.unPlusDeuxInt(dBornDate: natal))
table[4,2].content = try! PDFTableContent(content: NumerologieCore.mPlusAInt(dBornDate: natal))
document.add(table: table)

let generator = PDFGenerator(document: document)
let url = try generator.generateURL(filename: "Example.pdf")
print(url)