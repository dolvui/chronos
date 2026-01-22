%code requires {
#include <string>
#include <vector>

struct expr_ch;
struct type_ch;
}

%{
#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include "../src/runtime.hpp"
#include "../src/types/int_ch.hpp"
using namespace std;

extern Runtime* g_runtime;
extern int yylex();
void yyerror(const char* s);
%}

%union {
    expr_ch* expr;
    type_ch* value;
    std::string* str;
    int ival;
    double fval;
    bool bval;
    std::vector<type_ch*>* tlist;
    std::vector<std::string>* str_list;
}

%token <str> VAR
%token <ival> INT
%token <fval> FLOAT
%token <bval> BOOL

%token CREATE SAVE CHOOSE RETRO UNDO JMP

%type <expr> expression
%type <str_list> saved_list
%type <str_list> var_list
%type <str_list> optional_var_list

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
      CREATE VAR '=' expression ';' {
          type_ch* val = $4->eval(*g_runtime);delete $2;delete $4;delete val;
      }
    | SAVE VAR optional_expr ';' {
          std::cout << "Save state " << *$2 << std::endl;
          delete $2;
      }
    | CHOOSE saved_list ';' {
          std::cout << "Choose states: ";
          for (const auto& s : *$2) {
              std::cout << s << " ";
          }
          std::cout << std::endl;
          delete $2;
      }
    | RETRO VAR ';' {
          std::cout << "Retro to state " << *$2 << std::endl;
          delete $2;
      }
    | UNDO INT optional_var_list ';' {
          std::cout << "Undo " << $2 << " instructions";
          if ($3) {
              std::cout << " for vars: ";
              for (const auto& v : *$3) {
                  std::cout << v << " ";
              }
              delete $3;
          }
          std::cout << std::endl;
      }
    | JMP INT ';' {
          std::cout << "Jump " << $2 << " instructions" << std::endl;
      }
    ;

optional_expr:
      /* empty */
    | '[' expr_list ']'
    ;

expr_list:
      expression {
          delete $1;
      }
    | expr_list ',' expression {
          delete $3;
      }
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
      VAR {
          $$ = new var_expr(*$1);
          delete $1;
      }
    | INT {
          $$ = new int_literal($1);
      }
    | FLOAT {
          $$ = new float_literal($1);
      }
    | BOOL {
          $$ = new bool_literal($1);
      }
    | expression '+' expression {
          $$ = new add_expr($1, $3);
      }
    | expression '-' expression {
          $$ = new minus_expr($1, $3);
      }
    | expression '*' expression {
          $$ = new times_expr($1, $3);
      }
    | expression '/' expression {
          $$ = new divide_expr($1, $3);
      }
    | expression '^' expression {
          $$ = new power_expr($1, $3);
      }
    | '(' expression ')' {
          $$ = new parenthesis_expr($2);
      }
    ;

%%

void yyerror(const char *s) {
    std::cerr << "Parse error: " << s << std::endl;
}