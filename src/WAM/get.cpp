//
//  get.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "WAM.h"

void WAM::get_variable (RegType t, int regId, int argRegId) {
    DataCell* reg = getRegister (t, regId);

    // Ai <- Vn
    *reg = *getGlobalReg (regId);
    
    m_P = m_P + 1; 
}

void WAM::get_value (RegType t, int regId, int argRegId) {
    bool unifySuccess; 
    DataCell* reg = getRegister (t, regId);

    unifySuccess = unify (reg, *getGlobalReg (argRegId));  
    if (unifySuccess) {
        m_P = m_P + 1;
    } else {
        backtrack ();
    }
}

void WAM::get_structure (int functorId, int argRegId) {
    bool getStructureSuccess = true;
    DataCell* reg = getGlobalReg (argRegId);
    DataCell* address = deref (reg);
      
    switch (address->tag) {
        case REF:
            // HEAP[H] <- (STR, H+1)
            m_H->tag = STR;
            m_H->ref = m_H + 1;
            // HEAP[H+1] <- f 
            m_H = m_H + 1;
            m_H->tag = FUN;
            m_H->functorId = functorId;

            bind (address, m_H - 1);
            m_H = m_H + 1;
            m_Mode = WRITE;
            break;

        case STR:
            if (address->ref->functorId == functorId) {
                m_S = address + 1;  
                m_Mode = READ; 
            } else {
                getStructureSuccess = false;
            }
            break;
                
        default:
            getStructureSuccess = false; 
            break;
    };

    if (getStructureSuccess) {
        m_P = m_P + 1;
    } else {
        backtrack ();
    }
}

void WAM::get_list (int argRegId) {
    bool getListSuccess = true;
    DataCell* reg = getGlobalReg (argRegId);
    DataCell* address = deref (reg);
      
    switch (address->tag) {
        case REF:
            // HEAP[H] <- (LIS, H+1)
            m_H->tag = LIS;
            m_H->ref = m_H + 1;

            bind (address, m_H);
            m_H = m_H + 1;
            m_Mode = WRITE;
            break;

        case LIS:
            m_S = address;
            m_Mode = READ;
            break;

        default:
            getListSuccess = false; 
            break;
    };

    if (getListSuccess) {
        m_P = m_P + 1;
    } else {
        backtrack ();
    }

}

void WAM::get_constant (int functorId, int argRegId) {
    bool getConstantSuccess = true;
    DataCell* reg = getGlobalReg (argRegId);
    DataCell* address = deref (reg);

    switch (address->tag) {
        case REF:
            address->tag = CON;
            address->functorId = functorId;
            trail (address);
            break;
        case CON:
            getConstantSuccess = (address->functorId == functorId); 
            break;
        default:
            getConstantSuccess = false;
            break;
    } 

    if (getConstantSuccess) {
        m_P = m_P + 1;
    } else {
        backtrack ();
    }
}
