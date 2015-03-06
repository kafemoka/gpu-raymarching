#include "token.h"

std::string tokenType(TokenType _type) {
    static std::map<TokenType, std::string> s_tokenTypes;
    if(s_tokenTypes.size() == 0) {
        s_tokenTypes[TokenType::RAYMARCH] = "raymarch";
        s_tokenTypes[TokenType::CUBE] = "cube";
        s_tokenTypes[TokenType::SPACE] = "space";
        s_tokenTypes[TokenType::SPHERE] = "sphere";
        s_tokenTypes[TokenType::OBJECT] = "object";
        s_tokenTypes[TokenType::ENDOFLINE] = "end of line";
        s_tokenTypes[TokenType::FLOAT] = "float";
    }
    return s_tokenTypes[_type];
}

