%code requires {
#include <string>
#include <vector>
}


%{
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "../src/runtime.hpp"
using namespace std;

extern Runtime* g_runtime;
extern int yylex();
void yyerror(const char* s);
%}

%union {
    std::string* str; // VAR, BOOL
    int          ival; // INT
    double fval;       // FLOAT
    std::vector<std::string>* slist;
}

%token <str> VAR
%token <ival> INT
%token <fval> FLOAT
%token <str> BOOL

%token CREATE SAVE CHOOSE RETRO UNDO JMP

/* Declare the type for non-terminal symbols */
%type <str> expression
%type <slist> saved_list
%type <slist> var_list
%type <slist> optional_var_list

%left '+' '-'
%left '*' '/'
%right '^'

%start program

%%

program:
    /* empty */
    | program statement
    ;

statement:
      CREATE VAR '=' expression ';'   { g_runtime->create_variable(*$2, *$4); delete $2; delete $4; }
      | SAVE VAR optional_expr ';'    { g_runtime->save_state(*$2); delete $2; }
      | CHOOSE saved_list ';'         { g_runtime->choose_state(*$2);delete $2; }
      | RETRO VAR ';'                 { g_runtime->retro(*$2); delete $2; }
      | UNDO INT optional_var_list ';'{ g_runtime->undo($2, $3);delete $3; }
      | JMP INT ';' { g_runtime->jump($2); }
;

optional_expr:
      /* empty */
    | '[' expr_list ']'
    ;

expr_list:
      expression                            { delete $1; }
    | expr_list ',' expression              { delete $3; }
    ;

optional_var_list:
      /* empty */ {
          $$ = nullptr;
      }
    | '[' var_list ']' {
          $$ = $2;
      }
    ;

var_list:
      VAR {
          $$ = new std::vector<std::string>();
          $$->push_back(*$1);
          delete $1;
      }
    | var_list ',' VAR {
          $$ = $1;
          $$->push_back(*$3);
          delete $3;
      }
    ;

saved_list:
      VAR {
          $$ = new std::vector<std::string>();
          $$->push_back(*$1);
          delete $1;
      }
    | saved_list ',' VAR {
          $$ = $1;
          $$->push_back(*$3);
          delete $3;
      }

;

expression:
      VAR               { $$ = $1; }
    | INT               { $$ = new std::string(std::to_string($1)); }
    | FLOAT             { $$ = new std::string(std::to_string($1)); }
    | BOOL              { $$ = $1; }
    | expression '+' expression             { $$ = new std::string(*$1 + "+" + *$3); delete $1; delete $3; }
    | expression '-' expression             { $$ = new std::string(*$1 + "-" + *$3); delete $1; delete $3; }
    | expression '*' expression             { $$ = new std::string(*$1 + "*" + *$3); delete $1; delete $3; }
    | expression '/' expression             { $$ = new std::string(*$1 + "/" + *$3); delete $1; delete $3; }
    | expression '^' expression             { $$ = new std::string(*$1 + "^" + *$3); delete $1; delete $3; }
    | '(' expression ')'                    { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << std::endl;
}
