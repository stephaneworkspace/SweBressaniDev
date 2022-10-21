// swift-tools-version: 5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
        name: "SweSvg",
        products: [
                // Products define the executables and libraries a package produces, and make them visible to other packages.
                .library(
                        name: "SweSvg",
                        targets: ["cwrapper"]),
        ],
        targets: [.target(name: "cpplib"),
                  .target(name: "svglib"),
                  .target(name: "swelib"),
                  .target(name: "sweinterfacelib", dependencies: ["svglib", "swelib"]),
                  .executableTarget(name: "cpp-exec", dependencies: ["cpplib", "swelib", "svglib", "sweinterfacelib"]),
                  .target(name: "cwrapper", dependencies: ["cpplib", "swelib", "svglib", "sweinterfacelib"]),
                  .target(name: "SweSvg", dependencies: ["cwrapper"]),
                  .executableTarget(name: "SweSvgExec", dependencies: ["cwrapper", "SweSvg"]),
        ]
)