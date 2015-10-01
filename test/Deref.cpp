//
//  Deref.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/1/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "../src/stdafx.h"
#include "../src/WAM/Engine.h"

int main () {
    WAM w;

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

    w.printHeap();
    
    cout << "DEREFERENCING:" << endl;
    for (int i = 0; i < 11; i++) {
        int t = w.deref (i);
        cout << "Cell " << i << " Refers to Cell " << t << endl;
    }

    return 0;
}
