#ifndef ast_statements_hpp
#define ast_statements_hpp

#include "ast_nodes.hpp"

#include <string>
#include <cmath>
#include <iostream>
#include <vector>

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
        dst <<"\taddiu\t$sp,$sp," << std::hex << std::to_string(context.size()) << std::endl;
        // dst<<"\tnop"<<std::endl;
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

class whileStatement : public Node
{
protected:
    NodePtr condition, sequence;
    std::string seqLabel, condLabel;
public:
    static int whileCounter;
    std::string makeWhileLabel()
    {
        return "$WL"+std::to_string(whileCounter++);
    }
    whileStatement(NodePtr _condition, NodePtr _sequence)
            : condition(_condition),
            sequence(_sequence)
        {
            condLabel = makeWhileLabel();
            seqLabel = makeWhileLabel();   
        }
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
        Context inner_context = new Context(context);
        dst<<"\tb\t"<<condLabel<<std::endl;
        dst<<"\tnop\n";
        dst<<seqLabel<<":"<<std::endl;
        sequence->code_gen(dst,inner_context);
        dst<<condLabel<<":"<<std::endl;
        condition->code_gen(dst,context);
        dst<<"\tbne\t$s"<<context.get_current_register()<<",$0,"<<seqLabel;  
        dst<<std::endl<<"\tnop"<<std::endl;      
        //throw std::runtime_error("whileStatement::code_gen is not implemented.");
    }
};

class ifStatement : public Node
{
protected:
    NodePtr condition, sequence;
    std::string endLabel;
public:
    static int ifCounter;
    ifStatement(NodePtr _condition, NodePtr _sequence)
        : condition(_condition),
        sequence(_sequence)
    {
        endLabel = makeIfLabel();
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"if (";
        condition->translate(0,dst);
        dst<< "):";
        sequence->translate(level, dst);
    }
    std::string makeIfLabel()
    {
        return "$IL"+std::to_string(ifCounter++);
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        condition->code_gen(dst,context);
        dst<<"\tbeq\t$s"<<context.get_current_register()<<",$0,"<<endLabel;
        dst<<std::endl<<"\tnop"<<std::endl;
        Context inner_context = new Context(context);
        sequence->code_gen(dst,inner_context);
        dst<<endLabel<<":"<<std::endl;
    }
    NodePtr get_sequence() const {
        return sequence;
    }
    NodePtr get_condition() const {
        return condition;
    }
    std::string get_endLabel() const {
        return endLabel;
    }
};

class ifElseStatement : public Node
{
protected:
    NodePtr condition, ifSequence, elseSequence;
    std::string elseLabel, endLabel;
public:
    static int ifElseCounter;
    ifElseStatement(NodePtr _condition, NodePtr _ifSequence, NodePtr _elseSequence)
            : condition(_condition),
            ifSequence(_ifSequence),
            elseSequence(_elseSequence)
        {
            elseLabel = makeIfElseLabel();
            endLabel = makeIfElseLabel();
        }

    std::string makeIfElseLabel()
    {
        return "$IEL"+std::to_string(ifElseCounter++);
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<"if (";
        condition->translate(0,dst);
        dst<< "):";
        ifSequence->translate(level, dst);
        dst<< std::endl << std::string(level,'\t') << "else :";
        elseSequence->translate(level, dst);
        dst<<std::endl;
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        condition->code_gen(dst,context);
        dst<<"\tbeq\t$s"<<context.get_current_register()<<",$0,"<<elseLabel;
        dst<<std::endl<<"\tnop"<<std::endl;
        Context if_context = new Context(context);
        ifSequence->code_gen(dst,if_context);
        dst<<"\tbeq\t$0,$0,"<<endLabel;
        dst<<std::endl<<"\tnop"<<std::endl;
        dst<<elseLabel<<":"<<std::endl;
        Context else_context = new Context(context);
        elseSequence->code_gen(dst,else_context);
        dst<<endLabel<<":"<<std::endl;
    }
    
};

class forLoop : public Node
{
protected:
    NodePtr initializer, condition, increment, sequence;
    std::string seqLabel, condLabel;
public:
    static int forCounter;
    forLoop(NodePtr _initializer, NodePtr _condition, NodePtr _increment, NodePtr _sequence)
            : initializer(_initializer),
            condition(_condition),
            increment(_increment),
            sequence(_sequence)
        {
            seqLabel = makeForLabel();
            condLabel = makeForLabel();
        }
    virtual void translate(int level, std::ostream &dst) const override
    {
       throw std::runtime_error("forLoop::translate is not implemented.");
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        Context cond_context = new Context(context);
        Context inner_context = new Context(context);
        initializer->code_gen(dst, cond_context);
        dst<<"\tb\t"<<condLabel<<"\n\tnop\n";
        dst<<seqLabel<<":\n";
        sequence->code_gen(dst, inner_context);
        increment->code_gen(dst, cond_context);
        dst<<condLabel<<":"<<std::endl;
        condition->code_gen(dst, cond_context);
        dst<<"\tbne\t$s"<<cond_context.get_current_register()<<",$0,"<<seqLabel<<std::endl;

    }
    std::string makeForLabel()
    {
        return "$FL"+std::to_string(forCounter++);
    }

    
};
   





#endif
