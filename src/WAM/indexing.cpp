//
//  indexing.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 12/14/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include <unordered_map>
#include "WAM.h"

void WAM::switch_on_term (int V, int C, int L, int S) {
    DataCell* cell = deref (getGlobalReg (1));
    switch (cell->tag) {
    case REF:
        if (V == -1) {
            backtrack ();
        } else {
            m_P = m_functorTable->getLabel (m_functorId, V);
        }
        break;
    case CON:
        if (C == -1) {
            backtrack ();
        } else {
            m_P = m_functorTable->getLabel (m_functorId, C);
        }
        break;
    case LIS:
        if (L == -1) {
            backtrack ();
        } else {
            m_P = m_functorTable->getLabel (m_functorId, L);
        }
        break;
    case STR:
    case FUN: // TODO: Is this right?
        if (S == -1) {
            backtrack ();
        } else {
            m_P = m_functorTable->getLabel (m_functorId, S);
        }
        break;
    default:
        panic ("PANIC: switch_on_term not on term? tag: " + tag2str (cell->tag));
        break;
    }
}

// These are the same...
// TODO: fix this replication heresy OR find out if they should be different
void WAM::switch_on_constant () {
    DataCell* cell = deref (getGlobalReg (1));
    auto map = m_functorTable->getSwitchMap (m_functorId);

    // Find the dereferenced functor, then set the next instruction, else backtrack,
    auto labelIter = map->find (cell->functorId);
    if (labelIter == map->end ()) {
        backtrack ();
    } else {
        m_P = m_functorTable->getLabel (m_functorId, labelIter->first);
    }
}

void WAM::switch_on_structure () {
    DataCell* cell = deref (getGlobalReg (1));
    auto map = m_functorTable->getSwitchMap (m_functorId);

    // Find the dereferenced functor, then set the next instruction, else backtrack,
    auto labelIter = map->find (cell->functorId);
    if (labelIter == map->end ()) {
        backtrack ();
    } else {
        m_P = m_functorTable->getLabel (m_functorId, labelIter->first);
    }
}


