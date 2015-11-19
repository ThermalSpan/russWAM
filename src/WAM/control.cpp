//
//  control.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 11/19/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAM.h"

void WAM::call (int functorId) {
    m_Preg = m_FunctorTable->getLabel (functorId);
}


void WAM::proceed () {
    m_Preg = m_CPreg;
}

void WAM::allocate (int N) {
    m_EnvStack->push(new EnvFrame(m_Preg, N));
    incrPreg ();
}

void WAM::deallocate () {
    m_Preg = m_EnvStack->top ()->CP;
    delete (m_EnvStack->top ());
    m_EnvStack->pop ();
    incrPreg ();
}

DataCell* WAM::getEnvReg (int regId) {
    return &m_EnvStack->top()->registers[regId];
}
