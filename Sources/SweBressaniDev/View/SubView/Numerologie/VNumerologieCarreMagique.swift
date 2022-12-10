//
// Created by Stéphane on 10.12.22.
//


import Foundation
import SwiftUI

@available(iOS 15, macOS 12.0, *)
public struct VNumerologieCarreMagique: View {
    @Binding var bdNatal: Date
    @Binding var bsFirstName: String
    @Binding var bsSecondName: String
    @Binding var bsThirdName: String
    @Binding var bsLastName1: String
    @Binding var bsLastName2: String
    @Binding var bsLastName3: String
    @State var stText: TextCore

    public init(bdNatal: Binding<Date>,
                bsFirstName: Binding<String>,
                bsSecondName: Binding<String>,
                bsThirdName: Binding<String>,
                bsLastName1: Binding<String>,
                bsLastName2: Binding<String>,
                bsLastName3: Binding<String>,
                stText: TextCore) {
        self._bdNatal = bdNatal
        self._bsFirstName = bsFirstName
        self._bsSecondName = bsSecondName
        self._bsThirdName = bsThirdName
        self._bsLastName1 = bsLastName1
        self._bsLastName2 = bsLastName2
        self._bsLastName3 = bsLastName3
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        VStack {
            Text("Carré magique")
            let cm = NumerologieCore.cm(nom: bsFirstName
                    + " " + bsSecondName
                    + " " + bsThirdName
                    + " " + bsLastName1
                    + " " + bsLastName2
                    + " " + bsLastName3)
            ForEach(0..<3, id: \.self) { idx in
                HStack {
                    ForEach(0..<3, id: \.self) { jdx in
                        Text(String(cm[idx][jdx]))
                    }
                }
            }
        }
        Divider()
        VStack {
            Text("Équilibre")
            let cm2 = NumerologieCore.cm2(nom: bsFirstName
                    + " " + bsSecondName
                    + " " + bsThirdName
                    + " " + bsLastName1
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
        Divider()
        VStack {
            HStack {
                let prenom = concat(un: bsFirstName, deux: bsSecondName, trois: bsThirdName)
                VStack {
                    let cmGauche = NumerologieCore.cmGauche(nom: prenom)
                    Text("Voyelle(s)")
                    ForEach(0..<prenom.count, id: \.self) { idx in
                        HStack {
                            if cmGauche.0[idx].0 == 0 {
                                Text("/")
                            } else {
                                Text(String(cmGauche.0[idx].0))
                                if cmGauche.0[idx].0 != cmGauche.0[idx].1 {
                                    Text(String(cmGauche.0[idx].1))
                                }
                            }
                        }
                    }
                    HStack {
                        Text("=")
                    }
                    HStack {
                        Text(String(cmGauche.1.0))
                        Text(String(cmGauche.1.1))
                    }
                }
                VStack {
                    let prenom = NumerologieCore.lettres(nom: prenom)
                    //Text("Prénom")
                    ForEach(0..<prenom.count, id: \.self) { idx in
                        Text(prenom[idx])
                    }
                }
                VStack {
                    let cmDroite = NumerologieCore.cmDroite(nom: prenom)
                    Text("Consonne(s)")
                    ForEach(0..<prenom.count, id: \.self) { idx in
                        HStack {
                            if cmDroite.0[idx].0 == 0 {
                                Text("/")
                            } else {
                                Text(String(cmDroite.0[idx].0))
                                if cmDroite.0[idx].0 != cmDroite.0[idx].1 {
                                    Text(String(cmDroite.0[idx].1))
                                }
                            }
                        }
                    }
                    HStack {
                        Text("=")
                    }
                    HStack {
                        Text(String(cmDroite.1.0))
                        Text(String(cmDroite.1.1))
                    }
                }
            }
            Divider()
            HStack {
                let nom = concat(un: bsLastName1, deux: bsLastName2, trois: bsLastName3)
                VStack {
                    let cmGauche = NumerologieCore.cmGauche(nom: nom)
                    let cmDroite = NumerologieCore.cmDroite(nom: nom)
                    let nomL = NumerologieCore.lettres(nom: nom)
                    HStack {
                        Spacer()
                        Text("Voyelle(s)")
                                .multilineTextAlignment(.leading)
                        Text("Nom")
                                .multilineTextAlignment(.center)
                        Text("Consonne(s)")
                                .multilineTextAlignment(.trailing)
                        Spacer()
                    }
                    ForEach(0..<nom.count, id: \.self) { idx in
                        HStack {
                            Spacer()
                            Text(String(cmGauche.0[idx].1))
                                    .multilineTextAlignment(.leading)
                            Spacer()
                            Text(nomL[idx])
                                    .multilineTextAlignment(.center)
                            Spacer()
                            Text(String(cmDroite.0[idx].1))
                                    .multilineTextAlignment(.trailing)
                            Spacer()
                        }
                    }
                    HStack {
                        Text("=")
                    }
                    HStack {
                        Spacer()
                        if cmGauche.1.2 {
                            Text(String(cmGauche.1.0) + "*")
                                    .multilineTextAlignment(.center)
                        } else {
                            Text(String(cmGauche.1.0))
                                    .multilineTextAlignment(.center)
                        }
                        if cmGauche.1.3 {
                            Text(String(cmGauche.1.1) + "*")
                                    .multilineTextAlignment(.center)
                        } else {
                            Text(String(cmGauche.1.1))
                                    .multilineTextAlignment(.center)
                        }
                        Spacer()
                        if cmDroite.1.2 {
                            Text(String(cmDroite.1.0) + "*")
                                    .multilineTextAlignment(.center)
                        } else {
                            Text(String(cmDroite.1.0))
                                    .multilineTextAlignment(.center)
                        }
                        if cmDroite.1.3 {
                            Text(String(cmDroite.1.1) + "*")
                                    .multilineTextAlignment(.center)
                        } else {
                            Text(String(cmDroite.1.1))
                                    .multilineTextAlignment(.center)
                        }
                        Spacer()
                    }
                }
            }
            HStack {
                let nom = concat(un: bsLastName1, deux: bsLastName2, trois: bsLastName3)
                VStack {
                    let cmGauche = NumerologieCore.cmGauche(nom: nom)
                    Text("Voyelle(s)")
                    ForEach(0..<nom.count, id: \.self) { idx in
                        HStack {
                            if cmGauche.0[idx].0 == 0 {
                                Text("/")
                            } else {
                                Text(String(cmGauche.0[idx].0))
                                if cmGauche.0[idx].0 != cmGauche.0[idx].1 {
                                    Text(String(cmGauche.0[idx].1))
                                }
                            }
                        }
                    }
                    HStack {
                        Text("=")
                    }
                    HStack {
                        if cmGauche.1.2 {
                            Text(String(cmGauche.1.0) + "*")
                        } else {
                            Text(String(cmGauche.1.0))
                        }
                        if cmGauche.1.3 {
                            Text(String(cmGauche.1.1) + "*")
                        } else {
                            Text(String(cmGauche.1.1))
                        }
                    }
                }
                VStack {
                    let nom = NumerologieCore.lettres(nom: nom)
                    //Text("Nom")
                    ForEach(0..<nom.count, id: \.self) { idx in
                        Text(nom[idx])
                    }
                }
                VStack {
                    let cmDroite = NumerologieCore.cmDroite(nom: nom)
                    Text("Consonne(s)")
                    ForEach(0..<nom.count, id: \.self) { idx in
                        HStack {
                            if cmDroite.0[idx].0 == 0 {
                                Text("/")
                            } else {
                                Text(String(cmDroite.0[idx].0))
                                if cmDroite.0[idx].0 != cmDroite.0[idx].1 {
                                    Text(String(cmDroite.0[idx].1))
                                }
                            }
                        }
                    }
                    HStack {
                        Text("=")
                    }
                    HStack {
                        if cmDroite.1.2 {
                            Text(String(cmDroite.1.0) + "*")
                        } else {
                            Text(String(cmDroite.1.0))
                        }
                        if cmDroite.1.3 {
                            Text(String(cmDroite.1.1) + "*")
                        } else {
                            Text(String(cmDroite.1.1))
                        }
                    }
                }
            }
        }
    }
    func concat(un: String, deux: String, trois: String) -> String {
        var res = ""
        if un != "" {
            res = un
        }
        if deux != "" {
            if res == "" {
                res = deux
            } else {
                res = res + " " + deux
            }
        }
        if trois != "" {
            if res == "" {
                res = trois
            } else {
                res = res + " " + trois
            }
        }
        return res
    }
}