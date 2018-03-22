#ifndef ast_operators_hpp
#define ast_operators_hpp

#include "ast_nodes.hpp"

#include <string>
#include <cmath>
#include <iostream>

class Operator : public Node
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

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        right->code_gen(dst,context);
        dst<<"\t"<<getOp()<<"\t$s"<<context.next_register()<<",$s"<<context.get_current_register()-1<<",$s"<<context.get_current_register()<<std::endl;
    }
};

class AssignmentOperator : public Node
{
private:
    int hashit (std::string const& inString) const {
        if (inString == "=") return 1;
        if (inString == "+=") return 2;
        if (inString == "-=") return 3;
        if (inString == "*=") return 4;
        if (inString == "/=") return 5;
        if (inString == "%%=") return 6;
        if (inString == "&=") return 7;
        if (inString == "^=") return 8;
        if (inString == "|=") return 9;
        if (inString == "<<=") return 10;
        if (inString == ">>=") return 11;
        else return 0;
    }
protected:
    std::string id, assign_operator;
    NodePtr right;

    virtual const std::string getOpcode() const
    { return assign_operator; }
public:
    AssignmentOperator(std::string &_id, std::string &_assign_operator, NodePtr _right)
        : id(_id),
        assign_operator(_assign_operator),
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
        switch(hashit(assign_operator))
        {
            case 1: //equals
                right->code_gen(dst, context);
                dst << "\tsw\t$s"<<context.get_current_register()<<","<<context.get_binding(id)<<"($fp)"<<std::endl;
                break;
            default:
                throw std::runtime_error("AssignmentOperator::code_gen is not implemented.");
        }
    }
};

class AddOperator : public Operator
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

class SubOperator : public Operator
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


class MulOperator : public Operator
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

class DivOperator : public Operator
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

class EqualsOperator : public Operator
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

class NotEqualsOperator : public Operator
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

class GreaterOperator : public Operator
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

class GreaterEqualOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">="; }
public:
    GreaterEqualOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("LessEqualOperator::code_gen not implemented.");
    }
};

class LessOperator : public Operator
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

class LessEqualOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<="; }
public:
    LessEqualOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("LessEqualOperator::code_gen not implemented.");
    }
};

class AndOperator : public Operator
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

class OrOperator : public Operator
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

class ConditionalOperator : public Node
{
private:
    NodePtr cond, if_exp, else_exp;
public:
    ConditionalOperator(NodePtr _cond, NodePtr _if_exp, NodePtr _else_exp)
        : cond(_cond),
        if_exp(_if_exp),
        else_exp(_else_exp)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("ConditionalOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("ConditionalOperator::code_gen not implemented.");
    }
};

class BitwiseOrOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "|"; }
public:
    BitwiseOrOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("BitwiseOrOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("BitwiseOrOperator::code_gen not implemented.");
    }
};

class BitwiseAndOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "&"; }
public:
    BitwiseAndOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("BitwiseAndOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("BitwiseAndOperator::code_gen not implemented.");
    }
};

class BitwiseXorOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "^"; }
public:
    BitwiseXorOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("BitwiseXorOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("BitwiseXorOperator::code_gen not implemented.");
    }
};

class LeftShiftOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "<<"; }
public:
    LeftShiftOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("LeftShiftOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("LeftShiftOperator::code_gen not implemented.");
    }
};

class RightShiftOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return ">>"; }
public:
    RightShiftOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("RightShiftOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("RightShiftOperator::code_gen not implemented.");
    }
};

class Member : public Node
{
private:
    std::string id, member;
public:
    Member(std::string _id, std::string _member)
        : id(_id),
        member(_member)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("Member::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("Member::code_gen not implemented.");
    }
};

class MemberPtr : public Node
{
private:
    std::string id, member;
public:
    MemberPtr(std::string _id, std::string _member)
        : id(_id),
        member(_member)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("MemberPtr::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("MemberPtr::code_gen not implemented.");
    }
};


class Array : public Node
{
private:
    std::string id;
    NodePtr expr_list;
public:
    Array(std::string _id, NodePtr _expr_list)
        : id(_id),
        expr_list(_expr_list)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("Array::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("Array::code_gen not implemented.");
    }
};

class PostIncrement : public Node
{
private:
    std::string id;
public:
    PostIncrement(std::string _id)
        : id(_id)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("PostIncrement::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("PostIncrement::code_gen not implemented.");
    }
};

class PreIncrement : public Node
{
private:
    std::string id;
public:
    PreIncrement(std::string _id)
        : id(_id)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("PreIncrement::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("PreIncrement::code_gen not implemented.");
    }
};

class PostDecrement : public Node
{
private:
    std::string id;
public:
    PostDecrement(std::string _id)
        : id(_id)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("PostDecrement::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("PostDecrement::code_gen not implemented.");
    }
};

class PreDecrement : public Node
{
private:
    std::string id;
public:
    PreDecrement(std::string _id)
        : id(_id)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("PreDecrement::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("PreDecrement::code_gen not implemented.");
    }
};

class UnaryOperator : public Node
{
private:
    int hashit (std::string const& inString) const {
        if (inString == "*") return 1;
        if (inString == "&") return 2;
        if (inString == "!") return 3;
        if (inString == "~") return 4;
        if (inString == "+") return 5;
        if (inString == "-") return 6;
        else return 0;
    }
protected:
    std::string unary_operator;
    NodePtr right;

    virtual const std::string getOpcode() const
    { return unary_operator; }
public:
    UnaryOperator(std::string &_unary_operator, NodePtr _right)
        : unary_operator(_unary_operator),
        right(_right)
    {}
    
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("UnaryOperator::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        switch(hashit(unary_operator))
        {
            default:
                throw std::runtime_error("UnaryOperator::code_gen is not implemented.");
        }
    }
};

class SizeOf : public Node
{
private:
    std::string id;
public:
    SizeOf(std::string _id)
        : id(_id)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("SizeOf::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("SizeOf::code_gen not implemented.");
    }
};

class SizeOfType : public Node
{
private:
    std::string type;
public:
    SizeOfType(std::string _type)
        : type(_type)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("SizeOfType::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("SizeOfType::code_gen not implemented.");
    }
};

class CastOperator : public Node
{
private:
    std::string type;
    NodePtr cast_expr;
public:
    CastOperator(std::string _type, NodePtr _cast_expr)
        : type(_type),
        cast_expr(_cast_expr)
    {}

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("CastOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("CastOperator::code_gen not implemented.");
    }
};

#endif