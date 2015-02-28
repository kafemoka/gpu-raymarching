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

#define KW_SPHERE   "Sphere"
#define KW_CUBE     "Cube"
#define KW_OBJECT   "Object"
#define KW_RAYMARCH "raymarch"

class Lexer {
public:
    Lexer();

    Token identifier();
    Token digit();

    void init(std::string _scene);
    Token nextToken();

private:
    void addReservedWords();
    bool isKeyWord(std::string& _word);

    SymbolTable m_symbolTable;
    Scanner m_scanner;
    std::vector<std::string> m_keywords;
};
