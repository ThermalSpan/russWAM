//
//  Engine.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/12/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "Engine.h"

WAM::WAM () {
    m_argRegisters = (DataCell*) malloc (ARG_REG_COUNT * sizeof (DataCell));
    m_heap = new Heap (512); 
    m_UnifStack = new Stack (512);

    m_functortable = StrVec (10);
    m_mode = READ;
    m_Sreg = nullptr;
}

WAM::~WAM () {
    free (m_argRegisters);
    delete (m_heap);
    delete (m_UnifStack);
}

void WAM::put_structure (int functorId, int arity, int regId) {
    DataCell* curCell;
    DataCell* basCell;

    basCell = m_heap->allocate (arity + 2);
    
    // HEAP[H] <- (STR, H+1)
    curCell = basCell;
    curCell->type = VAL;
    curCell->tag = STR;
    curCell->ref = &basCell[1];

    //HEAP[H+1] <- (f / n)
    curCell = &basCell[1];
    curCell->type = FUN;
    curCell->functorId = functorId;
    curCell->arity = arity;

    // Xi <- HEAP[H]
    m_argRegisters[regId] = basCell[0];

    // H <- H+2
    m_Hindex = &basCell[2];   
}

void WAM::set_variable (int regId) {
    DataCell* curCell;
   	
    // HEAP[H] <- (REF, H)
    curCell = m_Hindex;
    curCell->type = VAL;
    curCell->tag = REF;
    curCell->ref = m_Hindex;

    // Xi <- HEAP[H]
    m_argRegisters[regId] = m_Hindex[0]; 
    // H <- H+1
    m_Hindex = &m_Hindex[1];    
}

void WAM::set_value (int regId) {
    // HEAP[H] <- Xi
    m_Hindex[0] = m_argRegisters[regId];    

    // H <- H+1
    m_Hindex = &m_Hindex[1];
}

DataCell* WAM::deref (DataCell* cell) {
    DataCell* result = cell;
    
    if (cell->type == VAL && cell->tag == REF && cell->ref != cell) {
        result = deref (cell->ref);
    }

    return result;
}

void WAM::addString (int i, string s) {
    m_functortable.at (i).assign (s);
}

void WAM::printHeap () {
    int i;
    DataCell* basCell = m_heap->at (0);

 	cout << "HEAP:" << endl;   
    for (i = 0; i < m_heap->getUsed(); i++) {
        cout << i << "\t| ";       
        if (basCell[i].type == VAL && m_heap->at (i)->tag == REF) {
            cout << "REF: " << basCell[i].ref;
        }
        else if (basCell[i].type == VAL && m_heap->at (i)->tag == STR) {
            cout << "STR: " << basCell[i].ref;
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

void WAM::printArgRegisters () {
    int i;
 	cout << "ARGUMENT REGISTERS:" << endl;

    for (i = 1; i < ARG_REG_COUNT; i++) {
        cout << i << "\t| ";       
        if (m_argRegisters[i].type == VAL && m_argRegisters[i].tag == REF) {
            cout << "REF: " << m_argRegisters[i].ref;
        }
        else if (m_argRegisters[i].type == VAL && m_argRegisters[i].tag == STR) {
            cout << "STR: " << m_argRegisters[i].ref;
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

DataCell* WAM::getBase () {
    return m_heap->at (0);
}

string WAM::getFunctor (int functorId) {
    return m_functortable.at (functorId);
}   
