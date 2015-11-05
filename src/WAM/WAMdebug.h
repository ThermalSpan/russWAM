//
//  WAMdebug.h
//  russWAM
//  Created by Russell Wilhelm Bentley on 10/12/15
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distibuted under the MIT License.
//

#pragma once

#include "../stdafx.h"
#include "WAM.h"

#define DEBUG WAMdebug* w = (WAMdebug*) this;

class WAMdebug : public WAM {
public:
    WAMdebug (FunctorTable* functorTable);

    ~WAMdebug ();

    void printHeap ();

    void printArgRegisters ();

    void printResultArg (int reg);

    void printHeapCell (int i);

    DataCell* getBase ();

    void printCell (DataCell* cell);

    void setHindex (DataCell* cell);

protected:

    DataCell* strDeref (DataCell* cell);

    void recurPrint (DataCell* cell);
    
    long ptrToHeapCell (DataCell* pointer);

    int m_maxHindex;
};
