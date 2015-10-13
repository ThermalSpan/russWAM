//
//  core.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAM.h"

WAM::WAM () {
    m_argRegisters = (DataCell*) malloc (ARG_REG_COUNT * sizeof (DataCell));
    m_heap = new Heap (512); 
    m_UnifStack = new Stack (512);

    m_functortable = StrVec (10);
    m_mode = READ;
    m_Sreg = nullptr;
}

WAM::~WAM () {
    free (m_argRegisters);
    delete (m_heap);
    delete (m_UnifStack);
}

DataCell* WAM::deref (DataCell* cell) {
    DataCell* result = cell;

    if (cell->type == VAL && cell->tag == REF && cell->ref != cell) {
        result = deref (cell->ref);
    }

    return result;
}

void WAM::addString (int i, string s) {
    m_functortable.at (i).assign (s);
}

string WAM::getFunctor (int functorId) {
    return m_functortable.at (functorId);
}
