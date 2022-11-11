//
//  Created by Stéphane on 06.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VSelection: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @Binding var baBodies: [Bool]

    public init(bsSwe: Binding<SweCore>, baBodies: Binding<[Bool]>) {
        self._bsSwe = bsSwe
        self._baBodies = baBodies
    }

    public var body: some View {
        ZStack {
            ScrollView {
                VStack {
                    HStack {
                    }.frame(height: 40) // TODO ok pour iphone11 les autres je ne sais pas
                    Spacer()
                    ForEach(Array(zip(bsSwe.bodiesForLoop.indices, bsSwe.bodiesForLoop)), id: \.1) { i, b in
                        HStack {
                            Toggle(bsSwe.swec.text_bodie(i: b.rawValue), isOn: $baBodies[i])
                            GeometryReader { geometry in
                                SVGView(contentsOf: try! bsSwe.swec.asset_bodie(i: b.rawValue))
                                        .frame(width: 25, height: 25)
                                        .padding()
                            }
                        }
                    }
                }
            }
        }
    }
}