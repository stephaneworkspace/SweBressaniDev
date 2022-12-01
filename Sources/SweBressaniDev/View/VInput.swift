//
// Created by Stéphane on 03.09.22.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VInput: View {
    @Binding var bdNatal: Date
    @Binding var bsFirstName: String
    @Binding var bsSecondName: String
    @Binding var bsThirdName: String
    @Binding var bsLastName1: String
    @Binding var bsLastName2: String
    @Binding var bsLastName3: String
    @Binding var bdLat: Double
    @Binding var bdLng: Double
    @Binding var biTimeZone: Int
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                bsFirstName: Binding<String>,
                bsSecondName: Binding<String>,
                bsThirdName: Binding<String>,
                bsLastName1: Binding<String>,
                bsLastName2: Binding<String>,
                bsLastName3: Binding<String>,
                bdLat: Binding<Double>,
                bdLng: Binding<Double>,
                biTimeZone: Binding<Int>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._bsFirstName = bsFirstName
        self._bsSecondName = bsSecondName
        self._bsThirdName = bsThirdName
        self._bsLastName1 = bsLastName1
        self._bsLastName2 = bsLastName2
        self._bsLastName3 = bsLastName3
        self._bdLat = bdLat
        self._bdLng = bdLng
        self._biTimeZone = biTimeZone
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        VStack {
            VTitleData(stText: stText)
            VDatePicker(bdNatal: $bdNatal, stText: stText)
            VNamesTextField(
                    stText: stText,
                    bsFirstName: $bsFirstName,
                    bsSecondName: $bsSecondName,
                    bsThirdName: $bsThirdName,
                    bsLastName1: $bsLastName1,
                    bsLastName2: $bsLastName2,
                    bsLastName3: $bsLastName3
            )
            VTitleLocalisation(stText: stText)
            VLocalisationTextFieldIOs(bdLat: $bdLat, bdLng: $bdLng, biTimeZone: $biTimeZone, stText: stText)
        }
    }
}