//
// Created by Stéphane on 09.12.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNumerologieCyclesRealisations: View {
    @Binding var bdNatal: Date
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
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
    }
}
