//
//  WAMdebug.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAMdebug.h"

WAMdebug::WAMdebug (FunctorTable* functorTable) : WAM (functorTable) {

}

WAMdebug::~WAMdebug () {

}

long WAMdebug::ptrToHeapCell (DataCell* pointer) {
    long dif = pointer - getBase ();
    
    if (dif > MEMSIZE || dif < 0) {
        return -1;
    } 
    else {
        return dif;
    }
}

void WAMdebug::printCell (DataCell* cell) {
    cout << "\t| ";       
    if (cell->type == VAL && cell->tag == REF) {
        cout << "REF: " << ptrToHeapCell (cell->ref);
    }
    else if (cell->type == VAL && cell->tag == STR) {
        cout << "STR: " << ptrToHeapCell (cell->ref);
    }       
    else if (cell->type == FUN) {
        cout << m_FunctorTable->getName (cell->functorId) << "/";
        cout << cell->arity << "\t"; 
    }
    else {
        cout << "What type is this?";
    }   
    cout << "|" << endl; 
}

void WAMdebug::printHeap () {
    int i;
    DataCell* basCell = m_heap->at (0);

 	cout << "HEAP:" << endl;   
    for (i = 0; i < m_heap->getUsed(); i++) {
        cout << i;       
        printCell (&basCell[i]);
     }

	cout << endl;
}

void WAMdebug::printArgRegisters () {
    int i;
 	cout << "ARGUMENT REGISTERS:" << endl;

    for (i = 1; i < ARG_REG_COUNT; i++) {
        cout << i << "\t| ";       
        printCell (&m_argRegisters[i]);           
    }

	cout << endl;
}

void WAMdebug::printResultArg (int reg) {
    DataCell* cell = deref (&m_argRegisters[reg]);
    printCell (cell);
}

DataCell* WAMdebug::getBase () {
    return m_heap->at (0);
}


