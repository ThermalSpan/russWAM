//
//	unify.cpp
//	russWAM
//
//	Created by Russell Wilhelm Bentley
//	Copyright (c) 2015 Russell Wilhelm Bentley
//	Distributed under the MIT License
//

#include "Engine.h"

void WAM::bind (DataCell* a, DataCell* b) {
    a[0] = b[0];
}

RtnCode WAM::get_structure (int functorId, int arity, int regId) {
    RtnCode result = SUCCESS;
    DataCell* cell = deref (&m_argRegisters[regId]);
    
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
            m_Hindex = &m_Hindex[2];

            m_mode = WRITE;
        }
        
        // CASE: (STR, a)
        if (cell->tag == STR) {
            // IF HEAP[a] = f/n
            if (cell->ref->functorId == functorId && cell->ref->arity == arity) {
                m_Sreg = &cell->ref[1];
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
    
    return result;
}

void WAM::unify_variable (int regId) {
    switch (m_mode) {
        case READ:
            // Xi <- HEAP[S]
            m_argRegisters[regId] = *m_Sreg;
            break;
        case WRITE:
            // HEAP[H] <- (REF, H)
            m_Hindex[0].type = VAL;
            m_Hindex[0].tag = REF;
            m_Hindex[0].ref = m_Hindex;

            // Xi <- HEAP[H]
            m_argRegisters[regId] = m_Hindex[0];

            // H <- H + 2
            m_Hindex = &m_Hindex[1];
            break;
    }

    // S <- S + 1
    m_Sreg = &m_Sreg[1];
}

void WAM::unify_value (int regId) {
    switch (m_mode) {
        case READ:
            // UNIFY (Xi, S)
            unify (&m_argRegisters[regId], m_Sreg);
            break;
        case WRITE:
            // HEAP[H] <- Xi
            m_Hindex[0] = m_argRegisters[regId];

            // H <- H + 1
            m_Hindex = &m_Hindex[1];
            break; 
    }

    // S <- S + 1
    m_Sreg = &m_Sreg[1];
}

RtnCode WAM::unify(DataCell* a1, DataCell* a2) {
    RtnCode result = SUCCESS;

    // PUSH (a1, PDL); PUSH (a2, PDL)
    m_UnifStack->push (a1);
    m_UnifStack->push (a2);
    
    while (!m_UnifStack->isEmpty()) {
        DataCell* d1 = deref (m_UnifStack->peek ());
        m_UnifStack->pop ();
        DataCell* d2 = deref (m_UnifStack->peek ());
        m_UnifStack->pop ();

        if (d1 != d2) {
            bool b1 = d1->type == VAL && d1->tag == REF;
            bool b2 = d2->type == VAL && d2->tag == REF;
            
            // IF (t1 = REF) || (t2 = REF)
            if (b1 || b2) {
                bind (d1, d2);
            } 
            else {
                bool f = d1->ref->functorId == d2->ref->functorId;
                bool n = d1->ref->arity == d2->ref->arity;
                
                if (f && n) {
                    for (int i = 1; i <= d1->ref->arity; i++) {
                        m_UnifStack->push (&d1->ref[i]);
                        m_UnifStack->push (&d2->ref[i]);
                    }
                }
                else {
                    result = UNIFY_FAIL;
                }
            }
        }
    }
    return result;
}










