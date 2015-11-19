//
//  set.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAM.h"

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
    setHindex (&m_Hindex[1]);

    incrPreg ();
}

void WAM::set_value (int regId) {
    // HEAP[H] <- Xi
    m_Hindex[0] = m_argRegisters[regId];    

    // H <- H+1
    setHindex (&m_Hindex[1]);

    incrPreg ();
}


