#ifndef ast_hpp
#define ast_hpp

#include "ast/ast_nodes.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_declarations.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_expressions.hpp"

extern const Node *parseAST();
extern FILE * yyin;
extern FILE * yyout;

#endif
