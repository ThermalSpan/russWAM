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
#include "utilities.h"
#include "Loader/gWAMparser.h"
#include "WAM/WAM.h"

using namespace std;

int main (int argc, char* argv[]) {
    // Does the User want the help menu?
    if (cmdOptionExists (argv, argv + argc, "-h") || cmdOptionExists (argv, argv + argc, "--help")) {
        printHelp ();
        exit (0);
    }

    // Get the name of the file, which should be the last argument
    string fileName;
    if (argc > 1) {
        fileName.assign (argv[argc - 1]);
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

    // Should we print the functor table?
    if (cmdOptionExists (argv, argv + argc, "--print-functor-table")) {
        functorTable.debugPrint ();
        exit (0);
    }
    // Should we exit now?
    if (cmdOptionExists (argv, argv + argc, "--parse-only")) {
        exit (0);
    }

    // Build the WAM and run!
    bool succf;
    WAM* wam = new WAM (&functorTable);
    string* q  = new string ("query");
    succf = wam->run (q, 1);
    if (succf) {
        cout << "yes." << endl;
        wam->printResultArg (0);
        while (wam->runBacktrack ()) {
            wam->printResultArg (0);
        }
    } else {
        cout << "no." << endl;
    }

    delete (q);
    delete (wam);
    return 0;
}
