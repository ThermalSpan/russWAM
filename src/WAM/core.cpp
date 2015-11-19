//
//  core.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 10/15/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License.
//

#include "WAM.h"

WAM::WAM (FunctorTable* functorTable, StrVec* stringTable,  WAMword* code, int size) {
    m_argRegisters = (DataCell*) malloc (ARG_REG_COUNT * sizeof (DataCell));
    m_heap = new Heap (512); 
    m_UnifStack = new AddrStack ();

    m_FunctorTable = functorTable;
    m_mode = READ;
    m_Sreg = nullptr;

    m_Code = code;
    m_Preg = m_Code;
    m_size = size;
    m_StringTable = stringTable;
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

void WAM::bind (DataCell* a, DataCell* b) {
    a[0] = b[0];
}

void WAM::setSreg (DataCell* cell) {
    m_Sreg = cell;
}

void WAM::setHindex (DataCell* cell) {
    m_Hindex = cell;

	int i = ptrToHeapCell (cell);
    if (i > m_maxHindex) {
        m_maxHindex = i;  
    }             
}
