//
// Created by Stéphane on 11.01.23.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VTelField: View {
    @State var stText: TextCore
    @Binding var bsTel: String
    @Binding var bsMobile: String

    public init(stText: TextCore,
                bsTel: Binding<String>,
                bsMobile: Binding<String>) {
        self._stText = .init(initialValue: stText)
        self._bsTel = bsTel
        self._bsMobile = bsMobile
    }

    public var body: some View {
        VStack {
            TextField("\(stText.tel())", text: $bsTel)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.mobile())", text: $bsMobile)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
        }
                .font(FONTSYSTEM)
                .clipped()
    }
}