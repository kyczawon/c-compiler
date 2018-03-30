%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include <stdio.h>
#include <vector>
#include "compiler_parser.tab.hpp"

void comment();
%}

%%
%{
//types
%}
int { yylval.string=new std::string(yytext); return T_INT;}
short { yylval.string=new std::string(yytext); return T_SHORT;}
char { yylval.string=new std::string(yytext); return T_CHAR;}
void { yylval.string=new std::string(yytext); return T_VOID;}

%{
//keywords
%}
return 			{ return T_RETURN; }
if              { return T_IF; }
else            { return T_ELSE; }
while           { return T_WHILE; }
for 			{return T_FOR; }
do 				{return T_DO; 	 }
break 			{return T_BREAK; }
continue		{return T_CONTINUE; }
switch 			{return T_SWITCH;}
case 			{return T_CASE;  }
default			{return T_DEFAULT;}
goto			{return T_GOTO; }
const			{return T_CONST; }
volatile		{return T_VOLATILE; }
signed			{return T_SIGNED; }
unsigned		{return T_UNSIGNED; }
extern			{return T_EXTERN; }

%{
//comments
%}
"/"[/]+.*    {;}
"/*"			{ comment(); }

%{
//Arithmetic operators
%}
[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { yylval.string=new std::string(yytext); return T_PLUS; }
[-]             { yylval.string=new std::string(yytext); return T_MINUS; }
[%]             { return T_MOD; }

%{
//Logical operators
%}
"&&"            { return T_AND; }
"||"            { return T_OR; }

%{
//Unary operators (except *, -, +,&)
%}
"!"            	{ yylval.string=new std::string(yytext); return T_NOT; }
"++"            { return T_INC; }
"--"            { return T_DEC; }
"~"				{ yylval.string=new std::string(yytext); return T_NEGATION; }
"sizeof"		{ return T_SIZE_OF; }
"->"			{ return T_PTR; }

%{
//Relational operators
%}
"=="            { return T_EQUALS_EQUALS; }
"!="            { return T_NOT_EQUALS; }
">"            	{ return T_GREATER; }
">="            { return T_GREATER_EQUALS; }
"<"            	{ return T_LESS; }
"<="            { return T_LESS_EQUALS; }

%{
//Bitwise operators
%}
"&"            	{ yylval.string=new std::string(yytext); return T_BIT_AND; }
"|"            	{ return T_BIT_OR; }
"^"            	{ return T_BIT_XOR; }
"<<"            { return T_SHIFT_LEFT; }
">>"            { return T_SHIFT_RIGHT; }

%{
//Assignment operators
%}
"="            	{ yylval.string=new std::string(yytext); return T_EQUALS; }
"+="			{ yylval.string=new std::string(yytext); return T_ADD_EQUALS; }
"-="			{ yylval.string=new std::string(yytext); return T_SUB_EQUALS; }
"*="			{ yylval.string=new std::string(yytext); return T_TIMES_EQUALS; }
"/="			{ yylval.string=new std::string(yytext); return T_DIV_EQUALS; }
"%="			{ yylval.string=new std::string(yytext); return T_MOD_EQUALS; }
"&="			{ yylval.string=new std::string(yytext); return T_AND_EQUALS; }
"^="			{ yylval.string=new std::string(yytext); return T_XOR_EQUALS; }
"|="			{ yylval.string=new std::string(yytext); return T_OR_EQUALS; }
"<<="			{ yylval.string=new std::string(yytext); return T_SHIFT_LEFT_EQUALS; }
">>="			{ yylval.string=new std::string(yytext); return T_SHIFT_RIGHT_EQUALS; }

%{
//Conditional operator
%}
"?"            	{ return T_QUESTION; }
":"            	{ return T_COLON; }

%{
//Symbols
%}
[(]             { return T_LBRACKET; }
[)]             { return T_RBRACKET; }
[{]             { return T_LCURLY; }
[}]             { return T_RCURLY; }
[[]             { return T_LSQUARE; }
[]]             { return T_RSQUARE; }
[;]             { return T_SEMI; }
[,]             { return T_COMMA; }
[.]				{ return T_PERIOD; }


[0-9]+  { yylval.integer=strtod(yytext, 0); return T_INTEGER; }
[a-zA-Z_][a-zA-Z0-9_]* { yylval.string=new std::string(yytext); return T_STRING; }
%{
//regex taken 30.03 from https://www.lysator.liu.se/c/ANSI-C-grammar-y.html#conditional-expression
%}
\"(\\.|[^\\"])*\" { yylval.string=new std::string(yytext); return T_STR;}
%{
//regex taken 30.03 https://stackoverflow.com/questions/3203190/regex-any-ascii-character
%}
'[\x00-\x7F]' { yylval.string=new std::string(yytext); return T_CHARACTER;}
[ \t\r\n]+		{;}

.               { fprintf(stderr, "Invalid token\n"); exit(1); }
%%

void yyerror (char const *s)
{
  fprintf (stderr, "Parse error : %s\n", s);
  exit(1);
}

void comment()
{
	char c, c1;

loop:
	while ((c = yyinput()) != '*' && c != 0){}

	if ((c1 = yyinput()) != '/' && c != 0)
	{
		unput(c1);
		goto loop;
	}
}