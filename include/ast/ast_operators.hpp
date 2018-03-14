#ifndef ast_operators_hpp
#define ast_operators_hpp

#include "ast_nodes.hpp"

#include <string>
#include <cmath>
#include <iostream>

class Operator
    : public Node
{
protected:
    NodePtr left;
    NodePtr right;

    Operator(NodePtr _left, NodePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual const char *getOpcode() const =0;

    NodePtr getLeft() const
    { return left; }

    NodePtr getRight() const
    { return right; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        left->translate(level, dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->translate(0, dst);
    }
};

class AssignmentOperator
    : public Node
{
protected:
    std::string value;
    NodePtr right;

    virtual const char *getOpcode() const
    { return "="; }
public:
    AssignmentOperator(std::string &_left, NodePtr _right)
        : value(_left),
        right(_right)
    {}
    
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<value;
        dst<<getOpcode();
        right->translate(0, dst);
    }

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("AssignmentOperator::code_gen is not implemented.");
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("AddOperator::code_gen is not implemented.");
    }
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
public:
    SubOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("SubOperator:code_gen is not implemented.");
    }
};


class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
public:
    MulOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("MulOperator::code_gen is not implemented.");
    }
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
public:
    DivOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("DivOperator::code_gen is not implemented.");
    }
};

class EqualsOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "=="; }
public:
    EqualsOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("EqualsOperator::code_gen is not implemented.");
    }
};

class NotEqualsOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "!="; }
public:
    NotEqualsOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("NotEqualsOperator::code_gen is not implemented.");
    }
};

class GreaterOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">"; }
public:
    GreaterOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("GreaterOperator::code_gen is not implemented.");
    }
};

class SmallerOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<"; }
public:
    SmallerOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("SmallerOperator::code_gen is not implemented.");
    }
};

class AndOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "and"; }
public:
    AndOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("AndOperator::code_gen is not implemented.");
    }
};

class OrOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "or"; }
public:
    OrOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        throw std::runtime_error("OrOperator::code_gen is not implemented.");
    }
};

#endif
