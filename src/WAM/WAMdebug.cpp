//
//  WAMdebug.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAMdebug.h"

WAMdebug::WAMdebug () : WAM () {

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

void WAMdebug::printHeap () {
    int i;
    DataCell* basCell = m_heap->at (0);

 	cout << "HEAP:" << endl;   
    for (i = 0; i < m_heap->getUsed(); i++) {
        cout << i << "\t| ";       
        if (basCell[i].type == VAL && m_heap->at (i)->tag == REF) {
            cout << "REF: " << ptrToHeapCell (basCell[i].ref);
        }
        else if (basCell[i].type == VAL && m_heap->at (i)->tag == STR) {
            cout << "STR: " << ptrToHeapCell (basCell[i].ref);
        }       
        else if (basCell[i].type == FUN) {
            cout << m_functortable.at (basCell[i].functorId) << "/";
            cout << basCell[i].arity << "\t"; 
        }
        else {
        cout << "What type is this?";
        }   
        cout << "|" << endl; 
    }

	cout << endl;
}

void WAMdebug::printArgRegisters () {
    int i;
 	cout << "ARGUMENT REGISTERS:" << endl;

    for (i = 1; i < ARG_REG_COUNT; i++) {
        cout << i << "\t| ";       
        if (m_argRegisters[i].type == VAL && m_argRegisters[i].tag == REF) {
            cout << "REF: " << ptrToHeapCell (m_argRegisters[i].ref);
        }
        else if (m_argRegisters[i].type == VAL && m_argRegisters[i].tag == STR) {
            cout << "STR: " << ptrToHeapCell (m_argRegisters[i].ref);
        }       
        else if (m_argRegisters[i].type == FUN) {
            cout << m_functortable.at (m_argRegisters[i].functorId) << "/";
            cout << m_argRegisters[i].arity << "\t"; 
        }
        else {
        cout << "What type is this?";
        }
        cout << "|" << endl; 
    }

	cout << endl;
}

DataCell* WAMdebug::getBase () {
    return m_heap->at (0);
}


