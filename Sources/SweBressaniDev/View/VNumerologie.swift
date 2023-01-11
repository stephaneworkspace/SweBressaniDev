//
// Created by Stéphane on 10.09.22.
//

import Foundation
import SwiftUI
import WebKit
import PDFKit

@available(iOS 15, macOS 12.0, *)
public struct VNumerologie: View {
    @Binding var bdNatal: Date
    @Binding var bsFirstName: String
    @Binding var bsSecondName: String
    @Binding var bsThirdName: String
    @Binding var bsLastName1: String
    @Binding var bsLastName2: String
    @Binding var bsLastName3: String
    @Binding var bsTel: String
    @Binding var bsMobile: String
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                bsFirstName: Binding<String>,
                bsSecondName: Binding<String>,
                bsThirdName: Binding<String>,
                bsLastName1: Binding<String>,
                bsLastName2: Binding<String>,
                bsLastName3: Binding<String>,
                bsTel: Binding<String>,
                bsMobile: Binding<String>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._bsFirstName = bsFirstName
        self._bsSecondName = bsSecondName
        self._bsThirdName = bsThirdName
        self._bsLastName1 = bsLastName1
        self._bsLastName2 = bsLastName2
        self._bsLastName3 = bsLastName3
        self._bsTel = bsTel
        self._bsMobile = bsMobile
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        ScrollView {
            VStack {
                VTitleNumerologie(stText: stText)
                VStack {
                    HStack {
                        Text("\(stText.born())")
                        Spacer()
                        Text("\(String(NumerologieCore.date(dBornDate: bdNatal)))")
                    }
                    HStack {
                        Text("\(stText.age())")
                        Spacer()
                        Text("\(String(NumerologieCore.age(dBornDate: bdNatal)))")
                    }
                    HStack {
                        Text("\(stText.lifePath())")
                        Spacer()
                        Text("\(NumerologieCore.cheminDeVie(dBornDate: bdNatal))")
                    }
                    HStack {
                        let iAp = anneeEnCours()
                        Text("Année personelle " + String(iAp))
                        Spacer()
                        Text("\(NumerologieCore.ap(dBornDate: bdNatal))")
                    }
                }
                Spacer()
            }
            Divider()
            VNumerologieCycles(bdNatal: $bdNatal, stText: stText)
            VNumerologieCarreMagique(
                    bdNatal: $bdNatal,
                    bsFirstName: $bsFirstName,
                    bsSecondName: $bsSecondName,
                    bsThirdName: $bsThirdName,
                    bsLastName1: $bsLastName1,
                    bsLastName2: $bsLastName2,
                    bsLastName3: $bsLastName3,
                    bsTel: $bsTel,
                    bsMobile: $bsMobile,
                    stText: stText)
            Button(action: {
                let pdf = try! NumerologieCore.pdf(natal: bdNatal, nom: bsFirstName
                        + " " + bsSecondName
                        + " " + bsThirdName
                        + " " + bsLastName1
                        + " " + bsLastName2
                        + " " + bsLastName3)
                //let size = (595.0, 842.0)
                #if os(iOS)
                let printInfo = UIPrintInfo(dictionary: nil)
                printInfo.outputType = UIPrintInfo.OutputType.general
                printInfo.jobName = "Theme de numérologie" // TODO
                let printController = UIPrintInteractionController.shared
                printController.printInfo = printInfo
                printController.printingItem = pdf
                //let paper = UIPrintPaper.bestPaperForPageSize(CGSize(size), withPapersFromArray: [UIPrintPaper])
                //printController.choosePaper = paper
                printController.present(animated: true, completionHandler: nil)
                #endif
            }, label: {
                VStack {
                    Text("Imprimer") // TODO
                            .padding()
                            .foregroundColor(.black)
                            .background(Color.white)
                            .mask(RoundedRectangle(cornerRadius: 30, style: .continuous))
                            .shadow(color: Color(#colorLiteral(red: 0, green: 0, blue: 0, alpha: 1)).opacity(0.3), radius: 10, x: 0, y: 10)
                            .padding()
                            .frame(maxWidth: 300)
                }
            })
            //Spacer()
        }
    }
    func anneeEnCours() -> String {
        let dateFormatter = DateFormatter()
        dateFormatter.dateFormat = "YYYY"
        let iyyyy = Int(dateFormatter.string(from: Date())) ?? 0
        return String(iyyyy)
    }
}