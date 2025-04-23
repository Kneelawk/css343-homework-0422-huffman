//
// Created by cyan on 4/22/25.
//

#ifndef PRINTER_H
#define PRINTER_H
#include <cstdint>
#include <ostream>

class CodePrinter {
    uint32_t code;
    size_t len;

public:
    CodePrinter(const uint32_t code, const size_t len)
        : code(code),
          len(len) {
    }

    friend std::ostream &operator<<(std::ostream &os, const CodePrinter &obj) {
        for (size_t i = 0; i < obj.len; i++) {
            size_t j = obj.len - i - 1;
            os << ((obj.code & (1 << j)) >> j);
        }

        return os;
    }
};

inline CodePrinter printCode(const uint32_t code, const size_t len) {
    return {code, len};
}

#endif //PRINTER_H
