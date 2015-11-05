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
    if (pointer == nullptr) {
        return -2;
    } 
  
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
    if (cell == nullptr) {
        cout << "null";
    }
    else if (cell->type == VAL && cell->tag == REF) {  
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
    for (i = 0; i < m_maxHindex; i++) {
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
    recurPrint (cell);  
    cout << endl;
}

void WAMdebug::printHeapCell (int i) {
    recurPrint (m_heap->at(i));
    cout << endl;
}

void WAMdebug::recurPrint (DataCell* cell) {
    DataCell* fun = strDeref (deref (cell));
    
    if (fun == nullptr) {
        cout << "NULL FUN";
    }

    int a = m_FunctorTable->getArity (fun->functorId);
    string name = m_FunctorTable->getName (fun->functorId);

    cout << name;
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

DataCell* WAMdebug::getBase () {
    return m_heap->at (0);
}

void WAMdebug::setHindex (DataCell* cell) {
    WAM::setHindex (cell);

    int i = ptrToHeapCell (cell);
    if (i > m_maxHindex) {
        m_maxHindex = i;  
    }               
}

DataCell* WAMdebug::strDeref (DataCell* cell) {
    DataCell* result;

    if (cell->type == VAL && cell->tag == STR) {
        result = strDeref (cell->ref);
    }
    else if (cell->type == FUN) {
        result = cell;
    }
    else {
        result = nullptr;
    }

    return result;
}

void WAMdebug::unifyHeapCells (int a, int b) {
    DataCell* cell1 = m_heap->at (a);
    DataCell* cell2 = m_heap->at (b);
    unify (cell1, cell2);
}
