//
//  utilities.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/29/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include <algorithm>
#include "utilities.h"

using namespace std;

void printHelp () {
    cout << "Usage: russWAMex [OPTIONS...] file" << endl;
    cout << endl;
    cout << "Options" << endl;
    cout << "\t-h / --help\t\tPrint help and exit." << endl;
    cout << "\t--print-functor-table\tPrint the functor table and exit." << endl;
    cout << "\t--parse-only\t\tBuild functor table then exit." << endl;
}

char *getCmdOption (char** begin, char** end, const string &option) {
    char** it = find (begin, end, option);
    if (it != end && (it + 1) != end) {
        return *(it + 1);
    } else {
        return nullptr;
    }
}

bool cmdOptionExists (char** begin, char** end, const string &option) {
    return find (begin, end, option) != end;
}


