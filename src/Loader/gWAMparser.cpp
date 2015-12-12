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

void gWAMparser::run (const string &fileName) {
    yyin = fopen (fileName.c_str (), "r");
    yyparse (this);
    fclose (yyin);

	FunctorTable functorTable;
	if (m_status && m_predList != nullptr) {
		bool semResult = true;
		// Semantic pass 1
        cout << "Starting sem pass 1" << endl;
		for (auto it = m_predList->begin(); it != m_predList->end(); it++) {
            cout << "Sem pass 1 : " << *((*it)->getName()) << endl;
			semResult = semResult && (*it)->passOne (functorTable);
		}

		// Semantic pass 2
        cout << "Starting sem pass 2" << endl;
		for (auto it = m_predList->begin(); it != m_predList->end(); it++) {
            cout << "Sem pass 2 : " << *((*it)->getName()) << endl;
			semResult = semResult && (*it)->passTwo (functorTable);
		}

		cout << "Semantic passes done: " << semResult << endl;
        delete (m_predList);
	} else {
		cout << "Parse Failure" << endl;
	}

    cout << "Done Parsing!" << endl;
}

void gWAMparser::setPredList (list <PredicateNode*>* predList) {
    m_predList = predList;
    cout << "Pred List set ";
    if (m_predList != nullptr) {
        cout << "and its non null";
    } else {
        cout << "and its null";
    }
    cout << endl;
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
