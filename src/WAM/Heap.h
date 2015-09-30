//
//  Heap.h
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/27/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#pragma once

#include "../stdafx.h"
#include "types.h"

class Heap {
public:
    Heap (int size);

    ~Heap ();

    int allocate ();

    int allocate (int size);
    
    void deallocate (int index);

    DataCell* at (int index);

	int getUsed () { return m_used; }

	int getSize () { return m_size; }

protected:
    int m_size;

    int m_used;

    int m_next;

    DataCell* m_array;
};
