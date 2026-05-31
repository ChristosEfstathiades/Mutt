#include "Tokenizer.hpp"

#include <iostream>
#include <unordered_map>

Tokenizer::Tokenizer(const std::string &src) : src(src)
{
}

std::vector<Token> Tokenizer::tokenize()
{
    static const std::unordered_map<std::string, TokenType> keywords = {
        {"exit", TokenType::exit},
        {"u8", TokenType::u8},
        {"u16", TokenType::u16},
        {"u32", TokenType::u32},
        {"u64", TokenType::u64},
        {"i8", TokenType::i8},
        {"i16", TokenType::i16},
        {"i32", TokenType::i32},
        {"i64", TokenType::i64},
        {"f32", TokenType::f32},
        {"f64", TokenType::f64},
        {"usize", TokenType::usize},
    };

    std::vector<Token> tokens;
    std::string buf;
    while (peek().has_value())
    {
        if (std::isalpha(peek().value()))
        {
            buf.push_back(consume());
            while (peek().has_value() && std::isalnum(peek().value()))
            {
                buf.push_back(consume());
            }
            if (auto it = keywords.find(buf); it != keywords.end())
            {
                tokens.push_back({it->second});
            }
            else
            {
                tokens.push_back({TokenType::ident, buf});
            }
            buf.clear();
            continue;
        }
        else if (std::isdigit(peek().value()))
        {
            buf.push_back(consume());
            while (peek().has_value() && std::isdigit(peek().value()))
            {
                buf.push_back(consume());
            }
            tokens.push_back({TokenType::int_lit, buf});
            buf.clear();
            continue;
        }
        else if (peek().value() == '=')
        {
            consume();
            tokens.push_back({TokenType::eq});
            continue;
        }
        else if (peek().value() == '(')
        {
            consume();
            tokens.push_back({TokenType::open_paren});
            continue;
        }
        else if (peek().value() == ')')
        {
            consume();
            tokens.push_back({TokenType::close_paren});
            continue;
        }
        else if (peek().value() == ';')
        {
            consume();
            tokens.push_back({TokenType::semi});
            continue;
        }
        else if (std::isspace(peek().value()))
        {
            consume();
            continue;
        }
        else
        {
            std::cerr << "wrong2" << std::endl;
            exit(EXIT_FAILURE);
        }
    }

    return tokens;
}

std::optional<char> Tokenizer::peek(size_t ahead) const
{
    if (index + ahead >= src.length())
    {
        return {};
    }
    else
    {
        return src.at(index + ahead);
    }
}

char Tokenizer::consume()
{
    return src.at(index++);
}
