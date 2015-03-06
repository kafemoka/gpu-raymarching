#pragma once

#include "symbolTable.h"

struct Context {
    std::shared_ptr<SymbolTable> m_symbolTable;
};
