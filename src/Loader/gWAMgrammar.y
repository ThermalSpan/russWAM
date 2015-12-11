/*             
    gWAMgrammar.y
    russWAM

    Created by Russell Wilhelm Bentley on 12/7/15
    Copyright (c) 2015 Russell Wilhelm Bentley.
    Distributed under the MIT License.

    This file, used with bison, will generate a parser
    for GNU Prolog's WAM code, as produced by 'pl2wam' 
*/

%{
    #include <list>
    #include "../../src/WAM/types.h"
    #include "../../src/Loader/gWAMsyntax.h"
    #include "../../src/Loader/gWAMparser.h"
%}

%union {
    int i;
    double f;
    std::string* s;
    PredicateNode* predNode;
    InstrNode* instrNode;
    FunctionLabel* funcLabel;
    Reg* reg;
    Functor* functor;
    std::list <PredicateNode*> predList;
    std::list <InstrNode*>* instrList;
    std::list <FunctionLabel*> listList;
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
%token <i> TK_INT
%token <f> TK_FLOAT
%token <s> TK_NAME

/* Grammar Only Tokens */
%type <predList> PredicateList
%type <predNode> Predicate
%type <instrList> InstrList
%type <instrList> OneOrMoreInstr
%type <instrNode> Instr
%type <reg> Reg
%type <labelList> OneOrMoreAtoms
%type <funcLabel> Atom
%type <i> OneOrMoreIntL
%type <i> IntL
%type <labelList> OneOrMoreStrs
%type <funcLabel> Str
%type <functor> Functor
%type <i> TermL

%%

Top: PredicateList  { parser->setPredicateList ($1); }
;

PredicateList: Predicate PredicateList { $2->push_front ($1); $$ = $2; }
             |                         { $$ = new list <PredicateNode*> (); } 
;

Predicate: TK_predicate '(' Functor ',' TK_INT ',' TK_static ',' TK_private ',' TK_monofile ',' TK_global ',' InstrList ')' '.' {$$ = new Predicate ($3, $15); } 
;

InstrList: '[' OneOrMoreInstr ']' { $$ = $2; }
;		 

OneOrMoreInstr: Instr { $$ = new list <InstrNode*> (); $$->push_back ($1); }
              | Instr ',' OneOrMoreInstr { $3->push_front ($1); $$ = $3; }
;

Reg: TK_x '(' TK_INT ')' { $$ = new Reg ($3, GLOBAL); }
   | TK_y '(' TK_INT ')' { $$ = new Reg ($3, LOCAL); }
;

OneOrMoreAtoms: Atom   { $$ = new list <Functor*> (); $$->push_back($1); }
              | Atom ',' OneOrMoreAtoms { $3->push_front ($1); $$ = $3; }
;

Atom: '(' TK_NAME ',' TK_INT ')' { $$ = new FunctorLabel ($2, 0, $4); }
;

OneOrMoreIntL: IntL {}
             | IntL ',' OneOrMoreIntL {}
;

IntL: '(' TK_INT ',' TK_INT ')' {}
;

OneOrMoreStrs: Str { $$ = new list <Functor*> (); $$->push_back ($1); }
             | Str ',' OneOrMoreStrs {}
;             
             
Str: '(' Functor ',' TK_INT ')' { $$ = new FunctorLabel ($2, $3); }
;

TermL: TK_INT { $$ = $1; }
	 | TK_fail { $$ = -1; }
;

Functor: TK_NAME '/' TK_INT { $$ = new Functor ($1, $3); }
;

Instr: TK_put_variable '(' Reg ',' TK_INT ')'  {}
| TK_put_void '(' TK_INT ')'  {}
| TK_put_value  '(' Reg ',' TK_INT ')' {}
| TK_put_unsafe_value '(' TK_y '(' TK_INT ')' ',' TK_INT ')'  {}
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
| TK_label '(' TK_INT ')'           { }
| TK_try_me_else '(' TK_INT ')'   {}
| TK_retry_me_else '(' TK_INT ')' {}
| TK_trust_me_else_fail  {}
| TK_try '(' TK_INT ')'   {}
| TK_retry '(' TK_INT ')' {}
| TK_trust '(' TK_INT ')' {}
| TK_get_current_choice {}
| TK_cut    {}
| TK_soft_cut   {}
| TK_pragma_arity   {}
| TK_switch_on_term '(' TermL ',' TermL ',' TermL ',' TermL ',' TermL ')' {}
| TK_switch_on_atom '(' '[' OneOrMoreAtoms ']' ')' {}
| TK_switch_on_integer '(' '[' OneOrMoreIntL ']' ')' {}
| TK_switch_on_structure '(' '[' OneOrMoreStrs ']' ')' {}
| TK_call_c {}
| TK_foreign_call_c {}
;
