#include "interpreter.h"

std::string Interpreter::assemble(std::string _shader) {
    std::string sTag = "#pragma begin raym";
    std::string eTag = "#pragma end raym";

    size_t start = _shader.find(sTag);
    size_t end = _shader.find(eTag);

    if(start == std::string::npos || end == std::string::npos) {
        std::cerr << "missing scene definition" << std::endl;
        return "";
    }

    start += sTag.length();

    std::shared_ptr<Lexer> lexer(new Lexer());
    lexer->init(_shader.substr(start, end - start));

    Parser parser(lexer);

    auto ast = parser.parse();

    auto errors = parser.getErrors();

    if(errors.size() > 0) {
        std::cout << errors.front() << std::endl;
    }

    return "";
}
