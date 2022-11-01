//
// Created by Stéphane on 24.10.22.
//

import Foundation
import SwiftUI

public struct DrawAstrologieView: View {
    //@Environment(\.colorScheme) var colorScheme: ColorScheme
    @State var swe_swift_ui: SweSwiftUi

    public init(swe_swift_ui: SweSwiftUi) {
        self.swe_swift_ui = swe_swift_ui
    }

    public var body: some View {
        VStack {
            swe_swift_ui.drawCircle(circles: swe_swift_ui.circles()).stroke(/*colorScheme == .light ? .black : .white*/ .black, lineWidth: 1.0)
        }.frame(width: swe_swift_ui.getSizeCGFLoat(), height: swe_swift_ui.getSizeCGFLoat())
    }
}