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
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t')<<"return ";
        expr->translate(0,dst);
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
    virtual void translate(int level, std::ostream &dst) const override
    {
        sequence_nest->translate(level,dst);
        next->translate(level,dst);
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
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t');
        statement->translate(level,dst);
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
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t') << "if (";
        condition->translate(0,dst);
        dst<< "):" << std::endl;
        sequence->translate(level+1, dst);
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
    virtual void translate(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t') << "while (";
        condition->translate(0,dst);
        dst<< "):" << std::endl;
        sequence->translate(level+1, dst);
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
        dst<<std::string(level,'\t') << "else :" << std::endl;
        sequence->translate(level+1, dst);
        dst<<std::endl;
    }
};


#endif
