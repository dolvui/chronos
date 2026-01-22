/* lexer.l - Chronos lexer */

%option noyywrap

%{
#include "parser.tab.hpp"
#include <string>
#include <iostream>

using namespace std;
%}

DIGIT   [0-9]
ID      [a-zA-Z_][a-zA-Z0-9_-]*

%%

"create"        { return CREATE; }
"save"          { return SAVE; }
"choose"        { return CHOOSE; }
"retro"         { return RETRO; }
"undo"          { return UNDO; }
"jmp"           { return JMP; }

"True"|"1"      { yylval.str = new std::string("True"); return BOOL; }
"False"|"0"     { yylval.str = new std::string("False"); return BOOL; }

{DIGIT}+        { yylval.ival = atoi(yytext); return INT; }
{DIGIT}+"."{DIGIT}+  { yylval.fval = atof(yytext); return FLOAT; }

{ID}            { yylval.str = new std::string(yytext); return VAR; }

[ \t\n\r]+      ; // skip whitespace
";"             { return ';'; }
","             { return ','; }
"="             { return '='; }
"["             { return '['; }
"]"             { return ']'; }
"("             { return '('; }
")"             { return ')' ; }
"+"             { return '+'; }
"-"             { return '-'; }
"*"             { return '*'; }
"/"             { return '/'; }
"^"             { return '^'; }

.               { std::cerr << "Unknown character: " << yytext << std::endl; }

%%
