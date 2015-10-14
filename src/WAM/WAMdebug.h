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

class WAMdebug : public WAM {
public:
    WAMdebug ();

    ~WAMdebug ();

    void printHeap ();

    void printArgRegisters ();

    DataCell* getBase ();

protected:
    
    long ptrToHeapCell (DataCell* pointer);
};
