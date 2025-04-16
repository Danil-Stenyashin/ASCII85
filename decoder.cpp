#include "decoder.h"
#include <vector>
#include <array>
#include <cmath>
#include <stdexcept>
#include <cctype>

void decoder(std::istream& in, std::ostream& out) {
    std::vector<char> block;
    char ch;

    while (in.get(ch)) {
        if (std::isspace(static_cast<unsigned char>(ch))) continue;

        if (ch == 'z') {
            if (!block.empty())
                throw std::runtime_error("'z' found in the middle of a block");
            out.write("\0\0\0\0", 4);
            continue;
        }

        if (ch < 33 || ch > 117)
            throw std::runtime_error("Invalid ASCII85 character");

        block.push_back(ch);

        if (block.size() == 5) {
            uint32_t num = 0;
            for (int i = 0; i < 5; ++i) {
                num += static_cast<uint32_t>(block[i] - 33) * static_cast<uint32_t>(std::pow(85, 4 - i));
            }

            std::array<char, 4> decoded;
            for (int i = 0; i < 4; ++i) {
                decoded[i] = static_cast<char>((num >> (8 * (3 - i))) & 0xFF);
            }

            out.write(decoded.data(), 4);
            block.clear();
        }
    }

    int size = block.size();
    if (size) {
        while (block.size() < 5)
            block.push_back('u');

        uint32_t num = 0;
        for (int i = 0; i < 5; ++i) {
            num += static_cast<uint32_t>(block[i] - 33) * static_cast<uint32_t>(std::pow(85, 4 - i));
        }

        std::array<char, 4> decoded;
        for (int i = 0; i < 4; ++i) {
            decoded[i] = static_cast<char>((num >> (8 * (3 - i))) & 0xFF);
        }

        out.write(decoded.data(), size - 1);
    }
}

