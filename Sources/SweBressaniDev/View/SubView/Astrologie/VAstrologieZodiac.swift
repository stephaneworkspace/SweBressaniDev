//
//  Created by Stéphane on 02.11.22.
//

import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieZodiac: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore

    public init(bsSwe: Binding<SweCore>) {
        self._bsSwe = bsSwe
    }

    public var body: some View {
        let colorStroke: Color = colorScheme == .light ? .black : .white
        VStack {
            DrawCircle(circles: bsSwe.circles()).stroke(colorStroke, lineWidth: 1.0)
        }
                .frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
        VStack {
            DrawLine(lines: bsSwe.zodiacLines()).stroke(colorStroke, lineWidth: 1.0)
        }
                .frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
    }
}