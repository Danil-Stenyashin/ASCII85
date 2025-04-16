#include <iostream>
#include <string>
#include <stdexcept>
#include "encoder.h"
#include "decoder.h"

int main(int argc, char* argv[]) {
    try {
        if (argc > 2) {
            throw std::runtime_error("Correct one: ascii85 '-e' or '-d'");
        } else if (argc == 2) {
            std::string arg = argv[1];
            if (arg == "-e") {
                encoder(std::cin, std::cout);
            } else if (arg == "-d") {
                decoder(std::cin, std::cout);
            } else {
                throw std::runtime_error("Unknown argument: " + arg);
            }
        } else {
            encoder(std::cin, std::cout);
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
        return 1;
    }

    return 0;
}

