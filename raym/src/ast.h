#pragma once

#include <vector>
#include <memory>
#include <iostream>
#include "context.h"

class ASTNode {
protected:
    std::vector<std::shared_ptr<ASTNode>> m_childs;
};

class ASTStatementNode : public ASTNode {
public:
    ASTStatementNode(std::shared_ptr<Context> _context) : m_context(_context) {}
protected:
    std::shared_ptr<Context> m_context;
};

class ASTStatementsNode : public ASTNode {
public:
    void addNode(ASTStatementsNode _node);
    void addStatement(std::shared_ptr<ASTStatementNode> _stmt);
};

class AST {
public:
    AST(std::shared_ptr<ASTStatementsNode> _root) : m_root(_root) {}
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

    // void evaluate(std::shared_ptr<ShaderSymbolTable> _shaderSymbols);
};

class ASTAggregateNode : public ASTStatementNode {
public:
    ASTAggregateNode(std::shared_ptr<ASTValueNode> _id,
        std::shared_ptr<Context> _context,
        int _line, int _column);
};

