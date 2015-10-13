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

using namespace std;

int main(int argc, const char * argv[]) {
    WAMdebug w;

    w.addString (0, "f");
    w.addString (1, "h");
    w.addString (2, "p");
    
    w.put_structure (1, 2, 3);
    w.set_variable (2);
    w.set_variable (5);
    w.put_structure (0, 1, 4);
    w.set_value (5);
    w.put_structure (2, 3, 1);
    w.set_value (2);
    w.set_value (3);
    w.set_value (4);

    w.printHeap ();
    w.printArgRegisters ();

    return 0;
}
