#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include "ast_nodes.hpp"

#include <string>
#include <iostream>

class Variable : public Node
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

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.load_binding(id,"s0",dst,0);
        dst << "\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class Number : public Node
{
private:
    int value;
public:
    Number(int _value)
        : value(_value)
    {}

    int getValue() const
    { return value; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        dst<<"\tli\t$s0,"<<value<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class Character : public Node
{
private:
    std::string value;
public:
    Character(const std::string &_value)
        : value(_value)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        int i = value[1];
        dst<<"\tli\t$s0,"<<i<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class Str : public Node
{
private:
    std::string value;
public:
    Str(const std::string &_value)
        : value(_value)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        getRData() = true;
        *(std::string *)&value = value.substr(0, value.size()-1);
        std::string label = make_name("LC");
        getGlobalDec()<<label<<":"<<std::endl<<"\t.ascii\t"<<value<<"\\000\""<<std::endl;
        dst<<"\tlui\t$s0,%hi("<<label<<")"<<std::endl;
        dst<<"\taddiu\t$s0,$s0,%lo("<<label<<")"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class NegativeNumber : public Node
{
private:
    int value;
public:
    NegativeNumber(int _value)
        : value(-1*_value)
    {}

    int getValue() const
    { return value; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<value;
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        dst << "\tli\t$s0,"<<value<<std::endl;
        dst << "\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

#endif
