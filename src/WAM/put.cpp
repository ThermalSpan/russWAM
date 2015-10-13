//
//  put.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAM.h"

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

   
