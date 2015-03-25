#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "context.h"

class ASTNode {
public:
    virtual std::vector<std::shared_ptr<ASTNode>> getChilds() { return m_childs; }
protected:
    std::vector<std::shared_ptr<ASTNode>> m_childs;
};

class ASTStatementNode : public ASTNode {
public:
    ASTStatementNode(std::shared_ptr<Context> _context) : m_context(_context) {}
protected:
    std::shared_ptr<Context> m_context;
    virtual void exec();
};

class ASTStatementsNode : public ASTNode {
public:
    void addNode(ASTStatementsNode _node);
    void addStatement(std::shared_ptr<ASTStatementNode> _stmt);
};

class AST {
public:
    AST(std::shared_ptr<ASTStatementsNode> _root) : m_root(_root) {}
    std::shared_ptr<ASTStatementsNode> getRoot() { return m_root; }
protected:
    std::shared_ptr<ASTStatementsNode> m_root;
};

class ASTValueNode : public ASTNode {
public:
    ASTValueNode(std::string _value) : m_value(_value) {}
    std::string getValue() const { return m_value; };
private:
    std::string m_value;
};

class ASTDeclarationNode : public ASTStatementNode {
public:
    ASTDeclarationNode(std::shared_ptr<ASTValueNode> _id,
                       std::shared_ptr<Context> _context,
                       std::vector<std::shared_ptr<ASTValueNode>> _args,
                       TokenType _type,
                       int _line, int _column);
};

class ASTAggregateNode : public ASTStatementNode {
public:
    ASTAggregateNode(std::shared_ptr<ASTValueNode> _id,
                     std::shared_ptr<Context> _context,
                     int _line, int _column);
};

class ASTExpressionNode : public ASTNode {
public:
    virtual void evaluate(std::shared_ptr<Context> _context) = 0;
};

class ASTExpressionStatementNode : public ASTStatementNode {
public:
    ASTExpressionStatementNode(std::shared_ptr<ASTExpressionNode> _expr,
                               std::shared_ptr<Context> _context);
};

class ASTOperatorNode : public ASTExpressionNode {
protected:
    std::shared_ptr<ASTExpressionNode> getLeftChild(); 
    std::shared_ptr<ASTExpressionNode> getRightChild();

public:
    ASTOperatorNode(std::shared_ptr<ASTExpressionNode> _left,
                    std::shared_ptr<ASTExpressionNode> _right);
};

class ASTAtomicNode : public ASTExpressionNode {
public:
    ASTAtomicNode(std::shared_ptr<ASTValueNode> _value);
    void evaluate(std::shared_ptr<Context> _context) override;
};

class ASTOperatorAssignNode : public ASTOperatorNode {
public:
    ASTOperatorAssignNode(std::shared_ptr<ASTExpressionNode> _left,
                          std::shared_ptr<ASTExpressionNode> _right)
    : ASTOperatorNode(_left, _right) {}
    void evaluate(std::shared_ptr<Context> _context) override;
};

class ASTOperatorUnionNode : public ASTOperatorNode {
public:
    ASTOperatorUnionNode(std::shared_ptr<ASTExpressionNode> _left,
                        std::shared_ptr<ASTExpressionNode> _right)
    : ASTOperatorNode(_left, _right) {}
    void evaluate(std::shared_ptr<Context> _context) override;
};

class ASTOperatorIntersectNode : public ASTOperatorNode {
public:
    ASTOperatorIntersectNode(std::shared_ptr<ASTExpressionNode> _left,
                             std::shared_ptr<ASTExpressionNode> _right)
    : ASTOperatorNode(_left, _right) {}
    void evaluate(std::shared_ptr<Context> _context) override;
};

class ASTOperatorSubstractNode : public ASTOperatorNode {
public:
    ASTOperatorSubstractNode(std::shared_ptr<ASTExpressionNode> _left,
                             std::shared_ptr<ASTExpressionNode> _right)
    : ASTOperatorNode(_left, _right) {}
    void evaluate(std::shared_ptr<Context> _context) override;
};