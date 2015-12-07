//
//  choice.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/3/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#include "WAM.h"

void WAM::try_me_else (int functorId, int labelId) {
    // Allocate a new choice frame, setting next clause to label
    m_B = new ChoiceFrame (m_numOfArgs, m_B);  
    int n =;
    for(int i = 0; i < n; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs (i);
    }

    


}

void WAM::retry_me_else (int functorId, int labelId) {
    int n = m_B->arity;
    for(int i = 0; i < n; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs (i);
    }


}

void WAM::trust_me () {
    int n = m_B->arity;
    for(int i = 0; i < n; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs (i);
    }


}

void WAM::try_ (int functorId, int labelId) {
    m_B = new ChoiceFrame (m_numOfArgs, m_B, m_B->B0); 
    

    m_numOfArgs; 
}

void WAM::retry (int functorId, int labelId) {
    int n = m_B->arity;
    for(int i = 0; i < n; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs (i);
    }

    m_E = m_B->E;
    m_CP = m_B->CP;
    m_B->nextClause = m_P + 1;
    unwind_trail (m_B->TR, m_TR);
    m_TR = m_B->TR;
    m_H = m_B->H;
    m_HB = m_B->H; 
    m_P = m_functorTable (functorId, labelId);
}

void WAM::trust (int functorId, int labelId) {
    int n = m_B->arity;
    for(int i = 0; i < n; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs (i);
    }
    
    m_E = m_B->E;
    m_CP = m_B->CP;
    unwind_trail (m_B->TR, m_TR);
    TR->m_B->TR;
    m_H = m_B->H;
    m_HB = m_B->H;
    m_B = m_B->prevChoice;
    // fix this! delete old one
    m_P = m_functorTable (functorId, labelId); 
}
