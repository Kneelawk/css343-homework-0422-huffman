#include <iostream>
#include "ktest.hpp"

#include "frequency.h"

const std::string toEncode = "Once there were brook trouts in the streams in the mountains. You could see them"
                                 " standing in the amber current where the white edges of their fins wimpled softly in"
                                 " the flow. They smelled of moss in your hand. Polished and muscular and torsional."
                                 " On their backs were vermiculate patterns that were maps of the world in its"
                                 " becoming. Maps and mazes. Of a thing which could not be put back. Not be made right"
                                 " again. In the deep glens where they lived all things were older than man and they"
                                 " hummed of mystery.";

int main() {
    ktest::runAllTests();
    const std::map<char, size_t> freqs = getFrequencies(toEncode);
    std::cout << "Frequencies:" << std::endl;
    for (const auto &[key, value] : freqs) {
        std::cout << "  " << key << ": " << value << std::endl;
    }
    return 0;
}