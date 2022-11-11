//
//  Created by Stéphane on 05.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieAssetAngles: View {
    @Binding var bsSwe: SweCore
    @State var saAngle: SweCore.Angles

    public init(bsSwe: Binding<SweCore>, saAngle: SweCore.Angles) {
        self._bsSwe = bsSwe
        self._saAngle = .init(initialValue: saAngle)
    }

    public var body: some View {
        VStack {
            let a = bsSwe.angle(a: saAngle)
            GeometryReader { geometry in
                SVGView(contentsOf: try! bsSwe.swec.asset_angle(i: Int(saAngle.rawValue)))
                        .offset(x: a.oPx, y: a.oPy)
                        .frame(width: a.oSx, height: a.oSy)
            }
        }.frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
    }
}