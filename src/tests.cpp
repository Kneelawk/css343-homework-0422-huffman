//
// Created by cyan on 4/21/25.
//

#include "ktest.hpp"
#include "frequency.h"

KTEST(frequency_test) {
    const std::string s = "aaabbc";
    std::map<char, size_t> freqs = getFrequencies(s);
    KASSERT_EQ(3, freqs.size());
    KASSERT_EQ(3, freqs['a']);
    KASSERT_EQ(2, freqs['b']);
    KASSERT_EQ(1, freqs['c']);
}

KTEST(frequency_test2) {
    const std::string s = "abcaba";
    std::map<char, size_t> freqs = getFrequencies(s);
    KASSERT_EQ(3, freqs.size());
    KASSERT_EQ(3, freqs['a']);
    KASSERT_EQ(2, freqs['b']);
    KASSERT_EQ(1, freqs['c']);
}
