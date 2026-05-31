#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>
#include <optional>
#include <vector>

#include "Tokenizer.hpp"





std::string tokens_to_asm(const std::vector<Token> &tokens) {
    std::stringstream out;
    out << "#include \"Runtime.h\"\n";
    out << "int main() {\n";
    for (size_t i=0; i < tokens.size(); i++) {
        const Token &token = tokens.at(i);
        if (token.type == TokenType::exit) {
            if (i + 1 < tokens.size() && tokens.at(i+1).type == TokenType::int_lit) {
                if (i + 2 < tokens.size() && tokens.at(i+2).type == TokenType::semi) {
                    out << "    return " << tokens.at(i + 1).value.value() << ";\n";
                }
            }
        }
    }
    out << "}\n";
    return out.str();
}


int main(int argc, char* argv[]) {

    if (argc != 2) {
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

    std::cout << contents << std::endl;

    Tokenizer tokenizer(contents);

    std::vector<Token> mytokens = tokenizer.tokenize();

    std::cout << tokens_to_asm(mytokens) << std::endl;
    
    {
        std::fstream outfile("../out.c", std::ios::out);
        outfile << tokens_to_asm(mytokens);
    }
    return 0;
}