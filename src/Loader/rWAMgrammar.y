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

%token <i> INT
%token <s> FUNCTOR
%token <s> STRING

%token PRINT_HEAP PRINT_ARG_REGISTERS PRINT_RESULT_ARG
%token WRITE_OUT QUOTE LABEL DIV COLON

%%

Top: labelList      { parser->success (); }
;

labelList: labelSection labelListTail;

labelListTail: %empty | labelSection labelListTail;

labelSection: label instrList;

label: LABEL functor DIV INT COLON { parser->addFunctor ($4); }

instrList: instr instrListTail;

instrListTail: %empty | instr instrListTail;

instr:
    P_STRUCTURE functor DIV INT INT     { parser->addFunctorInstr (OC_put_structure, $4, $5); }
|   S_VARIABLE INT                      { parser->addInstruction (OC_set_variable, $2); }
|   S_VALUE INT                         { parser->addInstruction (OC_set_value, $2);}
|   G_STRUCTURE functor DIV INT INT     { parser->addFunctorInstr (OC_get_structure, $4, $5); }
|   U_VARIABLE                          { parser->addInstruction (OC_unify_variable); }
|   U_VALUE                             { parser->addInstruction (OC_unify_value); }
|   WRITE_OUT QUOTE string QUOTE        { parser->addStringInstr (OC_write); }
|   CALL functor DIV INT                { parser->addFunctorInstr (OC_call, $4); } 
|   PRINT_HEAP                          { parser->addInstruction (OC_printHeap); }
|   PRINT_ARG_REGISTERS                 { parser->addInstruction (OC_printArgRegisters); }
|   PRINT_RESULT_ARG INT                { parser->addInstruction (OC_printResultArg, $2); }
;

functor: FUNCTOR                        { cout << "Y Functor: " << string ($1) << endl; parser->passString ($1); }
;

string: STRING                          { parser->passString ($1); }
;
%%







