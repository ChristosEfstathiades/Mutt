#pragma once

#include "Parser.hpp"

class Generator {
public:
    Generator(NodeExit root);

    std::string generate();
private:
    const NodeExit root;
};