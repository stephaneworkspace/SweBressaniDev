//
//  File.swift
//  
//
//  Created by Stéphane on 17.02.23.
//

import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNumerologieCarreMagiqueNom: View {
    @Binding var bsLastName1: String
    @Binding var bsLastName2: String
    @Binding var bsLastName3: String
    @State var stText: TextCore
    
    public init(bsLastName1: Binding<String>,
                bsLastName2: Binding<String>,
                bsLastName3: Binding<String>,
                stText: TextCore) {
        self._bsLastName1 = bsLastName1
        self._bsLastName2 = bsLastName2
        self._bsLastName3 = bsLastName3
        self._stText = .init(initialValue: stText)
    }
    
    public var body: some View {
        VStack {
            Text("Équilibre - " + bsLastName1)
            let cm2 = NumerologieCore.cm2(nom: bsLastName1)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm2[idx][jdx]))
                    }
                }
            }
        }
        VStack {
            Text("Équilibre - " + bsLastName2)
            let cm2 = NumerologieCore.cm2(nom: bsLastName2)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm2[idx][jdx]))
                    }
                }
            }
        }
        VStack {
            Text("Équilibre - " + bsLastName3)
            let cm2 = NumerologieCore.cm2(nom: bsLastName3)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm2[idx][jdx]))
                    }
                }
            }
        }
        VStack {
            Text("Équilibre - Nom(s)")
            let cm2 = NumerologieCore.cm2(nom: bsLastName1
                                          + " " + bsLastName2
                                          + " " + bsLastName3)
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
