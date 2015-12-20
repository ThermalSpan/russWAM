//
//  output.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/18/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include <iostream>
#include "WAM.h"

using namespace std;

void WAM::panic (string message) {
    cout << "!!! PANIC !!!" << endl;
    cout << message << endl;

    exit (EXIT_FAILURE);
}

long WAM::HeapCellId (DataCell* pointer) {
    if (pointer == nullptr) {
        return -2;
    } 
  
    long dif = pointer - m_Heap;

    if (dif > HEAPSIZE || dif < 0) {
        return -1;
    } 
    else {
        return dif;
    }
}

void WAM::printCell (DataCell* cell) {
    cout << "\t| ";       
    if (cell == nullptr) {
        cout << "null";
    }
    else if (cell->tag == REF) {  
        cout << "REF: " << HeapCellId (cell->ref);
    }
    else if (cell->tag == STR) {
        cout << "STR: " << HeapCellId (cell->ref);
    }       
    else if (cell->tag == FUN || cell->tag == CON) {
        cout << m_functorTable->getName (cell->functorId) << "/";
        cout << m_functorTable->getArity (cell->functorId) << "\t"; 
    }
    else {
        cout << "What type is this?";
    }   
    cout << "|" << endl; 
}

void WAM::printHeap () {
 	cout << "HEAP:" << endl;   
    // TODO: someday when i have max H index again, put that here instead of 12, that's arbitrary.
    for (int i = 0; i < 12; i++) {
        cout << i;       
        printCell (&m_Heap[i]);
     }

	cout << endl;
}

void WAM::printArgRegisters () {
    int i;
 	cout << "ARGUMENT REGISTERS:" << endl;

    for (i = 1; i < ARGREGCOUNT; i++) {
        cout << i << "\t| ";       
        printCell (&m_GlobalArgRegisters[i]);           
    }

	cout << endl;
}

void WAM::printResultArg (int reg) {
    DataCell* cell = deref (&m_GlobalArgRegisters[reg]);
    recurPrint (cell);  
    cout << endl;
}

void WAM::recurPrint (DataCell* cell) {
    DataCell* fun = strDeref (deref (cell));
    
    if (fun == nullptr) {
        panic ("ERROR: Tried to recur print null functor");
    }

    int a = m_functorTable->getArity (fun->functorId);
    string* name = m_functorTable->getName (fun->functorId);

    cout << *name;
    if (a != 0) {
        cout << "(";
    }

    for (int i = 1; i <= a; i++) {
        recurPrint (&fun[i]);
        if (i != a) {
            cout << ",";
         }
    }

    if (a != 0) {
        cout << ")";
    }
 }

DataCell* WAM::strDeref (DataCell* cell) {
    DataCell* result;

    if (cell->tag == STR) {
        result = strDeref (cell->ref);
    }
    else if (cell->tag == FUN || cell->tag == CON) {
        result = cell;
    }
    else {
        result = nullptr;
    }

    return result;
}
