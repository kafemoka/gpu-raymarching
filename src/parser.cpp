#include "parser.h"

void Parser::operation() {

}

void Parser::aggregate() {

}

void Parser::raymarch() {

}

std::shared_ptr<ASTValueNode> Parser::position() {
    readLookAhead();
    checkToken(TokenType::IDENTIFIER);
    if(peek().m_lexeme == "vec3") {
        readLookAhead();
        checkToken(TokenType::LPAREN);
        for(int i = 0; i < 3; ++i) {
            readLookAhead();
            checkToken(TokenType::FLOAT);
            readLookAhead();
            checkToken(TokenType::COMMA);
        }
        readLookAhead();
        checkToken(TokenType::RPAREN);
    }
}

std::shared_ptr<ASTCubeNode> Parser::cube() {
    readLookAhead();
    checkToken(TokenType::SPACE);
    readLookAhead();

    if(checkToken(TokenType::IDENTIFIER)) {
        std::shared_ptr<ASTValueNode> idNode(new ASTValueNode(peek().m_lexeme));
        readLookAhead();
        checkToken(TokenType::LPAREN);
        std::vector<std::shared_ptr<ASTValueNode>> args;
        args.push_back(position());
    }
}

void Parser::sphere() {

}

bool Parser::checkToken(TokenType _type) {
    if(_type != peek().m_type) {
        m_errors.push("Unexpected token " + tokenType(_type));
        return false;
    }
    return true;
}

void Parser::statements() {
    readLookAhead();

    while(peek().m_type != TokenType::ILLEGAL) {
        switch(peek().m_type) {
            case TokenType::RAYMARCH:
                raymarch();
                break;
            case TokenType::CUBE:
                cube();
                break;
            case TokenType::OBJECT:
                aggregate();
                break;
        }
        readLookAhead();
    }
}

Token Parser::peek() {
    return m_token;
}

void Parser::readLookAhead() {
    m_token = m_lexer->nextToken();
}

std::stack<std::string> Parser::parse() {
    statements();

    return m_errors;
}
