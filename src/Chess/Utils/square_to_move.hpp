#pragma once

#include <string>


inline std::string square_to_move(const int sq) {
    char file = 'a' + (sq % 8);
    char rank = '1' + (sq / 8);
    return { file, rank };
}