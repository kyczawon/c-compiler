#ifndef ast_expressions_hpp
#define ast_expressions_hpp

#include "ast_expression.hpp"

class FunctionInvocation
    : public Expression
{
protected:
    ExpressionPtr input_args;
    std::string identifier;
public:
    FunctionInvocation(std::string &_identifier, ExpressionPtr _input_args)
        : identifier(_identifier)
        , input_args(_input_args)
    {
    }
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<identifier<<"(";
        input_args->print(0,dst);
        dst<<")";
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class UnaryFunctionInvocation
    : public Expression
{
protected:
    std::string identifier;
public:
    UnaryFunctionInvocation(std::string &_identifier)
        : identifier(_identifier)
    {
    }
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<identifier<<"()";
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class ExpressionList
    : public Expression
{
protected:
    ExpressionPtr expr_list, expr;
public:
    ExpressionList(ExpressionPtr _expr_list, ExpressionPtr _expr)
            : expr_list(_expr_list),
            expr(_expr)
        {}
    virtual void print(int level, std::ostream &dst) const override
    {
        expr_list->print(level,dst);
        dst << ", ";
        expr->print(level,dst);
    }
};

#endif