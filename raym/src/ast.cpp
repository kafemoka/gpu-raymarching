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
    std::shared_ptr<ASTOperatorAssignNode> _assign,
    int _line, int _column)
: ASTStatementNode(_context) {

    m_childs.push_back(_id);

    if(_assign) {
        m_childs.push_back(_assign);
    }

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

void ASTDeclarationNode::exec() {
    auto identifier = std::dynamic_pointer_cast<ASTValueNode>(m_childs[0]);
    const std::string& lexeme = identifier->getValue();
    TokenType symbolType = m_context->m_symbolTable->getSymbolType(lexeme);

    createObject(symbolType, lexeme);
}

void ASTExpressionStatementNode::exec() {
    auto op = std::dynamic_pointer_cast<ASTOperatorNode>(m_childs[0]);
    op->evaluate(m_context);
}

void ASTAggregateNode::exec() {
    auto identifier = std::dynamic_pointer_cast<ASTValueNode>(m_childs[0]);
    const std::string& lexeme = identifier->getValue();

    createObject(lexeme);

    if (m_childs.size() == 2) {
        auto assign = std::dynamic_pointer_cast<ASTOperatorAssignNode>(m_childs[1]);
        auto aggregate = assign->evaluate(m_context);
        m_context->m_objects[aggregate.getSymbol()] = std::make_shared<RaymarchObject>(aggregate);
        m_context->m_objects[lexeme]->assign(aggregate);
    }
}

void ASTAggregateNode::createObject(const std::string& _name) {
    m_context->m_objects[_name] = std::shared_ptr<RaymarchObject>(
        new RaymarchAggregate(_name)
    );
}

void ASTDeclarationNode::createObject(TokenType _type, const std::string& _name) {
    auto pos = std::dynamic_pointer_cast<ASTValueNode>(m_childs[1]);
    std::shared_ptr<RaymarchObject> object = nullptr;

    switch (_type) {
        case TokenType::SPHERE: {
            auto radius = std::dynamic_pointer_cast<ASTValueNode>(m_childs[2]);
            object = std::shared_ptr<RaymarchObject>(
                new RaymarchSphere(_name, pos->getValue(), radius->getValue())
            );
            break;
        }

        case TokenType::CUBE: {
            auto dim = std::dynamic_pointer_cast<ASTValueNode>(m_childs[2]);
            object = std::shared_ptr<RaymarchObject>(
                new RaymarchCube(_name, pos->getValue(), dim->getValue())
            );
            break;
        }

        default:
            break;
    }

    if(object) {
        m_context->m_objects[_name] = object;
    }
}

ASTAtomicNode::ASTAtomicNode(std::shared_ptr<ASTValueNode> _value) {
    m_childs.push_back(_value);
}

RaymarchObject ASTAtomicNode::evaluate(std::shared_ptr<Context> _context) {
    auto child = std::dynamic_pointer_cast<ASTValueNode>(m_childs[0]);
    return *_context->m_objects[child->getValue()];
}

RaymarchObject ASTOperatorAssignNode::evaluate(std::shared_ptr<Context> _context) {
    return getRightChild()->evaluate(_context);
}

RaymarchObject ASTOperatorUnionNode::evaluate(std::shared_ptr<Context> _context) {
    auto op = getRightChild()->evaluate(_context) + getLeftChild()->evaluate(_context);
    _context->m_objects[op.getSymbol()] = std::make_shared<RaymarchObject>(op);
    return op;
}

RaymarchObject ASTOperatorSubstractNode::evaluate(std::shared_ptr<Context> _context) {
    auto op = getRightChild()->evaluate(_context) - getLeftChild()->evaluate(_context);
    _context->m_objects[op.getSymbol()] = std::make_shared<RaymarchObject>(op);
    return op;
}

RaymarchObject ASTOperatorIntersectNode::evaluate(std::shared_ptr<Context> _context) {
    auto op = getRightChild()->evaluate(_context) / getLeftChild()->evaluate(_context);
    _context->m_objects[op.getSymbol()] = std::make_shared<RaymarchObject>(op);
    return op;
}
