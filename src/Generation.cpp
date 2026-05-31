#include "Generation.hpp"
#include <sstream>

Generator::Generator(NodeExit root) : root(root) {}

std::string Generator::generate() {
    std::stringstream out;

    out << "#include \"Runtime.h\"\n";
    out << "int main() {\n";
    out << "    return " << root.expr.int_lit.value.value() << ";\n";
    out << "}\n";
    return out.str();
}