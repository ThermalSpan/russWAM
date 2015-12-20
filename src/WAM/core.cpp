//
//  core.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bently on 12/12/15
//  Copyright (c) 2015 Russell Wilhelm Bentley
//  Distributed under the MIT License
//

#include "WAM.h"
#include <iostream>

using namespace std;

WAM::WAM (FunctorTable* functorTable) {
    m_functorTable = functorTable;
    m_Heap = (DataCell*) malloc (sizeof (DataCell) * HEAPSIZE);
    m_GlobalArgRegisters = (DataCell*) malloc (sizeof (DataCell) * ARGREGCOUNT);
    m_Trail = (DataCell**) malloc (sizeof (DataCell*) * TRAILSIZE);
    m_PDL = new addressStack ();

    // Setup initial state registers
    m_H = m_Heap;
    m_HB = m_H;
    m_S = nullptr;
    m_B0 = nullptr;
    m_TR = m_Trail;
    m_E = nullptr;
    m_B = nullptr;
}

WAM::~WAM () {
    free (m_Heap);
    free (m_GlobalArgRegisters);
    free (m_Trail);
    delete (m_PDL);
}

DataCell* WAM::getLocalReg (int regId) {
    return &(m_E->LocalRegs.at (regId));
}

DataCell* WAM::getGlobalReg (int regId) {
    if (regId < 0 || regId >= ARGREGCOUNT) {
        panic ("ERROR: tried to get arg reg " + to_string (regId));
    }
    return &(m_GlobalArgRegisters[regId]);
}

DataCell* WAM::getRegister (RegType type, int regId) {
    switch (type) {
        case GLOBAL:
            return getGlobalReg (regId);
            break;
        case LOCAL:
            return getLocalReg (regId);
            break;
    }
}

bool WAM::isStackCell (DataCell* cell) {
    return !(isHeapCell (cell) || isGlobalCell (cell));
}

bool WAM::isHeapCell (DataCell* cell) {
    if (cell >= m_Heap && cell < m_Heap + HEAPSIZE) {
        return true; 
    } else {
        return false;
    }
}

bool WAM::isGlobalCell (DataCell* cell) {
    if (cell >= m_GlobalArgRegisters && cell < m_GlobalArgRegisters + ARGREGCOUNT) {
        return true;
    } else {
        return false;
    }
}

bool WAM::unboundHeap (DataCell* cell) {
    bool result;
    result = isHeapCell (cell);
    result = result && cell->tag == REF && cell->ref ==cell;
    return result;
}

bool WAM::unboundStack (DataCell* cell) {
     bool result;
    result = isStackCell (cell);
    result = result && cell->tag == REF && cell->ref ==cell;
    return result;

}

void WAM::backtrack () {
    if (m_B == nullptr) {
        m_P = new WAMword ();
        m_P->op = OC_FAIL;
    } else {
        m_B0 = m_B->B0;
        m_P = m_CP;
    }
}

DataCell* WAM::deref (DataCell* address) {
    // If cell is a bound reference, deference that. Else we're done.
    if (address->tag == REF && address->ref != address) {
        return deref (address->ref);
    } else {
        return address;
    }
}

// TODO: this is ugly. And I dunno about that cell2 < cell1 stuff. 
void WAM::bind (DataCell* cell1, DataCell* cell2) {
    bool test = cell1->tag == REF;
    test = test && cell2->tag != REF && cell2 < cell1;
    if (test) {
        *cell1 = *cell2;
        trail (cell1);
    } else {
        *cell2 = *cell1;
        trail (cell2);
    }
}

//
// Store an address that has been bound, but may become unbound during backtrackin
//
void WAM::trail (DataCell* address) {
    if ((isHeapCell (address) && address > m_HB) || isStackCell (address)) {
        *m_TR = address;
        m_TR = m_TR + 1;
    }
}

void WAM::unwind_trail (DataCell** oldTr, DataCell** curTr) {
   for (DataCell** cell = oldTr; cell < curTr; cell = cell + 1) {
        (*cell)->tag = REF;
        (*cell)->ref = (*cell);
   } 
}
