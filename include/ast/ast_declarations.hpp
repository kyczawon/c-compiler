#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_nodes.hpp"

#include <cmath>

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
        getStack()[identifier] = (NodePtr) this;
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"def "<<identifier<<"(";
        if (parameter_list != nullptr) parameter_list->translate(0, dst);
        dst<<"):";
        compound->translate(level, dst);
    }

    virtual void code_gen(std::ostream &dst) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::code_gen is not implemented.");
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

    virtual void code_gen(std::ostream &dst) const override
    {
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

    virtual void code_gen(std::ostream &dst) const override
    {
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

    virtual void code_gen(std::ostream &dst) const override
    {
    }
};

#endif
