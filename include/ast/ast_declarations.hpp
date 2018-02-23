#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>

class Function
    : public Expression
{
protected:
    ExpressionPtr sequence;
    std::string type, identifier;
public:
    Function(std::string &_type, std::string &_identifier, ExpressionPtr _sequence)
        : type(_type)
        , identifier(_identifier)
        , sequence(_sequence)
    {
        stack[identifier] = (ExpressionPtr) this;
    }
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<"def "<<identifier<<"():"<<std::endl;
        sequence->print(level+1, dst);
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        // NOTE : This should be implemented by the inheriting function nodes, e.g. LogFunction
        throw std::runtime_error("FunctionOperator::evaluate is not implemented.");
    }
};

class FunctionCall
    : public Expression
{
protected:
    std::string identifier;
public:
    FunctionCall(std::string &_identifier)
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

class VariableDeclaration
    : public Expression
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

    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<id<<"=0";
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        return bindings.at(id);
    }
};

#endif