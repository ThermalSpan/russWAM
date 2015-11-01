//
//  rWAMparser.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "rWAMparser.h"

using namespace std;

rWAMparser::rWAMparser () {
    m_status = false;
}

rWAMparser::~rWAMparser () {
    
}   
    extern int yyget_lineno ();

void rWAMparser::run (const char* fileName) {
    extern int yyparse (rWAMparser*);    
    extern FILE* yyin;
    extern int yydebug;
    
    if (fileName != 0) {
        yyin = fopen (fileName, "r");
		cout << "Opened File: " << fileName << " " << yyin << endl;
    }

    yyparse (this);
}

extern "C" int yywrap () {
    return 1;
}

int yyerror (rWAMparser* p, const char* s) {
    cerr << s << endl;
    cerr << "Error occured near line: " << yyget_lineno () << endl;
    return 0;
}

void rWAMparser::passString (char* s) {
    m_String = string (s);
}

int rWAMparser::mapFunctor (int arity) {
	int id = m_FunctorTable->addFunctor (m_String, arity, nullptr);
    return id;
}

void rWAMparser::addLabel (int arity) {
    m_FunctorTable->addFunctor (m_String, arity, &m_Code[m_codeIndex]);
}

void rWAMparser::addInstruction (OpCode op, int a, int b, int c) {
    if (op == OC_unify_variable) {
        cout << "parser: unify_variable " << a << endl;
    }

    m_Code[m_codeIndex].op = op;
    m_Code[m_codeIndex].a = a;
    m_Code[m_codeIndex].b = b;
    m_Code[m_codeIndex].c = c;
    m_codeIndex++;
}

void rWAMparser::addStringInstr (OpCode op) {
    m_Code[m_codeIndex].op = op;
    m_Code[m_codeIndex].a = m_stringIndex;
    m_StringTable->push_back(m_String);
    m_stringIndex++; 
    m_codeIndex++; 
}

void rWAMparser::addFunctorInstr (OpCode op, int arity, int b, int c) {
    if (op == OC_get_structure) {
        cout << "parser: get_structure" << endl;
    }
    int id = mapFunctor (arity);
    if (id == -1) {
        cout << "Cannont find functor: " << string (m_String) << " / " << arity << endl;
    }
    else {
        addInstruction (op, id, b, c);       
    }
}

void rWAMparser::setTableCode (FunctorTable* table, WAMword* code, StrVec* stringTable) {
	m_FunctorTable = table;
	m_Code = code;
    m_StringTable = stringTable;
	m_codeIndex = 0;
    m_stringIndex = 0;
}
