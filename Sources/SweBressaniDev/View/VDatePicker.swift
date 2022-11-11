//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

struct VDatePicker: View {
    @Binding var bdNatal: Date
    @State var text: TextCore

    var body: some View {
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