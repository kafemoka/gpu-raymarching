#include "symbolTable.h"

bool SymbolTable::add(const SymbolTableEntry& _entry) {
    std::string lexeme = _entry.m_lexeme;
    if(!contains(lexeme)) {
        m_symbols[lexeme] = _entry;
        return true;
    }
    return false;
}

bool SymbolTable::contains(const std::string& _lexeme) const {
    return m_symbols.find(_lexeme) != m_symbols.end();
}

TokenType SymbolTable::getSymbolType(const std::string& _lexeme) const {
    if(contains(_lexeme)) {
        return m_symbols.find(_lexeme)->second.m_type;
    }

    return TokenType::ILLEGAL;
}
