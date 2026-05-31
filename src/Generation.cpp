#include "Generation.hpp"
#include <sstream>

Generator::Generator(NodeProg prog) : prog(prog) {}

std::string Generator::gen_expr(const NodeExpr &expr) const
{
    struct ExprVisitor
    {
        void operator()(const NodeExprIntLit &expr_int_lit)
        {
        }
        void operator()(const NodeExprIdent &expr_ident)
        {
        }
    };
    ExprVisitor visitor;
    std::visit(visitor, expr.var);
}

std::string Generator::gen_stmt(const NodeStmt &stmt) const
{
    struct StmtVisitor
    {
        void operator()(const NodeStmtExit &stmt_exit)
        {
        }
        void operator()(const NodeStmtVar &stmt_var)
        {
        }
    };
    StmtVisitor visitor;
    std::visit(visitor, stmt.var);
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

    out << "    return 0;\n";
    out << "}\n";
    return out.str();
}