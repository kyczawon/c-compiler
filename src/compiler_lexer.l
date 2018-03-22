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

%{
//keywords
%}
return { return T_RETURN; }

"/"[/]+.*       {;}
"/*"			{ comment(); }

[;]             { return T_SEMI; }
[:]				{return T_COLON; }
[,]             { return T_COMMA; }
[=]             { return T_EQUALS; }

[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }

"&&"            { return T_AND; }
"||"            { return T_OR; }

"=="            { return T_EQUALS_EQUALS; }
"!="            { return T_NOT_EQUALS; }
">"             { return T_GREATER; }
"<"             { return T_LESS; }

[(]             { return T_LBRACKET;}
[)]             { return T_RBRACKET;}
[{]             { return T_LCURLY;}
[}]             { return T_RCURLY;}

if              {return T_IF;    }
else            {return T_ELSE;  }
while           {return T_WHILE; }
for 			{return T_FOR; 	 }
do 				{return T_DO; 	 }
break 			{return T_BREAK; }
continue		{return T_CONTINUE; }
switch 			{return T_SWITCH;}
case 			{return T_CASE;  }
default			{return T_DEFAULT;}

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
