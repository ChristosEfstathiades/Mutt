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
    // scalar types (see include/Runtime.h)
    u8,
    u16,
    u32,
    u64,
    i8,
    i16,
    i32,
    i64,
    f32,
    f64,
    usize
};

struct Token
{
    TokenType type;
    std::optional<std::string> value{};
};
