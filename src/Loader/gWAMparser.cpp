//
//  gWAMparser.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/7/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "gWAMparser.h"

using namespace std;

gWAMparser::gWAMparser () {
    m_status = false;
}

gWAMparser::~gWAMparser () {

}

void gWAMparser::run (const string &fileName) {
    yyin = fopen (fileName.c_str (), "r");
    yyparse (this);
    fclose (yyin);
}

int yyerror (gWAMparser* p, const char* s) {
    cerr << s << endl;
    cerr << "Error occured near line: " << yyget_lineno () << endl;
    return 0;
}

int yywrap () {
    return 1;
}
