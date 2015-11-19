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

    incrPreg ();
}

void WAM::deallocate () {

    incrPreg ();
}

DataCell* getEnvReg (int regId) {

    return nullptr;
}
