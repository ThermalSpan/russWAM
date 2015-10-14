//
//  rWAMparser.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/13/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "rWAMparser.h"

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
		std::cout << "Opened File: " << fileName << " " << yyin << std::endl;
    }

    yyparse (this);
}

extern "C" int yywrap () {
    return 1;
}

int yyerror (rWAMparser* p, const char* s) {
    std::cerr << s << std::endl;
    return 0;
}
