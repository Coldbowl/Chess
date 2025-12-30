#pragma once

#include <string>
#include <cstdint>

using std::string;

namespace sf { class Sprite; }

class Position {
    uint64_t white_king_bitboard = 0;
    uint64_t white_queen_bitboard = 0;
    uint64_t white_bishop_bitboard = 0;
    uint64_t white_knight_bitboard = 0;
    uint64_t white_rook_bitboard = 0;
    uint64_t white_pawn_bitboard = 0;

    uint64_t black_king_bitboard = 0;
    uint64_t black_queen_bitboard = 0;
    uint64_t black_bishop_bitboard = 0;
    uint64_t black_knight_bitboard = 0;
    uint64_t black_rook_bitboard = 0;
    uint64_t black_pawn_bitboard = 0;

    uint64_t white_piece_bitboard = 0;
    uint64_t black_piece_bitboard = 0;
public:
    Position() = default;
    Position(const Position& p) = default;

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

    void update_piece_bitboards();

    void log() const;

    static Position from_FEN(const string& FEN);


    uint64_t get_white_king_bitboard() const   { return white_king_bitboard; }
    uint64_t get_white_queen_bitboard() const  { return white_queen_bitboard; }
    uint64_t get_white_bishop_bitboard() const { return white_bishop_bitboard; }
    uint64_t get_white_knight_bitboard() const { return white_knight_bitboard; }
    uint64_t get_white_rook_bitboard() const   { return white_rook_bitboard; }
    uint64_t get_white_pawn_bitboard() const   { return white_pawn_bitboard; }

    uint64_t get_black_king_bitboard() const   { return black_king_bitboard; }
    uint64_t get_black_queen_bitboard() const  { return black_queen_bitboard; }
    uint64_t get_black_bishop_bitboard() const { return black_bishop_bitboard; }
    uint64_t get_black_knight_bitboard() const { return black_knight_bitboard; }
    uint64_t get_black_rook_bitboard() const   { return black_rook_bitboard; }
    uint64_t get_black_pawn_bitboard() const   { return black_pawn_bitboard; }

    uint64_t get_white_piece_bitboard() const  { return white_piece_bitboard; }
    uint64_t get_black_piece_bitboard() const  { return black_piece_bitboard; }
};
