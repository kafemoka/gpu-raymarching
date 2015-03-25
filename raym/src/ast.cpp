#include "ast.h"

ASTDeclarationNode::ASTDeclarationNode(std::shared_ptr<ASTValueNode> _id,
                                       std::shared_ptr<Context> _context,
                                       std::vector<std::shared_ptr<ASTValueNode>> _args,
                                       TokenType _type,
                                       int _line, int _column)
    : ASTStatementNode(_context) {

    m_childs.push_back(_id);
    for(auto& arg : _args) {
        m_childs.push_back(arg);
    }
    _context->m_symbolTable->add({ _type, _id->getValue(), _line, _column });
}

ASTAggregateNode::ASTAggregateNode(std::shared_ptr<ASTValueNode> _id,
                                   std::shared_ptr<Context> _context,
                                   int _line, int _column)
    : ASTStatementNode(_context) {

    _context->m_symbolTable->add({ TokenType::OBJECT, _id->getValue(), _line, _column });
}

ASTExpressionStatementNode::ASTExpressionStatementNode(std::shared_ptr<ASTExpressionNode> _expr,
                                                       std::shared_ptr<Context> _context)
    : ASTStatementNode(_context) {
        
    m_childs.push_back(_expr);
}

void ASTStatementsNode::addStatement(std::shared_ptr<ASTStatementNode> _stmt) {
    m_childs.push_back(_stmt);
}

ASTOperatorNode::ASTOperatorNode(std::shared_ptr<ASTExpressionNode> _left,
                                 std::shared_ptr<ASTExpressionNode> _right) {
    m_childs.push_back(_left);
    m_childs.push_back(_right);
}

std::shared_ptr<ASTExpressionNode> ASTOperatorNode::getLeftChild() {
    return std::dynamic_pointer_cast<ASTExpressionNode>(m_childs[0]);
}

std::shared_ptr<ASTExpressionNode> ASTOperatorNode::getRightChild() {
    return std::dynamic_pointer_cast<ASTExpressionNode>(m_childs[1]);
}

void ASTStatementNode::exec() {
    
}

ASTAtomicNode::ASTAtomicNode(std::shared_ptr<ASTValueNode> _value) {
    m_childs.push_back(_value);
}

void ASTAtomicNode::evaluate(std::shared_ptr<Context> _context) {

}

void ASTOperatorUnionNode::evaluate(std::shared_ptr<Context> _context) {

}

void ASTOperatorAssignNode::evaluate(std::shared_ptr<Context> _context) {
    
}

void ASTOperatorSubstractNode::evaluate(std::shared_ptr<Context> _context) {

}

void ASTOperatorIntersectNode::evaluate(std::shared_ptr<Context> _context) {

}
