#pragma once

#include <vector>
#include <cstdint>

#include "move.hpp"
#include "Position.hpp"
#include "Utils/binary.hpp"

using std::vector;

class Position;

namespace MoveGenerator {
    inline uint64_t generate_rank_mask(const int rank) {
        return 0xFFULL << (8 * (rank - 1));
    }

    constexpr uint64_t generate_file_mask(const int file) {
        return 0x01010101010101ULL << (file - 1);
    }

    inline int pop_lsb(uint64_t& b) {
        const int index = std::countr_zero(b);
        b &= b - 1;
        return index;
    }



    inline vector<Move> generate_legal_moves(const Position& p) {
        vector<Move> pseudo_legal_moves;
        const uint64_t occupied_square_bitboard = p.get_white_piece_bitboard() | p.get_black_piece_bitboard();

        constexpr uint64_t FILE_A = generate_file_mask(8);
        constexpr uint64_t FILE_H = generate_file_mask(1);

        // +---------------------------+
        // | MOVE GENERATION FOR WHITE |
        // +---------------------------+

        if (p.white_to_move) {
            uint64_t single_pawn_push_bitboard = (p.get_white_pawn_bitboard() << 8) & ~occupied_square_bitboard;
            uint64_t double_pawn_push_bitboard = ((single_pawn_push_bitboard & generate_rank_mask(3)) << 8) & ~occupied_square_bitboard;

            uint64_t right_capture_bitboard = ((p.get_white_pawn_bitboard() & ~FILE_A) << 9) & p.get_black_piece_bitboard();
            uint64_t left_capture_bitboard = ((p.get_white_pawn_bitboard() & ~FILE_H) << 7) & p.get_black_piece_bitboard();

            while (single_pawn_push_bitboard) {
                int to = pop_lsb(single_pawn_push_bitboard);
                int from = to - 8;
                pseudo_legal_moves.emplace_back(from, to, PAWN, INVALID);
            }

            while (double_pawn_push_bitboard) {
                int to = pop_lsb(double_pawn_push_bitboard);
                int from = to - 16;
                pseudo_legal_moves.emplace_back(from, to, PAWN, INVALID);
            }

            while (right_capture_bitboard) {
                int to = pop_lsb(right_capture_bitboard);
                int from = to - 9;
                pseudo_legal_moves.emplace_back(from, to, PAWN, CAPTURE);
            }

            while (left_capture_bitboard) {
                int to = pop_lsb(left_capture_bitboard);
                int from = to - 7;
                pseudo_legal_moves.emplace_back(from, to, PAWN, CAPTURE);
            }

        // +---------------------------+
        // | MOVE GENERATION FOR BLACK |
        // +---------------------------+

        } else {
            uint64_t single_pawn_push_bitboard = (p.get_black_pawn_bitboard() >> 8) & ~occupied_square_bitboard;
            uint64_t double_pawn_push_bitboard = ((single_pawn_push_bitboard & generate_rank_mask(6)) >> 8) & ~occupied_square_bitboard;

            uint64_t right_capture_bitboard = ((p.get_black_pawn_bitboard() & ~FILE_A) >> 7) & p.get_white_piece_bitboard();
            uint64_t left_capture_bitboard = ((p.get_black_pawn_bitboard() & ~FILE_H) >> 9) & p.get_white_piece_bitboard();

            while (single_pawn_push_bitboard) {
                int to = pop_lsb(single_pawn_push_bitboard);
                int from = to + 8;
                pseudo_legal_moves.emplace_back(from, to, PAWN, INVALID);
            }

            while (double_pawn_push_bitboard) {
                int to = pop_lsb(double_pawn_push_bitboard);
                int from = to + 16;
                pseudo_legal_moves.emplace_back(from, to, PAWN, INVALID);
            }

            while (right_capture_bitboard) {
                int to = pop_lsb(right_capture_bitboard);
                int from = to + 7;
                pseudo_legal_moves.emplace_back(from, to, PAWN, CAPTURE);
            }

            while (left_capture_bitboard) {
                int to = pop_lsb(left_capture_bitboard);
                int from = to + 9;
                pseudo_legal_moves.emplace_back(from, to, PAWN, CAPTURE);
            }
        }
        return pseudo_legal_moves;
    }
}