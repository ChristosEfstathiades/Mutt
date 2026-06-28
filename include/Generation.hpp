#pragma once

#include "Parser.hpp"
#include <sstream>

class Generator
{
public:
    Generator(NodeProg prog);

    std::string gen_prog() const;
    std::string gen_stmt(const NodeStmt *stmt) const;
    std::string gen_expr(const NodeExpr *expr) const;

private:
    const NodeProg prog;
};