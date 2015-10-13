/*             
    rWAMgrammar.y
    russWAM

    Created by Russell WIlhelm Bentley on 10/15/15
    Copyright (c) 2015 Russell Wilhelm Bentley.
    Distributed under the MIT License.

    This is a bison (yacc) grammar file for my version of WAM code. 
    It is heavily influenced by 
    "Warren's Abstract Machine: A Tutorial Reconstruction" by 
    Hassan Ait-Kaci.
*/

%{
    #include "../../src/Loader/rWAMparser.h"
%}

%union {
    int i;
    char* s;
}

%{
    int yyerror (rWAMparser* parser, const char* s);
    int yylex (YYSTYPE*);
%}

%defines
%pure-parser
%parse-param { rWAMparser* parser }
%expect 0

%token P_VARIABLE P_VALUE P_UNS_VALUE
%token P_STRUCTURE P_LIST P_CONSTANT

%token S_VARIABLE S_VALUE S_LCL_VALUE
%token S_CONSTANT S_VOID

%token G_VARIABLE G_VALUE G_STRUCTURE
%token G_LIST G_CONSTANT

%token U_VARIABLE U_VALUE U_LCL_CONSTANT
%token U_CONSTANT U_VOID

%token ALLOCATE DEALLOCATE CALL
%token EXECUTE PROCEED

%token SW_TERM SW_CONSTANT SW_STRUCTURE

%token TRY_ME_ELSE RETRY_ME_ELSE TRUST_ME
%token TRY RETRY TRUST

%token NECK_CUT GET_LEVEL CUT

%token <i> INT
%token <s> FUNCTOR
%token <s> STRING

%token PRINT_HEAP PRINT_ARG_REGISTERS PRINT_RESULT_ARG
%token WRITE_OUT QUOTE

%%

Top: 
;

%%
