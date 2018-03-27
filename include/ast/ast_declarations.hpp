#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_nodes.hpp"

#include <cmath>
#include <sstream>

class InitialisedVariableDeclaration : public Node
{
private:
    std::string type, id;
    NodePtr value;
public:
    InitialisedVariableDeclaration(const std::string &_type, const std::string &_id, const NodePtr _value)
        : type(_type),
        id(_id),
        value(_value)
    {}

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"=";
        value->translate(0, dst);
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(type, id);
        value->code_gen(dst, context);
        // dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        context.set_binding(id,"s0",dst,0);
    }
};

//currently global variable can only be a number (but in c it can be an expression evaluated at compile time)
class InitialisedGlobalVariableDeclaration : public Node
{
private:
    std::string type, id;
    double value;
public:
    InitialisedGlobalVariableDeclaration(const std::string &_type, const std::string &_id, const double _value)
        : type(_type),
        id(_id),
        value(_value)
    {
        getGlobals().push_back(id);
    }

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"="<<value;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        dst<<"\t.globl\t"<<id<<std::endl;
        if (context.is_first_global) {
            dst<<"\t.data\t"<<std::endl;
            context.is_first_global = false;
        }
        dst<<"\t.allign\t2"<<std::endl;
        dst<<"\t.type\t"<<id<<", @object"<<std::endl;
        dst<<"\t.size\t"<<id<<", "<<context.get_size(type)<<std::endl;
        dst<<id<<":"<<std::endl;
        dst<<"\t.word\t"<<(int)value<<std::endl;
    }
};

class GlobalVariableDeclaration : public Node
{
private:
    std::string type, id;
public:
    GlobalVariableDeclaration(const std::string &_type, const std::string &_id)
        : type(_type),
        id(_id)
    {
        getGlobals().push_back(id);
    }

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"=0";
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
    }
};

class Parameter : public Node
{
private:
    std::string type, id;
public:
    Parameter(const std::string &_type, const std::string &_id)
        : type(_type),
        id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(type,id);
        std::string reg = "a"+std::to_string(context.next_register());
        context.set_binding(id,reg,dst,0);
    }
};

class ParameterList : public Node
{
protected:
    NodePtr list, parameter;
public:
    ParameterList (NodePtr _list, NodePtr _parameter)
            : list(_list),
            parameter(_parameter)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        //parameter list could contain one parameter
       if (list != nullptr) {
            list->translate(0,dst);
            dst << ", ";
        }
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
        const Parameter* param = dynamic_cast<const Parameter *>(parameter);
        // parameter list could contain one parameter
        if (list != nullptr) {
            list->code_gen(dst, context);
        }
        parameter->code_gen(dst, context);
        // paremter list cannot containg more than 4 parameters (assuming 4 bytes parameters)
        // if (context.get_binding(param->Parameter::getId()) > 12) {
        //     throw std::runtime_error("More than 4 parameters not supported");
        // }
    }
};

class Function : public Node
{
protected:
    NodePtr compound, parameter_list;
    std::string type, identifier;
public:
    Function(std::string &_type, std::string &_identifier, NodePtr _parameter_list, NodePtr _compound)
        : type(_type)
        , identifier(_identifier)
        , parameter_list(_parameter_list)
        , compound(_compound)
    {
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"def "<<identifier<<"(";
        if (parameter_list != nullptr) parameter_list->translate(0, dst);
        dst<<"):";
        compound->translate(level, dst);
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (parameter_list != nullptr) {
            const ParameterList* params = dynamic_cast<const ParameterList *>(parameter_list);
            context.add_function(identifier, params->get_num());
        } else {
            context.add_function(identifier, 0);
        }

        std::stringstream init;

        if (context.is_first_text) {
            dst<<"\t.text\t"<<std::endl;
            context.is_first_text = false;
        }

        dst<<"\t.align\t2"<<std::endl;
        dst<<"\t.global\t"<<identifier<<std::endl;
        dst<<"\t.set\tnomips16"<<std::endl;
        dst<<"\t.set\tnomicromips"<<std::endl;
        dst<<"\t.ent\t"<<identifier<<std::endl;
        dst<<"\t.type\t"<<identifier<<", @function"<<std::endl;
        
        dst<<identifier<<":"<<std::endl; //.frame goes after the identifier
        init<<"\t.set\tnoreorder"<<std::endl;
        init<<"\t.set\tnomacro"<<std::endl;
        std::stringstream inner_compiled; 
        Context inner_context = new Context(context);
        if(parameter_list != NULL){
            parameter_list->code_gen(inner_compiled,inner_context);
            inner_context.reset_registers(); //after the parameter list
        }
        compound->code_gen(inner_compiled, inner_context);
        dst<<"\t.frame\t$fp,"<<inner_context.size()<<",$31"<<std::endl;
        dst<<init.str();
        dst<<"\taddiu\t$sp,$sp,-"<<inner_context.size()<<std::endl;
        dst<<"\tsw\t$31, 4($sp)\n";
        dst<<"\tsw\t$30, 8($sp)\n";
        dst<<"\tsw\t$29, 12($sp)\n";
        dst<<"\tsw\t$28, 16($sp)\n";
        dst<<"\tsw\t$s7, 20($sp)\n";
        dst<<"\tsw\t$s6, 24($sp)\n";
        dst<<"\tsw\t$s5, 28($sp)\n";
        dst<<"\tsw\t$s4, 32($sp)\n";
        dst<<"\tsw\t$s3, 36($sp)\n";
        dst<<"\tsw\t$s2, 40($sp)\n";
        dst<<"\tsw\t$s1, 44($sp)\n";
        dst<<"\tsw\t$s0, 48($sp)\n";
        dst<<"\tmove\t$fp,$sp"<<std::endl;
        dst<<inner_compiled.str();
        // dst << "\taddiu	$sp,$sp," << inner_context.size()<<std::endl;
        dst<<"\t.set\tmacro"<<std::endl;
        dst<<"\t.set\treorder"<<std::endl;
        dst<<"\t.end\t"<<identifier<<std::endl<<std::endl;
    }
};

class VariableDeclaration : public Node
{
private:
    std::string type, id;
public:
    VariableDeclaration(const std::string &_type, const std::string &_id)
        : type(_type),
        id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"=0";
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(type, id);
    }
};

class ArrayDeclaration : public Node
{
private:
    std::string type, id;
    int size;
public:
    ArrayDeclaration(const std::string &_type, const std::string &_id, int _size)
        : type(_type),
        id(_id),
        size(_size)
    {}

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("ArrayDeclaration::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_arr_binding(type,id,size);
    }
};

class InitParams : public Node
{
protected:
    NodePtr list, expr;
public:
    InitParams(NodePtr _list, NodePtr _expr)
            : list(_list),
            expr(_expr)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("InitParams::translate is not implemented.");
    }

    //undefined behaviour
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("InitParams::code_gen more input parameters to this function need to be supplied");
    }

    virtual void code_gen(std::ostream &dst, Context &context,const int& mem,const int& type_size, int& current) const
    {
        if (list != nullptr) {
            current++;
            const InitParams* params = dynamic_cast<const InitParams *>(list);
            params->code_gen(dst, context, mem,type_size, current);
        }
        expr->code_gen(dst,context);
        dst<<"\tlw\t$s0"<<","<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tsw\t$s0"<<","<<mem+type_size*current<<"($fp)"<<std::endl;
    }
};

class InitialisedArrayDeclaration : public Node
{
private:
    std::string type, id;
    int size;
    NodePtr init;
public:
    InitialisedArrayDeclaration(const std::string &_type, const std::string &_id, int _size, NodePtr _init)
        : type(_type),
        id(_id),
        size(_size),
        init(_init)
    {}

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("InitialisedArrayDeclaration::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_arr_binding(type,id,size);
        const InitParams* params = dynamic_cast<const InitParams *>(init);
        int num = 0;
        params->code_gen(dst,context, context.get_binding(id), context.get_size(type),num);
    }
};

#endif
