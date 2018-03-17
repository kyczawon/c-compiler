%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include <stdio.h>
#include "compiler_parser.tab.hpp"

void comment();
%}

%%
%{
//types
%}
int { yylval.string=new std::string(yytext); return T_INT;}

%{
//keywords
%}
return 			{ return T_RETURN; }
if              { return T_IF; }
else            { return T_ELSE; }
while           { return T_WHILE; }

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
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }
[%]             { return T_MOD; }

%{
//Logical operators
%}
"&&"            { return T_AND; }
"||"            { return T_OR; }
"!"            	{ return T_NOT; }

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
"&"            	{ return T_BIT_AND; }
"|"            	{ return T_BIT_OR; }
"^"            	{ return T_BIT_XOR; }
"<<"            { return T_SHIFT_LEFT; }
">>"            { return T_SHIFT_RIGHT; }

%{
//Assignment operators
%}
"="            	{ return T_EQUALS; }
"+="			{ return T_ADD_EQUALS; }
"-="			{ return T_SUB_EQUALS; }
"*="			{ return T_TIMES_EQUALS; }
"/="			{ return T_DIV_EQUALS; }
"%="			{ return T_MOD_EQUALS; }
"&="			{ return T_AND_EQUALS; }
"^="			{ return T_XOR_EQUALS; }
"|="			{ return T_OR_EQUALS; }
"<<="			{ return T_SHIFT_LEFT_EQUALS; }
">>="			{ return T_SHIFT_RIGHT_EQUALS; }

%{
//Conditional operator
%}
"?"            	{ return T_QUESTION; }
":"            	{ return T_COLON; }
%{
//increment and decrement operators
%}
"++"            	{ return T_INC; }
"--"            	{ return T_DEC; }

%{
//Symbols
%}
[(]             { return T_LBRACKET; }
[)]             { return T_RBRACKET; }
[{]             { return T_LCURLY; }
[}]             { return T_RCURLY; }
[;]             { return T_SEMI; }
[,]             { return T_COMMA; }

[0-9]+([.][0-9]*)? { yylval.number=strtod(yytext, 0); return T_NUMBER; }
[a-z]+          { yylval.string=new std::string(yytext); return T_STRING; }

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
