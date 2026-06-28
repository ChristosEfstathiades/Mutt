#pragma once

#include <vector>
#include <variant>

#include "Token.hpp"
#include "Arena.hpp"

struct NodeExprIntLit
{
    Token int_lit;
};
struct NodeExprIdent
{
    Token ident;
};

struct NodeExpr; // forward declaration

struct BinExprAdd
{
    NodeExpr *left;
    NodeExpr *right;
};

struct BinExprMult
{
    NodeExpr *left;
    NodeExpr *right;
};

struct NodeBinExpr
{
    std::variant<BinExprAdd *, BinExprMult *> var;
};

struct NodeExpr
{
    std::variant<NodeExprIntLit *, NodeExprIdent *, NodeBinExpr *> var;
};

struct NodeStmtExit
{
    NodeExpr *expr;
};
struct NodeStmtVar
{
    Token type;
    Token ident;
    NodeExpr *expr;
};

struct NodeStmt
{
    std::variant<NodeStmtExit *, NodeStmtVar *> var; // union with tracker for runtime
};

struct NodeProg
{
    std::vector<NodeStmt *> statements;
};

class Parser
{
public:
    Parser(std::vector<Token> &tokens);

    std::optional<NodeProg> parse_prog();
    std::optional<NodeExpr *> parse_expr();
    std::optional<NodeStmt *> parse_stmt();

private:
    std::vector<Token> tokens;
    size_t index = 0;
    ArenaAllocator arena;

    [[nodiscard]] std::optional<Token> peek(size_t ahead = 0) const;
    Token consume();
};