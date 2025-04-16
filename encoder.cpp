#include "encoder.h"
#include <array>

void encoder(std::istream& in, std::ostream& out) {
    std::array<char, 4> block;
    const std::array<int, 5> powers = { 52200625, 614125, 7225, 85, 1 };

    while (true) {
        in.read(block.data(), 4);
        int count = in.gcount();
        if (count == 0) break;

        if (count < 4) {
            for (int i = 0; i < 4 - count; ++i) {
                block[3 - i] = '\0';
            }
        }

        uint32_t num = 0;
        for (char c : block) {
            num = num * 256 + static_cast<unsigned char>(c);
        }

        if (num == 0 && count == 4) {
            out.put('z');
            continue;
        }

        std::array<char, 5> encoded;
        for (int i = 0; i < 5; ++i) {
            encoded[i] = static_cast<char>(num / powers[i] + 33);
            num %= powers[i];
        }

        out.write(encoded.data(), count + 1);
    }
}

