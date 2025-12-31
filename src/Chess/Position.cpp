#include "Position.hpp"

#include <vector>

#include "Utils/strings.hpp"
#include "Utils/binary.hpp"
#include "move.hpp"

using std::vector;

// This function isn't done, however it works for now
Position Position::from_FEN(const string& FEN) {
    const vector<string> resulting_string = split(FEN, " ");

    if (resulting_string.size() != 6) {
        throw std::invalid_argument("FEN-string is the wrong size");
    }

    Position p;

    int file = 0;
    int rank = 7;
    for (const char c : resulting_string[0]) {
        switch (c) {
            // white pieces
            case 'P':
                p.piece(WHITE, PAWN) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'N':
                p.piece(WHITE, KNIGHT) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'B':
                p.piece(WHITE, BISHOP) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'R':
                p.piece(WHITE, ROOK) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'Q':
                p.piece(WHITE, QUEEN) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'K':
                p.piece(WHITE, KING) |= (1ULL << (rank * 8 + file));
                file++;
                break;

                // black pieces
            case 'p':
                p.piece(BLACK, PAWN) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'n':
                p.piece(BLACK, KNIGHT) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'b':
                p.piece(BLACK, BISHOP) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'r':
                p.piece(BLACK, ROOK) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'q':
                p.piece(BLACK, QUEEN) |= (1ULL << (rank * 8 + file));
                file++;
                break;
            case 'k':
                p.piece(BLACK, KING) |= (1ULL << (rank * 8 + file));
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

    p.white_to_move = true; // This will of course be changed once I actually get to analyze the entire FEN-string

    return p;
}

Position::Position(
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
) {
    bitboards[WHITE][KING]   = white_king;
    bitboards[WHITE][QUEEN]  = white_queen;
    bitboards[WHITE][BISHOP] = white_bishop;
    bitboards[WHITE][KNIGHT] = white_knight;
    bitboards[WHITE][ROOK]   = white_rook;
    bitboards[WHITE][PAWN]   = white_pawn;

    bitboards[BLACK][KING]   = black_king;
    bitboards[BLACK][QUEEN]  = black_queen;
    bitboards[BLACK][BISHOP] = black_bishop;
    bitboards[BLACK][KNIGHT] = black_knight;
    bitboards[BLACK][ROOK]   = black_rook;
    bitboards[BLACK][PAWN]   = black_pawn;

    update_piece_bitboards();
}

void Position::move(const Move& m) {
    const uint64_t from_bb = 1ULL << m.from;
    const uint64_t to_bb = 1ULL << m.to;

    const int to_move = white_to_move ? WHITE : BLACK;

    bitboards[to_move][m.piece] ^= from_bb | to_bb;

    white_to_move ^= 1;
}


void Position::log() const {
    std::cout << "white pawn bitboard:";
    print_binary_number(bitboards[WHITE][PAWN]);

    std::cout << "white knight bitboard:";
    print_binary_number(bitboards[WHITE][KNIGHT]);

    std::cout << "white bishop bitboard:";
    print_binary_number(bitboards[WHITE][BISHOP]);

    std::cout << "white rook bitboard:";
    print_binary_number(bitboards[WHITE][ROOK]);

    std::cout << "white queen bitboard:";
    print_binary_number(bitboards[WHITE][QUEEN]);

    std::cout << "white king bitboard:";
    print_binary_number(bitboards[WHITE][KING]);

    std::cout << "black pawn bitboard:";
    print_binary_number(bitboards[BLACK][PAWN]);

    std::cout << "black knight bitboard:";
    print_binary_number(bitboards[BLACK][KNIGHT]);

    std::cout << "black bishop bitboard:";
    print_binary_number(bitboards[BLACK][BISHOP]);

    std::cout << "black rook bitboard:";
    print_binary_number(bitboards[BLACK][ROOK]);

    std::cout << "black queen bitboard:";
    print_binary_number(bitboards[BLACK][QUEEN]);

    std::cout << "black king bitboard:";
    print_binary_number(bitboards[BLACK][KING]);
}

void Position::update_piece_bitboards() {
    white_piece_bitboard =
        bitboards[WHITE][KING]   |
        bitboards[WHITE][QUEEN]  |
        bitboards[WHITE][BISHOP] |
        bitboards[WHITE][KNIGHT] |
        bitboards[WHITE][ROOK]   |
        bitboards[WHITE][PAWN];

    black_piece_bitboard =
        bitboards[BLACK][KING]   |
        bitboards[BLACK][QUEEN]  |
        bitboards[BLACK][BISHOP] |
        bitboards[BLACK][KNIGHT] |
        bitboards[BLACK][ROOK]   |
        bitboards[BLACK][PAWN];
}