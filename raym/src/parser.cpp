#include "parser.h"

Parser::Parser(std::shared_ptr<Lexer> _lexer) : m_lexer(_lexer) {
    m_context = std::shared_ptr<Context>(new Context {
        std::shared_ptr<SymbolTable>(new SymbolTable)
    });

    m_abort = false;
}

std::shared_ptr<ASTStatementNode> Parser::aggregate() {
    auto idNode = identifier();

    if(!idNode) {
        return nullptr;
    }

    readNext();

    switch(peek().m_type) {
        case TokenType::SEMICOLON: {
            auto node = new ASTAggregateNode(idNode, m_context, m_lexer->getLine(), m_lexer->getColumn());
            return std::shared_ptr<ASTAggregateNode>(node);
        }
        case TokenType::ASSIGN: {
            auto rightOperand = expressionF();
            auto atomicId = std::shared_ptr<ASTAtomicNode>(new
                ASTAtomicNode(idNode)
            );
            auto node = new ASTOperatorAssignNode(atomicId, rightOperand);
            return std::shared_ptr<ASTExpressionStatementNode>(
                new ASTExpressionStatementNode(std::shared_ptr<ASTExpressionNode>(node), m_context)
            );
        }
    }

    return nullptr;
}

std::shared_ptr<ASTExpressionNode> Parser::expressionF() {
    readNext();

    if(peek().m_type == TokenType::LPAREN) {
        std::shared_ptr<ASTExpressionNode> expr = expression();
        checkNextToken(TokenType::RPAREN);
        return expr;
    }

    if(peek().m_type != TokenType::IDENTIFIER) {
        unexpectedToken(TokenType::IDENTIFIER);
        return nullptr;
    }

    auto atomicId = atomicIdentifier();

    readNext();

    if(peek().m_type == TokenType::INTERSECT) {

    }
}

std::shared_ptr<ASTExpressionNode> Parser::expression() {
    auto atomicId = atomicIdentifier();

    readLookAhead();

    checkNextToken(TokenType::ASSIGN);

    auto rightOperand = expressionF();
    auto assignNode = new ASTOperatorAssignNode(atomicId, rightOperand);
    return std::shared_ptr<ASTOperatorAssignNode>(assignNode);
}

std::shared_ptr<ASTExpressionStatementNode> Parser::expressionStmt() {
    auto expr = std::shared_ptr<ASTExpressionStatementNode>(
         new ASTExpressionStatementNode(std::shared_ptr<ASTExpressionNode>(expression()), m_context)
    );

    checkNextToken(TokenType::SEMICOLON);

    return expr;
}

void Parser::raymarch() {
}

void Parser::abort() {
    m_abort = true;
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
            if(i < 2) {
                checkNextToken(TokenType::COMMA);
                appendToken(lexeme);
            }
        }

        checkNextToken(TokenType::RPAREN);
        appendToken(lexeme);
    }

    return std::shared_ptr<ASTValueNode>(new ASTValueNode(lexeme));
}

void Parser::appendToken(std::string& _lexeme) {
    _lexeme += peek().m_lexeme;
}

bool Parser::checkSymbol(const std::string& _lexeme, bool _shouldExist) {
    bool inSymbolTable = m_context->m_symbolTable->contains(_lexeme);

    if(_shouldExist) {
        if(!inSymbolTable) {
            m_errors.push("Undefined symbol " + _lexeme);
            abort();
            return false;
        }
    } else {
        if(inSymbolTable) {
            m_errors.push("Redefinition of symbol " + _lexeme);
            abort();
            return false;
        }
    }

    return true;
}

std::shared_ptr<ASTAtomicNode> Parser::atomicIdentifier() {
    std::string lexeme = peek().m_lexeme;

    if(!checkSymbol(lexeme, true)) {
        return nullptr;
    }

    auto id = std::shared_ptr<ASTValueNode>(new ASTValueNode(peek().m_lexeme));
    return std::shared_ptr<ASTAtomicNode>(new ASTAtomicNode(id));
}

std::shared_ptr<ASTValueNode> Parser::identifier() {
    checkNextToken(TokenType::SPACE, false);
    checkNextToken(TokenType::IDENTIFIER);

    std::string lexeme = peek().m_lexeme;

    if(!checkSymbol(lexeme, false)) {
        return nullptr;
    }

    return std::shared_ptr<ASTValueNode>(new ASTValueNode(peek().m_lexeme));
}

std::shared_ptr<ASTDeclarationNode> Parser::sphere() {
    std::vector<std::shared_ptr<ASTValueNode>> args;

    auto idNode = identifier();

    if(!idNode) {
        return nullptr;
    }

    checkNextToken(TokenType::LPAREN);
    args.push_back(position());
    checkNextToken(TokenType::COMMA);
    checkNextToken(TokenType::FLOAT);
    args.push_back(std::shared_ptr<ASTValueNode>(new ASTValueNode(peek().m_lexeme)));
    checkNextToken(TokenType::RPAREN);
    checkNextToken(TokenType::SEMICOLON);

    auto node = new ASTDeclarationNode(idNode, m_context, args, TokenType::SPHERE, m_lexer->getLine(), m_lexer->getColumn());

    return std::shared_ptr<ASTDeclarationNode>(node);
}

std::shared_ptr<ASTDeclarationNode> Parser::cube() {
    std::vector<std::shared_ptr<ASTValueNode>> args;

    auto idNode = identifier();

    if(!idNode) {
        return nullptr;
    }

    checkNextToken(TokenType::LPAREN);
    args.push_back(position());
    checkNextToken(TokenType::RPAREN);
    checkNextToken(TokenType::SEMICOLON);

    auto node = new ASTDeclarationNode(idNode, m_context, args, TokenType::CUBE, m_lexer->getLine(), m_lexer->getColumn());

    return std::shared_ptr<ASTDeclarationNode>(node);
}

void Parser::unexpectedToken(TokenType _requiredType) {
    std::string error;

    if(peek().m_lexeme != "") {
        error += "Unexpected " + peek().m_lexeme;
    } else {
        error += "Unexpected token " + tokenType(_requiredType);
    }

    error += " at line " + std::to_string(m_lexer->getLine()) + ", column " + std::to_string(m_lexer->getColumn());
    m_errors.push(error);

    abort();
}

bool Parser::checkNextToken(TokenType _type, bool _skipSpaces) {
    readLookAhead();

    if(_skipSpaces && peek().m_type == TokenType::SPACE) {
        readNext();
    }

    // stack errors
    if(_type != peek().m_type) {
        unexpectedToken(_type);
        return false;
    }

    return true;
}

std::queue<std::string> Parser::getErrors() {
    return m_errors;
}

std::shared_ptr<ASTStatementsNode> Parser::statements() {
    std::shared_ptr<ASTStatementsNode> stmts(new ASTStatementsNode);

    readNext();

    while(peek().m_type != TokenType::ILLEGAL && !m_abort) {

        // parse statements
        switch(peek().m_type) {
            case TokenType::RAYMARCH: {
                raymarch();
                break;
            }
            case TokenType::CUBE: {
                stmts->addStatement(cube());
                break;
            }
            case TokenType::SPHERE: {
                stmts->addStatement(sphere());
                break;
            }
            case TokenType::OBJECT: {
                stmts->addStatement(aggregate());
                break;
            }
            case TokenType::IDENTIFIER: {
                stmts->addStatement(expressionStmt());
                break;
            }
        }

        checkNextToken(TokenType::ENDOFLINE);
        readLookAhead();

        // move next line
        TokenType type = peek().m_type;
        while (type == TokenType::SPACE || type == TokenType::COMMENT) {
            readLookAhead();
            type = peek().m_type;
        }
    }

    if(peek().m_type == TokenType::ILLEGAL) {
        m_errors.push("Illegal token line " + std::to_string(m_lexer->getLine())
                      + " column " + std::to_string(m_lexer->getColumn()));
    }

    return stmts;
}

Token Parser::peek() {
    return m_token;
}

void Parser::readNext() {
    readLookAhead();

    while(peek().m_type == TokenType::SPACE) {
        readLookAhead();
    }
}

void Parser::readLookAhead() {
    m_last = m_token;
    m_token = m_lexer->nextToken();
}

std::shared_ptr<AST> Parser::parse() {
    return std::shared_ptr<AST>(new AST(statements()));
}
