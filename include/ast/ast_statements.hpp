#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <cmath>
#include <iostream>

class ReturnStatement
    : public Expression
{
protected:
    ExpressionPtr expr;
public:
    ReturnStatement(ExpressionPtr _expr)
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
    : public Expression
{
protected:
    ExpressionPtr sequence_nest, next;
public:
    Sequence(ExpressionPtr _sequence_nest, ExpressionPtr _next)
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
    : public Expression
{
protected:
    ExpressionPtr statement;
public:
    Statement(ExpressionPtr _statement)
            : statement(_statement)
        {}
    virtual void print(int level, std::ostream &dst) const override
    {
        dst<<std::string(level,'\t');
        statement->print(level,dst);
        dst<<std::endl;
    }
};

#endif
