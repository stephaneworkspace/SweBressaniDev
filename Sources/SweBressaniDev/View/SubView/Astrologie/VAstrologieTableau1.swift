//
// Created by Stéphane on 11.11.22.
//

import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieTableau1: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var saBodie: [Bool]

    public init(bsSwe: Binding<SweCore>, saBodie: [Bool]) {
        self._bsSwe = bsSwe
        self._saBodie = .init(initialValue: saBodie)
    }

    public var body: some View {
        VStack(spacing: 0) {
            ForEach(Array(zip(bsSwe.bodiesForLoop.indices, bsSwe.bodiesForLoop)), id: \.1) { i, b in
                if (saBodie[i]) {
                    ZStack(alignment: .topLeading) {
                        VAstrologieTableau1Bodies(bsSwe: $bsSwe, sbBodie: b)
                        VAstrologieTableau1Signs(bsSwe: $bsSwe, sbBodie: b, stTransit: false)
                        VAstrologieTableau1Signs(bsSwe: $bsSwe, sbBodie: b, stTransit: true)
                    }
                }
            }
        }
    }
}
