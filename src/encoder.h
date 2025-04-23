//
// Created by cyan on 4/22/25.
//

#ifndef ENCODER_H
#define ENCODER_H
#include "bit_set.h"
#include "huffman_tree.h"

void encode(const HuffmanTree<char> &tree, const std::string &str, BitSet &out);

#endif //ENCODER_H
