#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>
#include <unordered_map>

#include <memory>

class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
protected:
    std::unordered_map<std::string,ExpressionPtr> stack;
public:
    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print(int level, std::ostream &dst) const =0;

    //! Evaluate the tree using the given mapping of variables to numbers
    virtual double evaluate(
        const std::map<std::string,double> &bindings
    ) const
    { throw std::runtime_error("Not implemented."); }
};


#endif
