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

    m_functortable = StrVec (10);
}

WAM::~WAM () {
    free (m_argRegisters);
    delete (m_heap);
}

void WAM::put_structure (int functorId, int arity, int regId) {
    DataCell* curCell;
    int baseIndex;

    baseIndex = m_heap->allocate (arity + 2);
    cout << "Allocated: " << baseIndex << endl;

    
    // HEAP[H] <- (STR, H+1)
    curCell = m_heap->at(baseIndex);
    curCell->type = VAL;
    curCell->tag = STR;
    curCell->ref = baseIndex + 1;

    // HEAP[H+1] <- (f / n)
    curCell = m_heap->at(baseIndex + 1);
    curCell->type = FUN;
    curCell->functorId = functorId;
    curCell->arity = arity;

    // Xi <- HEAP[H]
    m_argRegisters[regId] = *m_heap->at (baseIndex);

    // H <- H+2
    m_Hindex = baseIndex;   
}

void WAM::set_variable (int regId) {
    DataCell* curCell;
    
    // HEAP[H] <- (REF, H)
    curCell = m_heap->at (m_Hindex);
    curCell->type = VAL;
    curCell->tag = STR;
    curCell->ref = m_Hindex;

    // Xi <- HEAP[H]
    m_argRegisters[regId] = *m_heap->at (m_Hindex);

    // H <- H+1
    m_Hindex++;    
}

void WAM::set_value (int regId) {
    DataCell* curCell;

    // HEAP[H] <- Xi
    curCell = m_heap->at (m_Hindex);
    curCell = &m_argRegisters[regId];    

    // H <- H+1
    m_Hindex++;
}

int WAM::deref (int index) {
    int result = index;
    DataCell* cell = m_heap->at (index);
    
    if (cell->type == VAL && cell->tag == REF && cell->ref != index) {
        result = deref (cell->ref);
    }

    return result;
}

void WAM::addString (int i, string s) {
    m_functortable.at (i).assign (s);
}

void WAM::printHeap () {
    int i;
    
    for (i = 0; i < m_heap->getUsed(); i++) {
        cout << i << "\t| ";
        
        if (m_heap->at (i)->type == VAL && m_heap->at (i)->tag == REF) {
            cout << "REF: " << m_heap->at (i)->ref;
        }
        else if (m_heap->at (i)->type == VAL && m_heap->at (i)->tag == STR) {
            cout << "STR: " << m_heap->at (i)->ref;
        }       
        else if (m_heap->at (i)->type == FUN) {
            cout << m_functortable.at (m_heap->at (i)->functorId) << "/";
            cout << m_heap->at (i)->arity << "\t"; 
        
        }
        else {
        cout << "What type is this?" << endl;
        }
        
        cout << "|" << endl; 
    }
}
