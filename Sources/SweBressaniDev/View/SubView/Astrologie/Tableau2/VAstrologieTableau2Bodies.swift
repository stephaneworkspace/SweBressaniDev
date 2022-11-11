//
//  Created by Stéphane on 08.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieTableau2Bodies: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var sbBodie: SweCore.Bodies
    @State var siI: Int

    public init(bsSwe: Binding<SweCore>, sbBodie: SweCore.Bodies, siI: Int) {
        self._bsSwe = bsSwe
        self._sbBodie = .init(initialValue: sbBodie)
        self._siI = .init(initialValue: siI)
    }

    public var body: some View {
        let xPos = xPos(size: bsSwe.size, i: siI)
        let yPos = yPos(i: siI)
        VStack {
            SVGView(contentsOf: try! bsSwe.swec.asset_bodie(i: sbBodie.rawValue)).frame(width: 20.0, height: 20.0)
        }.frame(maxWidth: .infinity, alignment: .leading).offset(x: xPos, y: yPos)
    }

    func bodPos(size: Int) -> Double {
        (Double(size) / 2.0) * -1.0
    }

    func cas(size: Int) -> Double {
        Double(size) / 16.0
    }

    func xPos(size: Int, i: Int) -> Double {
        let fix = 210.0
        let bodPos = bodPos(size: size)
        let cas = cas(size: size)
        return bodPos + (cas * Double(i)) + fix
    }

    func yPos(i: Int) -> Double {
        switch (i) {
        case 1:
            return Double(i) * 2.0
        case 2:
            return Double(i) * 3.0
        case 3:
            return Double(i) * 5.0
        default:
            return Double(i) * 5.0
        }
    }
}