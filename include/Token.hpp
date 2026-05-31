#pragma once
#include <string>
#include <optional>

enum class TokenType
{
    exit,
    semi,
    int_lit,
    open_paren,
    close_paren,
    ident,
    eq,
    i8
};

struct Token
{
    TokenType type;
    std::optional<std::string> value{};
};
