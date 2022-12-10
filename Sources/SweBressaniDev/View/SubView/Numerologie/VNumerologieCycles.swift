//
// Created by Stéphane on 09.12.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNumerologieCycles: View {
    @Binding var bdNatal: Date
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        VNumerologieCyclesAdjacents(bdNatal: $bdNatal, stText: stText)
        Divider()
        VNumerologieCyclesRealisations(bdNatal: $bdNatal, stText: stText)
        Divider()
        VNumerologieCyclesUniversels(bdNatal: $bdNatal, stText: stText)
        Divider()
    }
}