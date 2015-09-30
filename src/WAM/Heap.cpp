//
//  Heap.cpp
//  russWAM
//
//  Created by Russell Wilhelm Bentley on 9/27/15.
//  Copyright (c) 2015 Russell Wilhelm Bentley.
//  Distributed under the MIT License
//

#include "Heap.h"

Heap::Heap (int size) {
    m_size = size;
    m_used = 0;
    m_array = (DataCell*) malloc (m_size * sizeof(DataCell));
}

Heap::~Heap () {
    free (m_array);
}

int Heap::allocate () {
    if (m_used == m_size) {
        return -1;
    }

    m_used++;
    int result = m_next++;
    return result;
}

int Heap::allocate (int size) {
    if (m_used + size == m_size) {
        return -1;
    }
    
    m_used += size;  
    int result = m_next;
    m_next += size;
    return result;
}

void deallocate (int index) {

}

DataCell* Heap::at (int index) {
    return &m_array[index];
}


