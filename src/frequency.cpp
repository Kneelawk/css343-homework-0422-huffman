//
// Created by cyan on 4/22/25.
//

#include "frequency.h"

#include <iostream>

std::map<char, size_t> getFrequencies(const std::string &str) {
    std::map<char, size_t> res;

    for (char c : str) {
        if (!res.contains(c)) {
            res[c] = 1;
        } else {
            ++res[c];
        }
    }

    return res;
}
