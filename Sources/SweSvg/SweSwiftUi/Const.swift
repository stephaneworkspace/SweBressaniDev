//
// Created by Stéphane on 22.10.22.
//

import Foundation

let CIRCLE = 360.0
let CIRCLE_SIZE_TRANSIT: [(Double, Bool)] = [
    (42.0, true), // 0 CIRCLE ASPECT
    (59.0, true), // 1 CIRCLE TRANSIT
    (75.0, true), // 2 CIRCLE ZODIAC END
    (80.0, true), // 3 CIRCLE HOUSE
    (92.0, false), // 4 CIRCLE INVISIBLE -
    (92.0, false), // 5 CIRCLE INVISIBLE PLANET
    //    (0.0, false), // 5
    (0.0, false), // 6
    (82.0, false), // 7 between 2 and 3
    (85.0, false), // 8 correction planet between 2 and 3
    (49.0, false), // 9 Planet pos transit
    (57.5, false), // 10 - 7 transit
    (54.5, false), // 11 - 8 transit
]
let LARGER_DRAW_LINE_RULES_SMALL = 0.1
let LARGER_DRAW_LINE_RULES_LARGE = 0.2