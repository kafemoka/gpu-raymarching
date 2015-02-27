#pragma once

#include <memory>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>
#include "scanner.h"
#include "symbolTable.h"

struct AST {};
struct ASTNode {};

class Lexer {
public:
    Lexer();

    Token identifier();
    void init(std::string _scene);
    Token nextToken();

private:
    void addReservedWords();
    bool isKeyWord(std::string& _word);

    SymbolTable m_symbolTable;
    Scanner m_scanner;
    std::vector<std::string> m_keywords;
};
