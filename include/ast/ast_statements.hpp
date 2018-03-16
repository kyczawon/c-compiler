#ifndef ast_statements_hpp
#define ast_statements_hpp

#include "ast_nodes.hpp"

#include <string>
#include <cmath>
#include <iostream>

class ReturnStatement : public Statement2
{
protected:
    NodePtr expr;
public:
    ReturnStatement(NodePtr _expr)
            : expr(_expr)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"return ";
        expr->translate(0,dst);
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        expr->code_gen(dst,context);
        dst<<"\taddi\t$v0,$s"<<context.get_current_register()<<","<<std::hex<<0<<std::endl;
        dst<<"\tj\t$31"<<std::endl;
        context.reset_registers();	
    }
};

class CompoundStatement : public Node
{
protected:
    NodePtr seq;
public:
    CompoundStatement(NodePtr _seq)
            : seq(_seq)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        for (std::pair<std::string, NodePtr> element : getGlobals())
        {
            dst<<std::endl<<std::string(level+1,'\t')<<"global "<<element.first;
        }
        if (seq != nullptr) { //compound statement could be empty
            seq->translate(level+1,dst);
        }
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (seq != nullptr) { //compound statement could be empty
            seq->code_gen(dst,context);
        }
    }
};

class Sequence : public Node
{
protected:
    NodePtr sequence_nest, next;
public:
    Sequence(NodePtr _sequence_nest, NodePtr _next)
            : sequence_nest(_sequence_nest),
            next(_next)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        if (sequence_nest != nullptr) { //sequence could be only 1 statement
            sequence_nest->translate(level,dst);
        }
        dst<<std::endl<<std::string(level,'\t');
        next->translate(level,dst);
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (sequence_nest != nullptr) { //sequence could be only 1 statement
            sequence_nest->code_gen(dst,context);
        }
        next->code_gen(dst,context);
    }
};

class Statement : public Node
{
protected:
    NodePtr expr;
public:
    Statement(NodePtr _expr)
            : expr(_expr)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        expr->translate(level,dst);
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        expr->code_gen(dst,context);
        context.reset_registers();
    }
};

class ifStatement : public Node
{
protected:
    NodePtr condition, sequence;
public:
    ifStatement(NodePtr _condition, NodePtr _sequence)
            : condition(_condition),
            sequence(_sequence)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"if (";
        condition->translate(0,dst);
        dst<< "):"; //<<std::endl<< std::string(level+1,'\t');
        sequence->translate(level, dst);
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("ifStatement::code_gen is not implemented.");
    }
};

class whileStatement : public Node
{
protected:
    NodePtr condition, sequence;
public:
    whileStatement(NodePtr _condition, NodePtr _sequence)
            : condition(_condition),
            sequence(_sequence)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"while (";
        condition->translate(0,dst);
        dst<< "):";
        sequence->translate(level, dst);
        dst<<std::endl;
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("whileStatement::code_gen is not implemented.");
    }
};

class elseStatement : public Node
{
protected:
    NodePtr sequence;
public:
    elseStatement(NodePtr _sequence)
            : sequence(_sequence)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<< "else :";
        sequence->translate(level, dst);
        dst<<std::endl;
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        throw std::runtime_error("elseStatement::code_gen is not implemented.");
    }
};


#endif
