#ifndef ast_operators_hpp
#define ast_operators_hpp

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

    virtual void print(int level, std::ostream &dst) const override
    {
        left->print(level, dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(0, dst);
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    {
        double vr=right->evaluate(bindings);
        return vr;
    }
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<value;
        dst<<getOpcode();
        right->print(0, dst);
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        double vl=left->evaluate(bindings);
        double vr=right->evaluate(bindings);
        return vl+vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl-vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl*vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl/vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl==vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl!=vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl>vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl<vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl&&vr;
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

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
      double vl=left->evaluate(bindings);
      double vr=right->evaluate(bindings);
      return vl||vr;
    }
};

#endif
