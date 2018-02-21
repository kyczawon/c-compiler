#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <cmath>
#include <iostream>

class Operator
    : public Expression
{
protected:
    ExpressionPtr left;
    ExpressionPtr right;

    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual const char *getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print(int level, std::ostream &dst) const override
    {
        left->print(level, dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print(0, dst);
        dst<<std::endl;
    }
};

class AssignmentOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "="; }
public:
    AssignmentOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        double vr=right->evaluate(bindings);
        return vr;
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
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
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
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
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
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
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
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

#endif
