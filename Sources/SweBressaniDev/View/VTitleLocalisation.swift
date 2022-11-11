//
// Created by Stéphane on 06.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VTitleLocalisation: View {
    @State var stText: TextCore

    public init(stText: TextCore) {
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        HStack {
            Text("\(stText.localisation())")
            Spacer()
        }
                .font(FONTSYSTEM)
                .clipped()
    }
}
