#ifndef ast_statements_hpp
#define ast_statements_hpp

#include "ast_nodes.hpp"

#include <string>
#include <cmath>
#include <iostream>
#include <vector>

static std::vector<std::string> condTracker;
static std::vector<std::string> endTracker;
static std::vector<NodePtr> switchTracker;

class ReturnStatement : public Node
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
        dst<<"\tlw\t$v0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tb\t"<<FnTracker[0];
        dst<<"\n\tnop\n";
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
        for (std::string element : getGlobals())
        {
            dst<<std::endl<<std::string(level+1,'\t')<<"global "<<element;
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
        // context.reset_mem();
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
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tbeq\t$s0,$0,"<<endLabel;
        dst<<std::endl<<"\tnop"<<std::endl;
        sequence->code_gen(dst,context);
        dst<<endLabel<<":"<<std::endl;
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
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tbeq\t$s0,$0,"<<elseLabel;
        dst<<std::endl<<"\tnop"<<std::endl;
        ifSequence->code_gen(dst,context);
        dst<<"\tbeq\t$0,$0,"<<endLabel;
        dst<<std::endl<<"\tnop"<<std::endl;
        dst<<elseLabel<<":"<<std::endl;
        elseSequence->code_gen(dst,context);
        dst<<endLabel<<":"<<std::endl;
    }
    
};

class whileStatement : public Node
{
protected:
    NodePtr condition, sequence;
    std::string seqLabel, condLabel, endLabel;
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
            seqLabel = makeWhileLabel();
            condLabel = makeWhileLabel();
            endLabel = makeWhileLabel();
            condTracker.push_back(condLabel);
            endTracker.push_back(endLabel);
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
        dst<<"\tb\t"<<condLabel<<std::endl;
        dst<<"\tnop\n";
        dst<<seqLabel<<":"<<std::endl;
        sequence->code_gen(dst,context);
        dst<<condLabel<<":"<<std::endl;
        condition->code_gen(dst,context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tbne\t$s0,$0,"<<seqLabel;  
        dst<<std::endl<<"\tnop"<<std::endl;  
        dst<<endLabel<<":"<<std::endl;
        condTracker.erase(condTracker.begin());
        endTracker.erase(endTracker.begin());
    }
};

class doWhileStatement : public Node
{
protected:
    NodePtr condition, sequence;
    std::string seqLabel, condLabel, endLabel;
public:
    static int doWhileCounter;
    std::string makeDoWhileLabel()
    {
        return "$DWL"+std::to_string(doWhileCounter++);
    }
    doWhileStatement(NodePtr _sequence, NodePtr _condition)
            : sequence(_sequence),
            condition(_condition)
        {
            seqLabel = makeDoWhileLabel();
            condLabel = makeDoWhileLabel();
            endLabel = makeDoWhileLabel();   
            condTracker.push_back(condLabel);
            endTracker.push_back(endLabel);
        }
    virtual void translate(int level, std::ostream &dst) const override
    {
       throw std::runtime_error("doWhileLoop::translate is not implemented.");

    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        dst<<seqLabel<<":"<<std::endl;
        sequence->code_gen(dst,context);
        dst<<condLabel<<":"<<std::endl;
        condition->code_gen(dst,context);
        dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
        dst<<"\tbne\t$s0,$0,"<<seqLabel;  
        dst<<std::endl<<"\tnop"<<std::endl; 
        dst<<endLabel<<":"<<std::endl;
        condTracker.erase(condTracker.begin());
        endTracker.erase(endTracker.begin());
    }
};

class forLoop : public Node
{
protected:
    NodePtr initializer, condition, increment, sequence;
    std::string seqLabel, incLabel, condLabel, endLabel;
public:
    static int forCounter;
    forLoop(NodePtr _initializer, NodePtr _condition, NodePtr _increment, NodePtr _sequence)
            : initializer(_initializer),
            condition(_condition),
            increment(_increment),
            sequence(_sequence)
        {
            seqLabel = makeForLabel();
            incLabel = makeForLabel();
            condLabel = makeForLabel();
            endLabel = makeForLabel();
            condTracker.push_back(incLabel);
            endTracker.push_back(endLabel);
        }
    virtual void translate(int level, std::ostream &dst) const override
    {
       throw std::runtime_error("forLoop::translate is not implemented.");
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if (initializer != nullptr) initializer->code_gen(dst, context); //initializer could be empty
        dst<<"\tb\t"<<condLabel<<"\n\tnop\n";
        dst<<seqLabel<<":\n";
        sequence->code_gen(dst, context);
        if (increment != nullptr) {
            dst<<incLabel<<":\n";
            increment->code_gen(dst, context); //increment could be empty
        }
        dst<<condLabel<<":"<<std::endl;
        if (condition != nullptr) { //condition could be empty
            condition->code_gen(dst, context);
            dst<<"\tlw\t$s0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
            dst<<"\tbne\t$s0,$0,"<<seqLabel<<std::endl;
        } else {
            dst<<"\tb\t"<<seqLabel<<std::endl;
        }
        dst<<endLabel<<":"<<std::endl;
        condTracker.erase(condTracker.begin());
        endTracker.erase(endTracker.begin());
    }
    std::string makeForLabel()
    {
        return "$FL"+std::to_string(forCounter++);
    }

};
   
class continueStatement : public Node 
{
public:
    continueStatement()
    {
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
       throw std::runtime_error("continueStatement::translate is not implemented.");
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        std::string label = condTracker[0];
        dst<<"\tb\t"<<label;
        dst<<"\n\tnop\n";
    }

};

class breakStatement : public Node 
{
public:
    breakStatement(){
        
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
       throw std::runtime_error("breakStatement::translate is not implemented.");
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        std::string label = endTracker[0];
        dst<<"\tb\t"<<label;
        dst<<"\n\tnop\n";
    }


};

class caseStatement : public Node
{
protected:
    NodePtr condition, sequence;
    std::string endLabel;
public:
    static int caseCounter;
    caseStatement(NodePtr _condition, NodePtr _sequence)
        : condition(_condition),
        sequence(_sequence)
    {
        endLabel = makeCaseLabel();
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("caseStatement::translate is not implemented.");
    }
    std::string makeCaseLabel()
    {
        return "$CL"+std::to_string(caseCounter++);
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        if(condition!=NULL){
            switchTracker[0]->code_gen(dst, context);
            dst<<"\tlw\t$t0,"<<context.get_current_mem()<<"($fp)"<<std::endl;
            condition->code_gen(dst,context);
            dst<<"\tlw\t$s1,"<<context.get_current_mem()<<"($fp)"<<std::endl;
            dst<<"\tbne\t$s1,$t0,"<<endLabel<<std::endl;
            dst<<"\tnop"<<std::endl;
        }
        sequence->code_gen(dst,context);
        std::string label = endTracker[0];
        dst<<"\tb\t"<<label;
        dst<<"\n\tnop\n";
        dst<<endLabel<<":"<<std::endl;
        
    }
};

class switchStatement : public Node
{
protected:
    NodePtr condition, sequence;
    std::string endLabel;
public:
    static int switchCounter;
    switchStatement(NodePtr _condition, NodePtr _sequence)
        : condition(_condition),
        sequence(_sequence)
    {
        endLabel = makeSwitchLabel();
        switchTracker.push_back(condition);
        endTracker.push_back(endLabel);
    }
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("switchStatement::translate is not implemented.");
    }
    std::string makeSwitchLabel()
    {
        return "$SL"+std::to_string(switchCounter++);
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        sequence->code_gen(dst,context);
        dst<<endLabel<<":"<<std::endl;
        switchTracker.erase(switchTracker.begin());
        endTracker.erase(endTracker.begin());        
    }
};

class gotoStatement : public Node
{
protected:
    std::string label;
public:
    gotoStatement(std::string _label)
            : label(_label)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("gotoStatement::translate is not implemented.");
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        dst<<"\tb\t"<<label<<"\n\tnop\n";
    }
};

class Label : public Node
{
protected:
    std::string label;
public:
    Label(std::string _label)
            : label(_label)
        {}
    virtual void translate(int level, std::ostream &dst) const override
    {
        throw std::runtime_error("gotoStatement::translate is not implemented.");
    }
    virtual void code_gen(std::ostream &dst, Context &context) const override
    {
        dst<<label<<":\n";
    }
};



#endif