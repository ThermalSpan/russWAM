//
//  put.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAM.h"

void WAM::put_structure (int functorId, int regId) {
    DataCell* curCell;
    DataCell* baseCell;
    int arity = m_FunctorTable->getArity (functorId);

    baseCell = m_heap->allocate (arity + 2);

    // HEAP[H] <- (STR, H+1)
    curCell = baseCell;
    curCell->type = VAL;
    curCell->tag = STR;
    curCell->ref = &baseCell[1];

    //HEAP[H+1] <- (f / n)
    curCell = &baseCell[1];
    curCell->type = FUN;
    curCell->functorId = functorId;
    curCell->arity = arity;

    // Xi <- HEAP[H]
    m_argRegisters[regId] = baseCell[0];

    // H <- H+2
    setHindex (&baseCell[2]);
}

   
