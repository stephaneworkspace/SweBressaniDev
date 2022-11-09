// swift-tools-version: 5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
        name: "SweBressaniDev",
        platforms: [
            .iOS(.v15),
            .tvOS(.v13)
        ],
        products: [
                // Products define the executables and libraries a package produces, and make them visible to other packages.
                .library(
                        name: "SweBressaniDev",
                        targets: ["SweBressaniDev"]),
],
targets: [.target(name: "cpplib"),
                  .target(name: "svglib"),
                  .target(name: "swelib"),
                  .target(name: "sweinterfacelib", dependencies: ["svglib", "swelib"]),
                  .executableTarget(name: "cpp-exec", dependencies: ["cpplib", "swelib", "svglib", "sweinterfacelib"]),
                  .target(name: "cwrapper", dependencies: ["cpplib", "swelib", "svglib", "sweinterfacelib"]),
                  .target(name: "SweBressaniDev", dependencies: ["cwrapper"]),
                  .executableTarget(name: "SweBressaniDevExec", dependencies: ["cwrapper", "SweBressaniDev"]),
        ]
)
