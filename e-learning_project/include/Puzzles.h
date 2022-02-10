//
// Created by laurax on 01.07.21.
//

#ifndef AWESOMEARPROJECT_PUZZLES_H
#define AWESOMEARPROJECT_PUZZLES_H

#include "Field.h"

struct Puzzle {
	const std::string puzzle;
	Move lastMoveOfOpponent; // save last move of opponent
	Move solution; // where to move which figure
    const bool nextPlayer; // next player (white -> true, black -> false)
};

namespace Puzzles {
    Puzzle getPuzzle(int index);

    /*
     * Example from https://python-chess.readthedocs.io/en/latest/index.html
     * "r1bqkb1r/pppp1Qpp/2n2n2/4p3/2B1P3/8/PPPP1PPP/RNB1K1NR b KQkq - 0 4") starts at A8!!!
     *
     * figure names: pawn (Bauer), knight (Springer), bishop (Läufer),
     *               rook (Turm), queen, king
     * white -> upper case
     * black -> lower case
    */

    const Puzzle puzzle1 { // https://lichess.org/training/igTbP
            "3b2rk/8/1p1PQ2p/8/4ppq1/1P4P1/P6K/6R1",
            Move{Field{'F', 5}, Field{'F', 4}, Figure{"P_B", false}}, // last move of opponent
            Move{Field{'E', 6}, Field{'H', 6}, Figure{"Q_W", true}}, // solution
            true // next player (white -> true, black -> false)
    };
    const Puzzle puzzle2 { // https://lichess.org/training/sdwkq
            "r1b1k2r/ppppqppp/2n5/3Nn3/1bP5/5N2/PP1BPPPP/R2QKB1R",
            Move{Field{'C', 3}, Field{'D', 5}, Figure{"N_W", true}}, // last move of opponent
            Move{Field{'E', 5}, Field{'D', 3}, Figure{"N_B", true}}, // solution
            false // next player (white -> true, black -> false)
    };
    const Puzzle puzzle3 { // https://lichess.org/training/Hogr5
            "6r1/p5P1/Ppk2b2/1p1p1p2/3PpP2/KNP5/8/6R1",
            Move{Field{'H', 4}, Field{'F', 6}, Figure{"B_B", false}}, // last move of opponent
            Move{Field{'G', 1}, Field{'G', 6}, Figure{"R_W", true}}, // solution
            true // next player (white -> true, black -> false)
    };
    const Puzzle puzzle4 { // https://lichess.org/training/qU962
            "r5k1/P4ppp/4p3/3p1n2/8/5P2/7P/R5K1",
            Move{Field{'C', 8}, Field{'A', 8}, Figure{"R_B", false}}, // last move of opponent
            Move{Field{'A', 1}, Field{'B', 1}, Figure{"R_W", true}}, // solution
            true // next player (white -> true, black -> false)
    };
    const Puzzle puzzle5 { // https://lichess.org/training/kUCFj
            "r1bR1rk1/pp3pbp/6p1/4p3/4Pn2/1Q2B3/PP2BPPP/5RK1",
            Move{Field{'D', 1}, Field{'D', 8}, Figure{"R_W", true}}, // last move of opponent
            Move{Field{'F', 4}, Field{'E', 2}, Figure{"N_B", false}}, // solution
            false // next player (white -> true, black -> false)
    };
    const Puzzle puzzle6 { // https://lichess.org/training/jyS9H
            "8/2K5/k1P3P1/1P4pP/Pp2P2p/p3p3/6p1/8",
            Move{Field{'E', 3}, Field{'F', 2}, Figure{"K_W", true}}, // last move of opponent
            Move{Field{'B', 7}, Field{'B', 5}, Figure{"P_B", false}}, // solution
            false // next player (white -> true, black -> false)
    };
    const Puzzle puzzle7 { // https://lichess.org/training/Mhfvi
            "K1R4R/PP4PP/1B3Q2/1n3P2/r4qN1/3p2b1/p4ppp/r4k2",
            Move{Field{'B', 3}, Field{'C', 3}, Figure{"Q_W", true}}, // last move of opponent
            Move{Field{'C', 5}, Field{'G', 1}, Figure{"Q_B", false}}, // solution
            false // next player (white -> true, black -> false)
    };
    const Puzzle puzzle8{  // https://lichess.org/training/BlqqX
            "r6r/p3nkb1/3qpn1p/6p1/1RpPQp2/2P2N1P/P2BN1P1/5RK1",
            Move{Field{'D', 7}, Field{'F', 6}, Figure{"N_B", false}}, // last move of opponent
            Move{Field{'F', 3}, Field{'E', 5}, Figure{"N_W", true}}, // solution
            true // next player (white -> true, black -> false)
    };
    const Puzzle puzzle9 { // https://lichess.org/training/HplSz
            "Bnb1kr2/p1p1qpQp/1p5B/8/4n3/5N2/PPP2bPP/RN3K1R",
            Move{Field{'D', 5}, Field{'A', 8}, Figure{"B_W", true}}, // last move of opponent
            Move{Field{'C', 8}, Field{'A', 6}, Figure{"B_B", false}}, // solution
            false // next player (white -> true, black -> false)
    };
    const Puzzle puzzle10 { // https://lichess.org/training/Bf5Kr
            "r2qr1k1/5pp1/p2Qn2p/1pp5/4PN2/5P1P/PPP3P1/3RR1B1",
            Move{Field{'D', 3}, Field{'D', 6}, Figure{"Q_W", true}}, // last move of opponent
            Move{Field{'D', 8}, Field{'D', 6}, Figure{"Q_B", false}}, // solution
            false // next player (white -> true, black -> false)
    };
};

#endif //AWESOMEARPROJECT_PUZZLES_H
