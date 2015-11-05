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
    m_next = 0;
}

Heap::~Heap () {
    free (m_array);
}

DataCell* Heap::allocate () {
    if (m_used == m_size) {
        return nullptr;
    }

    m_used++;
    return &m_array[m_next++];
}

DataCell* Heap::allocate (int size) {
    if (m_used + size == m_size) {
        return nullptr;
    }
    
    m_used += size;  
    int result = m_next;
    m_next += size;
    return &m_array[result];
}

void deallocate (DataCell* pointer) {

}

DataCell* Heap::at (int index) {
    return &m_array[index];
}



