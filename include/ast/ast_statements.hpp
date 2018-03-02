#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <cmath>
#include <iostream>

class ReturnStatement
    : public Node
{
protected:
    NodePtr expr;
public:
    ReturnStatement(NodePtr _expr)
            : expr(_expr)
        {}
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<"return ";
        expr->print(0,dst);
        dst<<std::endl;
    }
};

class Sequence
    : public Node
{
protected:
    NodePtr sequence_nest, next;
public:
    Sequence(NodePtr _sequence_nest, NodePtr _next)
            : sequence_nest(_sequence_nest),
            next(_next)
        {}
    virtual void print(int level, std::ostream &dst) const override
    {
        sequence_nest->print(level,dst);
        next->print(level,dst);
    }
};

class Statement
    : public Node
{
protected:
    NodePtr statement;
public:
    Statement(NodePtr _statement)
            : statement(_statement)
        {}
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t');
        statement->print(level,dst);
        dst<<std::endl;
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
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t') << "if (";
        condition->print(0,dst);
        dst<< "):" << std::endl;
        sequence->print(level+1, dst);
        dst<<std::endl;
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
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t') << "while (";
        condition->print(0,dst);
        dst<< "):" << std::endl;
        sequence->print(level+1, dst);
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
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t') << "else :" << std::endl;
        sequence->print(level+1, dst);
        dst<<std::endl;
    }
};


#endif
