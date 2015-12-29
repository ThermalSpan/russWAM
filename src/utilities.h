//
//  utilities.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/29/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include <stdlib.h>
#include <iostream>

using namespace std;

//
// Prints a formatted help menu to standard out
//
void printHelp ();

//
// Returns the option next to a flag
// src: http://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
//
char *getCmdOption (char** begin, char** end, const string &option);

//
// Returns whether or not a flag is there
// src: http://stackoverflow.com/questions/865668/how-to-parse-command-line-arguments-in-c
//
bool cmdOptionExists (char** begin, char** end, const string &option);

