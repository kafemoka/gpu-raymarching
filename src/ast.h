#pragma once

#include <vector>
#include <memory>
#include "symbolTable.h"

class ASTNode {
protected:
    std::vector<std::shared_ptr<ASTNode>> m_childs;
};

class AST {
protected:
    std::shared_ptr<ASTNode> m_root;
};

class ASTStatementNode : public ASTNode {
public:
    ASTStatementNode(std::shared_ptr<SymbolTable> _symbolTable) : m_symbolTable(_symbolTable) {}
protected:
    std::shared_ptr<SymbolTable> m_symbolTable;
};

class ASTValueNode : public ASTNode {
public:
    ASTValueNode(std::string _value) : m_value(_value) {}
    std::string getValue() const { return m_value; };
private:
    std::string m_value;
};

class ASTCubeNode : public ASTStatementNode {
public:
    ASTCubeNode(std::shared_ptr<ASTValueNode> _id,
            std::shared_ptr<SymbolTable> _symbolTable,
            std::vector<std::shared_ptr<ASTValueNode>> _args,
            int _line, int _column);
};

