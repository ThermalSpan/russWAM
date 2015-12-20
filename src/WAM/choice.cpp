//
//  choice.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/3/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#include "WAM.h"

void WAM::try_me_else (int labelId) {
    // Allocate a new choice frame
    m_B = new ChoiceFrame (m_arity, m_B); 

    // Save the global registers
    for(int i = 0; i < m_arity; i++) {
        m_B->GlobalRegs[i] = *getGlobalReg (i);
    }
    
    // Get the next clause label
    m_B->L = m_functorTable->getLabel (m_functorId, labelId);

    // Save the current state
    m_B->E = m_E;
    m_B->CP = m_CP;
    m_B->TR = m_TR; 
    m_B->H = m_H;
    m_B->B0 = m_B0;
    m_B->functorId = m_functorId;
    m_B->arity = m_arity;
   
    // Set the new backtracking point
    m_HB = m_H;    
    m_P = m_P + 1;
}

void WAM::retry_me_else (int labelId) {
    // Undo any bindings of unbound cells
    unwind_trail (m_B->TR, m_TR);

    // Restore state
    m_E = m_B->E;
    m_CP = m_B->CP;
    m_TR = m_B->TR;
    m_H = m_B->H;
    m_functorId = m_B->functorId;
    m_arity = m_B->arity;

    // Restore the global registers
    for(int i = 0; i < m_arity; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs[i];
    }

    // Get label for next clause
    m_B->L = m_functorTable->getLabel (m_functorId, labelId);

    m_HB = m_H;
    m_P = m_P + 1;
}

void WAM::trust_me () {
   // Undo any bindings of unbound cells
    unwind_trail (m_B->TR, m_TR);

    // Restore state
    m_E = m_B->E;
    m_CP = m_B->CP;
    m_TR = m_B->TR;
    m_H = m_B->H;
    m_functorId = m_B->functorId;
    m_arity = m_B->arity;

    // Restore the global registers
    for(int i = 0; i < m_arity; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs[i];
    }

    // Reset Choice point to previous one
    ChoiceFrame* temp = m_B;
    m_B = m_B->prevChoice;
    delete (temp);

    m_HB = m_H;
    m_P = m_P + 1;
}

void WAM::try_ (int labelId) {
    // Allocate a new choice frame
    m_B = new ChoiceFrame (m_arity, m_B); 

    // Save the global registers
    for(int i = 0; i < m_arity; i++) {
        m_B->GlobalRegs[i] = *getGlobalReg (i);
    }
    
    // Save next instruction as the next clause
    m_B->L = m_P + 1;

    // Save the current state
    m_B->E = m_E;
    m_B->CP = m_CP;
    m_B->TR = m_TR; 
    m_B->H = m_H;
    m_B->B0 = m_B0;
    m_B->functorId = m_functorId;
    m_B->arity = m_arity;
   
    // Set the new backtracking point
    m_HB = m_H;    
    // The next instruction is the label passed in
    m_P = m_functorTable->getLabel (m_functorId, labelId);
}

void WAM::retry (int labelId) {
    // Undo any bindings of unbound cells
    unwind_trail (m_B->TR, m_TR);

    // Restore state
    m_E = m_B->E;
    m_CP = m_B->CP;
    m_TR = m_B->TR;
    m_H = m_B->H;
    m_functorId = m_B->functorId;
    m_arity = m_B->arity;
    
    // Restore the global registers
    for(int i = 0; i < m_arity; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs[i];
    }

    // Set next instruction as next clause
    m_B->L = m_P + 1;

    m_HB = m_H;
    // The next instruction is the label passed in 
    m_P = m_functorTable->getLabel (m_functorId, labelId);
}

void WAM::trust (int labelId) {
    // Undo any bindings of unbound cells
    unwind_trail (m_B->TR, m_TR);

    // Restore state
    m_E = m_B->E;
    m_CP = m_B->CP;
    m_TR = m_B->TR;
    m_H = m_B->H;
    m_functorId = m_B->functorId;
    m_arity = m_B->arity;
    
    // Restore the global registers
    for(int i = 0; i < m_arity; i++) {
        *getGlobalReg(i) = m_B->GlobalRegs[i];
    }

    // Reset Choice point to previous one
    ChoiceFrame* temp = m_B;
    m_B = m_B->prevChoice;
    delete (temp);

    m_HB = m_H;
    // Continue with label passed in 
    m_P = m_functorTable->getLabel (m_functorId, labelId);
}
