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
  unsigned int integer;
  double doubl;
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
%token T_IF T_ELSE T_WHILE T_FOR T_RETURN T_CASE T_SWITCH T_CONTINUE T_BREAK T_DO T_DEFAULT T_GOTO
//types
%token T_INT T_SHORT T_CHAR T_VOID
//symbols
%token T_LBRACKET T_RBRACKET T_LCURLY T_RCURLY T_SEMI T_COMMA T_LSQUARE T_RSQUARE
%token T_INTEGER T_STRING T_PERIOD T_CHARACTER T_CONST T_VOLATILE T_SIGNED T_UNSIGNED T_STR T_EXTERN

%type <expr> FACTOR STATEMENT DECLARATION GLOBAL_DECLARATION_LIST FUNCTION_DECLARATION COMPOUND_STATEMENT SEQUENCE SEQUENCE_PROG FUNCTION_DEFINITION
%type <expr> CONDITIONAL_STATEMENT PARAMETER_LIST PARAMETER EXPR_LIST GLOBAL_DECLARATION GLOBAL_VARIABLE_DECLARATION IF_STATEMENT
%type <expr> EMPTY CASE_COMPOUND CASE_STATEMENT INPUT_PARAMS INIT_PARAMS FOR_IN GBL_INIT_PARAMS
%type <expr> ASSIGN_EXPR COND_EXPR LOGICAL_OR_EXPR LOGICAL_AND_EXPR BIT_OR_EXPR BIT_XOR_EXPR BIT_AND_EXPR EQUALITY_EXPR RELATIONAL_EXPR
%type <expr> ADDITIVE_EXPR MULTIPLICATIVE_EXPR SHIFT_EXPR CAST_EXPR UNARY_EXPR POSTFIX_EXPR DECLARATION_LIST
%type <integer> T_INTEGER
//types
%type <string> T_INT T_SHORT T_CHAR T_VOID T_CHARACTER T_STR
%type <string> T_STRING DECLARATION_SPECIFIER TYPE T_IF T_ELSE T_WHILE T_COMMA ASSIGN_OPERATOR UNARY_OPERATOR
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
        | FUNCTION_DEFINITION  

FUNCTION_DECLARATION
        : DECLARATION_SPECIFIER T_STRING T_LBRACKET PARAMETER_LIST T_RBRACKET T_SEMI { $$ = new FunctionDeclaration(*$1, *$2, $4);}
        | DECLARATION_SPECIFIER T_TIMES T_STRING T_LBRACKET PARAMETER_LIST T_RBRACKET T_SEMI { std::string* test = new std::string("int"); $$ = new FunctionDeclaration(*test, *$3, $5);}

FUNCTION_DEFINITION
        : DECLARATION_SPECIFIER T_STRING T_LBRACKET PARAMETER_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new Function(*$1, *$2, $4, $6);}
        | DECLARATION_SPECIFIER T_TIMES T_STRING T_LBRACKET PARAMETER_LIST T_RBRACKET COMPOUND_STATEMENT { std::string* test = new std::string("int"); $$ = new Function(*test, *$3, $5, $7);}

PARAMETER_LIST
        : EMPTY PARAMETER { $$ = new ParameterList($1,$2);}
        | PARAMETER_LIST T_COMMA PARAMETER { $$ = new ParameterList($1,$3);}
        | EMPTY

PARAMETER
        : DECLARATION_SPECIFIER T_STRING { $$ = new Parameter(*$1, *$2);}
        | DECLARATION_SPECIFIER T_TIMES T_STRING { $$ = new Parameter(*$1, *$3);}

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
        | T_GOTO T_STRING T_SEMI { $$ = new gotoStatement(*$2);}
        | T_STRING T_COLON { $$ = new Label(*$1);}

CONDITIONAL_STATEMENT
        : T_WHILE T_LBRACKET EXPR_LIST T_RBRACKET COMPOUND_STATEMENT { $$ = new whileStatement( $3, $5 ); }
        | IF_STATEMENT
        | T_FOR T_LBRACKET FOR_IN T_SEMI FOR_IN T_SEMI FOR_IN T_RBRACKET COMPOUND_STATEMENT { $$ = new forLoop( $3, $5, $7, $9 ); }
        | T_DO COMPOUND_STATEMENT T_WHILE T_LBRACKET EXPR_LIST T_RBRACKET T_SEMI { $$ = new doWhileStatement( $2, $5 ); }
        | T_SWITCH T_LBRACKET EXPR_LIST T_RBRACKET T_LCURLY CASE_COMPOUND T_RCURLY { $$ = new switchStatement( $3, $6 ); }

FOR_IN
        : EXPR_LIST
        | EMPTY

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
        | EXPR_LIST T_COMMA ASSIGN_EXPR { $$ = new ExprList($1,$3);}

ASSIGN_EXPR
        : COND_EXPR
        | DECLARATION
        | T_STRING ASSIGN_OPERATOR COND_EXPR { $$ = new AssignmentOperator(*$1,nullptr,*$2,$3);}
        | T_STRING T_LSQUARE EXPR_LIST T_RSQUARE ASSIGN_OPERATOR COND_EXPR { $$ = new AssignmentOperator(*$1,$3,*$5,$6);}
        | T_TIMES T_STRING ASSIGN_OPERATOR COND_EXPR { $$ = new PointerAssignment(*$2,*$3,$4);}

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
        | MULTIPLICATIVE_EXPR T_MOD CAST_EXPR { $$ = new ModOperator($1, $3); }

CAST_EXPR
	: UNARY_EXPR
	| T_LBRACKET TYPE T_RBRACKET CAST_EXPR { $$ = new CastOperator(*$2, $4); }

UNARY_EXPR
	: POSTFIX_EXPR
        | UNARY_OPERATOR CAST_EXPR { $$ = new UnaryOperator(*$1, $2); }
        | T_TIMES T_STRING { $$ = new IndirectionOperator(*$2); }
        | T_BIT_AND T_STRING { $$ = new AddressOperator(*$2); }
	| T_INC T_STRING { $$ = new PreIncrement(*$2); }
	| T_DEC T_STRING { $$ = new PreDecrement(*$2); }
        | T_SIZE_OF T_STRING { $$ = new SizeOf(*$2); }
	| T_SIZE_OF T_LBRACKET TYPE T_RBRACKET { $$ = new SizeOfType(*$3); }
        | T_SIZE_OF T_LBRACKET T_STRING T_RBRACKET { $$ = new SizeOf(*$3); }

UNARY_OPERATOR
	: T_NOT
        | T_NEGATION
        | T_ADD
        | T_MINUS

POSTFIX_EXPR
        : FACTOR
        | T_STRING T_LBRACKET INPUT_PARAMS T_RBRACKET { $$ = new FunctionInvocation(*$1, $3);}
        | T_STRING T_INC { $$ = new PostIncrement(*$1); }
	| T_STRING T_DEC { $$ = new PostDecrement(*$1); }
        | T_STRING T_LSQUARE EXPR_LIST T_RSQUARE { $$ = new Array(*$1, $3); }
	| T_STRING T_PERIOD T_STRING  { $$ = new Member(*$1, *$3); }
	| T_STRING T_PTR T_STRING { $$ = new MemberPtr(*$1, *$3); }

INPUT_PARAMS
        : EMPTY ASSIGN_EXPR { $$ = new InputParams($1,$2);}
        | INPUT_PARAMS T_COMMA ASSIGN_EXPR { $$ = new InputParams($1,$3);}
        | EMPTY
FACTOR
        : T_MINUS T_INTEGER   {$$ = new NegativeNumber($2);}
        | T_INTEGER          {$$ = new Number( $1 );}
        | T_STRING          {$$ = new Variable(*$1);}
        | T_LBRACKET EXPR_LIST T_RBRACKET { $$ = $2;}
        | T_CHARACTER {$$ = new Character(*$1);}
        | T_STR {$$ = new Str(*$1);}

GLOBAL_VARIABLE_DECLARATION
        : DECLARATION_SPECIFIER GLOBAL_DECLARATION_LIST { $$ = new VariableDeclaration(*$1, $2 );}

GLOBAL_DECLARATION_LIST
        : T_STRING T_SEMI { $$ = new GlobalDeclarationList(nullptr, *$1 );}
        | T_STRING T_COMMA DECLARATION_LIST { $$ = new GlobalDeclarationList($3, *$1);}
        | T_STRING T_EQUALS T_INTEGER T_SEMI { $$ = new GlobalDeclarationList2(nullptr, *$1, $3 );}
        | T_STRING T_EQUALS T_INTEGER T_COMMA DECLARATION_LIST { $$ = new GlobalDeclarationList2($5, *$1, $3);}
        | T_TIMES T_STRING T_SEMI { $$ = new GlobalPointerDeclarationList(nullptr, *$2);}
        | T_TIMES T_STRING T_COMMA DECLARATION_LIST { $$ = new GlobalPointerDeclarationList($4, *$2);}
        | T_TIMES T_STRING T_EQUALS T_INTEGER T_SEMI { $$ = new GlobalPointerDeclarationList2(nullptr, *$2,$4);}
        | T_TIMES T_STRING T_EQUALS T_INTEGER T_COMMA DECLARATION_LIST { $$ = new GlobalPointerDeclarationList2($6, *$2,$4);}
        | T_TIMES T_STRING T_EQUALS T_BIT_AND T_STRING T_SEMI { $$ = new GlobalPointerDeclarationList3(nullptr, *$2,*$5);}
        | T_TIMES T_STRING T_EQUALS T_BIT_AND T_STRING T_COMMA DECLARATION_LIST { $$ = new GlobalPointerDeclarationList3($7, *$2,*$5);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_SEMI { $$ = new GlobalArrayDeclarationList(nullptr, *$1, $3);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_COMMA DECLARATION_LIST { $$ = new GlobalArrayDeclarationList($6, *$1, $3);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_EQUALS T_LCURLY GBL_INIT_PARAMS T_RCURLY T_SEMI { $$ = new GlobalArrayDeclarationList2(nullptr, *$1, $3, $7);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_EQUALS T_LCURLY GBL_INIT_PARAMS T_RCURLY T_COMMA DECLARATION_LIST { $$ = new GlobalArrayDeclarationList2($10, *$1, $3, $7);}

GBL_INIT_PARAMS
        : T_INTEGER { $$ = new GlobalInitParams(nullptr,$1);}
        | GBL_INIT_PARAMS T_COMMA T_INTEGER { $$ = new GlobalInitParams($1,$3);}

DECLARATION
        : DECLARATION_SPECIFIER DECLARATION_LIST    { $$ = new VariableDeclaration(*$1, $2 );}

DECLARATION_LIST
        : T_STRING T_SEMI { $$ = new DeclarationList(nullptr, *$1, nullptr);}
        | T_STRING T_COMMA DECLARATION_LIST { $$ = new DeclarationList($3, *$1, nullptr);}
        | T_STRING T_EQUALS EXPR_LIST T_SEMI { $$ = new DeclarationList(nullptr, *$1, $3);}
        | T_STRING T_EQUALS EXPR_LIST T_COMMA DECLARATION_LIST { $$ = new DeclarationList($5, *$1, $3);}
        | T_TIMES T_STRING T_SEMI { $$ = new PointerDeclarationList(nullptr, *$2, nullptr);}
        | T_TIMES T_STRING T_COMMA DECLARATION_LIST { $$ = new PointerDeclarationList($4, *$2, nullptr);}
        | T_TIMES T_STRING T_EQUALS EXPR_LIST T_SEMI { $$ = new PointerDeclarationList(nullptr, *$2, $4);}
        | T_TIMES T_STRING T_EQUALS EXPR_LIST T_COMMA DECLARATION_LIST { $$ = new PointerDeclarationList($6, *$2, $4);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_SEMI { $$ = new ArrayDeclarationList(nullptr, *$1, $3, nullptr);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_COMMA DECLARATION_LIST { $$ = new ArrayDeclarationList($6, *$1, $3, nullptr);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_EQUALS T_LCURLY INIT_PARAMS T_RCURLY T_SEMI { $$ = new ArrayDeclarationList(nullptr, *$1, $3, $7);}
        | T_STRING T_LSQUARE T_INTEGER T_RSQUARE T_EQUALS T_LCURLY INIT_PARAMS T_RCURLY T_COMMA DECLARATION_LIST { $$ = new ArrayDeclarationList($10, *$1, $3, $7);}

INIT_PARAMS
        : ASSIGN_EXPR { $$ = new InitParams(nullptr,$1);}
        | INIT_PARAMS T_COMMA ASSIGN_EXPR { $$ = new InitParams($1,$3);}

DECLARATION_SPECIFIER
        : TYPE_QUALIFIER_LIST TYPE { $$ = $2;}

TYPE
        : T_INT
        | T_CHAR
        | T_SHORT
        | T_VOID

TYPE_QUALIFIER_LIST
        : TYPE_QUALIFIER
        | TYPE_QUALIFIER_LIST TYPE_QUALIFIER
        | %empty

TYPE_QUALIFIER
        : T_CONST
        | T_VOLATILE
        | T_EXTERN
        | T_SIGNED
        | T_UNSIGNED

%%

const Node *g_root; // Definition of variable (to match declaration earlier)

const Node *parseAST()
{
  g_root=0;
  yyparse();
  return g_root;
}
