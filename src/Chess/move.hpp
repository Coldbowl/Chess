#pragma once

#include <cstdint>
#include <iostream>

enum Piece { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING };

enum Flags { INVALID, CAPTURE, CASTLING, PROMOTION_TO_KNIGHT, PROMOTION_TO_BISHOP, PROMOTION_TO_ROOK, PROMOTION_TO_QUEEN, EN_PASSANT };



struct Move {
    uint8_t from = INVALID;
    uint8_t to = INVALID;
    uint8_t piece = INVALID;
    uint8_t flags = INVALID; // To be continued

    Move() = default;

    Move(const int from, const int to, const int piece, const Flags flags)
    : from(from)
    , to(to)
    , piece(piece)
    , flags(flags) {
    }

    void reset() {
        from = INVALID;
        to = INVALID;
        piece = INVALID;
        flags = INVALID;
    }

    bool operator==(const Move& m) const = default;
    // bool operator==(const Move& m) const {
    //     bool eq_from  = from  == m.from;
    //     bool eq_to    = to    == m.to;
    //     bool eq_piece = piece == m.piece;
    //     bool eq_flags = flags == m.flags;
    //
    //     std::cout << "Comparing Moves:\n";
    //
    //     std::cout << "  from:  "
    //               << static_cast<int>(from) << " vs "
    //               << static_cast<int>(m.from)
    //               << " -> " << (eq_from ? "OK" : "DIFF") << '\n';
    //
    //     std::cout << "  to:    "
    //               << static_cast<int>(to) << " vs "
    //               << static_cast<int>(m.to)
    //               << " -> " << (eq_to ? "OK" : "DIFF") << '\n';
    //
    //     std::cout << "  piece: "
    //               << static_cast<int>(piece) << " vs "
    //               << static_cast<int>(m.piece)
    //               << " -> " << (eq_piece ? "OK" : "DIFF") << '\n';
    //
    //     std::cout << "  flags: "
    //               << static_cast<int>(flags) << " vs "
    //               << static_cast<int>(m.flags)
    //               << " -> " << (eq_flags ? "OK" : "DIFF") << '\n';
    //
    //     bool result = eq_from && eq_to && eq_piece && eq_flags;
    //
    //     std::cout << "  RESULT: "
    //               << (result ? "EQUAL" : "NOT EQUAL")
    //               << "\n\n";
    //
    //     return result;
    // }
};