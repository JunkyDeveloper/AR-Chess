//
// Created by laurax on 01.07.21.
//

#include "../../include/Puzzles.h"

Puzzle Puzzles::getPuzzle(int index) {
    switch (index) {
        case 1:
            return puzzle1;
        case 2:
            return puzzle2;
        case 3:
            return puzzle3;
        case 4:
            return puzzle4;
        case 5:
            return puzzle5;
        case 6:
            return puzzle6;
        case 7:
            return puzzle7;
        case 8:
            return puzzle8;
        case 9:
            return puzzle9;
        case 10:
            return puzzle10;
        default:
            std::cout << "No puzzle with number: " << index << std::endl;
            return Puzzle{};
    }
}
