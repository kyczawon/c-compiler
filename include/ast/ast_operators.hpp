#ifndef ast_operators_hpp
#define ast_operators_hpp

#include "ast_nodes.hpp"

#include <string>
#include <cmath>
#include <iostream>

class Operator
    : public Node
{
protected:
    NodePtr left;
    NodePtr right;

    Operator(NodePtr _left, NodePtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual const char *getOpcode() const =0;
    virtual const char *getOp() const {
        throw std::runtime_error("getOp() not implemented");
    };

    NodePtr getLeft() const
    { return left; }

    NodePtr getRight() const
    { return right; }

    virtual void translate(int level, std::ostream &dst) const override
    {
        left->translate(level, dst);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->translate(0, dst);
    }

    virtual void code_gen(std::ostream &dst, Context &context) const
    {
        left->code_gen(dst,context);
        right->code_gen(dst,context);
        dst<<"\t"<<getOp()<<"\t$s"<<context.next_register()<<",$s"<<context.get_current_register()-1<<",$s"<<context.get_current_register()<<std::endl;
    }
};

class AssignmentOperator
    : public Node
{
protected:
    std::string id;
    NodePtr right;

    virtual const char *getOpcode() const
    { return "="; }
public:
    AssignmentOperator(std::string &_id, NodePtr _right)
        : id(_id),
        right(_right)
    {}
    
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<id;
        dst<<getOpcode();
        right->translate(0, dst);
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        right->code_gen(dst, context);
        dst << "\tsw\t$s"<<context.get_current_register()<<","<<context.get_binding(id)<<"($fp)"<<std::endl;
        //throw std::runtime_error("AssignmentOperator::code_gen is not implemented.");
    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "+"; }
    virtual const char *getOp() const override
    { return "addu"; }
public:
    AddOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}
};

class SubOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "-"; }
    virtual const char *getOp() const override
    { return "sub"; }
public:
    SubOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}
};


class MulOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "*"; }
    virtual const char *getOp() const override
    { return "mul"; }
public:
    MulOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}
};

class DivOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "/"; }
    virtual const char *getOp() const override
    { return "div"; }
public:
    DivOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        right->code_gen(dst,context);
        int denominator = context.get_current_register();
        dst<<"\t"<<getOp()<<"\t$0,$s"<<context.get_current_register()-1<<",$s"<<denominator<<std::endl;
        dst<<"\tteq\t$s"<<denominator<<",$0,7"<<std::endl; //trap with code 7 if denominator is eqaul to zero
        dst<<"\tmfhi\t$s"<<denominator<<std::endl;
        dst<<"\tmflo\t$s"<<denominator<<std::endl;
    }
};

class EqualsOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "=="; }
public:
    EqualsOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        right->code_gen(dst,context);
        int second = context.get_current_register();
        dst<<"\txor\t$s"<<second<<",$s"<<context.get_current_register()-1<<",$s"<<second<<std::endl;
        dst<<"\tsltu\t$s"<<second<<",$s"<<second<<",1"<<std::endl;
        dst<<"\tandi\t$s"<<second<<",$s"<<second<<",0x00ff"<<std::endl;
    }
};

class NotEqualsOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "!="; }
public:
    NotEqualsOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        right->code_gen(dst,context);
        int second = context.get_current_register();
        dst<<"\txor\t$s"<<second<<",$s"<<context.get_current_register()-1<<",$s"<<second<<std::endl;
        dst<<"\tsltu\t$s"<<second<<",$0"<<",$s"<<second<<std::endl;
        dst<<"\tandi\t$s"<<second<<",$s"<<second<<",0x00ff"<<std::endl;
    }
};

class GreaterOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">"; }
public:
    GreaterOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        right->code_gen(dst,context);
        int second = context.get_current_register();
        dst<<"\tslt\t$s"<<second<<",$s"<<second<<",$s"<<context.get_current_register()-1<<std::endl;
        dst<<"\tandi\t$s"<<second<<",$s"<<second<<",0x00ff"<<std::endl;
    }
};

class LessOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<"; }
public:
    LessOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        right->code_gen(dst,context);
        int second = context.get_current_register();
        dst<<"\tsltu\t$s"<<second<<",$s"<<context.get_current_register()-1<<",$s"<<second<<std::endl;
        dst<<"\tandi\t$s"<<second<<",$s"<<second<<",0x00ff"<<std::endl;
    }
};

class AndOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "and"; }
public:
    AndOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        std::string break1 = make_name("AND");
        dst<<"\tbeq\t$s"<<context.get_current_register()<<",$0,"<<break1<<std::endl;
        context.reset_registers(); //so that the next && can use the same register
        dst<<"\tnop"<<std::endl<<std::endl;
        
        right->code_gen(dst,context);
        dst<<"\tbeq\t$s"<<context.get_current_register()<<",$0,"<<break1<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        std::string break2 = make_name("ANDSKIP");
        dst<<"\tli\t$s"<<context.get_current_register()<<",1"<<std::endl;
        dst<<"\tb\t"<<break2<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        dst<<break1<<":"<<std::endl;
        dst<<"\tmove\t$s"<<context.get_current_register()<<",$0"<<std::endl;
        dst<<break2<<":"<<std::endl;
    }
};

class OrOperator
    : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "or"; }
public:
    OrOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        std::string break1 = make_name("OR");
        dst<<"\tbne\t$s"<<context.get_current_register()<<",$0,"<<break1<<std::endl;
        context.reset_registers(); //so that the next && can use the same register
        dst<<"\tnop"<<std::endl<<std::endl;
        
        std::string break2 = make_name("OR");
        right->code_gen(dst,context);
        dst<<"\tbeq\t$s"<<context.get_current_register()<<",$0,"<<break2<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        std::string break3 = make_name("ORSKIP");
        dst<<break1<<":"<<std::endl;
        dst<<"\tli\t$s"<<context.get_current_register()<<",1"<<std::endl;
        dst<<"\tb\t"<<break3<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        dst<<break2<<":"<<std::endl;
        dst<<"\tmove\t$s"<<context.get_current_register()<<",$0"<<std::endl;
        dst<<break3<<":"<<std::endl;
    }
};

#endif
