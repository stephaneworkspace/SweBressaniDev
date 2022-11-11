//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

public struct VNamesTextField: View {
    @State var text: TextCore
    @State var ssFirstName: String
    @State var ssSecondName: String
    @State var ssThirdName: String
    @State var ssLastName1: String
    @State var ssLastName2: String
    @State var ssLastName3: String

    public var body: some View {
        VStack {
            HStack {
                Text("\(text.firstName())")
                        .font(FONTSYSTEM)
                        .clipped()
                Spacer()
            }
            TextField("\(text.firstName())", text: $ssFirstName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(text.secondName())", text: $ssSecondName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(text.thirdName())", text: $ssThirdName)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            HStack {
                Text("\(text.lastName())")
                        .font(FONTSYSTEM)
                        .clipped()
                Spacer()
            }
            TextField("\(text.lastName())", text: $ssLastName1)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(text.lastNameAux())", text: $ssLastName2)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
            TextField("\(text.lastNameAux())", text: $ssLastName3)
                    .textFieldStyle(RoundedBorderTextFieldStyle())
        }
                .font(FONTSYSTEM)
                .clipped()
    }
}