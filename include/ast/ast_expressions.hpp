#ifndef ast_nodes_hpp
#define ast_nodes_hpp

#include "ast_node.hpp"

class FunctionInvocation
    : public Node
{
protected:
    NodePtr input_args;
    std::string identifier;
public:
    FunctionInvocation(std::string &_identifier, NodePtr _input_args)
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
    : public Node
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

class NodeList
    : public Node
{
protected:
    NodePtr expr_list, expr;
public:
    NodeList(NodePtr _expr_list, NodePtr _expr)
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