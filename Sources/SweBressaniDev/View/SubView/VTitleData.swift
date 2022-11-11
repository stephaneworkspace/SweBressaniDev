//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VTitleData: View {
    @State var stText: TextCore

    public init(stText: TextCore) {
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        HStack {
            Image(systemName: "person")
                    .imageScale(IMAGESCALE)
                    .foregroundColor(FOREGROUNDCOLOR)
            Text("\(stText.data())")
                    .font(FONTSYSTEMTITLEMEDIUM)
                    .clipped()
            Spacer()
        }
                .font(FONTSYSTEMTITLE)
                .clipped()
    }
}
