//
// Created by Stéphane on 24.10.22.
//

import Foundation
import SwiftUI

public struct DrawAstrologieLightView: View {
    @State var swe_swift_ui: SweSwiftUi

    public init(swe_swift_ui: SweSwiftUi) {
        self.swe_swift_ui = swe_swift_ui
    }

    public var body: some View {
        ZStack {
            VStack {
                swe_swift_ui.drawCircle(circles: swe_swift_ui.circles()).stroke(.black, lineWidth: 1.0)
            }.frame(width: CGFloat(swe_swift_ui.size), height: CGFloat(swe_swift_ui.size))
            VStack {
                swe_swift_ui.drawLine(lines: swe_swift_ui.zodiac_lines()).stroke(.black, lineWidth: 1.0)
            }.frame(width: CGFloat(swe_swift_ui.size), height: CGFloat(swe_swift_ui.size))
        }
    }
}

public struct DrawAstrologieDarkView: View {
    @State var swe_swift_ui: SweSwiftUi

    public init(swe_swift_ui: SweSwiftUi) {
        self.swe_swift_ui = swe_swift_ui
    }

    public var body: some View {
        VStack {
            swe_swift_ui.drawCircle(circles: swe_swift_ui.circles()).stroke(.white, lineWidth: 1.0)
        }.frame(width: CGFloat(swe_swift_ui.size), height: CGFloat(swe_swift_ui.size))
        VStack {
            swe_swift_ui.drawLine(lines: swe_swift_ui.zodiac_lines()).stroke(.white, lineWidth: 1.0)
        }.frame(width: CGFloat(swe_swift_ui.size), height: CGFloat(swe_swift_ui.size))
    }
}