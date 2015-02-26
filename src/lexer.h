#pragma once

#include <memory>
#include <map>
#include <sstream>
#include <iostream>
#include <queue>
#include "scanner.h"
#include "symbolTable.h"

struct AST {};
struct ASTNode {};

class Lexer {
public:
    Lexer();

    std::shared_ptr<AST> parse(std::string _scene);

private:
    void addReservedWords();

    SymbolTable m_symbolTable;
    Scanner m_scanner;
};
