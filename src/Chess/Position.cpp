#include "Position.hpp"

#include <vector>
#include <iostream>

#include "Utils/strings.hpp"
#include "Utils/binary.hpp"

using std::vector;

Position Position::from_FEN(const string& FEN) {
    const vector<string> resulting_string = split(FEN, " ");

    if (resulting_string.size() != 6) {
        throw std::invalid_argument("FEN string is the wrong size");
    }

    Position p;

    int file = 0;
    int rank = 7;
    for (const char c : resulting_string[0]) {
        switch (c) {
            // white pieces
            case 'P':
                p.white_pawn_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'N':
                p.white_knight_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'B':
                p.white_bishop_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'R':
                p.white_rook_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'Q':
                p.white_queen_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'K':
                p.white_king_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;

                // black pieces
            case 'p':
                p.black_pawn_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'n':
                p.black_knight_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'b':
                p.black_bishop_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'r':
                p.black_rook_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'q':
                p.black_queen_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'k':
                p.black_king_bitboard |= (1ULL << (rank * 8 + file));
                file++;
                break;

                // Empty square
            case '1': case '2': case '3': case '4': // Each case behaves like a 'goto' to a block of code, which is crazy to me tbh
            case '5': case '6': case '7': case '8':
                file += (c - '0'); // Convert ASCII digit into its integer value. That's also crazy wow
                break;

                // Rank seperator
            case '/':
                rank--;
                file = 0;
                break;

            default:
                // invalid FEN character
                break;
        }
    }

    return p;
}

Position::Position(
    uint64_t white_king_bitboard,
    uint64_t white_queen_bitboard,
    uint64_t white_bishop_bitboard,
    uint64_t white_knight_bitboard,
    uint64_t white_rook_bitboard,
    uint64_t white_pawn_bitboard,
    uint64_t black_king_bitboard,
    uint64_t black_queen_bitboard,
    uint64_t black_bishop_bitboard,
    uint64_t black_knight_bitboard,
    uint64_t black_rook_bitboard,
    uint64_t black_pawn_bitboard
)
    : white_king_bitboard(white_king_bitboard),
      white_queen_bitboard(white_queen_bitboard),
      white_bishop_bitboard(white_bishop_bitboard),
      white_knight_bitboard(white_knight_bitboard),
      white_rook_bitboard(white_rook_bitboard),
      white_pawn_bitboard(white_pawn_bitboard),
      black_king_bitboard(black_king_bitboard),
      black_queen_bitboard(black_queen_bitboard),
      black_bishop_bitboard(black_bishop_bitboard),
      black_knight_bitboard(black_knight_bitboard),
      black_rook_bitboard(black_rook_bitboard),
      black_pawn_bitboard(black_pawn_bitboard)
{
    white_piece_bitboard =
        white_king_bitboard |
        white_queen_bitboard |
        white_bishop_bitboard |
        white_knight_bitboard |
        white_rook_bitboard |
        white_pawn_bitboard;

    black_piece_bitboard =
        black_king_bitboard |
        black_queen_bitboard |
        black_bishop_bitboard |
        black_knight_bitboard |
        black_rook_bitboard |
        black_pawn_bitboard;
}

void Position::log() const {
    std::cout << "white pawn bitboard:";
    print_binary_number(white_pawn_bitboard);

    std::cout << "white knight bitboard:";
    print_binary_number(white_knight_bitboard);

    std::cout << "white bishop bitboard:";
    print_binary_number(white_bishop_bitboard);

    std::cout << "white rook bitboard:";
    print_binary_number(white_rook_bitboard);

    std::cout << "white queen bitboard: ";
    print_binary_number(white_queen_bitboard);

    std::cout << "white king bitboard:";
    print_binary_number(white_king_bitboard);

    std::cout << "black pawn bitboard:";
    print_binary_number(black_pawn_bitboard);

    std::cout << "black knight bitboard:";
    print_binary_number(black_knight_bitboard);

    std::cout << "black bishop bitboard:";
    print_binary_number(black_bishop_bitboard);

    std::cout << "black rook bitboard:";
    print_binary_number(black_rook_bitboard);

    std::cout << "black queen bitboard:";
    print_binary_number(black_queen_bitboard);

    std::cout << "black king bitboard:";
    print_binary_number(black_king_bitboard);
}


void Position::update_piece_bitboards() {
    white_piece_bitboard =
        white_king_bitboard |
        white_queen_bitboard |
        white_bishop_bitboard |
        white_knight_bitboard |
        white_rook_bitboard |
        white_pawn_bitboard;

    black_piece_bitboard =
        black_king_bitboard |
        black_queen_bitboard |
        black_bishop_bitboard |
        black_knight_bitboard |
        black_rook_bitboard |
        black_pawn_bitboard;
}