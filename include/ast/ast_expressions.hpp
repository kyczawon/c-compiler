#ifndef ast_expressions_hpp
#define ast_expressions_hpp

#include "ast_nodes.hpp"

class FunctionInvocation : public Node
{
protected:
    NodePtr input_params;
    std::string identifier;
public:
    FunctionInvocation(std::string &_identifier, NodePtr _input_params)
        : identifier(_identifier)
        , input_params(_input_params)
    {
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<identifier<<"(";
        if (input_params != nullptr) {//there could be no input parameters into a function
            input_params->translate(0,dst);
        }
        dst<<")";
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("FunctionInvocation::code_gen is not implemented.");
    }
};

class InputParams : public Node
{
protected:
    NodePtr list, parameter;
public:
    InputParams(NodePtr _list, NodePtr _parameter)
            : list(_list),
            parameter(_parameter)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        //parameter list could contain one parameter
       if (list != nullptr) {
            list->translate(0,dst);
        }
        dst << ", ";
        parameter->translate(0,dst);
    }

    unsigned int get_num() const
    {
        const ParameterList* params = dynamic_cast<const ParameterList *>(list);
        unsigned int num = 1;
        if (list != nullptr) {
            num += params->get_num();
        }
        return num;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (list != nullptr) {
            list->code_gen(dst, context);
        }
        parameter->code_gen(dst, context);
    }
};

class ExprList : public Node
{
protected:
    NodePtr expr_list, expr;
public:
    ExprList(NodePtr _expr_list, NodePtr _expr)
            : expr_list(_expr_list),
            expr(_expr)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        expr_list->translate(level,dst);
        dst << ", ";
        expr->translate(level,dst);
    }
};

#endif