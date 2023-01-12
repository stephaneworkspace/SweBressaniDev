//
//  File.swift
//  
//
//  Created by Stéphane on 12.01.23.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VTitlePersonaliteJuridique: View {
    @State var stText: TextCore

    public init(stText: TextCore) {
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        HStack {
            Image(systemName: "person.text.rectangle")
                    .imageScale(IMAGESCALE)
                    .foregroundColor(FOREGROUNDCOLOR)
            Text("\(stText.personaliteJuridique())")
                    .font(FONTSYSTEMTITLEMEDIUM)
                    .clipped()
            Spacer()
        }
                .font(FONTSYSTEMTITLE)
                .clipped()
    }
}
