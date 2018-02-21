%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Expression *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Expression *expr;
  double number;
  std::string *string;
}

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_EXPONENT
%token T_LBRACKET T_RBRACKET T_LCURLY T_RCURLY T_SEMI T_EQUALS
%token T_INT
%token T_RETURN
%token T_NUMBER T_STRING

%type <expr> EXPR FACTOR STATEMENT VARIABLE FUNCTION COMPOUND_STATEMENT SEQUENCE RETURN_STATEMENT
%type <number> T_NUMBER
%type <string> T_STRING T_INT

%start PROGRAM

%%

PROGRAM : STATEMENT { g_root = $1;}
        | FUNCTION { g_root = $1;}

FUNCTION : T_INT T_STRING T_LBRACKET T_RBRACKET COMPOUND_STATEMENT { $$ = new Function(*$1, *$2, $5);}

COMPOUND_STATEMENT : T_LCURLY SEQUENCE T_RCURLY { $$ = $2;}

SEQUENCE : STATEMENT { $$ = $1;}

STATEMENT : EXPR T_SEMI { $$ = $1; }
          | RETURN_STATEMENT { $$ = $1; }

RETURN_STATEMENT : T_RETURN EXPR T_SEMI { $$ = new ReturnStatement($2);}

EXPR : VARIABLE T_EQUALS FACTOR {$$ = new AssignmentOperator($1,$3);}
      | FACTOR { $$ = $1; }

FACTOR : T_MINUS T_NUMBER  {$$ = new NegativeNumber($2);}
        | T_NUMBER          {$$ = new Number( $1 );}
        | VARIABLE       {$$ = $1;}
        | T_LBRACKET EXPR T_RBRACKET { $$ = $2;}

VARIABLE : T_STRING       {$$ = new Variable( *$1 );}

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
