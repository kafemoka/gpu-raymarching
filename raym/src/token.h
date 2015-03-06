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

std::string tokenType(TokenType _type);

struct Token {
    Token(TokenType _type = TokenType::ILLEGAL, std::string _lexeme = "")
        : m_type(_type), m_lexeme(_lexeme) {}

    TokenType m_type;
    std::string m_lexeme;
};

