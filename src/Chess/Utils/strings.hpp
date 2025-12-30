#pragma once

#include <vector>
#include <string>

// Yeah fam I didn't write this at all
inline std::vector<std::string> split(const std::string& s, const std::string& delim) {
    std::vector<std::string> result;
    size_t start = 0;
    size_t end;

    while ((end = s.find(delim, start)) != std::string::npos) {
        result.push_back(s.substr(start, end - start));
        start = end + delim.length();
    }

    result.push_back(s.substr(start));
    return result;
}