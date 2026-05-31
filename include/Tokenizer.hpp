#pragma once
#include <string>
#include <optional>
#include <vector>
#include <cstdint>

#include "Token.hpp"

class Tokenizer {
public:
    Tokenizer(const std::string & src);

    std::vector<Token> tokenize();
private:
    const std::string src;
    size_t index = 0;

    [[nodiscard]] std::optional<char> peek(size_t ahead = 0) const;
    char consume();
};