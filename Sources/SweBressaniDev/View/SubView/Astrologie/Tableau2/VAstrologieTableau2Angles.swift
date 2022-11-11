//
//  Created by Stéphane on 08.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieTableau2Angles: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var saAngle: SweCore.Angles
    @State var siI: Int
    let fix = -150.0
    let bodPos = CGFloat((300 / 2) * -1)
    let cas = Double(300) / 16.0
    let casDiv = 1.1

    public init(bsSwe: Binding<SweCore>, saAngle: SweCore.Angles, siI: Int) {
        self._bsSwe = bsSwe
        self._saAngle = .init(initialValue: saAngle)
        self._siI = .init(initialValue: siI)
    }

    public var body: some View {
        let xPos = xPos(size: bsSwe.size, i: siI)
        let yPos = yPos(i: siI, angle: saAngle)
        VStack {
            SVGView(contentsOf: try! bsSwe.swec.asset_angle(i: Int(saAngle.rawValue))).frame(width: 20.0, height: 20.0)
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

    func yPos(i: Int, angle: SweCore.Angles) -> Double {
        if (angle == SweCore.Angles.Mc) {
            return Double(i) * 5.2
        } else {
            return Double(i) * 5.0
        }
    }
}