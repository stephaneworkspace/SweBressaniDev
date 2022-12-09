//
// Created by Stéphane on 09.12.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNumerologieCyclesUniversels: View {
    @Binding var bdNatal: Date
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
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
    }
}
