#pragma once

#include <memory>
#include <map>
#include "token.h"

struct SymbolTableEntry {
    TokenType m_type;
    std::string m_lexeme;
    int m_line;
    int m_column;
};

class SymbolTable {

public:
    SymbolTable() {}

    bool add(const SymbolTableEntry& _entry);
    bool contains(std::string _lexeme);

private:
    std::map<std::string, SymbolTableEntry> m_symbols;

};
