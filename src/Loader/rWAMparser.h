//
//  rWAMparser.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "../WAM/types.h"
#include "../WAM/FunctorTable.h"

class rWAMparser {
public:
    rWAMparser ();
    
    ~rWAMparser ();

    void run (const char* fileName = 0);

    void success () { m_status = true; }

    bool status () { return m_status; }

    void passString (char* s);

	void addFunctor (int arity);

	void addInstruction (OpCode op, int a = -1, int b = -1, int c = -1);

    void addStringInstr (OpCode op);

    void addFunctorInstr (OpCode op, int arity, int b = -1, int c = -1);

	void setTableCode (FunctorTable* table, WAMword* code, StrVec* stringTable);

protected:
	
	FunctorTable* m_FunctorTable;

	WAMword* m_Code;	

    StrVec* m_StringTable;

    int m_codeIndex;

    int m_stringIndex;

    bool m_status;

    string m_String;
};
