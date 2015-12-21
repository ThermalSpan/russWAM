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
    m_status = true;
    m_predList = nullptr;
}

gWAMparser::~gWAMparser () {

}

void gWAMparser::run (const string &fileName, FunctorTable &functorTable) {
    yyin = fopen (fileName.c_str (), "r");
    yyparse (this);
    fclose (yyin);

    if (m_status && m_predList != nullptr) {
        bool semResult = true;
        // Semantic pass 1
        for (auto it = m_predList->begin(); it != m_predList->end(); it++) {
            semResult = (*it)->passOne (functorTable) && semResult;
        }

        // Semantic pass 2
        for (auto it = m_predList->begin(); it != m_predList->end(); it++) {
            semResult = (*it)->passTwo (functorTable) && semResult; // Heh, don't let shortcircuit prevent all errors from surfacing
            delete (*it);
        }

        cout << "Parsed Succesfully" << endl;
        delete (m_predList);
    } else {
        cout << "Parse Failure" << endl;
    }

}

void gWAMparser::setPredList (list <PredicateNode*>* predList) {
    m_predList = predList;
}

int yyerror (gWAMparser* p, const char* s) {
    cerr << s << endl;
    cerr << "Error occured near line: " << yyget_lineno () << endl;
    p->setStatus (false);
    return 0;
}

int yywrap () {
    return 1;
}
