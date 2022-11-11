//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VDatePicker: View {
    @Binding var bdNatal: Date
    @State var text: TextCore

    public init(bdNatal: Binding<Date>, text: TextCore) {
        self._bdNatal = bdNatal
        self._text = .init(initialValue: text)
    }

    public var body: some View {
        VStack {
            DatePicker("\(text.birthDate())",
                    selection: $bdNatal,
                    displayedComponents: [.date, .hourAndMinute]
            )
                    .font(FONTSYSTEM)
                    .clipped()
        }
    }
}