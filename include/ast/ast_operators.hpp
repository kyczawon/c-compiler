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
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\t"<<getOp()<<"\t$s2,$s1,$s0"<<std::endl;
        dst<<"\tsw\t$s2,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\t"<<getOp()<<"\t$0,$s1,$s0"<<std::endl;
        dst<<"\tteq\t$s0,$0,7"<<std::endl; //trap with code 7 if denominator is eqaul to zero
        dst<<"\tmflo\t$s0"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class ModOperator : public Operator
{
protected:
    virtual const char *getOpcode() const override
    { return "%"; }
public:
    ModOperator(NodePtr _left, NodePtr _right)
        : Operator(_left, _right)
    {}
    virtual const char *getOp() const override
    { return "div"; }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        left->code_gen(dst,context);
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\t"<<getOp()<<"\t$0,$s1,$s0"<<std::endl;
        dst<<"\tteq\t$s0,$0,7"<<std::endl; //trap with code 7 if denominator is eqaul to zero
        dst<<"\tmfhi\t$s0"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\txor\t$s0,$s1,$s0"<<std::endl;
        dst<<"\tsltu\t$s0,$s0,1"<<std::endl;
        dst<<"\tandi\t$s0,$s0,0x00ff"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\txor\t$s0,$s1,$s0"<<std::endl;
        dst<<"\tsltu\t$s0,$0,$s0"<<std::endl;
        dst<<"\tandi\t$s0,$s0,0x00ff"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tslt\t$s0,$s0,$s1"<<std::endl;
        dst<<"\tandi\t$s0,$s0,0x00ff"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        left->code_gen(dst,context);
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tslt\t$s0,$s1,$s0"<<std::endl;
        dst<<"\txori\t$s0,$s0,1";
        dst<<"\n\tandi\t$s0,$s0,0x00ff"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tsltu\t$s0,$s1,$s0"<<std::endl;
        dst<<"\tandi\t$s0,$s0,0x00ff"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        left->code_gen(dst,context);
        int res = context.get_current_mem();
        right->code_gen(dst,context);
        dst<<"\tlw\t$s1,"<<res<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tsltu\t$s0,$s0,$s1"<<std::endl;
        dst<<"\txori\t$s0,$s0,"<<1;
        dst<<"\n\tandi\t$s0,$s0,0x00ff"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        std::string break1 = make_name("AND");
        dst<<"\tbeq\t$s0,$0,"<<break1<<std::endl;
        context.reset_mem(); //so that the next && can use the same memory
        dst<<"\tnop"<<std::endl<<std::endl;
        
        right->code_gen(dst,context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tbeq\t$s0,$0,"<<break1<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        std::string break2 = make_name("ANDSKIP");
        dst<<"\tli\t$s0,1"<<std::endl;
        dst<<"\tb\t"<<break2<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        dst<<break1<<":"<<std::endl;
        dst<<"\tmove\t$s0,$0"<<std::endl;
        dst<<break2<<":"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        std::string break1 = make_name("OR");
        dst<<"\tbne\t$s0,$0,"<<break1<<std::endl;
        context.reset_mem(); //so that the next || can use the same memory
        dst<<"\tnop"<<std::endl<<std::endl;
        
        std::string break2 = make_name("OR");
        right->code_gen(dst,context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tbeq\t$s0,$0,"<<break2<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        std::string break3 = make_name("ORSKIP");
        dst<<break1<<":"<<std::endl;
        dst<<"\tli\t$s0,1"<<std::endl;
        dst<<"\tb\t"<<break3<<std::endl;
        dst<<"\tnop"<<std::endl<<std::endl;

        dst<<break2<<":"<<std::endl;
        dst<<"\tmove\t$s0,$0"<<std::endl;
        dst<<break3<<":"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class ConditionalOperator : public Node
{
private:
    NodePtr cond, if_exp, else_exp;
    std::string elseLabel, endLabel;
public:
    ConditionalOperator(NodePtr _cond, NodePtr _if_exp, NodePtr _else_exp)
        : cond(_cond),
        if_exp(_if_exp),
        else_exp(_else_exp)
    {
        elseLabel = makeIfElseLabel();
        endLabel = makeIfElseLabel();
    }

    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("ConditionalOperator::translate not implemented.");
    }
    
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        cond->code_gen(dst,context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tbeq\t$s0,$0,"<<elseLabel;
        dst<<std::endl<<"\tnop"<<std::endl;
        if_exp->code_gen(dst,context);
        dst<<"\tlw\t$s4,"<<context.get_current_mem()<<"($fp)\n";
        dst<<"\tbeq\t$0,$0,"<<endLabel;
        dst<<"\n\tnop"<<std::endl;
        dst<<elseLabel<<":"<<std::endl;
        else_exp->code_gen(dst,context);
        dst<<"\tlw\t$s4,"<<context.get_current_mem()<<"($fp)\n";
        dst<<endLabel<<":"<<std::endl;
        dst<<"\tsw\t$s4,"<<context.next_mem()<<"($fp)\n";
    }

    std::string makeIfElseLabel()
    {
        return "$IEL"+std::to_string(ifElseStatement::ifElseCounter++);
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
        left->code_gen(dst, context);
        right->code_gen(dst, context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s1,"<<context.get_current_mem()-4<<"($fp)"<<std::endl;
        dst<<"\tor\t$s0,$s1,$s0\n";
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        left->code_gen(dst, context);
        right->code_gen(dst, context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s1,"<<context.get_current_mem()-4<<"($fp)"<<std::endl;
        dst<<"\tand\t$s0,$s1,$s0\n";
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        left->code_gen(dst, context);
        right->code_gen(dst, context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s1,"<<context.get_current_mem()-4<<"($fp)"<<std::endl;
        dst<<"\txor\t$s0,$s1,$s0\n";
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        left->code_gen(dst, context);
        right->code_gen(dst, context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s1,"<<context.get_current_mem()-4<<"($fp)"<<std::endl;
        dst<<"\tsllv\t$s0,$s1,$s0\n";
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        left->code_gen(dst, context);
        right->code_gen(dst, context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tlw\t$s1,"<<context.get_current_mem()-4<<"($fp)"<<std::endl;
        dst<<"\tsra\t$s0,$s1,$s0\n";
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

//needs  implementing
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

//needs  implementing
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

//needs  implementing
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
        expr_list->code_gen(dst, context);
        dst<<"\tlw\t$s0"<<","<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tli\t$s1,"<<context.get_size(context.get_arr_type(id))<<std::endl;
        dst<<"\tmul\t$s0,$s1,$s0"<<std::endl;
        dst<<"\tli\t$s1,"<<context.get_binding(id)<<std::endl;
        dst<<"\taddu\t$t0,$s0,$s1"<<std::endl;
        dst<<"\taddu\t$t0,$fp,$t0"<<std::endl;
        dst<<"\tlw\t$s0,($t0)"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        context.load_binding(id, "s0", dst,0);
        dst<<"\taddiu\t$s1,$s0,1"<<std::endl;
        context.set_binding(id, "s1", dst,0);
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;

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
        context.load_binding(id, "s0", dst,0);
        dst<<"\taddiu\t$s0,$s0,1"<<std::endl;
        context.set_binding(id, "s0", dst,0);
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        context.load_binding(id, "s0", dst,0);
        dst<<"\taddiu\t$s1,$s0,-1"<<std::endl;
        context.set_binding(id, "s1", dst,0);
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;

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
        context.load_binding(id, "s0", dst,0);
        dst<<"\taddiu\t$s0,$s0,-1"<<std::endl;
        context.set_binding(id, "s0", dst,0);
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

//needs  implementing
class UnaryOperator : public Node
{
private:
    int hashit (std::string const& inString) const {
        if (inString == "!") return 1;
        if (inString == "~") return 2;
        if (inString == "+") return 3;
        if (inString == "-") return 4;
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
        right->code_gen(dst, context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        switch(hashit(unary_operator))
        {
            case 1: //not
                {
                    dst<<"\tsltu\t$s0,$s0,1"<<std::endl;
                    dst<<"\tandi\t$s0,$s0,0x00ff"<<std::endl;
                    dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
                    break;
                }
            case 5:
                {
                    break;
                }
            case 6:
                {
                    dst<<"\tsubu\t$s0,$0,$s0\n";
                    dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
                    break;
                }
            default:
                throw std::runtime_error("UnaryOperator::code_gen the operator '" + unary_operator + "' is not implemented.");
        }
    }
};

class IndirectionOperator : public Node
{
protected:
    std::string id;
public:
    IndirectionOperator(const std::string &_id)
        : id(_id)
    {}
    
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("IndirectionOperator::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        context.load_binding(id,"s0",dst,0);
        dst<<"\tlw\t$s1,($s0)"<<std::endl;
        dst<<"\tsw\t$s1,"<<context.next_mem()<<"($fp)"<<std::endl;
    }
};

class AddressOperator : public Node
{
protected:
    std::string id;
public:
    AddressOperator(std::string &_id)
        : id(_id)
    {}
    
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("AddressOperator::translate is not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        dst<<"\taddu\t$s0,$0,$0"<<std::endl;
        dst<<"\tli\t$s0,"<<context.get_binding(id)<<std::endl;
        dst<<"\taddu\t$s0,$s0,$fp"<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        int size = context.get_size_bind(id);
        dst<<"\tli\t$s0,"<<size<<std::endl;
        dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
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
        int size = context.get_size(type);
        if (size != 0) {
            dst<<"\tli\t$s0,"<<size<<std::endl;
            dst<<"\tsw\t$s0,"<<context.next_mem()<<"($fp)"<<std::endl;
        } else {
            throw std::runtime_error("SizeOfType::translate not implemented.");
        }
    }
};

//needs  implementing
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

class AssignmentOperator : public Node
{
private:
    int hashit (std::string const& inString) const {
        if (inString == "=") return 1;
        if (inString == "+=") return 2;
        if (inString == "-=") return 3;
        if (inString == "*=") return 4;
        if (inString == "/=") return 5;
        if (inString == "%=") return 6;
        if (inString == "&=") return 7;
        if (inString == "^=") return 8;
        if (inString == "|=") return 9;
        if (inString == "<<=") return 10;
        if (inString == ">>=") return 11;
        else return 0;
    }
protected:
    std::string id, assign_operator;
    NodePtr offset, right;

    virtual const std::string getOpcode() const
    { return assign_operator; }
public:
    AssignmentOperator(std::string &_id, NodePtr _offset, std::string &_assign_operator, NodePtr _right)
        : id(_id),
        offset(_offset),
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
                {
                right->code_gen(dst, context);
                break;
                }
            case 2: //plus equals
                {
                AddOperator *addition = new AddOperator( new Variable(id), right);
                addition->code_gen(dst, context);
                break;
                }
            case 3: //minus equals
                {
                SubOperator *substraction = new SubOperator( new Variable(id), right);
                substraction->code_gen(dst, context);
                break;
                }
            case 4: //times equals
                {
                MulOperator *mult = new MulOperator( new Variable(id), right);
                mult->code_gen(dst, context);
                break;
                }
            case 5: //divide equals
                {
                DivOperator *division = new DivOperator( new Variable(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 6: //mod equals
                {
                ModOperator *division = new ModOperator( new Variable(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 7: //and equals
                {
                BitwiseAndOperator *division = new BitwiseAndOperator( new Variable(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 8: //xor equals
                {
                BitwiseXorOperator *division = new BitwiseXorOperator( new Variable(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 9: //or equals
                {
                BitwiseOrOperator *division = new BitwiseOrOperator( new Variable(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 10: //leftshift equals
                {
                LeftShiftOperator *division = new LeftShiftOperator( new Variable(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 11: //rightshift equals
                {
                RightShiftOperator *division = new RightShiftOperator( new Variable(id), right);
                division->code_gen(dst, context);
                break;
                }
            default:
                throw std::runtime_error("AssignmentOperator::code_gen is not implemented.");
        }
        dst<<"\tlw\t$s3,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        if (offset != nullptr) {//it is an array
            offset->code_gen(dst, context);
            dst<<"\tlw\t$s1,"<<context.get_current_mem()<<"($fp)"<<std::endl;
            dst<<"\tli\t$s2,"<<context.get_size(context.get_arr_type(id))<<std::endl;
            dst<<"\tmul\t$s1,$s1,$s2"<<std::endl;
            context.load_array(id, "t0",dst);
            dst<<"\tsw\t$s3,($t0)"<<std::endl;
        } else context.set_binding(id, "s3", dst, 0);
    }
};


class PointerAssignment : public Node
{
private:
    int hashit (std::string const& inString) const {
        if (inString == "=") return 1;
        if (inString == "+=") return 2;
        if (inString == "-=") return 3;
        if (inString == "*=") return 4;
        if (inString == "/=") return 5;
        if (inString == "%=") return 6;
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
    PointerAssignment(std::string &_id, std::string &_assign_operator, NodePtr _right)
        : id(_id),
        assign_operator(_assign_operator),
        right(_right)
    {}
    
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("PointerAssignment::translate not implemented.");
    }

    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        switch(hashit(assign_operator))
        {
            case 1: //equals
                {
                right->code_gen(dst, context);
                break;
                }
            case 2: //plus equals
                {
                AddOperator *addition = new AddOperator( new IndirectionOperator(id), right);
                addition->code_gen(dst, context);
                break;
                }
            case 3: //minus equals
                {
                SubOperator *substraction = new SubOperator( new IndirectionOperator(id), right);
                substraction->code_gen(dst, context);
                break;
                }
            case 4: //times equals
                {
                MulOperator *mult = new MulOperator( new IndirectionOperator(id), right);
                mult->code_gen(dst, context);
                break;
                }
            case 5: //divide equals
                {
                DivOperator *division = new DivOperator( new IndirectionOperator(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 6: //mod equals
                {
                ModOperator *division = new ModOperator( new IndirectionOperator(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 7: //and equals
                {
                BitwiseAndOperator *division = new BitwiseAndOperator( new IndirectionOperator(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 8: //xor equals
                {
                BitwiseXorOperator *division = new BitwiseXorOperator( new IndirectionOperator(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 9: //or equals
                {
                BitwiseOrOperator *division = new BitwiseOrOperator( new IndirectionOperator(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 10: //leftshift equals
                {
                LeftShiftOperator *division = new LeftShiftOperator( new IndirectionOperator(id), right);
                division->code_gen(dst, context);
                break;
                }
            case 11: //rightshift equals
                {
                RightShiftOperator *division = new RightShiftOperator( new IndirectionOperator(id), right);
                division->code_gen(dst, context);
                break;
                }
            default:
                throw std::runtime_error("AssignmentOperator::code_gen is not implemented.");
        }
        dst<<"\tlw\t$s1,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        context.load_binding(id,"s0",dst, 0);
        dst<<"\tsw\t$s1,($s0)"<<std::endl;
    }
};

#endif