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

#endif
