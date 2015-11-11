//
//  Driver.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/6/2015
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "types.h"
#include "WAMdebug.h"
#include "FunctorTable.h"

class Driver {
public:
    Driver (WAMword* code, FunctorTable* functorTable, StrVec* stringTable, int size);

    ~Driver ();

    void run ();
 
protected:
	// Protected Methods
	RtnCode ExecuteInstruction (WAMword* instr);

    void incr ();
	
	// Protected Variables
    int m_size;

	FunctorTable* m_FunctorTable;

	StrVec*	m_StringTable;

    WAMdebug* m_wam;

    WAMword* m_Code;

    WAMword* m_Preg;

    WAMword* m_CPreg;
};
