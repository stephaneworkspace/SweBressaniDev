//
//  Created by Stéphane on 08.11.22.
//

import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieTableau2: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var sbTransit1: Bool
    @State var sbTransit2: Bool

    public init(bsSwe: Binding<SweCore>, sbTransit1: Bool, sbTransit2: Bool) {
        self._bsSwe = bsSwe
        self._sbTransit1 = .init(initialValue: sbTransit1)
        self._sbTransit2 = .init(initialValue: sbTransit2)
    }

    public var body: some View {
        ZStack {
            // Header
            VStack(spacing: 0) {
                ForEach(bsSwe.bodAng(), id: \.id) { b in
                    switch (b.bodAng) {
                    case .Bodie(let bodie):
                        if bodie != SweCore.Bodies.PartChance {
                            ZStack(alignment: .topLeading) {
                                VAstrologieTableau2Bodies(bsSwe: $bsSwe, sbBodie: bodie, siI: b.pos)
                            }
                        }
                    case .Angle(let angle):
                        ZStack(alignment: .topLeading) {
                            VAstrologieTableau2Angles(bsSwe: $bsSwe, saAngle: angle, siI: b.pos)
                        }
                    }
                }
            }
            // Border
            DrawAspectArray(size: Double(bsSwe.size)).stroke(colorScheme == .light ? .black : .white).offset(x: 7, y: -3)
            // Content
            let ba = bsSwe.bodAng()
            ForEach(ba, id: \.id) { b in
                ZStack(alignment: .topLeading) {
                    ForEach(b.pos...ba.count - 1, id: \.self) { i in // - 1 = - la part chance, car il y a 12 sous parts
                        let bodAng = bsSwe.bodAngAspectPos(bodAngPos: b.pos, swTransit1: sbTransit1, swTransit2: sbTransit2, y: i)
                        if bodAng.1 {
                            if (bodAng.0.pos1 >= ba.count - 3) { // -1 - voir commentaire au dessus
                            } else {
                                VAstrologieTableau2AspectsBodies(bsSwe: $bsSwe, saAspect: bodAng.0.aspect, siI: bodAng.0.pos1, sdY: Double(i))
                            }
                        }
                    }
                }
            }
        }
    }
}