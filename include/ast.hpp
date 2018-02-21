#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_expression.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_statements.hpp"


extern const Expression *parseAST();
extern FILE * yyin;
extern FILE * yyout;

#endif
