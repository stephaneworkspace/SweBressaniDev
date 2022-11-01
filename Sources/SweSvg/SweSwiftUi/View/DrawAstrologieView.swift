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
        ForEach(1...12, id: \.self) { idx in
            VStack {
                GeometryReader { geometry in
                        Image(String(format: "asset_%d_sign.svg", idx))
                            .resizable()
                            .offset(
                                    x: swe_swift_ui.zodiac_sign(sign: Int32(idx)).oPx,
                                    y: swe_swift_ui.zodiac_sign(sign: Int32(idx)).oPy)
                            .frame(
                                    width: swe_swift_ui.zodiac_sign(sign: Int32(idx)).oSx,
                                    height: swe_swift_ui.zodiac_sign(sign: Int32(idx)).oSy)
                }
            }.frame(width: CGFloat(swe_swift_ui.size), height: CGFloat(swe_swift_ui.size))
        }
    }
}