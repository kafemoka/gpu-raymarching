#include "lexer.h"

Lexer::Lexer() {
    m_keywords.push_back("Sphere");
    m_keywords.push_back("Cube");
}

bool Lexer::isKeyWord(std::string& _word) {
    return std::find(m_keywords.begin(), m_keywords.end(), _word) != m_keywords.end();
}

Token Lexer::identifier() {
    Token token;
    std::string lexeme = "";
    char c = m_scanner.get(false);

    while(!isspace(c)) {
        lexeme += c;
        c = m_scanner.get(false);
    }

    if(isKeyWord(lexeme)) {
        std::cout << "keyword:" << lexeme << std::endl;

        if(lexeme == "Sphere") {
            return Token(TokenType::SPHERE);
        } else if(lexeme == "Cube") {
            return Token(TokenType::CUBE);
        }
    } else {
        return Token(TokenType::IDENTIFIER, lexeme);
    }

    return token;
}

Token Lexer::nextToken() {
    Token token;

    while(!m_scanner.isEOS()) {
        switch(m_scanner.peek()) {
            case '(':
                return Token(TokenType::LPAREN);
            case ')':
                return Token(TokenType::RPAREN);
            case ';':
                return Token(TokenType::SEMICOLON);
            case ',':
                return Token(TokenType::COMMA);
        }

        if(isdigit(m_scanner.peek())) {

        } else {
            return identifier();
        }

        m_scanner.nextLine();
    }

    return token;
}

void Lexer::init(std::string _scene) {
    std::istringstream iss(_scene);

    std::vector<std::string> lines;

    for(std::string l; std::getline(iss, l); ) {
        if(l.length() != 0) {
            lines.push_back(l);
        }
    }

    m_scanner = Scanner(lines);
}
