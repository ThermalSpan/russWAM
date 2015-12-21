//
//  set.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "WAM.h"
#include <assert.h>

void WAM::set_variable (RegType t, int regId) {
    DataCell* reg = getRegister (t, regId);

    // HEAP[H] <- (REF, H)
    m_H->tag = REF;
    m_H->ref = m_H;
    // Vn <- HEAP[H]
    *reg = *m_H;

    m_H = m_H + 1;
    m_P = m_P + 1;
}

void WAM::set_value (RegType t, int regId) {
    DataCell* reg = getRegister (t, regId);

    // HEAP[H] <- Vn
    *m_H = *reg;

    m_H = m_H + 1;
    m_P = m_P + 1;
}

void WAM::set_local_value (RegType t, int regId) {
    DataCell* reg = getRegister (t, regId);
    DataCell* address = deref (reg);

    // If unbound heap var, push copy onto HEAP
    if (unboundHeap (address)) {
        // HEAP[H] <- HEAP[address]
        *m_H = *address;
    }
    // If unbound stack var push, push new unbound to HEAP, bind to address
    else {
        assert (unboundStack (address));
        // HEAP[H] <- HEAP[address]
        m_H->tag = REF;
        m_H->ref = m_H;
        bind (address, m_H);
    }

    m_H = m_H + 1;
    m_P = m_P + 1;
}

void WAM::set_constant (int functorId) {
    // HEAP[H] <- (CON, c)
    m_H->tag = CON;
    m_H->functorId = functorId;

    m_H = m_H + 1;
    m_P = m_P + 1;
}

void WAM::set_void (int n) {
    for (int i = 0; i < n; i++) {
        (m_H + i)->tag = REF;
        (m_H + i)->ref = (m_H + i);
    }

    m_H = m_H + n;
    m_P = m_P + 1;
}
