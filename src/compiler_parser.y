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

%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_COMMA
%token T_LBRACKET T_RBRACKET T_LCURLY T_RCURLY T_SEMI T_EQUALS
%token T_INT T_IF T_ELSE T_WHILE
%token T_RETURN
%token T_NUMBER T_STRING

%type <expr> EXPR TERM FACTOR STATEMENT DECLARATION FUNCTION COMPOUND_STATEMENT SEQUENCE SEQUENCE_PROG
%type <expr> CONDITIONAL_STATEMENT PARAMETER_LIST PARAMETER EXPR_LIST
%type <number> T_NUMBER
%type <string> T_STRING T_INT TYPE T_IF T_ELSE T_WHILE T_COMMA

%start PROGRAM

%%

PROGRAM : SEQUENCE_PROG { g_root = $1;}

SEQUENCE_PROG
        : FUNCTION { $$ = $1; }
        | DECLARATION { $$ = $1;}
        | SEQUENCE_PROG FUNCTION { $$ = new Sequence($1,$2);}
        | SEQUENCE_PROG DECLARATION { $$ = new Sequence($1,$2);}

FUNCTION
        : TYPE T_STRING T_LBRACKET PARAMETER_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new Function(*$1, *$2, $4, $6);}
        | TYPE T_STRING T_LBRACKET T_RBRACKET COMPOUND_STATEMENT { $$ = new NullaryFunction(*$1, *$2, $5);}

PARAMETER_LIST
        : PARAMETER { $$ = $1;}
        | PARAMETER_LIST T_COMMA PARAMETER { $$ = new ParameterList($1,$3);}

PARAMETER
        : TYPE T_STRING { $$ = new Parameter(*$1, *$2);}

COMPOUND_STATEMENT
        : T_LCURLY SEQUENCE T_RCURLY { $$ = $2;}

SEQUENCE
        : STATEMENT { $$ = $1; }
        | SEQUENCE STATEMENT { $$ = new Sequence($1,$2);}

STATEMENT
        : EXPR T_SEMI { $$ = new Statement($1);}
        | CONDITIONAL_STATEMENT { $$ = $1; }
        | T_RETURN EXPR T_SEMI { $$ = new ReturnStatement($2);}
        | DECLARATION { $$ = $1; }

CONDITIONAL_STATEMENT
        : T_IF T_LBRACKET EXPR T_RBRACKET COMPOUND_STATEMENT { $$ = new ifStatement( $3, $5 ); }
        | T_WHILE T_LBRACKET EXPR T_RBRACKET COMPOUND_STATEMENT { $$ = new whileStatement( $3, $5 ); }
        | T_ELSE COMPOUND_STATEMENT { $$ = new elseStatement( $2 );  }

EXPR
        : TERM             { $$ = $1; }
        | T_STRING T_EQUALS TERM { $$ = new AssignmentOperator(*$1,$3);}
        | EXPR T_PLUS TERM { $$ = new AddOperator($1, $3); }
        | EXPR T_MINUS TERM { $$ = new SubOperator($1, $3); }

EXPR_LIST
        : EXPR { $$ = $1;}
        | EXPR_LIST T_COMMA EXPR { $$ = new ExpressionList($1,$3);}

TERM
        : FACTOR              { $$ = $1; }
        | T_STRING T_LBRACKET T_RBRACKET { $$ = new UnaryFunctionInvocation(*$1);}
        | T_STRING T_LBRACKET EXPR_LIST T_RBRACKET { $$ = new FunctionInvocation(*$1, $3);}
        | TERM T_TIMES FACTOR { $$ = new MulOperator($1, $3); }
        | TERM T_DIVIDE FACTOR { $$ = new DivOperator($1, $3); }

FACTOR
        : T_MINUS T_NUMBER   {$$ = new NegativeNumber($2);}
        | T_NUMBER          {$$ = new Number( $1 );}
        | T_STRING          {$$ = new Variable(*$1);}
        | T_LBRACKET EXPR T_RBRACKET { $$ = $2;}

DECLARATION
        : TYPE T_STRING T_SEMI    { $$ = new VariableDeclaration(*$1, *$2 );}


TYPE
        : T_INT { $$ = $1; }

%%

const Expression *g_root; // Definition of variable (to match declaration earlier)

const Expression *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
