//
// Created by Stéphane on 11.11.22.
//

import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieChart: View {
    @Binding var bsSwe: SweCore
    @Binding var baBodies: [Bool]

    public init(bsSwe: Binding<SweCore>, baBodies: Binding<[Bool]>) {
        self._bsSwe = bsSwe
        self._baBodies = baBodies
    }

    public var body: some View {
        ZStack {
            VAstrologieZodiac(bsSwe: $bsSwe)
            ForEach(1...12, id: \.self) { i in
                VAstrologieAssetSigns(bsSwe: $bsSwe, siSign: i)
            }
            ForEach(1...4, id: \.self) { i in
                let angle = SweCore.Angles(rawValue: Int32(i))!
                VAstrologieAssetAngles(bsSwe: $bsSwe, saAngle: angle)
                VAstrologieAngles(bsSwe: $bsSwe, saAngle: angle)
            }
            VAstrologieHouses(bsSwe: $bsSwe)
            ForEach(1...12, id: \.self) { i in
                VAstrologieAssetHouses(bsSwe: $bsSwe, siHouse: i)
            }
            //
            ForEach(Array(zip(bsSwe.bodiesForLoop.indices, bsSwe.bodiesForLoop)), id: \.1) { i, b in
                if (baBodies[i]) {
                    VAstrologieBodies(bsSwe: $bsSwe, sbBodie: b, sbTransit: false)
                    VAstrologieBodies(bsSwe: $bsSwe, sbBodie: b, sbTransit: true)
                    VAstrologieAssetBodies(bsSwe: $bsSwe, sbBodie: b, sbTransit: false)
                    VAstrologieAssetBodies(bsSwe: $bsSwe, sbBodie: b, sbTransit: true)
                }
            }
            // aspect
            ForEach(SweCore.Aspects.Conjunction.rawValue...SweCore.Aspects.Semisextile.rawValue, id: \.self) { i in
                // aspect type
                ForEach(SweCore.AspectType.Natal.rawValue...SweCore.AspectType.NatalAndTransit.rawValue, id: \.self) { j in
                    let aspect = SweCore.Aspects.init(rawValue: i)!
                    let aspectType = SweCore.AspectType.init(rawValue: j)!
                    let aspectColor = aspect.color()
                    let aspectStyle = aspect.style()
                    let lines = bsSwe.aspectLines(swBodies: baBodies, aspect: aspect, aspectType: aspectType)
                    if lines.count > 0 {
                        VStack {
                            DrawAspectLines(lines: lines).stroke(aspectColor, style: aspectStyle)
                        }.frame(width: CGFloat(bsSwe.size), height: CGFloat(bsSwe.size))
                    }
                }
            }
        }
    }
}
