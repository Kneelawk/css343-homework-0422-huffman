#include <algorithm>
#include <iostream>

#include "encoder.h"
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

    const HuffmanTree<char> ht(freqs);

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

    std::cout << std::endl;

    BitSet encoded;
    encode(ht, toEncode, encoded);
    std::vector<uint8_t> encodedBytes;
    const size_t encodedBitCount = encoded.getAll(encodedBytes);
    const size_t lastBitCount = encodedBitCount % 8;

    // print the first 8 bytes
    std::cout << "First 8 bytes: ";
    for (size_t i = 0; i < 8; i++) {
        std::cout << printCode(encodedBytes[i], 8);
    }
    std::cout << std::endl;

    std::cout << "Total Encoded Bit Count: " << encodedBitCount << std::endl;
    std::cout << "Total Encoded Byte Count: " << encodedBytes.size() << std::endl;
    std::cout << "That is " << (encodedBytes.size() - 1) << " with an additional " << lastBitCount << " bits." <<
            std::endl;
    std::cout << "Compression Ratio: " << (static_cast<double>(encodedBitCount) / static_cast<double>(
                                               toEncode.size() * 8)) << std::endl;
    return 0;
}
