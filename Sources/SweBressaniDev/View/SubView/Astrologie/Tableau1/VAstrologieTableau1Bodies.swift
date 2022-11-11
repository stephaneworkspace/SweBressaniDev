//
//  Created by Stéphane on 06.11.22.
//

import SwiftUI
import SVGView

@available(iOS 15, macOS 12.0, *)
public struct VAstrologieTableau1Bodies: View {
    @Environment(\.colorScheme) var colorScheme: ColorScheme
    @Binding var bsSwe: SweCore
    @State var sbBodie: SweCore.Bodies

    public init(bsSwe: Binding<SweCore>, sbBodie: SweCore.Bodies) {
        self._bsSwe = bsSwe
        self._sbBodie = .init(initialValue: sbBodie)
    }

    public var body: some View {
        VStack {
            SVGView(contentsOf: try! bsSwe.swec.asset_bodie(i: sbBodie.rawValue)).frame(width: 20.0, height: 20.0)
        }.frame(maxWidth: .infinity, alignment: .leading).offset(x: 5, y: 0)
        VStack {
            Text(bsSwe.swec.text_bodie(i: sbBodie.rawValue))
        }.frame(maxWidth: .infinity, alignment: .leading).offset(x: 30)
    }
}