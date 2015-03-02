#pragma once

#include <map>
#include <string>

enum class TokenType {
    ENDOFFILE,
    ENDOFLINE,
    ILLEGAL,
    COMMENT,    // #
    FLOAT,      // 123.12

    UNION,      // +
    INTERSECT,  // /
    SUBSTRACT,  // -
    TWIST,      // ~

    IDENTIFIER, // A-Za-z

    ASSIGN,     // =
    LPAREN,     // (
    RPAREN,     // )
    COMMA,      // ,
    SEMICOLON,  // ;
    COLON,      // :
    SPACE,

    RAYMARCH,   // raymarch
    SPHERE,     // Sphere
    CUBE,       // Cube
    OBJECT
    // ...
};

static std::string tokenType(TokenType _type) {
    static std::map<TokenType, std::string> s_tokenTypes;
    if(s_tokenTypes.size() == 0) {
        s_tokenTypes[TokenType::RAYMARCH] = "raymarch";
        s_tokenTypes[TokenType::CUBE] = "cube";
        s_tokenTypes[TokenType::SPACE] = "space";
        s_tokenTypes[TokenType::SPHERE] = "sphere";
    }
    return s_tokenTypes[_type];
}

struct Token {
    Token(TokenType _type = TokenType::ILLEGAL, std::string _lexeme = "")
        : m_type(_type), m_lexeme(_lexeme) {}

    TokenType m_type;
    std::string m_lexeme;
};

