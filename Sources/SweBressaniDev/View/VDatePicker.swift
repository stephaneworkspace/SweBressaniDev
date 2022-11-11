//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

public struct VDatePicker: View {
    @Binding var bdNatal: Date
    @State var text: TextCore

    public init(bdNatal: Binding<Date>, text: State<TextCore>) {
        self._bdNatal = bdNatal
        self._text = text
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