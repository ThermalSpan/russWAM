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

    // Pass the WAM file to the parser
    string wamFileName (".wam");
    wamFileName.insert (0, fileName, 0,  fileName.size() - 3);
    cout << "pl2wam generated " << wamFileName << endl; 
	gWAMparser parser;
	parser.run (wamFileName);
	
	cout << "exiting normally?" << endl;
    return 0;
}
