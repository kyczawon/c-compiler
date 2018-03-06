#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>

class Variable
    : public Node
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<id;
    }

    virtual void code_gen(std::ostream &dst) const override
    {

    }
};

class Number
    : public Node
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual void code_gen(std::ostream &dst) const override
    {
    }
};

class NegativeNumber
    : public Node
{
private:
    double value;
public:
    NegativeNumber(double _value)
        : value(-1*_value)
    {}

    double getValue() const
    { return value; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual void code_gen(std::ostream &dst) const override
    {
    }
};

#endif
