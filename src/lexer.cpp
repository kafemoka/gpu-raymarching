#include "lexer.h"

Lexer::Lexer() {

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
            std::cout << m_scanner.get(false) << std::endl;
        }
        m_scanner.nextLine();
    }

    return nullptr;
}
