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
                VTitlePersonaliteJuridique(stText: stText)
                VStack {
                    HStack {
                        TextField("", text: .constant("\(stText.firstName())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsFirstName)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsFirstName)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                    .font(FONTSYSTEM)
                    .clipped()
                    HStack {
                        TextField("", text: .constant("\(stText.secondName())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsSecondName)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsSecondName)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                    .font(FONTSYSTEM)
                    .clipped()
                    HStack {
                        TextField("", text: .constant("\(stText.thirdName())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsThirdName)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsThirdName)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                    .font(FONTSYSTEM)
                    .clipped()
                    HStack {
                        TextField("", text: .constant("\(stText.lastName())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsLastName1)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsLastName1)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                    .font(FONTSYSTEM)
                    .clipped()
                    HStack {
                        TextField("", text: .constant("\(stText.lastNameAux())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsLastName2)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsLastName2)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                    .font(FONTSYSTEM)
                    .clipped()
                    HStack {
                        TextField("", text: .constant("\(stText.lastNameAux())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsLastName3)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsLastName3)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                    .font(FONTSYSTEM)
                    .clipped()
                }
                VTitlePhone(stText: stText)
                VStack {
                    HStack {
                        TextField("", text: .constant("\(stText.tel())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsTel)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsTel)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                    HStack {
                        TextField("", text: .constant("\(stText.mobile())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant("\(bsMobile)"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.center)
                            .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.chaineDeCaractereVersNombreReduction(chars: bsMobile)))
                            .disabled(true)
                            .textFieldStyle(RoundedBorderTextFieldStyle())
                            .multilineTextAlignment(.trailing)
                            .clipped()
                    }
                }
                .font(FONTSYSTEM)
                .clipped()
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
