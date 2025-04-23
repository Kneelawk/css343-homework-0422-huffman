//
// Created by cyan on 4/22/25.
//

#ifndef BIT_SET_H
#define BIT_SET_H
#include <cstdint>
#include <string>
#include <vector>


class BitSet {
    std::vector<uint8_t> bytes;
    uint8_t bitIndex = 0;

public:
    void add32(uint32_t bits, size_t len);

    void add(bool value);

    size_t getAll(std::vector<uint8_t> &out) const;

    std::string toBinString() const;
};



#endif //BIT_SET_H
