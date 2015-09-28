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
  heap = new Heap (512); 
}

WAM::~WAM () {
  free (m_argRegisters);
  delete (heap);
}

void WAM::put_structure (int functorId, int arity, int regId) {
    DataCell* curCell;
    int baseIndex;

    baseIndex = m_heap->allocate (arity + 2)
    
    // HEAP[H] <- (STR, H+1)
    curCell = m_heap->at(baseIndex);
    curCell->type = VAL;
    curCell->tag = STR;
    curCell->ref = baseIndex + 1;

    // HEAP[H+1] <- (REF, H)
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
    *curCell = m_argRegisters (regId);    

    // H <- H+1
    m_Hindex++;
}

int deref (DataCell *cell) {
    DataCell result = cell;
    Char cVAR
    if (cell->type == VAL && cell->tag == REF && cell->ref != cell) {
        result = deref (cell->ref);
    }

    return result;
}

void print () {
    int i;
    
    for (i = 0; i < m_used; i++) {
        cout << i << "\t| ";
        
        if (m_array[i]->type == VAL && m_array[i]->tag == REF) {
            cout << "REF: " << m_array[i]->ref;
        }
        else if (m_array[i]->type == VAL && m_array[i]->tag == STR) {
            cout << "STR: " << m_array[i]->ref;
        }       
        else if (m_array[i]->type == FUN) {
            cout << m_functortable[m_array[i]->functorId] << "/";
            cout << m_array[i]->arity; 
        
        }
        else {
        cout << "What type is this?" << endl;
        }
        
        cout << "\t|" << endl; 
    }
}
