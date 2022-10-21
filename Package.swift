// swift-tools-version: 5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
        name: "SweSvg",
        targets: [.target(name: "cpplib"),
                  .target(name: "svglib"),
                  .target(name: "swelib"),
                  .target(name: "sweinterfacelib", dependencies: ["svglib", "swelib"]),
                  .executableTarget(name: "cpp-exec", dependencies: ["cpplib", "swelib", "svglib", "sweinterfacelib"]),
                  .target(name: "cwrapper", dependencies: ["cpplib", "swelib"]),
                  .executableTarget(name: "SweSvg", dependencies: ["cwrapper"]),
        ]
)