//
//	unify.cpp
//	russWAM
//
//	Created by Russell Wilhelm Bentley
//	Copyright (c) 2015 Russell Wilhelm Bentley
//	Distributed under the MIT License
//

#include "WAM.h"
#include "WAMdebug.h"

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
    setSreg (&m_Sreg[1]);
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
    setSreg (&m_Sreg[1]);
}

RtnCode WAM::unify(DataCell* a1, DataCell* a2) {
    RtnCode result = SUCCESS;

    // PUSH (a1, PDL); PUSH (a2, PDL)
    m_UnifStack->push (a1);
    m_UnifStack->push (a2);
    
    while (!m_UnifStack->empty ()) {
        DataCell* d1 = deref (m_UnifStack->top ());
        m_UnifStack->pop ();
        DataCell* d2 = deref (m_UnifStack->top ());
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










