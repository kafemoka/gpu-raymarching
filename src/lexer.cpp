#include "lexer.h"

Lexer::Lexer() {
    m_keywords.push_back(KW_RAYMARCH);
    m_keywords.push_back(KW_OBJECT);
    m_keywords.push_back(KW_CUBE);
    m_keywords.push_back(KW_SPHERE);
}

bool Lexer::isKeyWord(std::string& _word) {
    return std::find(m_keywords.begin(), m_keywords.end(), _word) != m_keywords.end();
}

Token Lexer::identifier() {
    Token token;
    std::string lexeme;
    char c = m_scanner.peek();

    while(!isspace(c) && (isalpha(c) || isdigit(c))) {
        lexeme += m_scanner.peek();
        m_scanner.get(false);
        c = m_scanner.peek();
    }

    if(isKeyWord(lexeme)) {
        std::cout << "keyword:" << lexeme << std::endl;
        if(lexeme == KW_SPHERE) {
            return Token(TokenType::SPHERE);
        } else if(lexeme == KW_CUBE) {
            return Token(TokenType::CUBE);
        } else if(lexeme == KW_OBJECT) {
            return Token(TokenType::OBJECT);
        } else if(lexeme == KW_RAYMARCH) {
            return Token(TokenType::RAYMARCH);
        }
    } else {
        std::cout << "identifier:" << lexeme << std::endl;
        return Token(TokenType::IDENTIFIER, lexeme);
    }

    return token;
}

Token Lexer::digit() {
    Token token;
    std::string lexeme;
    char c = m_scanner.peek();
    bool fract = false;

    while(!isspace(c) && (isdigit(c) || c == '.')) {
        fract |= (c == '.');
        lexeme += m_scanner.peek();
        m_scanner.get(false);
        c = m_scanner.peek();
    }

    if(fract) {
        std::cout << "float:" << lexeme << std::endl;
        return Token(TokenType::FLOAT, lexeme);
    }

    return token;
}

Token Lexer::nextToken() {
    Token token;

    while(!m_scanner.isEOS()) {
        if(m_scanner.isEOL()) {
            m_scanner.nextLine();
            return Token(TokenType::ENDOFLINE);
        }

        switch(m_scanner.peek()) {
            case '(':
                std::cout << "token:lparen" << std::endl;
                m_scanner.get(false);
                return Token(TokenType::LPAREN, "(");
            case ')':
                std::cout << "token:rparen" << std::endl;
                m_scanner.get(false);
                return Token(TokenType::RPAREN, ")");
            case ';':
                std::cout << "token:semicolon" << std::endl;
                m_scanner.get(true);
                return Token(TokenType::SEMICOLON);
            case ',':
                std::cout << "token:comma" << std::endl;
                m_scanner.get(false);
                return Token(TokenType::COMMA, ",");
            case '#':
                std::cout << "token:comment" << std::endl;
                m_scanner.nextLine();
                return Token(TokenType::COMMENT);
            case '=':
                std::cout << "token:assign" << std::endl;
                m_scanner.get(false);
                return Token(TokenType::ASSIGN);
            case '+':
                std::cout << "token:union" << std::endl;
                m_scanner.get(false);
                return Token(TokenType::UNION);
            case '-':
                std::cout << "token:substract" << std::endl;
                m_scanner.get(false);
                return Token(TokenType::SUBSTRACT);
            case '/':
                std::cout << "token:intersect" << std::endl;
                m_scanner.get(false);
                return Token(TokenType::INTERSECT);
        }

        if(isspace(m_scanner.peek())) {
            m_scanner.get(false);
            return Token(TokenType::SPACE);
        }

        if(isdigit(m_scanner.peek())) {
            return digit();
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
