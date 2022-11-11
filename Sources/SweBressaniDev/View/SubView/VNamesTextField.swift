//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNamesTextField: View {
    @State var stText: TextCore
    @State var ssFirstName: String
    @State var ssSecondName: String
    @State var ssThirdName: String
    @State var ssLastName1: String
    @State var ssLastName2: String
    @State var ssLastName3: String

    public init(stText: TextCore,
                ssFirstName: String,
                ssSecondName: String,
                ssThirdName: String,
                ssLastName1: String,
                ssLastName2: String,
                ssLastName3: String) {
        self._stText = .init(initialValue: stText)
        self._ssFirstName = .init(initialValue: ssFirstName)
        self._ssSecondName = .init(initialValue: ssSecondName)
        self._ssThirdName = .init(initialValue: ssThirdName)
        self._ssLastName1 = .init(initialValue: ssLastName1)
        self._ssLastName2 = .init(initialValue: ssLastName2)
        self._ssLastName3 = .init(initialValue: ssLastName3)
    }

    public var body: some View {
        VStack {
            HStack {
                Text("\(stText.firstName())")
                        .font(FONTSYSTEM)
                        .clipped()
                Spacer()
            }
            TextField("\(stText.firstName())", text: $ssFirstName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.secondName())", text: $ssSecondName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.thirdName())", text: $ssThirdName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            HStack {
                Text("\(stText.lastName())")
                        .font(FONTSYSTEM)
                        .clipped()
                Spacer()
            }
            TextField("\(stText.lastName())", text: $ssLastName1)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.lastNameAux())", text: $ssLastName2)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(stText.lastNameAux())", text: $ssLastName3)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
        }
                .font(FONTSYSTEM)
                .clipped()
    }
}