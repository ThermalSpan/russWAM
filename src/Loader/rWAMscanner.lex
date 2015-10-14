/*             
    rWAMscanner.lex
    russWAM

    Created by Russell Wilhelm Bentley on 10/15/15
    Copyright (c) 2015 Russell Wilhelm Bentley.
    Distributed under the MIT License.

    This is a lex file for my version of WAM code. 
    It is heavily influenced by 
    "Warren's Abstract Machine: A Tutorial Reconstruction" by 
    Hassan Ait-Kaci.
*/

%{
    #include <math.h>
    #include "../../src/Loader/rWAMparser.h"
    #include "rWAMgrammar.h"
%}

INTEGER ([1-9][0-9]*)|(0)
FUNCTOR [a-z][a-zA-Z0-9_]*

STRING [A-Za-z0-9_]+

%%

    /* Put           */
"put_variable"          { return P_VARIABLE; }
"put_value"             { return P_VALUE; }
"put_unsafe_value"      { return P_UNS_VALUE; }
"put_structure"         { return P_STRUCTURE; }
"put_list"              { return P_LIST; }
"put_constant"          { return P_CONSTANT; }
    
    /* Set          */
"set_variable"          { return S_VARIABLE; }
"set_value"             { return S_VALUE; }
"set_local_value"       { return S_LCL_VALUE; }
"set_constant"          { return S_CONSTANT; }
"set_void"              { return S_VOID; }
    
    /* Get          */
"get_variable"          { return G_VARIABLE; }
"get_value"             { return G_VALUE; }
"get_strucutre"         { return G_STRUCTURE; }
"get_list"              { return G_LIST; }
"get_constant"          { return G_CONSTANT; }

    /* Unify        */
"unify_variable"        { return U_VARIABLE; }
"unify_value"           { return U_VALUE; }
"unify_local_constant"  { return U_LCL_CONSTANT; }
"unify_constant"        { return U_CONSTANT; }
"unify_void"            { return U_VOID; }

    /* Control      */
"allocate"              { return ALLOCATE; }
"deallocate"            { return DEALLOCATE; }
"call"                  { return CALL; }
"execute"               { return EXECUTE; }
"proceed"               { return PROCEED; }
    
    /* Indexing     */
"switch_on_term"        { return SW_TERM; }
"switch_on_constant"    { return SW_CONSTANT; }
"switch_on_structure"   { return SW_STRUCTURE; }
    
    /* Choice       */
"try_me_else"           { return TRY_ME_ELSE; }
"retry_me_else"         { return RETRY_ME_ELSE; }
"trust_me"              { return TRUST_ME; }
"try"                   { return TRY; }
"retry"                 { return RETRY; }
"trust"                 { return TRUST; }

    /* Cut          */        
"neck_cut"              { return NECK_CUT; }
"get_level"             { return GET_LEVEL; }
"cut"                   { return CUT; }

    /* Accessories  */
"printHeap"             { return PRINT_HEAP; }
"printArgRegisters"     { return PRINT_ARG_REGISTERS; }
"printResultArg"        { return PRINT_RESULT_ARG;}
"write"                 { return WRITE_OUT; }
"label"                 { return LABEL; }
"/"                     { return DIV; }
":"                     { return COLON; }
\"                      { return QUOTE; }

    /* Other stuff  */
{INTEGER}         {
    yylval->i = atoi (yytext);
    return INT;
}

{FUNCTOR}         {
    yylval->s = yytext;
    return FUNCTOR;
}

{STRING}          {
    yylval->s = yytext;
    return STRING;
}

    /* Ignore Comments, and everything else */
\/\/.*$
.


