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
};

class ifStatement
    : public Node
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
        dst<< "):";
        sequence->translate(level, dst);
    }
};

class whileStatement
    : public Node
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
};

class elseStatement
    : public Node
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
};


#endif
