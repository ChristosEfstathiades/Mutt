#pragma once
#include <string>
#include <optional>

enum class TokenType {
    exit,
    semi,
    int_lit
};

struct Token {
    TokenType type;
    std::optional<std::string> value {};
};
