//
//  put.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "WAM.h"

void WAM::put_variable (RegType t, int regId, int argRegId) {
    switch (t) {
        case GLOBAL:
            DataCell* globalRegX = getGlobalReg (regId);
            DataCell* globalRegA = getGlobalReg (argRegId);
            
            // HEAP[H] <- (REF, H);
            m_H->tag = REF;
            m_H->ref = m_H;
            // Xn <- HEAP[H]
            // Ai <- HEAP[H]
            *globalRegX = *m_H;
            *globalRegA = *m_H;
            
            m_H = m_H + 1;
            break;
        case LOCAL:
            DataCell* localReg = getLocalReg (regId); 
            DataCell* globalReg = getGlobalReg (argRegId);
            
            // STACK[addr] <- (REF, addr)
            localReg->tag = REF;
            localReg->ref = reg;
            //Ai <- STACK[addr]
            *globalReg = *localReg; 
            break;
    }

    m_P = m_P + 1;
}

void WAM::put_value (RegType t, int regId, int argRegId) {
    DataCell* valueReg;
     switch (t) {
        case GLOBAL:
            valueReg = getGlobalReg (regId);
            break;
        case LOCAL:
            valueReg = getLocalReg (regId);
            break;
    }
    // Ai <- Vn
    DataCell* globalReg = getGlobalReg (argRegId);
    *globalReg = *valueReg;
    
    m_P = m_P + 1;
}

void WAM::put_unsafe_value (int regId, int argRegId) {
    DataCell* localReg = getLocalReg (int regId);
    DataCell* address = deref (DataCell* localReg);
    
    // If deref (Yn) is unbound then make an unbound cell on the heap, save to Ai
    if (unbound (address)) {
        m_H->tag = REF;
        m_H->ref = m_H;
        bind (address, m_H);
        *getGlobalReg (argRegId) = *m_H; 
    } 
    // Else save the value at address to Ai 
    else {
        *getGlobalReg (regId) = *address;
    }

    m_P = m_P + 1;
}

void WAM::put_structure (int functorId, int argRegId) {
    // HEAP[H] <- f/n
    m_H->tag = FUN;
    m_H->functorId = functorId;
    // Ai <- (STR, H)
    DataCell* globalReg = getGlobalReg (argRegId);
    globalReg->type = STR;
    globalReg->ref = m_H;

    m_H = m_H + 1;
    m_P = m_P + 1;
}

void WAM::put_list (int argRegId) {
    // Ai <- (LIS, H)
    DataCell* globalReg = getGlobalReg (argRegId);
    globalReg->type = LIS;
    globalReg->ref = m_H;

    m_P = m_P + 1;
}

void WAM::put_constant (int functorId, int argRegId) {
    // Ai <- (CON, H)
    DataCell* globalReg = getGlobalReg (argRegId);
    globalReg->type = CON;
    globalReg->functorId = functorId;

    m_P = m_p + 1;
}








