%option noyywrap

%{
// Avoid error "error: `fileno' was not declared in this scope"
extern "C" int fileno(FILE *stream);

#include "compiler_parser.tab.hpp"
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

[;]             { return T_SEMI; }
[,]             { return T_COMMA; }
[=]             { return T_EQUALS; }

[*]             { return T_TIMES; }
[/]             { return T_DIVIDE; }
[+]             { return T_PLUS; }
[-]             { return T_MINUS; }

[(]             { return T_LBRACKET;}
[)]             { return T_RBRACKET;}
[{]             { return T_LCURLY;}
[}]             { return T_RCURLY;}

if              {return T_IF;    }
else            {return T_ELSE;  }
while           {return T_WHILE; }

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
