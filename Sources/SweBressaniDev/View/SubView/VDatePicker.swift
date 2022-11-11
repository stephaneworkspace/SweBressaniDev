//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VDatePicker: View {
    @Binding var bdNatal: Date
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>, stText: TextCore) {
        self._bdNatal = bdNatal
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        VStack {
            DatePicker("\(stText.birthDate())",
                    selection: $bdNatal,
                    displayedComponents: [.date, .hourAndMinute]
            )
                    .font(FONTSYSTEM)
                    .clipped()
        }
    }
}