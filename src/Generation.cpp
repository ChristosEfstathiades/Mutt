#include "Generation.hpp"

#include <sstream>
#include <variant>

namespace
{
    // Maps a Mutt type token to its C type name. The Mutt scalar type names
    // (see include/Runtime.h) are identical to their C aliases, so this is a
    // straight 1:1 mapping.
    std::string c_type(const Token &type)
    {
        switch (type.type)
        {
        case TokenType::u8:
            return "u8";
        case TokenType::u16:
            return "u16";
        case TokenType::u32:
            return "u32";
        case TokenType::u64:
            return "u64";
        case TokenType::i8:
            return "i8";
        case TokenType::i16:
            return "i16";
        case TokenType::i32:
            return "i32";
        case TokenType::i64:
            return "i64";
        case TokenType::f32:
            return "f32";
        case TokenType::f64:
            return "f64";
        case TokenType::usize:
            return "usize";
        default:
            return "int";
        }
    }
}

Generator::Generator(NodeProg prog) : prog(prog) {}

std::string Generator::gen_expr(const NodeExpr &expr) const
{
    struct ExprVisitor
    {
        std::string operator()(const NodeExprIntLit &expr_int_lit) const
        {
            return expr_int_lit.int_lit.value.value();
        }
        std::string operator()(const NodeExprIdent &expr_ident) const
        {
            return expr_ident.ident.value.value();
        }
    };
    ExprVisitor visitor;
    return std::visit(visitor, expr.var);
}

std::string Generator::gen_stmt(const NodeStmt &stmt) const
{
    struct StmtVisitor
    {
        const Generator &gen;
        std::string operator()(const NodeStmtExit &stmt_exit) const
        {
            return "return " + gen.gen_expr(stmt_exit.expr) + ";\n";
        }
        std::string operator()(const NodeStmtVar &stmt_var) const
        {
            return c_type(stmt_var.type) + " " +
                   stmt_var.ident.value.value() + " = " +
                   gen.gen_expr(stmt_var.expr) + ";\n";
        }
    };
    StmtVisitor visitor{*this};
    return std::visit(visitor, stmt.var);
}

std::string Generator::gen_prog() const
{
    std::stringstream out;

    out << "#include \"Runtime.h\"\n";
    out << "int main() {\n";

    for (const NodeStmt &stmt : prog.statements)
    {
        out << gen_stmt(stmt);
    }

    out << "}\n";
    return out.str();
}
