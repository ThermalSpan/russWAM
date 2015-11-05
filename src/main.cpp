//
//  main.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "stdafx.h"
#include "WAM/WAMdebug.h"
#include "Loader/rWAMparser.h"
#include "WAM/Driver.h"

using namespace std;

int main(int argc, const char * argv[]) {
    const char* fn = 0;
   	if (argc == 2) {
      	fn = argv[1];
        cout << "Input: " << fn << endl;
    }
   	rWAMparser p;

    FunctorTable* funTab = new FunctorTable ();
    StrVec* strTab = new StrVec ();
    WAMword* codeArray = (WAMword*) malloc (4096 * sizeof(WAMword));

    p.setTableCode(funTab, codeArray, strTab);

 	p.run(fn);

   	if (p.status ()) {
     	cout << "Input OK" << endl;
        //cout << "FunctorTable size: " << funTab->getTableSize () << endl;

		Driver dr (codeArray, funTab, strTab, 400);
		dr.run ();		

   	} else 
     	cout << "Input BAD" << endl;

	free (codeArray);
    delete (strTab);
    delete (funTab);
    
    return 0;
}
