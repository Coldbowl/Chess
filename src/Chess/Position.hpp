#pragma once

#include <string>

#include "move.hpp"

using std::string;

namespace sf { class Sprite; }

enum { WHITE, BLACK };

class Position {
    uint64_t bitboards[2][6] = { 0 };

    uint64_t white_piece_bitboard = 0;
    uint64_t black_piece_bitboard = 0;

public:
    bool white_to_move;
    bool can_move = true; // For rendering purposes

    Position() = default;
    Position(const Position& p) = default;
    Position& operator=(const Position&) = default;

    explicit Position(
        uint64_t white_king,
        uint64_t white_queen,
        uint64_t white_bishop,
        uint64_t white_knight,
        uint64_t white_rook,
        uint64_t white_pawn,
        uint64_t black_king,
        uint64_t black_queen,
        uint64_t black_bishop,
        uint64_t black_knight,
        uint64_t black_rook,
        uint64_t black_pawn
    );

    void move(const Move& m);

    uint64_t& piece(int color, int piece) {
        return bitboards[color][piece];
    }

    const uint64_t& piece(int color, int piece) const {
        return bitboards[color][piece];
    }

    void update_piece_bitboards();

    void log() const;

    static Position from_FEN(const string& FEN);


    [[nodiscard]] uint64_t get_white_king_bitboard() const   { return bitboards[WHITE][KING]; }
    [[nodiscard]] uint64_t get_white_queen_bitboard() const  { return bitboards[WHITE][QUEEN]; }
    [[nodiscard]] uint64_t get_white_bishop_bitboard() const { return bitboards[WHITE][BISHOP]; }
    [[nodiscard]] uint64_t get_white_knight_bitboard() const { return bitboards[WHITE][KNIGHT]; }
    [[nodiscard]] uint64_t get_white_rook_bitboard() const   { return bitboards[WHITE][ROOK]; }
    [[nodiscard]] uint64_t get_white_pawn_bitboard() const   { return bitboards[WHITE][PAWN]; }

    [[nodiscard]] uint64_t get_black_king_bitboard() const   { return bitboards[BLACK][KING]; }
    [[nodiscard]] uint64_t get_black_queen_bitboard() const  { return bitboards[BLACK][QUEEN]; }
    [[nodiscard]] uint64_t get_black_bishop_bitboard() const { return bitboards[BLACK][BISHOP]; }
    [[nodiscard]] uint64_t get_black_knight_bitboard() const { return bitboards[BLACK][KNIGHT]; }
    [[nodiscard]] uint64_t get_black_rook_bitboard() const   { return bitboards[BLACK][ROOK]; }
    [[nodiscard]] uint64_t get_black_pawn_bitboard() const   { return bitboards[BLACK][PAWN]; }

    [[nodiscard]] uint64_t get_white_piece_bitboard() const  { return white_piece_bitboard; }
    [[nodiscard]] uint64_t get_black_piece_bitboard() const  { return black_piece_bitboard; }
};
