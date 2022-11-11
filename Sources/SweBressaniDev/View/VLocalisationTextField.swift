//
// Created by Stéphane on 06.09.22.
//
// This file work only for ios
//

import Foundation
import SwiftUI
import CoreLocation

#if os(iOS)
public struct VLocalisationTextFieldIOs: View {
    @Binding var bdLat: Double
    @Binding var bdLng: Double
    @Binding var biTimeZone: Int
    @State var stText: TextCore
    @FocusState private var fbLat: Bool
    @FocusState private var fbLng: Bool

    public init(bdLat: Binding<Double>, bdLng: Binding<Double>, biTimeZone: Binding<Int>, stText: TextCore) {
        self._bdLat = bdLat
        self._bdLng = bdLng
        self._biTimeZone = biTimeZone
        self._stText = .init(initialValue: stText)
    }

    public var body: some View {
        VStack {
            HStack {
                Text("\(stText.latitude())")
                        .font(FONTSYSTEM)
                        .clipped()
                TextField(
                        "\(stText.latitude())",
                        value: $bdLat,
                        formatter: FORMATTER
                )
                        .focused($fbLat)
                        .keyboardType(.decimalPad)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .font(FONTSYSTEM)
                        .clipped()
                Text("\(stText.longitude())")
                        .font(FONTSYSTEM)
                        .clipped()
                TextField(
                        "\(stText.longitude())",
                        value: $bdLng,
                        formatter: FORMATTER
                )
                        .focused($fbLng)
                        .keyboardType(.decimalPad)
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                let manager = CLLocationManager()
                if manager.authorizationStatus == .restricted || manager.authorizationStatus == .denied {

                } else {
                    Button(action: {
                        if (manager.authorizationStatus == .authorizedWhenInUse ||
                                manager.authorizationStatus == .authorizedAlways) {
                            let locationManager = CLLocationManager()
                            locationManager.requestWhenInUseAuthorization()
                            var currentLoc: CLLocation!
                            currentLoc = locationManager.location
                            fbLat = false
                            fbLng = false
                            bdLat = currentLoc.coordinate.latitude
                            bdLng = currentLoc.coordinate.longitude
                        }
                    }, label: {
                        ZStack {
                            Image(systemName: "location.circle")
                                    .imageScale(IMAGESCALE)
                                    .foregroundColor(FOREGROUNDCOLOR)
                        }
                    })
                }
            }
            HStack {
                Picker("", selection: $biTimeZone, content: {
                    ForEach(-12...0, id: \.self) { idx in
                        if idx != 0 {
                            Text("GMT " + idx.formatted()).tag(idx)
                        }
                    }
                    ForEach(0...12, id: \.self) { idx in
                        Text("GMT +" + idx.formatted()).tag(idx)
                    }
                })
                        .textFieldStyle(RoundedBorderTextFieldStyle())
                        .foregroundColor(FOREGROUNDCOLOR)
                        .font(FONTSYSTEM)
                        .pickerStyle(WheelPickerStyle())
            }
            Spacer()
        }
                .padding()
    }
}
#endif
