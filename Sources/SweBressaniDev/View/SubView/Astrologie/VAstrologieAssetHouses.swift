//
//  Created by Stéphane on 03.11.22.
//

import SwiftUI
import SVGView

public struct VAstrologieAssetHouses: View {
    @Binding var bsSwe: SweCore
    @State var siHouse: Int

    public init(bsSwe: Binding<SweCore>, siHouse: Int) {
        self._bsSwe = bsSwe
        self._siHouse = .init(initialValue: siHouse)
    }

    public var body: some View {
        let h = bsSwe.house(number: siHouse)
        VStack {
            GeometryReader { geometry in
                SVGView(contentsOf: try! bsSwe.swec.asset_house(i: siHouse))
                        .offset(x: h.oPx, y: h.oPy)
                        .frame(width: h.oSx, height: h.oSy)
            }
        }.frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
    }
}