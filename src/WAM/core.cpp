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

DataCell* WAM::getLocalReg (int regId) {
    return nullptr;
}

DataCell* WAM::getGlobalReg (int regId) {
    return nullptr;
}

DataCell* WAM::getRegister (RegType t, int regId) {
    return nullptr;
}

bool WAM::isStackCell (DataCell* cell) {
    return false;
}

bool WAM::isHeapCell (DataCell* cell) {
    return false;
}

bool WAM::unboundHeap (DataCell* cell) {
    return false;
}

bool WAM::unboundStack (DataCell* cell) {
    return false;
}

void WAM::backtrack () {

}

DataCell* WAM::deref (DataCell* address) {
    if (address->tag == REF) {
        return deref (address->ref);
    } else {
        return address;
    }
}

void WAM::bind (DataCell* cell1, DataCell* cell2) {

}

void WAM::trail (DataCell* address) {

}

void WAM::unwind_trail (TrailFrame* oldTr, TrailFrame* curTr) {

}
