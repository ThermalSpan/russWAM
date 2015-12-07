//
//  gWAMparser.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/7/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <iostream>
#include "../WAM/types.h"

using namespace std;

class gWAMparser;

// Bison Parser Methods
// --------------------
extern int yyget_lineno ();
extern int yyparse (gWAMparser* p);
int yyerror (gWAMparser* p, const char* s);

// Bison Parser Variables
// ----------------------
extern FILE* yyin;
extern int yydebug;

// Bison Interface
// --------------- 
// The bison parser calls this when it reaches EOF, if 1 (true) then function terminates
extern "C" int yywrap ();

class gWAMparser {
protected:
    bool m_status;

public:
    gWAMparser ();
    
    ~gWAMparser ();

    void run (const string &fileName);

    bool getStatus () { return m_status; }

    void setStatus (bool status) { m_status = status; }

};
