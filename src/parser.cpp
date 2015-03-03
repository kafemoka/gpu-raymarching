#include "parser.h"

Parser::Parser(std::shared_ptr<Lexer> _lexer) : m_lexer(_lexer) {
    m_symbolTable = std::shared_ptr<SymbolTable>(new SymbolTable);
}

void Parser::operation() {

}

void Parser::aggregate() {

}

void Parser::raymarch() {

}

std::shared_ptr<ASTValueNode> Parser::position() {
    checkNextToken(TokenType::IDENTIFIER);
    std::string lexeme;

    appendToken(lexeme);

    if(peek().m_lexeme == KW_VEC3) {
        checkNextToken(TokenType::LPAREN);
        appendToken(lexeme);

        for(int i = 0; i < 3; ++i) {
            checkNextToken(TokenType::FLOAT);
            appendToken(lexeme);
            checkNextToken(TokenType::COMMA);
            appendToken(lexeme);
        }

        checkNextToken(TokenType::RPAREN);
        appendToken(lexeme);
    }

    return std::shared_ptr<ASTValueNode>(new ASTValueNode(lexeme));
}

void Parser::appendToken(std::string& _lexeme) {
    _lexeme += peek().m_lexeme;
}

std::shared_ptr<ASTCubeNode> Parser::cube() {
    checkNextToken(TokenType::SPACE, false);
    checkNextToken(TokenType::IDENTIFIER);

    std::shared_ptr<ASTValueNode> idNode(new ASTValueNode(peek().m_lexeme));
    checkNextToken(TokenType::LPAREN);
    std::vector<std::shared_ptr<ASTValueNode>> args;
    args.push_back(position());

    return std::shared_ptr<ASTCubeNode>(new ASTCubeNode(idNode, m_symbolTable, args, 0, 0));
}

void Parser::sphere() {

}

bool Parser::checkNextToken(TokenType _type, bool _skipSpaces) {
    readLookAhead();
    if(_skipSpaces) {
        while(peek().m_type == TokenType::SPACE) {
            readLookAhead();
        }
    }
    if(_type != peek().m_type) {
        m_errors.push("Unexpected token " + tokenType(_type));
        return false;
    }
    return true;
}

std::stack<std::string> Parser::getErrors() {
    return m_errors;
}

std::shared_ptr<ASTStatementsNode> Parser::statements() {
    std::shared_ptr<ASTStatementsNode> stmts(new ASTStatementsNode);

    readLookAhead();

    while(peek().m_type != TokenType::ILLEGAL) {
        switch(peek().m_type) {
            case TokenType::RAYMARCH: {
                raymarch();
                break;
            }
            case TokenType::CUBE: {
                auto c = cube();
                
                break;
            }
            case TokenType::OBJECT: {
                aggregate();
                break;
            }
        }
        readLookAhead();
    }

    return stmts;
}

Token Parser::peek() {
    return m_token;
}

void Parser::readLookAhead() {
    m_token = m_lexer->nextToken();
}

std::shared_ptr<AST> Parser::parse() {
    auto stmts = statements();
    return std::shared_ptr<AST>(new AST(stmts));
}
