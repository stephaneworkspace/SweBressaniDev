//
// Created by Stéphane on 05.09.22.
//

import Foundation
import SwiftUI

public struct VTitleData: View {
    @State var text: TextCore

    public var body: some View {
        HStack {
            Image(systemName: "person")
                    .imageScale(IMAGESCALE)
                    .foregroundColor(FOREGROUNDCOLOR)
            Text("\(text.data())")
                    .font(FONTSYSTEMTITLEMEDIUM)
                    .clipped()
            Spacer()
        }
                .font(FONTSYSTEMTITLE)
                .clipped()
    }
}
