//
//  Created by Stéphane on 05.11.22.
//

import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieAngles: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var saAngle: SweCore.Angles

    public init(bsSwe: Binding<SweCore>, saAngle: SweCore.Angles) {
        self._bsSwe = bsSwe
        self._saAngle = .init(initialValue: saAngle)
    }

    public var body: some View {
        let l = bsSwe.angleLines(angle: saAngle)
        let colorStroke: Color = colorScheme == .light ? .black : .white
        VStack {
            DrawAngleLine(lines: l).stroke(colorStroke, lineWidth: 1.5)
        }.frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
    }
}