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
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                bsFirstName: Binding<String>,
                bsSecondName: Binding<String>,
                bsThirdName: Binding<String>,
                bsLastName1: Binding<String>,
                bsLastName2: Binding<String>,
                bsLastName3: Binding<String>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._bsFirstName = bsFirstName
        self._bsSecondName = bsSecondName
        self._bsThirdName = bsThirdName
        self._bsLastName1 = bsLastName1
        self._bsLastName2 = bsLastName2
        self._bsLastName3 = bsLastName3
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
                }
                Spacer()
                VStack {
                    Text("Cycle adjacents")
                            .multilineTextAlignment(.center)
                            .font(FONTSYSTEMTITLEMEDIUM)
                            .clipped()
                    HStack {
                        TextField("", text: .constant("\(stText.cycle())"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("\(stText.calcul())"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("\(stText.nombre())"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                            .font(FONTSYSTEM)
                            .clipped()
                    HStack {
                        TextField("", text: .constant("Formatif"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("Mois"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.cycleAdjacents(dBornDate: bdNatal, eCycle: .Formatif)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                            .font(FONTSYSTEMSMALL)
                            .clipped()
                    HStack {
                        TextField("", text: .constant("Productif"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("Jour"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.cycleAdjacents(dBornDate: bdNatal, eCycle: .Productif)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                            .font(FONTSYSTEMSMALL)
                            .clipped()
                    HStack {
                        TextField("", text: .constant("Moisson"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("Année"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.cycleAdjacents(dBornDate: bdNatal, eCycle: .Moisson)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                            .font(FONTSYSTEMSMALL)
                            .clipped()
                }
            }
            VStack {
                Text("\(stText.cycleRealisation())").multilineTextAlignment(.center)
                        .font(FONTSYSTEMTITLEMEDIUM)
                        .clipped()
                HStack {
                    TextField("", text: .constant("Age de à"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                    Spacer()
                    TextField("", text: .constant("Calcul"))
                            .disabled(true)
                            .multilineTextAlignment(.center)
                            .clipped()
                    Spacer()
                    TextField("", text: .constant("\(stText.nombre())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.trailing)
                            .clipped()
                }
                        .font(FONTSYSTEM)
                        .clipped()
                VStack {
                    HStack {
                        TextField("", text: .constant(stText.cycleRealisation(iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: bdNatal), eCycle: .JplusM)))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("J + M"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.jPlusMInt(dBornDate: bdNatal)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                    HStack {
                        TextField("", text: .constant(stText.cycleRealisation(iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: bdNatal), eCycle: .JplusA)))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("J + A"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.jPlusAInt(dBornDate: bdNatal)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                    HStack {
                        TextField("", text: .constant(stText.cycleRealisation(iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: bdNatal), eCycle: .UnplusDeux)))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("1 + 2"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.unPlusDeuxInt(dBornDate: bdNatal)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                    HStack {
                        TextField("", text: .constant(stText.cycleRealisation(iLivePath: NumerologieCore.cheminDeVieInt(dBornDate: bdNatal), eCycle: .MplusA)))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant("M + A"))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.center)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(NumerologieCore.mPlusAInt(dBornDate: bdNatal)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                }
                        .font(FONTSYSTEMSMALL)
                        .clipped()
            }
            VStack {
                Text("\(stText.cycleUniversels())")
                        .multilineTextAlignment(.center)
                        .font(FONTSYSTEMTITLEMEDIUM)
                        .clipped()
                HStack {
                    TextField("", text: .constant("\(stText.ageDe())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.leading)
                            .clipped()
                    Spacer()
                    TextField("", text: .constant("\(stText.nombre())"))
                            .disabled(true)
                            .textFieldStyle(.plain)
                            .multilineTextAlignment(.trailing)
                            .clipped()
                }
                        .font(FONTSYSTEM)
                        .clipped()
                ForEach(1...9, id: \.self) { idx in
                    HStack {
                        TextField("", text: .constant(stText.cycleUniversel(iNombre: idx)))
                                .disabled(true)
                                .textFieldStyle(.plain)
                                .multilineTextAlignment(.leading)
                                .clipped()
                        Spacer()
                        TextField("", text: .constant(String(idx)))
                                .disabled(true)
                                .textFieldStyle(RoundedBorderTextFieldStyle())
                                .multilineTextAlignment(.trailing)
                                .clipped()
                    }
                            .font(FONTSYSTEMSMALL)
                            .clipped()
                }
            }
            VStack {
                let cm = NumerologieCore.cm(nom: bsFirstName
                        + " " + bsSecondName
                        + " " + bsThirdName
                        + " " + bsLastName1
                        + " " + bsLastName2
                        + " " + bsLastName3)
                ForEach(0..<3, id: \.self) { idx in
                    HStack {
                        ForEach(0..<3, id: \.self) { jdx in
                            Text(String(cm[idx][jdx]))
                        }
                    }
                }
            }
            Button(action: {
                let pdf = try! NumerologieCore.pdf(natal: bdNatal)
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
            Spacer()
        }
    }
}