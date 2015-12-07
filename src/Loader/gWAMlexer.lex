/*             
    gWAMlexer.lex
    russWAM

    Created by Russell Wilhelm Bentley on 12/7/15
    Copyright (c) 2015 Russell Wilhelm Bentley.
    Distributed under the MIT License.

    In conjunction with flex, this file will generate
    a lexer for GNU prolog's WAM code, as generated 
    by 'pl2wam'.
*/

%option nounput
%option yylineno

%{
    #include <math.h>
	#include <string>
    #include "../../src/Loader/gWAMparser.h"
    #include "gWAMgrammar.h"
%}

INTEGER ([1-9][0-9]*)|(0)
FLOAT [-+]?[0-9]*\.?[0-9]+
NAME [a-z][a-zA-Z0-9_]*

STRING \"[A-Za-z0-9_ ]+\"

%%

    /* Put Instructions */
"put_variable"                  { return TK_put_variable; }
"put_void"                      { return TK_put_void; }
"put_value"                     { return TK_put_value; }
"put_unsafe_value"              { return TK_put_unsafe_value; }
"put_atom"                      { return TK_put_atom; }            
"put_integer"                   { return TK_put_integer; }                
"put_float"                     { return TK_put_float; }            
"put_nil"                       { return TK_put_nil; }            
"put_list"                      { return TK_put_list; }            
"put_structure"                 { return TK_put_structure; }                

    /* Get Instructions */
"get_variable"                  { return TK_get_variable; }                
"get_value"                     { return TK_get_value; }            
"get_atom"                      { return TK_get_atom; }            
"get_integer"                   { return TK_get_integer; }                
"get_nil"                       { return TK_get_nil; }            
"get_list"                      { return TK_get_list; }            
"get_structure"                 { return TK_get_structure; }                

    /* Unify Instructions */
"unify_variable"                { return TK_unify_variable; }                    
"unify_void"                    { return TK_unify_void; }                
"unify_value"                   { return TK_unify_value; }                
"unify_local_value"             { return TK_unify_local_value; }                    
"unify_atom"                    { return TK_unify_atom; }                
"unify_integer"                 { return TK_unify_integer; }                
"unify_nil"                     { return TK_unify_nil; }            
"unify_list"                    { return TK_unify_list; }                
"unify_structure"               { return TK_unify_structure; }                    

   /* Control Instructions */
"allocate"                      { return TK_allocate; }            
"deallocate"                    { return TK_deallocate; }                
"math_load_value"               { return TK_math_load_value; }                    
"math_fast_load_value"          { return TK_math_fast_load_value; }                        
"call"                          { return TK_call; }        
"execute"                       { return TK_execute; }            
"proceed"                       { return TK_proceed; }            
"fail"                          { return TK_fail; }        
"label"                         { return TK_label; }        
"x"                             { return TK_x; }    
"y"                             { return TK_y; }    

    /* Choice Instructions */
"try_me_else"                   { return TK_try_me_else; }                
"retry_me_else"                 { return TK_retry_me_else; }                
"trust_me_else_fail"            { return TK_trust_me_else_fail; }                
"try"                           { return TK_try; }        
"retry"                         { return TK_retry; }        
"trust"                         { return TK_trust; }        
"get_current_choice"            { return TK_get_current_choice; }                        
"cut"                           { return TK_cut; }        
"soft_cut"                      { return TK_soft_cut; }            
"pragma_arity"                  { return TK_pragma_arity; }                
"switch_on_term"                { return TK_switch_on_term; }            
"switch_on_atom"                { return TK_switch_on_atom; }            
"switch_on_integer"             { return TK_switch_on_integer; }            
"switch_on_structure"           { return TK_switch_on_structure; }                

    /* Accessories */
"call_c"                        { return TK_call_c; }            
"foreign_call_c"                { return TK_foreign_call_c; }                    
"true"                          { return TK_true; }        
"false"                         { return TK_false; }        
"predicate"                     { return TK_predicate; }            
"static"                        { return TK_static; }             
"private"                       { return TK_private; }            
"monofile"                      { return TK_monofile; }            
"global"                        { return TK_global; }            
file_name.*$                    /* We're gonna ignore this for the moment... */


    /* Other Stuff */
[\(\)\/\:\[\]\,\.]             	{ return yytext[0]; }

{INTEGER}         {
    yylval->i = atoi (yytext);
    return TK_INT;
}

{FLOAT}         {
    yylval->f = atof (yytext);
    return TK_FLOAT;
}

{NAME}          {
    yylval->s = new std::string (yytext);
    return TK_NAME;
}

    /* Ignore Header Information, and everything else */
%.*$	
[ \t\n]*
.

%%





