#pragma once

#include "lexer.h"
#include "token.h"
#include "ast.h"
#include "symbolTable.h"
#include <iostream>
#include <stack>
#include <string>
#include <memory>

class Parser {
public:
    Parser(std::shared_ptr<Lexer> _lexer);

    std::stack<std::string> getErrors();
    std::shared_ptr<AST> parse();

private:
    std::shared_ptr<ASTStatementsNode> statements();
    void aggregate();
    void operation();
    void raymarch();
    std::shared_ptr<ASTCubeNode> cube();
    std::shared_ptr<ASTValueNode> position();
    void sphere();

    bool checkNextToken(TokenType _type, bool _skipSpaces = true);

    Token peek();
    void readLookAhead();
    void appendToken(std::string& _lexeme);

    Token m_token;
    std::shared_ptr<Lexer> m_lexer;
    std::shared_ptr<SymbolTable> m_symbolTable;
    std::stack<std::string> m_errors;
};
