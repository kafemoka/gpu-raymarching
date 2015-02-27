#pragma once

#include <memory>
#include <map>
#include "token.h"

struct SymbolTableEntry {
    std::shared_ptr<Token> m_token;
    int m_line;
    int m_column;
    bool m_isReservedWord;
};

class SymbolTable {

public:
    SymbolTable() {}

    void add(std::string _identifier, int _line);
    bool contains(std::string _lexeme);

private:
    std::map<std::string, SymbolTableEntry> m_symbols;

};
