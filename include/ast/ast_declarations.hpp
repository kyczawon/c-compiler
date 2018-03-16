#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_nodes.hpp"

#include <cmath>
#include <sstream>

class Parameter;

class Function
    : public Node
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
       

        dst<<"\t.align\t2"<<std::endl;
        dst<<"\t.global\t"<<identifier<<std::endl;
        dst<<"\t.set\tnomips16"<<std::endl;
        dst<<"\t.set\tnomicromips"<<std::endl;
        dst<<"\t.type\t"<<identifier<<", @function"<<std::endl;
        dst<<"\t.ent\t"<<identifier<<std::endl;
        dst<<"\t.type\t"<<identifier<<", @function"<<std::endl;
        
        dst<<identifier<<":"<<std::endl;
        dst<<"\t.set\tnoreorder"<<std::endl;
        dst<<"\t.set\tnomacro"<<std::endl;
        std::stringstream inner_compiled; 
        Context inner_context = new Context(context);
        parameter_list->code_gen(inner_compiled,inner_context);
        inner_context.reset_registers(); //after the parameter list
        compound->code_gen(inner_compiled, inner_context);
        dst << "\taddiu	$sp,$sp,-" << inner_context.size()<<std::endl;
        dst<<inner_compiled.str();
        dst << "\taddiu	$sp,$sp," << inner_context.size()<<std::endl;

        dst<<"\t.set\tmacro"<<std::endl;
        dst<<"\t.set\treorder"<<std::endl;
        dst<<"\t.end\t"<<identifier<<std::endl;
    }
};

class VariableDeclaration
    : public Node
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
        dst<<id<<"=0"<<std::endl;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(id,4);
    }
};

class InitialisedVariableDeclaration
    : public Node
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
        dst<<std::endl;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(id,4);
    }
};

class InitialisedGlobalVariableDeclaration
    : public Node
{
private:
    std::string type, id;
    NodePtr value;
public:
    InitialisedGlobalVariableDeclaration(const std::string &_type, const std::string &_id, const NodePtr _value)
        : type(_type),
        id(_id),
        value(_value)
    {
        getGlobals()[id] = (NodePtr) this;
    }

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"=";
        value->translate(0, dst);
        dst<<std::endl;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(id, 4);
    }
};

class GlobalVariableDeclaration
    : public Node
{
private:
    std::string type, id;
public:
    GlobalVariableDeclaration(const std::string &_type, const std::string &_id)
        : type(_type),
        id(_id)
    {
        getGlobals()[id] = (NodePtr) this;
    }

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id<<"=0"<<std::endl;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.add_binding(id, 4);
    }
};



class ParameterList
    : public Node
{
protected:
    NodePtr list, paramter;
public:
    ParameterList (NodePtr _list, NodePtr _paramter)
            : list(_list),
            paramter(_paramter)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        list->translate(0,dst);
        dst << ", ";
        paramter->translate(0,dst);
    }
};

class Parameter
    : public Node
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
        context.add_binding(id,4);
        dst << "\tsw\t$a"<<context.next_register()<<","<<context.get_binding(id)<<"($fp)"<<std::endl;
    }
};

class ParameterList
    : public Node
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
        }
        dst << ", ";
        parameter->translate(0,dst);
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
        if (context.get_binding(param->Parameter::getId()) > 12) {
            throw std::runtime_error("More than 4 parameters not supported");
        }
    }
};

#endif
