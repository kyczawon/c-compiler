#ifndef ast_expressions_hpp
#define ast_expressions_hpp

#include "ast_nodes.hpp"

class FunctionInvocation : public Node
{
protected:
    NodePtr input_args;
    std::string identifier;
public:
    FunctionInvocation(std::string &_identifier, NodePtr _input_args)
        : identifier(_identifier)
        , input_args(_input_args)
    {
        input_args->setParent(this);
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<identifier<<"(";
        if (input_args != nullptr) input_args->translate(0,dst); //input_args could be empty
        dst<<")";
    }

    virtual void code_gen(std::ostream &dst) const override
    {
        get_binding(identifier);
    }
};

class NodeList : public Node
{
protected:
    NodePtr expr_list, expr;
public:
    NodeList(NodePtr _expr_list, NodePtr _expr)
            : expr_list(_expr_list),
            expr(_expr)
        {
            expr_list->setParent(this);
            expr->setParent(this);
        }
    virtual void translate(int level, std::ostream &dst) const override
    {
        expr_list->translate(level,dst);
        dst << ", ";
        expr->translate(level,dst);
    }
};

#endif