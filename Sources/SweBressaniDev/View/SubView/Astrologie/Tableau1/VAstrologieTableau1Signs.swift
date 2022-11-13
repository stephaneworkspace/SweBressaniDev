//
//  Created by Stéphane on 06.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieTableau1Signs: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var sbBodie: SweCore.Bodies
    @State var stTransit: Bool
    let offset = 120.0

    public init(bsSwe: Binding<SweCore>, sbBodie: SweCore.Bodies, stTransit: Bool) {
        self._bsSwe = bsSwe
        self._sbBodie = .init(initialValue: sbBodie)
        self._stTransit = .init(initialValue: stTransit)
    }

    public var body: some View {
        if !stTransit {
            // Natal
            VStack {
                SVGView(contentsOf: try! bsSwe.swec.asset_sign(i: bsSwe.bodieSign(bodie: sbBodie, swTransit: false)))
                        .frame(width: 20.0, height: 20.0)
            }.frame(maxWidth: .infinity, alignment: .leading).offset(x: 145, y: 0)
        } else {
            // Transit
            VStack {
                SVGView(contentsOf: try! bsSwe.swec.asset_sign(i: bsSwe.bodieSign(bodie: sbBodie, swTransit: true)))
                        .frame(width: 20.0, height: 20.0)
            }.frame(maxWidth: .infinity, alignment: .leading).offset(x: 270, y: 0)
        }
        let degMinSec = bsSwe.bodieDegMinSec(bodie: sbBodie, swTransit: stTransit)
        VStack {
            Text("°")
        }.frame(maxWidth: .infinity, alignment: .leading).offset(x: !stTransit ? 195 : 195 + offset)
        VStack {
            Text(degMinSec.0.formatted())
        }.frame(maxWidth: 25, alignment: .trailing).offset(x: !stTransit ? 170 : 170 + offset)
        VStack {
            Text("'")
        }.frame(maxWidth: .infinity, alignment: .leading).offset(x: !stTransit ? 225 : 225 + offset)
        VStack {
            Text(degMinSec.1.formatted())
        }.frame(maxWidth: 25, alignment: .trailing).offset(x: !stTransit ? 200 : 200 + offset)
        VStack {
            Text("\"")
        }.frame(maxWidth: .infinity, alignment: .leading).offset(x: !stTransit ? 255 : 255 + offset)
        VStack {
            Text(degMinSec.2.formatted())
        }.frame(maxWidth: 25, alignment: .trailing).offset(x: !stTransit ? 230 : 230 + offset)
    }
}
