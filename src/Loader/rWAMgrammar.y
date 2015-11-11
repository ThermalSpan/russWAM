/*             
    rWAMgrammar.y
    russWAM

    Created by Russell Wilhelm Bentley on 10/15/15
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

%code {
    int yyerror (rWAMparser* parser, const char* s);
    int yylex (YYSTYPE*);

    using namespace std;
}

%defines
%pure-parser
%parse-param { rWAMparser* parser }
%define parse.error verbose
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

%token <i> INT REGTYPE
%token <s> FUNCTOR
%token <s> STRING

%token '(' ')' '/' ':'

%token PRINT_HEAP PRINT_ARG_REGISTERS PRINT_RESULT_ARG PRINT_HEAP_CELL UNIFY_HEAP_CELLS
%token WRITE_OUT LABEL TERMINATE

%%

Top: instrList                          { parser->success (); }
;

instrList: instr instrListTail;

instrListTail: %empty | instr instrListTail;

instr:
    LABEL functor '/' INT ':'           { parser->addLabel ($4); } 
|   P_VARIABLE REGTYPE '(' INT ')' INT  { parser->addInstruction (OC_put_variable, $2, $4, $6); }
|   P_VALUE REGTYPE '(' INT ')' INT     { parser->addInstruction (OC_put_value, $2, $4, $6); } 
|   P_STRUCTURE functor '/' INT INT     { parser->addFunctorInstr (OC_put_structure, $4, $5); }
|   S_VARIABLE INT                      { parser->addInstruction (OC_set_variable, $2); }
|   S_VALUE INT                         { parser->addInstruction (OC_set_value, $2);}
|   G_VARIABLE REGTYPE '(' INT ')' INT  { parser->addInstruction (OC_get_variable, $2, $4, $6); }
|   G_VALUE REGTYPE '(' INT ')' INT     { parser->addInstruction (OC_get_value, $2, $4, $6); }
|   G_STRUCTURE functor '/' INT INT     { parser->addFunctorInstr (OC_get_structure, $4, $5); }
|   U_VARIABLE INT                      { parser->addInstruction (OC_unify_variable, $2); }
|   U_VALUE INT                         { parser->addInstruction (OC_unify_value, $2); }
|   WRITE_OUT string        			{ parser->addStringInstr (OC_write); }
|   CALL functor '/' INT                { parser->addFunctorInstr (OC_call, $4); } 
|   PRINT_HEAP                          { parser->addInstruction (OC_printHeap); }
|   PRINT_ARG_REGISTERS                 { parser->addInstruction (OC_printArgRegisters); }
|   PRINT_RESULT_ARG INT                { parser->addInstruction (OC_printResultArg, $2); }
|   PRINT_HEAP_CELL INT                 { parser->addInstruction (OC_printHeapCell, $2); }
|   UNIFY_HEAP_CELLS INT INT            { parser->addInstruction (OC_unifyHeapCells, $2, $3); }
|   TERMINATE                           { parser->addInstruction (OC_terminate); }
|   PROCEED                             { parser->addInstruction (OC_proceed); }
;

functor: FUNCTOR                        { parser->passString ($1); }
;

string: 
	  STRING                          { parser->passString ($1); }
;
%%







