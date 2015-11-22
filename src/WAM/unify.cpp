//
//  put.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/22/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "WAM.h"
#include <assert.h>

void WAM::unify_variable (RegType t, int regId) {
    DataCell* reg = getRegister (t, regId);
    
    switch (m_Mode) {
        case READ:
            // Vn <- HEAP[S]
            *reg = *m_S;
            break;
        case WRITE:
            // HEAP[H] <- (REF, H)
            m_H->tag = REF;
            m_H->ref = m_H;
            m_H = m_H + 1;
            break;
    }

    m_S = m_S + 1;
    m_P = m_P + 1;
}

void WAM::unify_value (RegType t, int regId) {
    bool unifySuccess = true;
    DataCell* reg = getRegister (t, regId);

    switch (m_Mode) {
        case READ:
            unifySuccess = unify (reg, m_S);
            break;
        case WRITE:
            // HEAP[H] <- Vn
            *m_H = *reg;
            m_H = m_H + 1;
            break;
    }

    if (unifySuccess) {
        m_P = m_P + 1;
    } else {
        backtrack ();
    } 
}

void WAM::unify_local_value (RegType t, int regId) {
    bool unifySuccess = true;
    DataCell* reg = getRegister (t, regId);
    
    switch (m_Mode) {
        case READ: 
            unifySuccess = unify (reg, m_S);
            break;

        case WRITE:
            DataCell* address = deref (reg);
            // If addr is unbound Heap, then push copy onto HEAP
            if (unboundHeap (reg)) {
                // HEAP[H] <- HEAP[address]
                *m_H = *address;
            }
            // Else, if unbound stack, but unbound on HEAP and bind to address
            else {
                assert (unboundStack (address));
                m_H->tag = REF;
                m_H->ref = m_H;
                bind (address, m_H);
            }
            m_H = m_H + 1;
            break;
    }

    m_S = m_S + 1;
    if (unifySuccess) {
        m_P = m_P + 1;
    } else {
        backtrack ();
    }
}

void WAM::unify_constant (int functorId) {
    bool unifySuccess = true;
    switch (m_Mode) {
        case READ: {
            DataCell* address = deref (m_S);
            switch (address->tag) {
                case REF:
                    // STORE[addr] <- (CON, c)
                    address->tag = CON;
                    address->functorId = functorId;
                    trail (address);
                    break;

                case CON:
                    unifySuccess = (address->functorId == functorId);
                    break;

                default:
                    unifySuccess = false;
                    break;
            }
        } break;

        case WRITE:
            // HEAP[H] <- (CON, c)
            m_H->tag = CON;
            m_H->functorId = functorId;
            m_H = m_H + 1;
            break;
    }

    if (unifySuccess) {
        m_P = m_P + 1;
        backtrack ();
    }
}

void WAM::unify_void (int n) {
    switch (m_Mode) {
        case READ:
            m_S = m_S + n;
            break;

        case WRITE:
            for (int i = 0; i < n; i++) {
                (m_H + i)->tag = REF;
                (m_H + i)->ref = (m_H + i);
            }
            m_H = m_H + n;
            break;
    }

    m_P = m_P + 1;
}

bool WAM::unify (DataCell* cell1, DataCell* cell2) {
    bool unifySuccess = true;
    m_PDL->push (cell1); 
    m_PDL->push (cell2);

    while (!m_PDL->empty () || !unifySuccess) {
        DataCell* d1 = deref (m_PDL->top ());
        m_PDL->pop ();
        DataCell* d2 = deref (m_PDL->top ());
        m_PDL->pop ();

        if (d1 != d2) {
            
        
        }
    }
    
    return unifySuccess;
}
