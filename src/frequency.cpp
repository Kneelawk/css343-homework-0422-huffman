//
// Created by cyan on 4/22/25.
//

#include "frequency.h"

#include <iostream>

void getFrequencies(const std::string &str, std::map<char, size_t> &frequencyMap) {
    for (char c : str) {
        if (frequencyMap.find(c) == frequencyMap.end()) {
            frequencyMap[c] = 1;
        } else {
            ++frequencyMap[c];
        }
    }
}
