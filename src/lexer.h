#pragma once

#include <memory>
#include <map>
#include <sstream>
#include <iostream>
#include <queue>
#include "scanner.h"

enum class TokenType {
    IDENTIFIER,
    STATEMENT,
    KEYWORD,
    SEPARATOR,
    EOS
};

enum class SymbolType {
    SPHERE,
    CUBE
};

struct AST {};
struct ASTNode {};

struct Token {
    Token* m_previous;
    TokenType m_type;
    std::string m_value;
};

struct Statement {};

struct Symbol {
    SymbolType m_type;
    std::string m_name;
};

struct SymbolTable {
    std::map<int, Symbol> m_symbols;
};


class Lexer {
public:
    Lexer();

    std::shared_ptr<AST> parse(std::string _scene);

private:
    SymbolTable m_symbolTable;
    Scanner m_scanner;
};
