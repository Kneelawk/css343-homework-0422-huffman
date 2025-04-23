#include <algorithm>
#include <iostream>
#include "ktest.hpp"

#include "frequency.h"
#include "huffman_tree.h"
#include "printer.h"

const std::string toEncode = "Once there were brook trouts in the streams in the mountains. You could see them"
        " standing in the amber current where the white edges of their fins wimpled softly in"
        " the flow. They smelled of moss in your hand. Polished and muscular and torsional."
        " On their backs were vermiculate patterns that were maps of the world in its"
        " becoming. Maps and mazes. Of a thing which could not be put back. Not be made right"
        " again. In the deep glens where they lived all things were older than man and they"
        " hummed of mystery.";

int main() {
    ktest::runAllTests();
    std::map<char, size_t> freqs;
    getFrequencies(toEncode, freqs);

    HuffmanTree<char> ht(freqs);

    std::vector<HuffmanLeaf<char> > leaves;
    ht.collect(leaves);
    // sort by length, then by value
    std::sort(leaves.begin(), leaves.end(), [](const HuffmanLeaf<char> &a, const HuffmanLeaf<char> &b) {
        if (a.len != b.len) return a.len < b.len;
        return a.data < b.data;
    });

    std::cout << "Codes:" << std::endl;
    for (const auto &leaf: leaves) {
        std::cout << "  " << leaf.data << ": " << printCode(leaf.code, leaf.len) << std::endl;
    }
    return 0;
}
