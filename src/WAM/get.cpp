//
//  get.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "WAM.h"

RtnCode WAM::get_structure (int functorId, int regId) {
    RtnCode result = SUCCESS;
    DataCell* cell = deref (&m_argRegisters[regId]);
    int arity = m_FunctorTable->getArity (functorId);

    if (cell->type == VAL) {
        // CASE: (REF, _)
        if (cell->tag == REF) {
            // HEAP[H] <- (STR, H+1)
            m_Hindex[0].type = VAL;
            m_Hindex[0].tag = STR;
            m_Hindex[0].ref = &m_Hindex[1];

            // HEAP[H+1] <- f/n
            m_Hindex[1].type = FUN;
            m_Hindex[1].functorId = functorId;
            m_Hindex[1].arity = arity;

            bind (cell, m_Hindex);

            // H <- H + 2;
            setHindex(&m_Hindex[2]);

            m_mode = WRITE;
        }
        
        // CASE: (STR, a)
        else if (cell->tag == STR) {
            // IF HEAP[a] = f/n
            if (cell->ref->functorId == functorId && cell->ref->arity == arity) {
                // S <- a + 1
                setSreg (&cell->ref[1]);
                m_mode = READ;
            } 
            else {
                result = GET_STRUCT_FAIL;
            }
        }
    }
    else {
        result = GET_STRUCT_FAIL;
    }
    
    incrPreg ();    
    return result;
}

void WAM::get_variable (int regType, int regId, int argRegId) {

}

void WAM::get_value (int regType, int regId, int argRegId) {

}
