#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdint>
#include <optional>
#include <vector>


enum class TokenType {
    _return,
    semi,
    int_lit
};

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};


std::string tokens_to_asm(const std::vector<Token> &tokens) {
    std::stringstream out;
    out << "#include \"Runtime.h\"\n";
    out << "int main() {\n";
    for (size_t i=0; i < tokens.size(); i++) {
        const Token &token = tokens.at(i);
        if (token.type == TokenType::_return) {
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



std::vector<Token> tokenize(const std::string &str) {
    std::vector<Token> tokens;
    std::string buf;
    for (size_t i = 0; i < str.length(); i++) {
        char c = str.at(i);
        if (std::isalpha(c)) {
            buf.push_back(c);
            i++;
            while (std::isalnum(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;

            if (buf == "return") {
                Token token = {TokenType::_return};
                tokens.push_back(token);
                buf.clear();
                continue;
            } else {
                std::cerr << "wrong" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
        else if (std::isdigit(c)) {
            buf.push_back(c);
            i++;
            while (std::isdigit(str.at(i))) {
                buf.push_back(str.at(i));
                i++;
            }
            i--;
            Token token = {TokenType::int_lit, buf};
            tokens.push_back(token);
            buf.clear();
        }
        else if (c == ';') {
            Token token = {TokenType::semi};
            tokens.push_back(token);
        }
        else if (std::isspace(c)) {
            continue;
        } else {
            std::cerr << "wrong" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    return tokens;
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
    std::vector<Token> mytokens = tokenize(contents);

    std::cout << tokens_to_asm(mytokens) << std::endl;
    
    {
        std::fstream outfile("../out.c", std::ios::out);
        outfile << tokens_to_asm(mytokens);
    }
    return 0;
}