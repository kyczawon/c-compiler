%code requires{
  #include "ast.hpp"
  #include <vector>
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

//Unary operators
%token T_NOT T_INC T_DEC T_NEGATION T_SIZE_OF T_PTR
//arithmetic operators
%token T_TIMES T_DIVIDE T_PLUS T_MINUS T_ADD T_MOD
//logical operators
%token T_AND T_OR
//relational operators
%token T_EQUALS_EQUALS T_NOT_EQUALS T_GREATER T_GREATER_EQUALS T_LESS T_LESS_EQUALS
//bitwsie operators
%token T_BIT_AND T_BIT_OR T_BIT_XOR T_SHIFT_LEFT T_SHIFT_RIGHT
//conditional operators
%token T_QUESTION T_COLON
//assignment operators
%token T_EQUALS T_ADD_EQUALS T_SUB_EQUALS T_TIMES_EQUALS T_DIV_EQUALS T_MOD_EQUALS
%token T_AND_EQUALS T_XOR_EQUALS T_OR_EQUALS T_SHIFT_LEFT_EQUALS T_SHIFT_RIGHT_EQUALS
//keywords
%token T_INT T_IF T_ELSE T_WHILE T_FOR T_RETURN T_CASE T_SWITCH T_CONTINUE T_BREAK T_DO T_DEFAULT
//symbols
%token T_LBRACKET T_RBRACKET T_LCURLY T_RCURLY T_SEMI T_COMMA T_LSQUARE T_RSQUARE
%token T_NUMBER T_STRING T_PERIOD

%type <expr> FACTOR STATEMENT DECLARATION FUNCTION_DECLARATION COMPOUND_STATEMENT SEQUENCE SEQUENCE_PROG
%type <expr> CONDITIONAL_STATEMENT PARAMETER_LIST PARAMETER EXPR_LIST GLOBAL_DECLARATION GLOBAL_VARIABLE_DECLARATION IF_STATEMENT
%type <expr> EMPTY CASE_COMPOUND CASE_STATEMENT 
%type <expr> ASSIGN_EXPR COND_EXPR LOGICAL_OR_EXPR LOGICAL_AND_EXPR BIT_OR_EXPR BIT_XOR_EXPR BIT_AND_EXPR EQUALITY_EXPR RELATIONAL_EXPR
%type <expr> ADDITIVE_EXPR MULTIPLICATIVE_EXPR SHIFT_EXPR CAST_EXPR UNARY_EXPR POSTFIX_EXPR 
%type <number> T_NUMBER
%type <string> T_STRING T_INT TYPE T_IF T_ELSE T_WHILE T_COMMA ASSIGN_OPERATOR UNARY_OPERATOR
%type <string> T_EQUALS_EQUALS T_NOT_EQUALS T_GREATER T_LESS T_AND T_OR
//assignment operators
%type <string> T_EQUALS T_ADD_EQUALS T_SUB_EQUALS T_TIMES_EQUALS T_DIV_EQUALS T_MOD_EQUALS
%type <string> T_AND_EQUALS T_XOR_EQUALS T_OR_EQUALS T_SHIFT_LEFT_EQUALS T_SHIFT_RIGHT_EQUALS
//unary operators
%type <string>T_TIMES T_BIT_AND T_NOT T_NEGATION T_ADD T_MINUS

%start PROGRAM

%%

PROGRAM : SEQUENCE_PROG { g_root = $1;}

SEQUENCE_PROG
        : EMPTY GLOBAL_DECLARATION { $$ = new Sequence($1,$2);}
        | SEQUENCE_PROG GLOBAL_DECLARATION { $$ = new Sequence($1,$2);}

GLOBAL_DECLARATION
        : GLOBAL_VARIABLE_DECLARATION
        | FUNCTION_DECLARATION       

FUNCTION_DECLARATION
        : TYPE T_STRING T_LBRACKET PARAMETER_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new Function(*$1, *$2, $4, $6);}

PARAMETER_LIST
        : PARAMETER
        | PARAMETER_LIST T_COMMA PARAMETER { $$ = new ParameterList($1,$3);}
        | EMPTY

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
        | CONDITIONAL_STATEMENT
        | T_RETURN EXPR_LIST T_SEMI { $$ = new ReturnStatement($2);}
        | DECLARATION
        | COMPOUND_STATEMENT
        | T_BREAK T_SEMI { $$ = new breakStatement(); }
        | T_CONTINUE T_SEMI { $$ = new continueStatement(); }

CONDITIONAL_STATEMENT
        : T_WHILE T_LBRACKET EXPR_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new whileStatement( $3, $5 ); }
        | IF_STATEMENT
        | T_FOR T_LBRACKET EXPR_LIST T_SEMI EXPR_LIST T_SEMI EXPR_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new forLoop( $3, $5, $7, $9 ); }
        | T_DO COMPOUND_STATEMENT T_WHILE T_LBRACKET EXPR_LIST T_RBRACKET T_SEMI { $$ = new doWhileStatement( $2, $5 ); }
        | T_SWITCH T_LBRACKET EXPR_LIST T_RBRACKET T_LCURLY CASE_COMPOUND T_RCURLY { $$ = new switchStatement( $3, $6 ); }

CASE_COMPOUND
        : CASE_STATEMENT
        | CASE_COMPOUND CASE_STATEMENT { $$ = new Sequence($1, $2); }

CASE_STATEMENT
        : T_CASE ASSIGN_EXPR T_COLON SEQUENCE { $$ = new caseStatement( $2, $4 ); }
        | T_DEFAULT T_COLON SEQUENCE { $$ = new caseStatement( nullptr, $3 ); }

IF_STATEMENT
        : T_IF T_LBRACKET EXPR_LIST T_RBRACKET STATEMENT { $$ = new ifStatement( $3, new CompoundStatement( new Sequence( nullptr, $5 )) ); }
        | T_IF T_LBRACKET EXPR_LIST T_RBRACKET STATEMENT T_ELSE STATEMENT { $$ = new ifElseStatement( $3, $5, $7 ); }

EXPR_LIST
        : ASSIGN_EXPR
        | EXPR_LIST T_COMMA ASSIGN_EXPR { $$ = new NodeList($1,$3);}

ASSIGN_EXPR
        : COND_EXPR
        | T_STRING ASSIGN_OPERATOR COND_EXPR { $$ = new AssignmentOperator(*$1,*$2,$3);}

ASSIGN_OPERATOR
        : T_EQUALS
        | T_ADD_EQUALS
        | T_SUB_EQUALS
        | T_TIMES_EQUALS
        | T_DIV_EQUALS
        | T_MOD_EQUALS
        | T_AND_EQUALS
        | T_XOR_EQUALS
        | T_OR_EQUALS
        | T_SHIFT_LEFT_EQUALS
        | T_SHIFT_RIGHT_EQUALS

COND_EXPR
        : LOGICAL_OR_EXPR
        | LOGICAL_OR_EXPR T_QUESTION EXPR_LIST T_COLON COND_EXPR { $$ = new ConditionalOperator($1, $3, $5); }

LOGICAL_OR_EXPR
        : LOGICAL_AND_EXPR
        | LOGICAL_OR_EXPR T_OR LOGICAL_AND_EXPR { $$ = new OrOperator($1, $3); }

LOGICAL_AND_EXPR
        : BIT_OR_EXPR
        | LOGICAL_AND_EXPR T_AND BIT_OR_EXPR { $$ = new AndOperator($1, $3); }

BIT_OR_EXPR
        : BIT_XOR_EXPR
        | BIT_OR_EXPR T_BIT_OR BIT_XOR_EXPR { $$ = new BitwiseOrOperator($1, $3); }

BIT_XOR_EXPR
        : BIT_AND_EXPR
        | BIT_XOR_EXPR T_BIT_XOR BIT_AND_EXPR { $$ = new BitwiseXorOperator($1, $3); }

BIT_AND_EXPR
        : EQUALITY_EXPR
        | BIT_AND_EXPR T_BIT_AND EQUALITY_EXPR { $$ = new BitwiseAndOperator($1, $3); }

EQUALITY_EXPR
        : RELATIONAL_EXPR
        | EQUALITY_EXPR T_EQUALS_EQUALS RELATIONAL_EXPR { $$ = new EqualsOperator($1, $3); }
        | EQUALITY_EXPR T_NOT_EQUALS RELATIONAL_EXPR { $$ = new NotEqualsOperator($1, $3); }

RELATIONAL_EXPR
        : SHIFT_EXPR
        | RELATIONAL_EXPR T_GREATER SHIFT_EXPR { $$ = new GreaterOperator($1, $3); }
        | RELATIONAL_EXPR T_GREATER_EQUALS SHIFT_EXPR { $$ = new GreaterEqualOperator($1, $3); }
        | RELATIONAL_EXPR T_LESS SHIFT_EXPR { $$ = new LessOperator($1, $3); }
        | RELATIONAL_EXPR T_LESS_EQUALS SHIFT_EXPR { $$ = new LessEqualOperator($1, $3); }

SHIFT_EXPR
        : ADDITIVE_EXPR
        | SHIFT_EXPR T_SHIFT_LEFT ADDITIVE_EXPR { $$ = new LeftShiftOperator($1, $3); }
	| SHIFT_EXPR T_SHIFT_RIGHT ADDITIVE_EXPR { $$ = new RightShiftOperator($1, $3); }

ADDITIVE_EXPR
        : MULTIPLICATIVE_EXPR
        | ADDITIVE_EXPR T_PLUS MULTIPLICATIVE_EXPR {$$= new AddOperator($1,$3);}
        | ADDITIVE_EXPR T_MINUS MULTIPLICATIVE_EXPR {$$= new SubOperator($1,$3);}

MULTIPLICATIVE_EXPR
        : CAST_EXPR
        | MULTIPLICATIVE_EXPR T_TIMES CAST_EXPR { $$ = new MulOperator($1, $3); }
        | MULTIPLICATIVE_EXPR T_DIVIDE CAST_EXPR { $$ = new DivOperator($1, $3); }

CAST_EXPR
	: UNARY_EXPR
	| T_LBRACKET TYPE T_RBRACKET CAST_EXPR { $$ = new CastOperator(*$2, $4); }

UNARY_EXPR
	: POSTFIX_EXPR
        | UNARY_OPERATOR CAST_EXPR { $$ = new UnaryOperator(*$1, $2); }
	| T_INC T_STRING { $$ = new PreIncrement(*$2); }
	| T_DEC T_STRING { $$ = new PreDecrement(*$2); }
        | T_SIZE_OF T_STRING { $$ = new SizeOf(*$2); }
	| T_SIZE_OF T_LBRACKET TYPE T_RBRACKET { $$ = new SizeOfType(*$3); }

UNARY_OPERATOR
	: T_TIMES
        | T_BIT_AND
        | T_NOT
        | T_NEGATION
        | T_ADD
        | T_MINUS

POSTFIX_EXPR
        : FACTOR
        | T_STRING T_LBRACKET T_RBRACKET { $$ = new UnaryFunctionInvocation(*$1);}
        | T_STRING T_LBRACKET EXPR_LIST T_RBRACKET { $$ = new FunctionInvocation(*$1, $3);}
        | T_STRING T_INC { $$ = new PostIncrement(*$1); }
	| T_STRING T_DEC { $$ = new PostDecrement(*$1); }
        | T_STRING T_LSQUARE EXPR_LIST T_RSQUARE { $$ = new Array(*$1, $3); }
	| T_STRING T_PERIOD T_STRING  { $$ = new Member(*$1, *$3); }
	| T_STRING T_PTR T_STRING { $$ = new MemberPtr(*$1, *$3); }

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
        : T_INT

%%

const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
