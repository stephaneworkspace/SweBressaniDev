//
//  Created by Stéphane on 03.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieAssetBodies: View {
    @Binding var bsSwe: SweCore
    @State var sbBodie: SweCore.Bodies
    @State var sbTransit: Bool

    public init(bsSwe: Binding<SweCore>, sbBodie: SweCore.Bodies, sbTransit: Bool) {
        self._bsSwe = bsSwe
        self._sbBodie = .init(initialValue: sbBodie)
        self._sbTransit = .init(initialValue: sbTransit)
    }

    public var body: some View {
        VStack {
            let b = bsSwe.bodie(bodie: sbBodie, swTransit: sbTransit)
            GeometryReader { geometry in
                SVGView(contentsOf: try! bsSwe.swec.asset_bodie(i: sbBodie.rawValue))
                        .offset(x: b.oPx, y: b.oPy)
                        .frame(width: b.oSx, height: b.oSy)
                if (b.swRetrograde) {
                    SVGView(contentsOf: try! bsSwe.swec.asset_bodie_r(i: sbBodie.rawValue))
                            .offset(x: b.oPx + b.oSx / RETROGRADE_DIV, y: b.oPy + b.oSy / RETROGRADE_DIV)
                            .frame(width: b.oSx / RETROGRADE_SIZE_DIV, height: b.oSy / RETROGRADE_SIZE_DIV)
                }
            }
        }.frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
    }
}