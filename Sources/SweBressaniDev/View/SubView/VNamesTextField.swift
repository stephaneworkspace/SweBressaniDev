//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNamesTextField: View {
    @State var stText: TextCore
    @Binding var bsFirstName: String
    @Binding var bsSecondName: String
    @Binding var bsThirdName: String
    @Binding var bsLastName1: String
    @Binding var bsLastName2: String
    @Binding var bsLastName3: String

    public init(stText: TextCore,
                bsFirstName: Binding<String>,
                bsSecondName: Binding<String>,
                bsThirdName: Binding<String>,
                bsLastName1: Binding<String>,
                bsLastName2: Binding<String>,
                bsLastName3: Binding<String>) {
        self._stText = .init(initialValue: stText)
        self._bsFirstName = bsFirstName
        self._bsSecondName = bsSecondName
        self._bsThirdName = bsThirdName
        self._bsLastName1 = bsLastName1
        self._bsLastName2 = bsLastName2
        self._bsLastName3 = bsLastName3
    }

    public var body: some View {
        VStack {
            HStack {
                Text("\(stText.firstName())")
                        .font(FONTSYSTEM)
                        .clipped()
                Spacer()
            }
            TextField("\(stText.firstName())", text: $bsFirstName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.secondName())", text: $bsSecondName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.thirdName())", text: $bsThirdName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            HStack {
                Text("\(stText.lastName())")
                        .font(FONTSYSTEM)
                        .clipped()
                Spacer()
            }
            TextField("\(stText.lastName())", text: $bsLastName1)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.lastNameAux())", text: $bsLastName2)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.lastNameAux())", text: $bsLastName3)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
        }
                .font(FONTSYSTEM)
                .clipped()
    }
}