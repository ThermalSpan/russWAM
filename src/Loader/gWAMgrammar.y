/*             
    gWAMgrammar.y
    russWAM

    Created by Russell Wilhelm Bentley on 10/15/15
    Copyright (c) 2015 Russell Wilhelm Bentley.
    Distributed under the MIT License.

    This file, used with bison, will generate a parser
    for GNU Prolog's WAM code, as produced by 'pl2wam' 
*/

%{
    #include "../../src/Loader/gWAMparser.h"
%}

%union {
    int i;
    char* s;
    double f;
    string* s;
}

%code {
    int yyerror (gWAMparser* parser, const char* s);
    int yylex (YYSTYPE*);

    using namespace std;
}

%defines
%pure-parser
%parse-param { gWAMparser* parser }
%define parse.error verbose
%expect 0

/*  Put Instructions */
%token TK_put_variable
%token TK_put_void
%token TK_put_value
%token TK_put_unsafe_value
%token TK_put_atom
%token TK_put_integer
%token TK_put_float
%token TK_put_nil
%token TK_put_list
%token TK_put_structure

/*  Get Instructions */
%token TK_get_variable
%token TK_get_value
%token TK_get_atom
%token TK_get_integer
%token TK_get_nil
%token TK_get_list
%token TK_get_structure

/* Unify Instructions */
%token TK_unify_variable
%token TK_unify_void
%token TK_unify_value
%token TK_unify_local_value
%token TK_unify_atom
%token TK_unify_integer
%token TK_unify_nil
%token TK_unify_list
%token TK_unify_structure

/* Control Instructions */
%token TK_allocate
%token TK_deallocate
%token TK_math_load_value
%token TK_math_fast_load_value
%token TK_call
%token TK_execute
%token TK_proceed
%token TK_fail
%token TK_label
%token TK_x
%token TK_y

/*  Choice Instructions */
%token TK_try_me_else
%token TK_retry_me_else
%token TK_trust_me_else_fail
%token TK_try
%token TK_retry
%token TK_trust
%token TK_get_current_choice
%token TK_cut
%token TK_soft_cut
%token TK_pragma_arity
%token TK_switch_on_term
%token TK_switch_on_atom
%token TK_switch_on_integer
%token TK_switch_on_structure

/* Accessories */
%token TK_call_c
%token TK_foreign_call_c
%token TK_true;
%token TK_false;
%token TK_predicate
%token TK_static
%token TK_private
%token TK_monofile
%token TK_global

/*  Other Stuff */
%token '(' ')' '[' ']' '.' ',' ':' '/'
%token TK_INT
%token TK_NAME

/* Grammar Only Tokens */

%%

Top: PredicateList  { parser->done (); }
;

PredicateList: Predicate PredicateList {}
             |                         {} 
;

Predicate: TK_predicate '(' TK_NAME ',' TK_INT ',' TK_STATIC ',' TK_PRIVATE ',' TK_MONOFILE ',' TK_GLOBAL ',' InstrList ')' '.'
;

OneOrMoreInstr: Instr
              | Instr ',' OneOrMoreInstr
;

Bool: TK_true
    | TK_false
;

Reg: TK_x '(' TK_NAME ')'
   | TK_y '(' TK_NAME ')'
;

OneOrMoreAtoms: Atom  
              | Atom ',' OneOrMoreAtoms
;

Atom: '(' TK_NAME ',' TK_INT ')'
;

OneOrMoreIntL: IntL
             | IntL ',' OneOrMoreInt
;

IntL: '(' TK_INT ',' TK_INT ')'
;

OneOrMoreStrs: Str
             | Str ',' OneOrMoreStrs
;             
             
Str: '(' Functor ',' TK_INT ')'
;

Functor: TK_NAME '/' TK_INT
;

Instr: TK_put_variable '(' Reg ',' TK_INT ')'  {}
| TK_put_void '(' TK_INT ')'  {}
| TK_put_value  '(' Reg ',' TK_INT ')' {}
| TK_put_unsafe_value '(' TK_Y '(' TK_INT ')' ',' TK_INT ')'  {}
| TK_put_atom '(' TK_NAME ',' TK_INT ')' {}
| TK_put_integer '(' TK_INT ',' TK_INT ')'   {}
| TK_put_float '(' TK_FLOAT ',' TK_INT ')'  {}
| TK_put_nil '(' TK_INT ')'    {}
| TK_put_list '(' TK_INT ')'  {}
| TK_put_structure '(' Functor ',' TK_INT ')'   {}
| TK_get_variable  '(' Reg ',' TK_INT ')' {}
| TK_get_value  '(' Reg ',' TK_INT ')' {}
| TK_get_atom '(' TK_NAME ',' TK_INT ')'  {}
| TK_get_integer '(' TK_INT ',' TK_INT ')'   {}
| TK_get_nil '(' TK_INT ')'     {}
| TK_get_list '(' TK_INT ')' {}
| TK_get_structure  '(' Functor ',' TK_INT ')' {}
| TK_unify_variable '(' Reg ')' {}
| TK_unify_void '(' TK_INT ')' {}
| TK_unify_value '(' TK_INT ')' {}
| TK_unify_local_value '(' TK_INT ')'  {}
| TK_unify_atom '(' TK_NAME ')' {}
| TK_unify_integer  '(' TK_NAME ')' {}
| TK_unify_nil {}
| TK_unify_list {}
| TK_unify_structure '(' Functor ')' {}
| TK_allocate '(' TK_INT ')' {}
| TK_deallocate {}
| TK_math_load_value '(' TK_INT ',' TK_INT ')'   {}
| TK_math_fast_load_value '(' TK_INT ',' TK_INT ')'  {}
| TK_call '(' Functor ')' {}
| TK_execute '(' Functor ')' {}
| TK_proceed                        {  }
| TK_fail {}
| TK_label '(' TK_INT ')'           { $$ = new LabelNode ($3); }
| TK_try_me_else '(' TK_INT ')'   {}
| TK_retry_me_else '(' TK_INT ')' {}
| TK_trust_me_else_fail  {}
| TK_try    {}
| TK_retry  {}
| TK_trust  {}
| TK_get_current_choice {}
| TK_cut    {}
| TK_soft_cut   {}
| TK_pragma_arity   {}
| TK_switch_on_term '(' TermL ',' TermL ',' TermL ',' TermL ',' TermL ')'
| TK_switch_on_atom '(' '[' OneOrMoreAtoms ']' ')'
| TK_switch_on_integer '(' '[' OneOrMoreIntL ']' ')'
| TK_switch_on_structure '(' '[' OneOrMoreStrs ']' ')'
| TK_call_c {}
| TK_foreign_call_c {}
;
