#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<id;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        return bindings.at(id);
    }
};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        return value;
    }
};

class NegativeNumber
    : public Expression
{
private:
    double value;
public:
    NegativeNumber(double _value)
        : value(-1*_value)
    {}

    double getValue() const
    { return value; }

    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const override
    {
        return value;
    }
};

#endif
