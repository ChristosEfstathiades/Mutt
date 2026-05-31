#pragma once

#include <vector>

#include "Token.hpp"

struct NodeExpr {
    Token int_lit;
};
struct NodeExit {
    NodeExpr expr;
};

class Parser {
public:
    Parser(std::vector<Token> &tokens);

    std::optional<NodeExit> parse();
    std::optional<NodeExpr> parse_expr();

private:
    std::vector<Token> tokens;
    size_t index = 0;


    std::optional<Token> peek(size_t ahead = 0) const;
    Token consume();

};