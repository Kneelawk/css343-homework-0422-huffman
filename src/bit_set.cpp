//
// Created by cyan on 4/22/25.
//

#include <sstream>

#include "bit_set.h"

#include "printer.h"

void BitSet::add32(uint32_t bits, size_t len) {
    for (size_t j = 0; j < len; j++) {
        const size_t i = len - j - 1;
        add((bits >> i) & 1);
    }
}

void BitSet::add(const bool value) {
    if (bytes.empty() || bitIndex >= 8) {
        bitIndex = 0;
        bytes.push_back(0);
    }

    // keep msb bits msb & append new codepoints in lsb
    const size_t i = bytes.size() - 1;
    bytes[i] = bytes[i] << 1 | !!value;

    bitIndex++;
}

size_t BitSet::getAll(std::vector<uint8_t> &out) const {
    if (bytes.empty()) {
        return 0;
    }

    out = bytes;

    return (bytes.size() - 1) * 8 + bitIndex;
}

std::string BitSet::toBinString() const {
    if (bytes.empty()) {
        return "";
    }

    std::stringstream ss;

    for (size_t i = 0; i < bytes.size() - 1; i++) {
        ss << printCode(bytes[i], 8);
    }

    ss << printCode(bytes[bytes.size() - 1], bitIndex);

    return ss.str();
}
