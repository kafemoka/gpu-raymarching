#pragma once

#include "lexer.h"
#include "token.h"
#include "ast.h"
#include <iostream>
#include <stack>
#include <string>
#include <memory>

class Parser {
public:
    Parser(std::shared_ptr<Lexer> _lexer) : m_lexer(_lexer) {}

    std::stack<std::string> parse();

private:
    void statements();
    void aggregate();
    void operation();
    void raymarch();
    std::shared_ptr<ASTCubeNode> cube();
    std::shared_ptr<ASTValueNode> position();
    void sphere();

    bool checkToken(TokenType _type);

    Token peek();
    void readLookAhead();

    std::stack<std::string> m_errors;

    Token m_token;
    std::shared_ptr<Lexer> m_lexer;
};
