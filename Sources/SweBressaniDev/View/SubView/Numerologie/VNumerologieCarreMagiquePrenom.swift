//
//  File.swift
//  
//
//  Created by Stéphane on 17.02.23.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNumerologieCarreMagiquePrenom: View {
    @Binding var bsFirstName: String
    @Binding var bsSecondName: String
    @Binding var bsThirdName: String
    @State var stText: TextCore
    
    public init(bsFirstName: Binding<String>,
                bsSecondName: Binding<String>,
                bsThirdName: Binding<String>,
                stText: TextCore) {
        self._bsFirstName = bsFirstName
        self._bsSecondName = bsSecondName
        self._bsThirdName = bsThirdName
        self._stText = .init(initialValue: stText)
    }
    
    public var body: some View {
        VStack {
            Text("Équilibre - " + bsFirstName)
            let cm2 = NumerologieCore.cm2(nom: bsFirstName)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm2[idx][jdx]))
                    }
                }
            }
        }
        VStack {
            Text("Équilibre - " + bsSecondName)
            let cm2 = NumerologieCore.cm2(nom: bsSecondName)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm2[idx][jdx]))
                    }
                }
            }
        }
        VStack {
            Text("Équilibre - " + bsThirdName)
            let cm2 = NumerologieCore.cm2(nom: bsThirdName)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm2[idx][jdx]))
                    }
                }
            }
        }
        VStack {
            Text("Équilibre - Prenom(s)")
            let cm2 = NumerologieCore.cm2(nom: bsFirstName
                    + " " + bsSecondName
                    + " " + bsThirdName)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm2[idx][jdx]))
                    }
                }
            }
        }
    }
}
