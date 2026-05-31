#include "Tokenizer.hpp"

#include <iostream>

Tokenizer::Tokenizer(const std::string &src) : src(src)
{
    
}

std::vector<Token> Tokenizer::tokenize() {
    std::vector<Token> tokens;
    std::string buf;
    while (peek().has_value()) {
        if (std::isalpha(peek().value())) {
            buf.push_back(consume());
            while (peek().has_value() && std::isalnum(peek().value())) {
                buf.push_back(consume());
            }
            if (buf == "exit") {
                tokens.push_back({ TokenType::exit });
                buf.clear();
                continue;
            } else {
                std::cerr << "wrong1" << std::endl;
                exit(EXIT_FAILURE);
            }
        } else if (std::isdigit(peek().value())) {
            buf.push_back(consume());
            while (peek().has_value() && std::isdigit(peek().value())) {
                buf.push_back(consume());

            }
            tokens.push_back({ TokenType::int_lit, buf });
            buf.clear();
            continue;
        } else if (peek().value() == ';') {
            consume();
            tokens.push_back({ TokenType::semi });
            continue;
        } else if (std::isspace(peek().value())) {
            consume();
            continue;
        } else {
            std::cerr << "wrong2" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    
    
    return tokens;
}

std::optional<char> Tokenizer::peek(size_t ahead) const {
    if (index + ahead >= src.length()) {
        return {};
    } else {
        return src.at(index + ahead);
    }
}


char Tokenizer::consume() {
    return src.at(index++);
}
