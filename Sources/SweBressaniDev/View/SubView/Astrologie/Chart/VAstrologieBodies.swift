//
//  Created by Stéphane on 04.11.22.
//

import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieBodies: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var sbBodie: SweCore.Bodies
    @State var sbTransit: Bool

    public init(bsSwe: Binding<SweCore>, sbBodie: SweCore.Bodies, sbTransit: Bool) {
        self._bsSwe = bsSwe
        self._sbBodie = .init(initialValue: sbBodie)
        self._sbTransit = .init(initialValue: sbTransit)
    }

    public var body: some View {
        let colorStroke: Color = colorScheme == .light ? .black : .white
        VStack {
            DrawBodieLine(lines: bsSwe.bodie_lines(bodie: sbBodie, swTransit: sbTransit)).stroke(colorStroke, lineWidth: 1.0)
        }.frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
    }
}