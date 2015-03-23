#pragma once

#include "lexer.h"
#include "token.h"
#include "ast.h"
#include "symbolTable.h"
#include "context.h"
#include <iostream>
#include <queue>
#include <string>
#include <memory>

/*
 * Grammar :
 *
 *   statements -> (statement statements | epsilon) raym
 *   raym -> raymarch (num, id);
 *   statement -> (operation | declaration | aggr-declaration | epsilon);
 *   operation -> operation + id | operation - id | operation / id | id
 *   declaration -> non-aggregate id (position, opt-params)
 *   non-aggregate -> Cube | Sphere | ...
 *   aggregate -> Object
 *   aggr-declaration -> aggregate id = operation
 *   opt-params -> params | epsilon
 *   params -> params, param | param
 *   param -> 3d-position | 2d-position | float-digit
 *   3d-position -> vec3 (float-digit) | vec3 (float-digit, float-digit, float-digit) | vec3 (2d-position)
 *   2d-position -> vec2 (float-digit) | vec2 (float-digit, float-digit)
 *   float-digit -> num.num
 *   num -> 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
 *
 * */

class Parser {
public:
    Parser(std::shared_ptr<Lexer> _lexer);

    std::queue<std::string> getErrors();
    std::shared_ptr<AST> parse();

private:
    void abort();
    void raymarch();
    void unexpectedToken(TokenType _requiredType);
    std::shared_ptr<ASTAtomicNode> atomicIdentifier();
    std::shared_ptr<ASTValueNode> identifier();
    std::shared_ptr<ASTStatementNode> aggregate();
    std::shared_ptr<ASTExpressionStatementNode> expressionStmt();
    std::shared_ptr<ASTExpressionNode> expression();
    std::shared_ptr<ASTExpressionNode> expressionF();
    std::shared_ptr<ASTStatementsNode> statements();
    std::shared_ptr<ASTDeclarationNode> cube();
    std::shared_ptr<ASTDeclarationNode> sphere();
    std::shared_ptr<ASTValueNode> position();

    bool checkNextToken(TokenType _type, bool _skipSpaces = true);

    Token peek();
    void readLookAhead();
    void readNext();
    void appendToken(std::string& _lexeme);

    bool m_abort;
    Token m_token;
    Token m_last;
    std::shared_ptr<Lexer> m_lexer;
    std::shared_ptr<Context> m_context;
    std::queue<std::string> m_errors;
};
