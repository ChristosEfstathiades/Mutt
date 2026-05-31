#include "Parser.hpp"

#include <iostream>

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens) {}


std::optional<Token> Parser::peek(size_t ahead) const {
    if (index + ahead >= tokens.size()) {
        return {};
    } else {
        return tokens.at(index + ahead);
    }
}

std::optional<NodeExpr> Parser::parse_expr() {
    std::optional<NodeExpr> expr_node;
    if (peek().has_value() && peek().value().type == TokenType::int_lit) {
        return NodeExpr{consume()};
    } else {
        return {};
    }
    
    return expr_node.value();
}

std::optional<NodeExit> Parser::parse() {
    std::optional<NodeExit> exit_node;
    while (peek().has_value()) {
        if (peek().value().type == TokenType::exit) {
            consume();
            if (auto node_expr = parse_expr()) { // true if optional has value
                exit_node = NodeExit {node_expr.value()};
            } else {
                std::cerr << "Invalid Expression" << std::endl;
                exit(EXIT_FAILURE);
            }
            if (peek().has_value() && peek().value().type == TokenType::semi) {
                consume();
            } else {
                std::cerr << "Invalid Expression" << std::endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    index = 0;
    return exit_node;
}

Token Parser::consume() {
    return tokens.at(index++);
}
