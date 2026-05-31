#pragma once
#include <string>
#include <optional>
#include <vector>
#include <cstdint>

enum class TokenType {
    exit,
    semi,
    int_lit
};

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};


class Tokenizer {
public:
    Tokenizer(const std::string & src);

    std::vector<Token> tokenize();
private:
    const std::string src;
    size_t index = 0;

    std::optional<char> peek(size_t ahead = 0) const;
    char consume();
};