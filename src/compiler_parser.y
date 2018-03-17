%code requires{
  #include "ast.hpp"

  #include <cassert>

  extern const Node *g_root; // A way of getting the AST out

  //! This is to fix problems when generating C++
  // We are declaring the functions provided by Flex, so
  // that Bison generated code can call them.
  int yylex(void);
  void yyerror(const char *);
}

// Represents the value associated with any kind of
// AST node.
%union{
  const Node *expr;
  double number;
  std::string *string;
}
//arithmetic operators
%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_MOD
//logical operators
%token T_AND T_OR T_NOT
//relational operators
%token T_EQUALS_EQUALS T_NOT_EQUALS T_GREATER T_GREATER_EQUALS T_LESS T_LESS_EQUALS
//bitwsie operators
%token T_BIT_AND T_BIT_OR T_BIT_XOR T_SHIFT_LEFT T_SHIFT_RIGHT
//conditional operators
%token T_QUESTION T_COLON
//increment and decrement operators
%token T_INC T_DEC
//assignment operators
%token T_EQUALS T_ADD_EQUALS T_SUB_EQUALS T_TIMES_EQUALS T_DIV_EQUALS T_MOD_EQUALS
%token T_AND_EQUALS T_XOR_EQUALS T_OR_EQUALS T_SHIFT_LEFT_EQUALS T_SHIFT_RIGHT_EQUALS
//keywords
%token T_INT T_IF T_ELSE T_WHILE T_RETURN
//symbols
%token T_LBRACKET T_RBRACKET T_LCURLY T_RCURLY T_SEMI T_COMMA
%token T_NUMBER T_STRING

%type <expr> FACTOR STATEMENT DECLARATION FUNCTION_DECLARATION COMPOUND_STATEMENT SEQUENCE SEQUENCE_PROG
%type <expr> CONDITIONAL_STATEMENT PARAMETER_LIST PARAMETER EXPR_LIST GLOBAL_DECLARATION GLOBAL_VARIABLE_DECLARATION IF_STATEMENT ELSE_STATEMENT
%type <expr> ASSIGN_EXPR COND_EXPR LOGICAL_OR_EXPR LOGICAL_AND_EXPR BIT_OR_EXPR BIT_XOR_EXPR BIT_AND_EXPR EQUALITY_EXPR RELATIONAL_EXPR
%type <expr> SHIFT_EXPR ADDITIVE_EXPR MULTIPLICATIVE_EXPR
%type <expr> EMPTY
%type <number> T_NUMBER
%type <string> T_STRING T_INT TYPE ASIGN_OPERATOR
//assignment operators
%type <string> T_EQUALS T_ADD_EQUALS T_SUB_EQUALS T_TIMES_EQUALS T_DIV_EQUALS T_MOD_EQUALS
%type <string> T_AND_EQUALS T_XOR_EQUALS T_OR_EQUALS T_SHIFT_LEFT_EQUALS T_SHIFT_RIGHT_EQUALS

%start PROGRAM

%%

PROGRAM : SEQUENCE_PROG { g_root = $1;}

SEQUENCE_PROG
        : EMPTY GLOBAL_DECLARATION { $$ = new Sequence($1,$2);}
        | SEQUENCE_PROG GLOBAL_DECLARATION { $$ = new Sequence($1,$2);}

GLOBAL_DECLARATION
        : GLOBAL_VARIABLE_DECLARATION { $$ = $1;}
        | FUNCTION_DECLARATION { $$ = $1;}       

FUNCTION_DECLARATION
        : TYPE T_STRING T_LBRACKET PARAMETER_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new Function(*$1, *$2, $4, $6);}

PARAMETER_LIST
        : PARAMETER { $$ = $1;}
        | PARAMETER_LIST T_COMMA PARAMETER { $$ = new ParameterList($1,$3);}
        | EMPTY {$$ = $1;}

PARAMETER
        : TYPE T_STRING { $$ = new Parameter(*$1, *$2);}

COMPOUND_STATEMENT
        : T_LCURLY SEQUENCE T_RCURLY { $$ = new CompoundStatement($2);}

SEQUENCE
        : SEQUENCE STATEMENT { $$ = new Sequence($1,$2);}
        | EMPTY STATEMENT { $$ = new Sequence($1,$2);}
        | EMPTY {$$ = $1;}

EMPTY
        : %empty {$$ = nullptr;}

STATEMENT
        : EXPR_LIST T_SEMI { $$ = new Statement($1);}
        | CONDITIONAL_STATEMENT { $$ = $1; }
        | T_RETURN EXPR_LIST T_SEMI { $$ = new ReturnStatement($2);}
        | DECLARATION { $$ = $1; }

CONDITIONAL_STATEMENT
        : IF_STATEMENT 
        | IF_STATEMENT ELSE_STATEMENT
        | T_WHILE T_LBRACKET EXPR_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new whileStatement( $3, $5 ); }

IF_STATEMENT
        : T_IF T_LBRACKET EXPR_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new ifStatement( $3, $5 ); }
        | T_IF T_LBRACKET EXPR_LIST T_RBRACKET STATEMENT { $$ = new ifStatement( $3, new CompoundStatement( new Sequence( nullptr, $5 )) ); }

ELSE_STATEMENT
        : T_ELSE STATEMENT { $$ = new elseStatement( $2 );  }
        | T_ELSE COMPOUND_STATEMENT { $$ = new elseStatement( $2 );  }

EXPR_LIST
        : ASSIGN_EXPR { $$ = $1;}
        | EXPR_LIST T_COMMA ASSIGN_EXPR { $$ = new NodeList($1,$3);}

ASSIGN_EXPR
        : COND_EXPR { $$ = $1; }
        | T_STRING ASIGN_OPERATOR COND_EXPR { $$ = new AssignmentOperator(*$1,*$2,$3);}

ASIGN_OPERATOR
        : T_EQUALS { $$ = $1; }
        | T_ADD_EQUALS { $$ = $1; }
        | T_SUB_EQUALS { $$ = $1; }
        | T_TIMES_EQUALS { $$ = $1; }
        | T_DIV_EQUALS { $$ = $1; }
        | T_MOD_EQUALS { $$ = $1; }
        | T_AND_EQUALS { $$ = $1; }
        | T_XOR_EQUALS { $$ = $1; }
        | T_OR_EQUALS { $$ = $1; }
        | T_SHIFT_LEFT_EQUALS { $$ = $1; }
        | T_SHIFT_RIGHT_EQUALS { $$ = $1; }

COND_EXPR
        : LOGICAL_OR_EXPR { $$ = $1; }
        | LOGICAL_OR_EXPR T_QUESTION EXPR_LIST T_COLON COND_EXPR { $$ = new ConditionalOperator($1, $3 $5); }

LOGICAL_OR_EXPR
        : LOGICAL_AND_EXPR { $$ = $1; }
        | LOGICAL_OR_EXPR T_OR LOGICAL_AND_EXPR { $$ = new OrOperator($1, $3); }

LOGICAL_AND_EXPR
        : BIT_OR_EXPR { $$ = $1; }
        | LOGICAL_AND_EXPR T_AND BIT_OR_EXPR { $$ = new AndOperator($1, $3); }

BIT_OR_EXPR
        : BIT_XOR_EXPR { $$ = $1; }
        | BIT_OR_EXPR T_BIT_OR BIT_XOR_EXPR { $$ = new BitwiseOrOperator($1, $3); }

BIT_XOR_EXPR
        : BIT_AND_EXPR { $$ = $1; }
        | BIT_XOR_EXPR T_BIT_XOR BIT_AND_EXPR { $$ = new BitwiseXorOperator($1, $3); }

BIT_AND_EXPR
        : EQUALITY_EXPR { $$ = $1; }
        | BIT_AND_EXPR BIT_AND_EXPR EQUALITY_EXPR { $$ = new BitwiseAndOperator($1, $3); }

EQUALITY_EXPR
        : EQUALITY_EXPR { $$ = $1; }
        | EQUALITY_EXPR T_EQUALS_EQUALS RELATIONAL_EXPR { $$ = new EqualsOperator($1, $3); }
        | EQUALITY_EXPR T_NOT_EQUALS RELATIONAL_EXPR { $$ = new NotEqualsOperator($1, $3); }

RELATIONAL_EXPR
        : SHIFT_EXPR { $$ = $1; }
        | RELATIONAL_EXPR T_GREATER SHIFT_EXPR { $$ = new GreaterOperator($1, $3); }
        | RELATIONAL_EXPR T_GREATER_EQUALS SHIFT_EXPR { $$ = new GreaterEqualOperator($1, $3); }
        | RELATIONAL_EXPR T_LESS SHIFT_EXPR { $$ = new LessOperator($1, $3); }
        | RELATIONAL_EXPR T_LESS_EQUALS SHIFT_EXPR { $$ = new LessEqualOperator($1, $3); }

SHIFT_EXPR
        : ADDITIVE_EXPR { $$ = $1; }
        | SHIFT_EXPR T_SHIFT_LEFT ADDITIVE_EXPR { $$ = new LeftShiftOperator($1, $3); }
	| SHIFT_EXPR T_SHIFT_RIGHT ADDITIVE_EXPR { $$ = new RightShiftOperator($1, $3); }

ADDITIVE_EXPR
        : MULTIPLICATIVE_EXPR { $$ = $1; }
        | ADDITIVE_EXPR T_PLUS MULTIPLICATIVE_EXPR { $$ = new AddOperator($1, $3); }
        | ADDITIVE_EXPR T_MINUS MULTIPLICATIVE_EXPR { $$ = new SubOperator($1, $3); }

MULTIPLICATIVE_EXPR
        : FACTOR              { $$ = $1; }
        | T_STRING T_LBRACKET T_RBRACKET { $$ = new UnaryFunctionInvocation(*$1);}
        | T_STRING T_LBRACKET EXPR_LIST T_RBRACKET { $$ = new FunctionInvocation(*$1, $3);}
        | MULTIPLICATIVE_EXPR T_TIMES FACTOR { $$ = new MulOperator($1, $3); }
        | MULTIPLICATIVE_EXPR T_DIVIDE FACTOR { $$ = new DivOperator($1, $3); }

FACTOR
        : T_MINUS T_NUMBER   {$$ = new NegativeNumber($2);}
        | T_NUMBER          {$$ = new Number( $1 );}
        | T_STRING          {$$ = new Variable(*$1);}
        | T_LBRACKET EXPR_LIST T_RBRACKET { $$ = $2;}

GLOBAL_VARIABLE_DECLARATION
        : TYPE T_STRING T_SEMI { $$ = new GlobalVariableDeclaration(*$1, *$2 );}
        | TYPE T_STRING T_EQUALS EXPR_LIST T_SEMI { $$ = new InitialisedGlobalVariableDeclaration(*$1, *$2, $4 );}

DECLARATION
        : TYPE T_STRING T_SEMI    { $$ = new VariableDeclaration(*$1, *$2 );}
        | TYPE T_STRING T_EQUALS EXPR_LIST T_SEMI { $$ = new InitialisedVariableDeclaration(*$1, *$2, $4 );}


TYPE
        : T_INT { $$ = $1; }

%%

const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
