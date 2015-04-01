#pragma once

#include "symbolTable.h"
#include "raymarchObject.h"
#include <map>
#include <string>
#include <memory>

struct Context {
    std::shared_ptr<SymbolTable> m_symbolTable;
    std::map<std::string, std::shared_ptr<RaymarchObject>> m_objects;
};
