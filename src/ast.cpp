#include "ast.h"

ASTDeclarationNode::ASTDeclarationNode(std::shared_ptr<ASTValueNode> _id,
        std::shared_ptr<SymbolTable> _symbolTable,
        std::vector<std::shared_ptr<ASTValueNode>> _args,
        TokenType _type,
        int _line, int _column)
    : ASTStatementNode(_symbolTable) {

    m_childs.push_back(_id);
    for(auto& arg : _args) {
        m_childs.push_back(arg);
    }
    _symbolTable->add({ _type, _id->getValue(), _line, _column });
}

// void ASTDeclarationNode::evaluate(std::shared_ptr<ShaderSymbolTable> _shaderSymbols) {
//
// }

ASTAggregateNode::ASTAggregateNode(std::shared_ptr<ASTValueNode> _id,
        std::shared_ptr<SymbolTable> _symbolTable,
        int _line, int _column)
    : ASTStatementNode(_symbolTable) {

    _symbolTable->add({ TokenType::OBJECT, _id->getValue(), _line, _column });
}

void ASTStatementsNode::addStatement(std::shared_ptr<ASTStatementNode> _stmt) {
    m_childs.push_back(_stmt);
}
