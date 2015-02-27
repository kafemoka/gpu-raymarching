#include "shaderAssembler.h"

std::string ShaderAssembler::assemble(std::string _path) {
    std::string shader;

    if(!loadFromPath(_path, &shader)) {
        std::cerr << "error loading shader from " + _path << std::endl;
        return "";
    }

    std::string sTag = "#pragma begin scene";
    std::string eTag = "#pragma end scene";

    size_t start = shader.find(sTag);
    size_t end = shader.find(eTag);

    if(start == std::string::npos || end == std::string::npos) {
        std::cerr << "missing scene definition" << std::endl;
        return "";
    }

    start += sTag.length();

    Lexer lexer;
    lexer.init(shader.substr(start, end - start));

    Token t = lexer.nextToken();

    return "";
}
