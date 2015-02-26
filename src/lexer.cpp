#include "lexer.h"

Lexer::Lexer() {}

Token consumeToken(std::queue<Token>& _tokens, TokenType _type) {

}

std::shared_ptr<ASTNode> statements() {

}

void variableDefinition(std::queue<Token>& _tokens, Token& _token) {
    // add to symbol table
}

void line() {
    /*Token token = consumeToken(_tokens, TokenType::STATEMENT);

    switch(token.m_type) {
        case TokenType::KEYWORD:
            variableDefinition(_tokens, token);
            break;
        case TokenType::STATEMENT:
            // auto node = statements(token, _code);
            // add node to syntax tree
            break;
    }*/
}


std::shared_ptr<AST> Lexer::parse(std::string _scene) {
    std::istringstream iss(_scene);

    std::vector<std::string> lines;

    for(std::string l; std::getline(iss, l); ) {
        if(l.length() != 0) {
            lines.push_back(l);
        }
    }

    m_scanner = Scanner(lines);

    while(!m_scanner.isEOS()) {
        while(!m_scanner.isEOL()) {
            std::cout << m_scanner.get(true) << std::endl;
        }
        m_scanner.nextLine();
    }

    return nullptr;
}
