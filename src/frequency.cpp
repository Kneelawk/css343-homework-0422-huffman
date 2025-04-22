//
// Created by cyan on 4/22/25.
//

#include "frequency.h"

#include <iostream>

std::unordered_map<char, size_t> getFrequency(const std::string &str) {
    std::unordered_map<char, size_t> res;

    for (char c : str) {
        if (res.find(c) == res.end()) {
            res[c] = 1;
        } else {
            ++res[c];
        }
    }

    return res;
}
