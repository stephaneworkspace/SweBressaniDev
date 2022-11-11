//
//  Created by Stéphane on 02.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieAssetSigns: View {
    @Binding var bsSwe: SweCore
    @State var siSign: Int

    public init(bsSwe: Binding<SweCore>, siSign: Int) {
        self._bsSwe = bsSwe
        self._siSign = .init(initialValue: siSign)
    }

    public var body: some View {
        VStack {
            let s = bsSwe.zodiacSign(sign: siSign)
            GeometryReader { geometry in
                SVGView(contentsOf: try! bsSwe.swec.asset_sign(i: siSign))
                        .offset(
                                x: s.oPx,
                                y: s.oPy)
                        .frame(
                                width: s.oSx,
                                height: s.oSy)
            }
        }.frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
    }
}