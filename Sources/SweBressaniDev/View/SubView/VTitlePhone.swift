//
//  File.swift
//  
//
//  Created by Stéphane on 16.01.23.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VTitlePhone: View {
    @State var stText: TextCore

    public init(stText: TextCore) {
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        HStack {
            Image(systemName: "teletype.answer")
                    .imageScale(IMAGESCALE)
                    .foregroundColor(FOREGROUNDCOLOR)
            Text("\(stText.phone())")
                    .font(FONTSYSTEMTITLEMEDIUM)
                    .clipped()
            Spacer()
        }
                .font(FONTSYSTEMTITLE)
                .clipped()
    }
}
