//
// Created by cyan on 4/21/25.
//

#include "encoder.h"
#include "ktest.hpp"
#include "frequency.h"
#include "huffman_tree.h"

KTEST(frequency_test) {
    const std::string s = "aaabbc";
    std::map<char, size_t> freqs;
    getFrequencies(s, freqs);
    KASSERT_EQ(3, freqs.size());
    KASSERT_EQ(3, freqs['a']);
    KASSERT_EQ(2, freqs['b']);
    KASSERT_EQ(1, freqs['c']);
}

KTEST(frequency_test2) {
    const std::string s = "abcaba";
    std::map<char, size_t> freqs;
    getFrequencies(s, freqs);
    KASSERT_EQ(3, freqs.size());
    KASSERT_EQ(3, freqs['a']);
    KASSERT_EQ(2, freqs['b']);
    KASSERT_EQ(1, freqs['c']);
}

KTEST(full_encode_1) {
    // Test against teacher's bits
    const std::string message = "AAAABBBCCCDDEEF";

    std::map<char, size_t> freqs;
    getFrequencies(message, freqs);
    KASSERT_EQ(6, freqs.size());
    KASSERT_EQ(4, freqs['A']);
    KASSERT_EQ(3, freqs['B']);
    KASSERT_EQ(3, freqs['C']);
    KASSERT_EQ(2, freqs['D']);
    KASSERT_EQ(2, freqs['E']);
    KASSERT_EQ(1, freqs['F']);

    const HuffmanTree<char> tree(freqs);
    std::map<char, HuffmanLeaf<char>> keys;
    tree.collectMap(keys);

    KASSERT_EQ("10", keys['A'].bitStr());
    KASSERT_EQ("111", keys['B'].bitStr());
    KASSERT_EQ("00", keys['C'].bitStr());
    KASSERT_EQ("011", keys['D'].bitStr());
    KASSERT_EQ("110", keys['E'].bitStr());
    KASSERT_EQ("010", keys['F'].bitStr());

    BitSet encoded;
    encode(tree, message, encoded);

    KASSERT_EQ("10101010111111111000000011011110110010", encoded.toBinString());
}
