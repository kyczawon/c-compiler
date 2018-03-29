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
        if (input_params != nullptr) input_params->code_gen(dst,context);
        context.reset_registers();//reset the registers used by input parameters
        dst<<"\n\t.option pic0\n";
        dst<<"\tjal\t"<<identifier<<std::endl;
        dst<<"\tnop"<<std::endl;
        dst<<"\n\t.option pic2\n";
        dst<<"\tsw\t$v0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class InputParams : public Node
{
protected:
    NodePtr list, expr;
public:
    InputParams(NodePtr _list, NodePtr _expr)
            : list(_list),
            expr(_expr)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        //parameter list could contain one parameter
       if (list != nullptr) {
            list->translate(0,dst);
            dst << ", ";
        }
        expr->translate(0,dst);
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
        expr->code_gen(dst, context);
        if(context.get_current_register()<3){
            dst<<"\tlw\t$a"<<context.next_register()<<","<<context.get_current_mem()<<"($fp)"<<std::endl;
        } else {
            dst<<"\tlw\t$t2,"<<context.get_current_mem()<<"($fp)"<<std::endl;
            dst<<"\tsw\t$t2,"<<context.next_register()*4<<"($sp)\n";
        }
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