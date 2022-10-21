// swift-tools-version: 5.7
// The swift-tools-version declares the minimum version of Swift required to build this package.

import PackageDescription

let package = Package(
        name: "SweSvg",
        targets: [.target(name: "cpplib"),
                  .executableTarget(name: "cpp-exec", dependencies: ["cpplib"]),
                  .target(name: "cwrapper", dependencies: ["cpplib"]),
                  .executableTarget(name: "SweSvg", dependencies: ["cwrapper"]),
        ]
)