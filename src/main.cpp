#include <cctype>
#include <cstdlib>
#include <fstream>
#include <ios>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "./generation.hpp"
#include "./parser.hpp"
#include "./tokenization.hpp"

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "Wrong usage..." << std::endl;
        std::cout << "Try yelang <input file>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string c;
    {
        std::stringstream cStream;
        std::fstream input(argv[1], std::ios::in);
        cStream << input.rdbuf();
        c = cStream.str();
    }

    Tokenizer tokenizer(std::move(c));
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<NodeExit> tree = parser.parse();

    if (!tree.has_value()) {
        std::cerr << "No exit statement found" << std::endl;
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());

    {
        std::fstream file("out.asm", std::ios::out);
        file << generator.generate();
    }

    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}
