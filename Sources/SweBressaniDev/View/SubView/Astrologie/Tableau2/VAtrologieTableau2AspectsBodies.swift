//
//  Created by Stéphane on 08.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieTableau2AspectsBodies: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var saAspect: SweCore.Aspects
    @State var siI: Int
    @State var sdY: Double

    public init(bsSwe: Binding<SweCore>, saAspect: SweCore.Aspects, siI: Int, sdY: Double) {
        self._bsSwe = bsSwe
        self._saAspect = .init(initialValue: saAspect)
        self._siI = .init(initialValue: siI)
        self._sdY = .init(initialValue: sdY)
    }

    public var body: some View {
        let xPos = xPos(size: bsSwe.size, i: siI)
        let yPos = yPos(size: bsSwe.size, y: sdY)
        VStack {
            if (saAspect.rawValue >= 0) {
                SVGView(contentsOf: try! bsSwe.swec.asset_aspect(i: saAspect.rawValue)).frame(width: 16.0, height: 16.0)
            }
        }.frame(maxWidth: .infinity, alignment: .leading).offset(x: xPos, y: yPos)
    }

    func bodPos(size: Int) -> Double {
        Double((Double(size) / 2.0) * -1.0)
    }

    func cas(size: Int) -> Double {
        Double(size) / 16.0
    }

    func xPos(size: Int, i: Int) -> Double {
        let cas = cas(size: size)
        let bodPos = bodPos(size: size)
        let casDivx = 1.00
        let fix = 199.0
        return bodPos + (cas / 2.0) + (cas * Double(i) * casDivx) + fix
    }

    func yPos(size: Int, y: Double) -> Double {
        let cas = cas(size: size)
        let bodPos = bodPos(size: size)
        let casDiv = 1.0
        let fix = 49.5
        return bodPos + (cas * (y + 1.0) * casDiv) + fix;
    }
}