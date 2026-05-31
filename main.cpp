#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>
#include <optional>
#include <vector>
#include <cstdlib>

#include "Tokenizer.hpp"
#include "Generation.hpp"

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        std::cerr << "Incorrect usage. Correct usage is..." << std::endl;
        std::cerr << "mutt <input.mutt>" << std::endl;
        return EXIT_FAILURE;
    }
    std::string contents;
    std::string fileName = argv[1];
    {
        std::fstream file("../MuttSrc/" + fileName);
        std::stringstream contents_stream;
        contents_stream << file.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(contents);

    std::vector<Token> mytokens = tokenizer.tokenize();
    Parser parser(mytokens);
    std::optional<NodeProg> tree = parser.parse_prog();
    if (!tree.has_value())
    {
        std::cerr << "No exit statement" << std::endl;
        exit(EXIT_FAILURE);
    }

    Generator generator(tree.value());

    {
        std::fstream outfile("../out.c", std::ios::out);
        outfile << generator.gen_prog();
    }

    system("gcc ../out.c -I../include -o output");

    return 0;
}