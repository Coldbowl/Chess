#pragma once

#include <cstdint>
#include <iostream>

inline void print_binary_number(const uint64_t number) {
    std::cout << "\n";
    for (int i = 63; i >= 0; i--) {
        char output;
        (number & 1ULL << i) ? output = '1' : output = '0';
        std::cout << output;
        if (i % 8 == 0) std::cout << "\n";
    }
    std::cout << "\n";
}