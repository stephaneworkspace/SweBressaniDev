//
// Created by Stéphane on 09.12.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNumerologieCyclesAdjacents: View {
    @Binding var bdNatal: Date
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
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
}