#include "ast.h"

ASTCubeNode::ASTCubeNode(std::shared_ptr<ASTValueNode> _id,
        std::shared_ptr<SymbolTable> _symbolTable,
        std::vector<std::shared_ptr<ASTValueNode>> _args,
        int _line, int _column)
    : ASTStatementNode(_symbolTable) {

    m_childs.push_back(_id);
    for(auto& arg : _args) {
        m_childs.push_back(arg);
    }
    _symbolTable->add({ _id->getValue(), _line, _column });
}

void ASTStatementsNode::addStatement(std::shared_ptr<ASTStatementNode> _stmt) {
    m_childs.push_back(_stmt);
}