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
    return 0;
}

void rWAMparser::passString (char* s) {
    m_String = string (s);
}

void rWAMparser::addFunctor (int arity) {
	int id = m_FunctorTable->addFunctor (m_String, arity, &m_Code[m_codeIndex]);
    //cout << "Functor " << m_String << "/" << arity << " had Id: " << id << endl;
}

void rWAMparser::addInstruction (OpCode op, int a, int b, int c) {
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
    int id = m_FunctorTable->getFunctorId(m_String, arity);
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
