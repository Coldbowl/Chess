#pragma once

#include <cstdint>

enum Piece { PAWN, KNIGHT, BISHOP, ROOK = 3, QUEEN, KING };

struct Move {
    uint8_t from = -1;
    uint8_t to = -1;
    uint8_t piece;
    uint8_t flags; // To be continued
};