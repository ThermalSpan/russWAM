//
//  control.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/21/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//  

#include "WAM.h"
#include <assert.h>

void WAM::allocate (int N) {
    m_E = new EnvFrame (N, m_CP, m_E);
}

void WAM::deallocate () {
    assert(m_E != nullptr);
    EnvFrame* oldE = m_E;

    m_E = oldE->prev;
    m_CP = oldE->contPoint;

    
    delete (oldE);
    m_P = m_P + 1;
}

void WAM::call (int functorId) {
    WAMword* label = m_functorTable->getLabel (functorId);
    if (label != nullptr) {
        m_CP = m_P + 1;
        m_arity = m_functorTable->getArity (functorId);
        m_B->cutPointer = m_B;
        m_P = label;
    } else {
        backtrack ();
    }
}

void WAM::execute (int functorId) {
    WAMword* label = m_functorTable->getLabel (functorId);
    
    if (label != nullptr) {
        m_arity = m_functorTable->getArity (functorId);
        m_B->cutPointer = m_B;
        m_P = label;
    } else {
       backtrack ();
    } 
}

void WAM::proceed () {
    m_P = m_CP;
}
