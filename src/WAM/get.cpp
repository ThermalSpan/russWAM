//
//  get.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "WAM.h"

void get_variable (RegType t, int regId, int argRegId) {
    DataCell* reg;
    switch(t) {
        case GLOBAL:
            reg = getGlobalReg (regId);
            break;
        case LOCAL:
            reg = getLocalReg (regId);
            break;
    }

    // Ai <- Vn
    *reg = *getGlobalReg (regId);
    
    m_P = m_P + 1; 
}

void get_value (RegType t, int regId, int argRegId) {
    bool unifySuccess; 
    DataCell* reg;
    switch(t) {
        case GLOBAL:
            reg = getGlobalReg (regId);
            break;
        case LOCAL:
            reg = getLocalReg (regId);
            break;
    }

    unifySuccess = unify (reg, *getGlobalReg (argRegId));  
    if (unifySuccess) {

    } 
}


