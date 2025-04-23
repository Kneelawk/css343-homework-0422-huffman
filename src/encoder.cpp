//
// Created by cyan on 4/22/25.
//

#include "encoder.h"

void encode(const HuffmanTree<char> &tree, const std::string &str, BitSet &out) {
    std::map<char, HuffmanLeaf<char>> map;
    tree.collectMap(map);

    for (char c : str) {
        const HuffmanLeaf<char> &leaf = map[c];
        out.add32(leaf.code, leaf.len);
    }
}
