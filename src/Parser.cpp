#include "Parser.hpp"

#include <iostream>

namespace
{
    // True for the scalar type keywords that may open a variable declaration.
    bool is_type(TokenType type)
    {
        switch (type)
        {
        case TokenType::u8:
        case TokenType::u16:
        case TokenType::u32:
        case TokenType::u64:
        case TokenType::i8:
        case TokenType::i16:
        case TokenType::i32:
        case TokenType::i64:
        case TokenType::f32:
        case TokenType::f64:
        case TokenType::usize:
            return true;
        default:
            return false;
        }
    }
}

Parser::Parser(std::vector<Token> &tokens) : tokens(tokens) {}

std::optional<Token> Parser::peek(size_t ahead) const
{
    if (index + ahead >= tokens.size())
    {
        return {};
    }
    else
    {
        return tokens.at(index + ahead);
    }
}

// expression can be identifier or literal
std::optional<NodeExpr> Parser::parse_expr()
{
    std::optional<NodeExpr> expr_node;
    if (peek().has_value() && peek().value().type == TokenType::int_lit)
    {
        NodeExprIntLit intLit = {consume()};
        return NodeExpr{intLit};
    }
    else if (peek().has_value() && peek().value().type == TokenType::ident)
    {
        NodeExprIdent identifier = {consume()};
        return NodeExpr{identifier};
    }
    else
    {
        return {};
    }

    return expr_node.value();
}

std::optional<NodeProg> Parser::parse_prog()
{
    NodeProg prog;

    while (peek().has_value())
    {
        if (auto stmt = parse_stmt())
        {
            prog.statements.push_back(stmt.value());
        }
        else
        {
            std::cerr << "Invalid statement" << std::endl;
            exit(EXIT_FAILURE);
        }
    }
    return prog;
}

std::optional<NodeStmt> Parser::parse_stmt()
{
    if (peek().value().type == TokenType::exit && peek(1).has_value() && peek(1).value().type == TokenType::open_paren)
    {
        consume(); // open paren
        consume();
        NodeStmtExit stmt_exit;
        if (auto node_expr = parse_expr())
        { // true if optional has value
            stmt_exit = {node_expr.value()};
        }
        else
        {
            std::cerr << "Invalid Expression" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (peek().has_value() && peek().value().type == TokenType::close_paren)
        {
            consume();
        }
        else
        {
            std::cerr << "Expected ')'" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (peek().has_value() && peek().value().type == TokenType::semi)
        {
            consume();
        }
        else
        {
            std::cerr << "Expected semicolon" << std::endl;
            exit(EXIT_FAILURE);
        }
        return NodeStmt{stmt_exit};
    }
    else if (is_type(peek().value().type) && peek(1).has_value() && peek(1).value().type == TokenType::ident && peek(2).has_value() && peek(2).value().type == TokenType::eq)
    {
        Token type = consume();
        Token identifier = consume();

        auto stmnt_var = NodeStmtVar{};
        stmnt_var.type = type;
        stmnt_var.ident = identifier;
        consume();
        if (auto expr = parse_expr())
        {
            stmnt_var.expr = expr.value();
        }
        else
        {
            std::cerr << "Invalid expression" << std::endl;
            exit(EXIT_FAILURE);
        }
        if (peek().has_value() && peek().value().type == TokenType::semi)
        {
            consume();
        }
        else
        {
            std::cerr << "Expected semicolon" << std::endl;
            exit(EXIT_FAILURE);
        }
        return NodeStmt{stmnt_var};
    }
    else
    {
        return {};
    }
}

Token Parser::consume()
{
    return tokens.at(index++);
}
