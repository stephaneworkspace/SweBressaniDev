//
// Created by Stéphane on 10.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VTitleNumerologie: View {
    @State var stText: TextCore

    public init(stText: TextCore) {
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        HStack {
            Image(systemName: "plus")
                    .imageScale(IMAGESCALE)
                    .foregroundColor(FOREGROUNDCOLOR)
            Text("\(stText.numerologie())")
                    .font(FONTSYSTEMTITLEMEDIUM)
                    .clipped()
            Spacer()
        }
                .font(FONTSYSTEMTITLE)
                .clipped()
    }
}
