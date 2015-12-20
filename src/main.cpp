//
//  main.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include <stdlib.h>
#include <iostream>
#include "Loader/gWAMparser.h"
#include "WAM/WAM.h"

using namespace std;

int main(int argc, const char * argv[]) {
    // Get the name of the file
    string fileName;
   	if (argc == 2) {
      	fileName.assign(argv[1]);
        cout << "Input: " << fileName << endl;
    } else {
        cerr << "No input file given." << endl;
        return 1;
    }

    // Check that the file is a prolog source file
    if (fileName.compare (fileName.size() - 3, 3, ".pl") != 0 ) {
        cerr << "Input file is not a prolog source file (*.pl)" << endl;
        return 1;
    }

    // Pass the file to pl2wam and check the return value
    string command = "pl2wam --no-redef-error --no-call-c " + fileName;
    int ret = system (command.c_str ());
    if (ret != 0) {
        cerr << "pl2wam returned " << ret << endl;
        return 1;
    }

    // Pass the WAM file to the parser and build the Functor Table
    FunctorTable functorTable;
    string wamFileName (".wam");
    wamFileName.insert (0, fileName, 0,  fileName.size() - 3);
    cout << "pl2wam generated " << wamFileName << endl; 
	gWAMparser parser;
	parser.run (wamFileName, functorTable);

	// Build the WAM an run!
	bool succf;
	WAM* wam = new WAM (&functorTable);
	string* q  = new string ("query");
	succf = wam->run (q, 1);
	if (succf) {
		cout << "It worked! YES!" << endl;	
		wam->printResultArg (0);
	} else {
		cout << "run failed" << endl;
	}
	
	delete (q);
	delete (wam);
    return 0;
}
